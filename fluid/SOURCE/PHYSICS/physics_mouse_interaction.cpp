/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#include "physics_mouse_interaction.h"

// -- LOCAL

// .. REFERENCEs

#include "physics_fluid_particle_array.h"

// .. CONSTANTS

#define LOCAL_Descaling_factor 128.0f

// -- PUBLIC

// .. OPERATIONS

// It applies the ineraction of mouse according to the 
// position of the attractor a circular force to the 
// game_entity with a maximum radius of max_dis_attractor.

VOID PHYSICS_MOUSE_INTERACTION::ApplyMouseBehaviour(
	PHYSICS_ENTITY & game_entity,
	const REAL32 max_dis_attractor
	)
{
	REAL32
		attractor_distance_from_particle_squared;

	attractor_distance_from_particle_squared = ( game_entity.GetPosition() - MouseAttractorVector).GetSquareLength();

	if( IsAttracting )
	{
		if( attractor_distance_from_particle_squared < max_dis_attractor * max_dis_attractor )
		{
			game_entity.SetForce( 
				game_entity.GetForce() 
				- ( game_entity.GetPosition()
				- MouseAttractorVector ) / LOCAL_Descaling_factor
				);
		}
	}

	if( IsRepelling )
	{
		if( attractor_distance_from_particle_squared < max_dis_attractor * max_dis_attractor )
		{
			game_entity.SetForce( 
				game_entity.GetForce() 
				+ ( game_entity.GetPosition() 
				- MouseAttractorVector ) / LOCAL_Descaling_factor
				);
		}
	}
}