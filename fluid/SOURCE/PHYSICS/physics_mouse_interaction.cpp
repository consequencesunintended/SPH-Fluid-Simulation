#include "physics_mouse_interaction.h"

// -- LOCAL

// .. REFERENCEs


// .. CONSTANTS

#define LOCAL_Descaling_factor 128.0f

// -- PUBLIC

// .. OPERATIONS

// It applies the ineraction of mouse according to the 
// position of the attractor a circular force to the 
// game_entity with a maximum radius of max_dis_attractor.

void PHYSICS_MOUSE_INTERACTION::ApplyMouseBehaviour(
	PHYSICS_ENTITY & game_entity,
	const float max_dis_attractor
	)
{
	float
		attractor_distance_from_particle_squared;

	attractor_distance_from_particle_squared = ( game_entity.Position - MouseAttractorVector ).GetSquareLength();

	if( IsAttracting )
	{
		if( attractor_distance_from_particle_squared < max_dis_attractor * max_dis_attractor )
		{
			game_entity.Force = game_entity.Force - ( game_entity.Position - MouseAttractorVector ) / LOCAL_Descaling_factor;
		}
	}

	if( IsRepelling )
	{
		if( attractor_distance_from_particle_squared < max_dis_attractor * max_dis_attractor )
		{
			game_entity.Force = game_entity.Force + ( game_entity.Position - MouseAttractorVector ) / LOCAL_Descaling_factor;
		}
	}
}