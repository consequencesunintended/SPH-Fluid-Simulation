#ifndef __PHYSICS_COLLISION_2D__
#define __PHYSICS_COLLISION_2D__

// -- LOCAL
	
// .. REFERENCES

#include "physics_entity.h"
#include "math_point_2d.h"
	
// -- GLOBAL

// .. TYPES

class PHYSICS_COLLISION_2D
{
	// -- PUBLIC

public:

	// .. OPERATIONS

	void CheckForWall(
		PHYSICS_ENTITY &entity,
		const float wall_spring_coefficient,
		const MATH_POINT_2D & position,
		const float min_x_value,
		const float max_x_value,
		const float min_y_value,
		const float max_y_value
		);
};
#endif