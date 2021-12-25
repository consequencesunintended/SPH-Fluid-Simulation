#include "physics_collision_2d.h"

// -- LOCAL

// .. REFERENCES

#include "physics_entity.h"

// -- PUBLIC

// .. OPERATIONS

void PHYSICS_COLLISION_2D::CheckForWall(
			PHYSICS_ENTITY &entity,
			const float wall_spring_coefficient,
			const MATH_POINT_2D & position,
			const float min_x_value,
			const float max_x_value,
			const float min_y_value,
			const float max_y_value
			)
{
	if( entity.Position.X < min_x_value + position.X ) 
	{
		entity.Force = MATH_VECTOR_2D( 
				entity.Force.X - ( entity.Position.X - ( min_x_value + position.X ) ) * wall_spring_coefficient,
				entity.Force.Y );
	}

	if( entity.Position.X >  max_x_value + position.X ) 
	{
		entity.Force = MATH_VECTOR_2D(
				entity.Force.X - ( entity.Position.X - ( max_x_value + position.X ) ) * wall_spring_coefficient,
				entity.Force.Y );		
	}

	if( entity.Position.Y < min_y_value + position.Y ) 
	{
		entity.Force =MATH_VECTOR_2D(
				entity.Force.X,
				entity.Force.Y - ( entity.Position.Y - ( min_y_value + position.Y ) ) * wall_spring_coefficient );
	}

	if( entity.Position.Y > max_y_value + position.Y )
	{
		entity.Force = MATH_VECTOR_2D(
				entity.Force.X,
				entity.Force.Y - ( entity.Position.Y - ( max_y_value + position.Y ) ) * wall_spring_coefficient );
	}
}