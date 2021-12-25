#ifndef __PHYSICS_FLUID_NEIGHBOUR_PARTICLE__
#define __PHYSICS_FLUID_NEIGHBOUR_PARTICLE__

#include "math_vector_2d.h"
#include <assert.h>

struct PHYSICS_FLUID_NEIGHBOUR_PARTICLE
{
	float SmoothingKernel;
	float PoweredTwoSmoothingKernel;
	float Distance;
	size_t ParticleIndex;
};
#endif