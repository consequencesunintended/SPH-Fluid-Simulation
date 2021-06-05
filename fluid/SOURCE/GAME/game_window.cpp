// -- LOCAL

// .. REFERENCES

#include "glfw3.h"
#include "physics_fluid_neighbour_particle.h"
#include "physics_fluid_particle.h"
#include "physics_level_fluid_constants.h"
#include "game_core_engine.h"
#include "graphics_marching_squares.h"
#include "graphics_color.h"
#include "fundamental_delta_time.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;

// .. CONSTANTS

constexpr int	LOCAL_width = 600;
constexpr int   LOCAL_height = 600;				           					
constexpr int   LOCAL_number_of_pixels_width = 50;
constexpr int   LOCAL_number_of_pixels_height = 50;


// .. ATTRIBUTES

bool							attracting = false;
bool							repelling  = false;
bool							Viscoelasticity = false;
bool							Plasticity = true;
bool							Viscosity = false;
bool							PauseSimulation = false;
int								GraphicalMode = 3;
GAME_CORE_ENGINE				GameCoreEngine;
GRAPHICS_MARCHING_SQUARES		GraphicsMarchingSquares;
bool							displayed_info = false;

enum RenderModes{ LargeParticleMode = 1, SmallParticleMode = 2, MarchingSquareMode = 3 };

// ..OPERATIONS

void CalculateFrameRate( void )
{
    static float 
		frame_per_second = 0.0f,
		lastTime = 0.0f;
    static ostringstream 
		convert,
        convert2;				
	string 
		strFrameRate;								
	float 
		currentTime;

	//currentTime = GetTickCount() * 0.001f;
    ++frame_per_second;
    if( currentTime - lastTime > 1.0f )
    {
		convert.str( " " );
	    lastTime = currentTime;
		convert << "Mouse Left/Right to Interact with Fluid - FPS:"  << frame_per_second;
		//glutSetWindowTitle( convert.str().c_str() );
	    frame_per_second = 0;
    }
}

// ~~

void ShowInfo( void )
{
	if ( !displayed_info )
	{
		cout << "PRESS P, M or E for Different Modes" << endl;
		displayed_info = true;
	}
}

// ~~

