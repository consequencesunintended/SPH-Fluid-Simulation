#ifndef __PHYSICS_ENTITY__
#define __PHYSICS_ENTITY__

#include "math_vector_2d.h"
#include <assert.h>

struct PHYSICS_ENTITY
{
	MATH_VECTOR_2D Velocity;
	MATH_VECTOR_2D Position;
	MATH_VECTOR_2D Force;
	MATH_VECTOR_2D OldPosition;
};
#endif