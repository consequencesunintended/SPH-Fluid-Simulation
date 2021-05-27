/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHYSICS_COLLISION_2D__
	#define __PHYSICS_COLLISION_2D__

	// -- LOCAL
	
	// .. REFERENCES

	#include "physics_entity.h"
	#include "fundamental_data_types.h"
	#include "math_point_2d.h"
	
	// -- GLOBAL

	// .. TYPES

	class PHYSICS_COLLISION_2D
	{
		// -- PUBLIC

	public:

		// .. OPERATIONS

		VOID CheckForWall(
			PHYSICS_ENTITY &entity,
			const REAL32 wall_spring_coefficient,
			const MATH_POINT_2D & position,
			const REAL32 min_x_value,
			const REAL32 max_x_value,
			const REAL32 min_y_value,
			const REAL32 max_y_value
			);
	};
#endif