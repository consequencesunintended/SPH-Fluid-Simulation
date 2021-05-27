/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
// -- LOCAL

// .. REFERENCES

#include <cstdlib>
#include "graphics_glut_header.h"
#include <iostream>
#include <sstream>
#include <string>
#include "physics_fluid_neighbour_particle.h"
#include "physics_fluid_particle.h"
#include "physics_level_fluid_constants.h"
#include "game_core_engine.h"
#include "graphics_marching_squares.h"
#include "graphics_color.h"
#include "fundamental_delta_time.h"
using namespace std;

// .. CONSTANTS

#define   LOCAL_width						600 
#define   LOCAL_height						600				           					
#define   LOCAL_number_of_pixels_width       50	
#define   LOCAL_number_of_pixels_height      50

// .. ATTRIBUTES

BOOL attracting = BOOLEAN_false;
BOOL repelling  = BOOLEAN_false;
BOOL Viscoelasticity = BOOLEAN_false;
BOOL Plasticity = BOOLEAN_true;
BOOL Viscosity = BOOLEAN_false;
BOOL PauseSimulation = BOOLEAN_false;
INT32 GraphicalMode = 3;
GAME_CORE_ENGINE GameCoreEngine;
GRAPHICS_MARCHING_SQUARES GraphicsMarchingSquares;
enum RenderModes{ LargeParticleMode = 1, SmallParticleMode = 2, MarchingSquareMode = 3 };

// ..OPERATIONS

void CalculateFrameRate(
	VOID
	)
{
    static REAL32 
		frame_per_second = 0.0f,
		lastTime = 0.0f;
    static ostringstream 
		convert,
        convert2;				
	string 
		strFrameRate;								
	REAL32 
		currentTime;

	currentTime = GetTickCount() * 0.001f;
    ++frame_per_second;
    if( currentTime - lastTime > 1.0f )
    {
		convert.str( " " );
	    lastTime = currentTime;
		convert << "Mouse Left/Right to Interact with Fluid - FPS:"  << frame_per_second;
		glutSetWindowTitle( convert.str().c_str() );
	    frame_per_second = 0;
    }
}

// ~~

VOID ShowInfo(
	VOID
	)
{
	GLUT_FUNCTIONS::glutPrint( -45.0f, 45.0f, GLUT_FUNCTIONS::GlutFonts[ 1 ], "PRESS P, M or E for Different Modes", 1.0f, 1.0f, 1.0f, 1.0f);
}

// ~~

