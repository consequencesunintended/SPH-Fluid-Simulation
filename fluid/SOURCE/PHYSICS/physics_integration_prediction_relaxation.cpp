// This is an integration based on the paper published by
// "CLAVET, S., BEAUDOIN, P., AND POULIN, P. 2005. Particle-based 
// viscoelastic ﬂuid simulation. In SCA 2005, 219–228" A link to 
// view the paper  is avaiable here 
// http://www.iro.umontreal.ca/labs/infographie/papers/Clavet-2005-PVFS/pvfs.pdf

#include "physics_integration_prediction_relaxation.h"

// -- LOCAL

// .. REFERENCES

#include "math_vector_2D.h"
#include "physics_integration.h"
#include "physics_entity.h"

// -- PUBLIC

// .. OPERATIONS

void PHSYICS_INTEGRATION_PREDICTION_RELAXATION::UpdateVelocity( PHYSICS_ENTITY & game_entity, const float delta_time )
{
	MATH_VECTOR_2D new_position;
		
	new_position = game_entity.Position + game_entity.Force * delta_time;
	game_entity.Velocity = ( new_position - game_entity.OldPosition ) / delta_time;
}

// ~~

void PHSYICS_INTEGRATION_PREDICTION_RELAXATION::UpdatePosition( PHYSICS_ENTITY & game_entity, const float delta_time )
{
	game_entity.Position = game_entity.Position + game_entity.Force * delta_time;
	game_entity.OldPosition = game_entity.Position;
	game_entity.Position = game_entity.Position + game_entity.Velocity * delta_time;
}