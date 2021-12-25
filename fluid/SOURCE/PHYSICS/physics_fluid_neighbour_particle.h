#ifndef __PHYSICS_FLUID_NEIGHBOUR_PARTICLE__
#define __PHYSICS_FLUID_NEIGHBOUR_PARTICLE__

#include "math_vector_2d.h"
#include <assert.h>

struct PHYSICS_FLUID_NEIGHBOUR_PARTICLE
{
	float SmoothingKernel{ 0.0f };
	float PoweredTwoSmoothingKernel{ 0.0f };
	float Distance{ 0.0f };
	size_t ParticleIndex{ 0 };
};
#endif