void render(
	VOID
	)
{
	INDEX
		temp_index_1,
		temp_index_2,
		start_position,
		end_position;

	glClearColor( 
		GRAPHICS_COLOR::Black().GetRGBA()[0],
		GRAPHICS_COLOR::Black().GetRGBA()[1],
		GRAPHICS_COLOR::Black().GetRGBA()[2],
		1.0f
		);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if( GraphicalMode == LargeParticleMode )
	{
		glPointSize(
			PHSYICS_LEVEL_FLUID_Particle_Size
			*PHSYICS_LEVEL_FLUID_Particle_Size
			);
	}
	else if ( GraphicalMode == SmallParticleMode )
	{
		glPointSize( PHSYICS_LEVEL_FLUID_Particle_Size );
	}

	switch( GraphicalMode )
	{
		case 1:
		case 2:
		{
			temp_index_2 = 0;

			glBegin(GL_POINTS);
			FUNDAMENTAL_DATA_TYPES_loop_through_table(
				temp_index_2,
				GameCoreEngine.ParticleTable
				)
			{
				glColor4fv( GRAPHICS_COLOR::Red().GetRGBA() );
				glVertex2f( GameCoreEngine.ParticleTable[temp_index_2].GetPosition().X , GameCoreEngine.ParticleTable[temp_index_2].GetPosition().Y);
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

			FUNDAMENTAL_DATA_TYPES_loop_through_table( 
				temp_index_2, 
				GraphicsMarchingSquares.GetPolygonVertexCountTable()
				)
			{
					end_position 
						= start_position 
						+ GraphicsMarchingSquares.GetPolygonVertexCountTable()[ temp_index_2 ] - 1;
					glBegin(GL_POLYGON);

					FUNDAMENTAL_DATA_TYPES_loop_through_index( 
						temp_index_1, 
						start_position,
						end_position
						)
					{
						glVertex2f(GraphicsMarchingSquares.GetPointTable()[temp_index_1].X , 
							GraphicsMarchingSquares.GetPointTable()[temp_index_1].Y );
					}
					glEnd();
					start_position 
						+= GraphicsMarchingSquares.GetPolygonVertexCountTable()[ temp_index_2 ];
			}
			GraphicsMarchingSquares.Reset();
			break;
		}
	}
	ShowInfo();
	CalculateFrameRate();
	glutSwapBuffers();

}

// ~~

void idle(
	VOID
	)
{
	INT32
		index_1,
		index_2;
	INDEX
		particle_index;
	REAL32
		delta_time;

	delta_time = FUNDAMENTAL_DELTA_TIME::GetDeltaTime();

	if ( !PauseSimulation )
	{

		GameCoreEngine.Update( 
			delta_time, 
			Viscosity, 
			Viscoelasticity, 
			Plasticity 
			);
	}

	if ( GraphicalMode == MarchingSquareMode )
	{
		particle_index = 0;

		FUNDAMENTAL_DATA_TYPES_loop_through_table( 
			particle_index, 
			GameCoreEngine.ParticleTable
			)
		{
			if ( GameCoreEngine.ParticleTable[particle_index].GetPosition().X < 0.0f )
			{
				index_1 = INT32( GameCoreEngine.ParticleTable[particle_index].GetPosition().X ) 
					- 1 
					+ LOCAL_number_of_pixels_width;
			}
			else
			{
				index_1 = INT32( GameCoreEngine.ParticleTable[particle_index].GetPosition().X ) 
					+ LOCAL_number_of_pixels_width;
			}

			if ( GameCoreEngine.ParticleTable[particle_index].GetPosition().Y < 0.0f )
			{
				index_2 = INT32( GameCoreEngine.ParticleTable[particle_index].GetPosition().Y ) 
					- 1 
					- LOCAL_number_of_pixels_height;
				index_2 *= -1;
			}
			else
			{
				index_2 = INT32( GameCoreEngine.ParticleTable[particle_index].GetPosition().Y ) 
					- LOCAL_number_of_pixels_height;
				index_2 *= -1;
			}

			GraphicsMarchingSquares.CalculatePoints(
				GameCoreEngine.ParticleTable[ particle_index ].GetPosition(),
				INDEX( index_1 ),
				INDEX( index_2 ),
				4
				);
		}
		GraphicsMarchingSquares.GeneratePoints();
	}	
	render();
}

// ~~

VOID Keyboard( 
	UCHAR c, 
	INT32 x, 
	INT32 y
	)
{
    switch(c)
    {
        case VK_ESCAPE:
        case 'q':
        case 'Q':
	    {
           exit(0);
           break;
        }

		case 'E':
        case 'e':
	    {
			if ( !Plasticity )
			{
				GameCoreEngine.ResetViscoelasticity();
				Viscoelasticity = !Viscoelasticity;
			}
			break;
        }

		case 'P':
		case 'p':
		{
			if ( !Viscoelasticity )
			{
				Plasticity = !Plasticity;
				if ( Plasticity )
				{
					GameCoreEngine.InitialisePlasticity();
				}
			}
			break;
		}

		case 'm':
		case 'M':
		{
			GraphicalMode = ( GraphicalMode + 1 > 3 ) ? 1 : GraphicalMode + 1;  
		break;
		}

		case VK_SPACE:
		{
			PauseSimulation = !PauseSimulation;
			break;
		}
    }
}

// ~~

VOID motion(
	INT32 x, 
	INT32 y
	)
{
	REAL32 
		relx,
		rely;
	MATH_VECTOR_2D 
		mouse;

	relx = (REAL32)(x - LOCAL_width/2) / LOCAL_width;
	rely = -(REAL32)(y - LOCAL_height/2) / LOCAL_height;
	mouse = MATH_VECTOR_2D(
		 relx*LOCAL_number_of_pixels_width*2, 
		 rely*LOCAL_number_of_pixels_height*2);
	 {
		 GameCoreEngine.SetAttractor( mouse );
	 }
}

// ~~

VOID mouse(
	INT32 button, 
	INT32 state, 
	INT32 x, 
	INT32 y)
{
  if (button == GLUT_LEFT_BUTTON)
    {
    if(state == GLUT_DOWN) 
	{
		{
			GameCoreEngine.SetMouse( BOOLEAN_true, BOOLEAN_false );
		}
	}
    else
    {

		{
			GameCoreEngine.SetMouse( BOOLEAN_false , BOOLEAN_false );
			GameCoreEngine.SetAttractor(  
				MATH_VECTOR_2D(
					REAL32( LOCAL_number_of_pixels_width ) * 99.0f, 
					REAL32( LOCAL_number_of_pixels_height ) * 99.0f
					) 
				);
		}

    }
  }
  else if (button == GLUT_RIGHT_BUTTON)
  {
    if(state == GLUT_DOWN)
	{
		{
			GameCoreEngine.SetMouse( BOOLEAN_false, BOOLEAN_true );
		}
	}
    else
    {
		{
			GameCoreEngine.SetMouse( BOOLEAN_false , BOOLEAN_false );
			GameCoreEngine.SetAttractor(  
				MATH_VECTOR_2D(
					REAL32( LOCAL_number_of_pixels_width ) * 99.0f, 
					REAL32( LOCAL_number_of_pixels_height ) * 99.0f
					) 
				);
		}
    }
  }
}


// ~~

VOID init(
	VOID
	)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(
		-LOCAL_number_of_pixels_width,
		LOCAL_number_of_pixels_width,
		-LOCAL_number_of_pixels_height, 
		LOCAL_number_of_pixels_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glEnable(GL_POINT_SMOOTH);

	GameCoreEngine.Initialize(
		LOCAL_number_of_pixels_width,
		LOCAL_number_of_pixels_height);

	if ( Plasticity )
	{
		GameCoreEngine.InitialisePlasticity();
	}
	GraphicsMarchingSquares.Initialise(
		LOCAL_number_of_pixels_width,
		LOCAL_number_of_pixels_height
		);
}

// ~~

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(LOCAL_width, LOCAL_height);
	glutCreateWindow("SPH Fluid Simulation");

	glutDisplayFunc(render);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(idle);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);

	init();

	glutMainLoop();	
}





