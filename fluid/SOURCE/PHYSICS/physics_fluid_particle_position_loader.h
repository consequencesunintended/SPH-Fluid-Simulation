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

class PHYSICS_FLUID_PARTICLE_POSITION_LOADER
{
// -- PUBLIC
public:

// .. CONSTRUCTORS

PHYSICS_FLUID_PARTICLE_POSITION_LOADER(
	void
	) :
	PointTable()
{
}

// ~~

virtual ~PHYSICS_FLUID_PARTICLE_POSITION_LOADER(
	void
	)
{
}
		
// ~~

PHYSICS_FLUID_PARTICLE_POSITION_LOADER(
	const PHYSICS_FLUID_PARTICLE_POSITION_LOADER & other
	) :
	PointTable( other.PointTable )
{
}

// .. OPERATORS

PHYSICS_FLUID_PARTICLE_POSITION_LOADER & operator=(
	const PHYSICS_FLUID_PARTICLE_POSITION_LOADER & other
	)
{
	assert( this != &other );

	PointTable = other.PointTable;

	return *this;
}

// .. ACCESSORS

const std::vector<MATH_POINT_2D> & GetPointTable(
	void
	) const
{
	return PointTable;
}

// ~~

void SetPointTable(
	const std::vector<MATH_POINT_2D> &point_table
	)
{
	PointTable = point_table;
}

// .. OPERATIONS

void LoadPositions(
	const char * bitmap
	);

// -- PRIVATE

private:

// .. ATTRIBUTES

std::vector<MATH_POINT_2D>
	PointTable;
};
#endif