void render( GLFWwindow* window )
{
	unsigned int temp_index_1;
	unsigned int temp_index_2;
	unsigned int start_position;
	unsigned int end_position;

	glClearColor( GRAPHICS_COLOR::Black().GetRGBA()[0], GRAPHICS_COLOR::Black().GetRGBA()[1], GRAPHICS_COLOR::Black().GetRGBA()[2], 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if ( GraphicalMode == LargeParticleMode )
	{
		glPointSize( PHSYICS_LEVEL_FLUID_Particle_Size * PHSYICS_LEVEL_FLUID_Particle_Size );
	}
	else if ( GraphicalMode == SmallParticleMode )
	{
		glPointSize( PHSYICS_LEVEL_FLUID_Particle_Size );
	}

	constexpr float ratio_w = ((float)LOCAL_width / ( LOCAL_width / LOCAL_number_of_pixels_width ) );
	constexpr float ratio_h = ((float)LOCAL_height / (LOCAL_height / LOCAL_number_of_pixels_height));

	temp_index_2 = 0;
	start_position = 0;
	end_position = 0;

	glColor4fv( GRAPHICS_COLOR::Green().GetRGBA() );

	std::vector<PHYSICS_FLUID_PARTICLE> c_particles = GameCoreEngine.ParticleTable;

	switch( GraphicalMode )
	{
		case LargeParticleMode:
		case SmallParticleMode:
		{
			temp_index_2 = 0;

			glBegin(GL_POINTS);
			for ( auto& p_tb : c_particles )
			{
				glColor4fv( GRAPHICS_COLOR::Red().GetRGBA() );
				glVertex2f( p_tb.GetPosition().X / ratio_w, p_tb.GetPosition().Y / ratio_h );
			}	
			glEnd();
			break;
		}

		case MarchingSquareMode:
		{
			temp_index_2 = 0;
			start_position = 0;
			end_position = 0;

			glColor4fv( GRAPHICS_COLOR::Green().GetRGBA() );

			for ( auto& p_tb : GraphicsMarchingSquares.GetPolygonVertexCountTable() )
			{
					end_position = start_position + p_tb - 1;
					glBegin(GL_POLYGON);

					for ( temp_index_1 = start_position; temp_index_1 <= end_position; temp_index_1++ )
					{
						glVertex2f( GraphicsMarchingSquares.GetPointTable()[temp_index_1].X / ratio_w, GraphicsMarchingSquares.GetPointTable()[temp_index_1].Y / ratio_h );
					}
					glEnd();
					start_position += p_tb;
			}
			GraphicsMarchingSquares.Reset();
			break;
		}
	}
	ShowInfo();
	glfwSwapBuffers( window );
}

// ~~


void idle( GLFWwindow* window )
{

	float			delta_time;
	bool			threaded = true;

	delta_time = FUNDAMENTAL_DELTA_TIME::GetDeltaTime();

	vector<std::thread> threads;

	if ( !PauseSimulation )
	{
		GameCoreEngine.Update( GameCoreEngine.ParticleTable, delta_time, Viscosity, Viscoelasticity, Plasticity );
	}

	unsigned int	particle_index = 0;
	int				index_1 = 0;
	int				index_2 = 0;

	for ( auto& p_tb : GameCoreEngine.ParticleTable )
	{
		if ( p_tb.GetPosition().X < 0.0f )
		{
			index_1 = int( p_tb.GetPosition().X ) - 1 + LOCAL_number_of_pixels_width;
		}
		else
		{
			index_1 = int( p_tb.GetPosition().X ) + LOCAL_number_of_pixels_width;
		}

		if ( p_tb.GetPosition().Y < 0.0f )
		{
			index_2 = int( p_tb.GetPosition().Y ) - 1 - LOCAL_number_of_pixels_height;
			index_2 *= -1;
		}
		else
		{
			index_2 = int( p_tb.GetPosition().Y ) - LOCAL_number_of_pixels_height;
			index_2 *= -1;
		}

		GraphicsMarchingSquares.CalculatePoints( p_tb.GetPosition(), unsigned int( index_1 ), unsigned int( index_2 ), 4 );
	}
	GraphicsMarchingSquares.GeneratePoints();
}

// ~~

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mode )
{
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose( window, true );
	}
	else if (glfwGetKey( window, GLFW_KEY_P ) == GLFW_PRESS )
	{
		if ( !Viscoelasticity )
		{
			Plasticity = !Plasticity;

			if ( Plasticity )
			{
				GameCoreEngine.InitialisePlasticity();
			}
		}
	}
	else if ( glfwGetKey( window, GLFW_KEY_E ) == GLFW_PRESS )
	{
		GameCoreEngine.ResetViscoelasticity();
		Viscoelasticity = !Viscoelasticity;
	}
	else if ( glfwGetKey( window, GLFW_KEY_M ) == GLFW_PRESS )
	{
		GraphicalMode = (GraphicalMode + 1 > 3) ? 1 : GraphicalMode + 1;
	}
	else if ( glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS )
	{
		PauseSimulation = !PauseSimulation;
	}
}
//
//// ~~
//
void motion( double x, double y )
{
	float relx;
	float rely;
	MATH_VECTOR_2D mouse;

	relx = (float)(x - LOCAL_width/2) / LOCAL_width;
	rely = -(float)(y - LOCAL_height/2) / LOCAL_height;
	mouse = MATH_VECTOR_2D( relx*LOCAL_number_of_pixels_width*2, rely*LOCAL_number_of_pixels_height*2 );
	GameCoreEngine.SetAttractor( mouse );
}

// ~~

void mouse_callback( GLFWwindow* window, double xpos, double ypos )
{

    if ( glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_LEFT ) == GLFW_TRUE )
    {
		GameCoreEngine.SetMouse( true, false );
    }
	else if ( glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_TRUE )
	{
		GameCoreEngine.SetMouse( false, true );
	}
	else
	{
		GameCoreEngine.SetMouse( false, false );
	}
	motion( xpos, ypos );
}


// ~~

void init(
	void
	)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-LOCAL_number_of_pixels_width,
		LOCAL_number_of_pixels_width,
		-LOCAL_number_of_pixels_height, 
		LOCAL_number_of_pixels_height, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glEnable(GL_POINT_SMOOTH);

	GameCoreEngine.Initialize( GameCoreEngine.ParticleTable, LOCAL_number_of_pixels_width, LOCAL_number_of_pixels_height);

	if ( Plasticity )
	{
		GameCoreEngine.InitialisePlasticity();
	}
	GraphicsMarchingSquares.Initialise( LOCAL_number_of_pixels_width, LOCAL_number_of_pixels_height );
}

// ~~

int main(int argc, char **argv)
{
	GLFWwindow* window;

	if ( !glfwInit() )
		return -1;

	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	window = glfwCreateWindow( LOCAL_width, LOCAL_height, "SPH Fluid Simulation", NULL, NULL );

	if ( !window )
	{
		glfwTerminate();
		return -1;
	}
	init();


	glfwMakeContextCurrent( window );
	glfwSetKeyCallback( window, key_callback );
	glfwSetCursorPosCallback( window, mouse_callback );

	while ( !glfwWindowShouldClose( window ) )
	{

		idle( window );

		render( window );

		glfwPollEvents();
	}

	glfwTerminate();
}





