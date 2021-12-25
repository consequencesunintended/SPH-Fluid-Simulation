#ifndef __PHYSICS_FLUID_PARTICLE_POSITION_LOADER__
#define __PHYSICS_FLUID_PARTICLE_POSITION_LOADER__

// -- LOCAL

// .. REFERENCES

#include "graphics_image_pixel_loader.h"
#include "math_point_2d.h"
#include "math_vector_2d.h"
#include <assert.h>
#include <vector>

// -- GLOBAL

// .. TYPES

struct PHYSICS_FLUID_PARTICLE_POSITION_LOADER
{
	void LoadPositions( const char* bitmap );

	std::vector<MATH_POINT_2D> PointTable;
};
#endif