#ifndef __PHYSICS_FLUID_PARTICLE__
#define __PHYSICS_FLUID_PARTICLE__

// --LOCAL

// .. REFERENCES

#include "math_vector_2d.h"
#include "physics_entity.h"
#include "physics_fluid_neighbour_particle.h"
#include <assert.h>
#include <vector>

// -- GLOBAL

// TYPES

struct PHYSICS_FLUID_PARTICLE : public PHYSICS_ENTITY
{
	float											Density{ 0.0f };
	float											NearDensity{ 0.0f };
	float											ViscositySigma{ 0.0f };
	float											ViscosityBeta{ 0.0f };
	float											Mass{ 0.0f };
	std::vector<PHYSICS_FLUID_NEIGHBOUR_PARTICLE>	NeighboursTable;
};
#endif