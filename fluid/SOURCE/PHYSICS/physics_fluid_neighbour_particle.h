#ifndef __PHYSICS_FLUID_NEIGHBOUR_PARTICLE__
#define __PHYSICS_FLUID_NEIGHBOUR_PARTICLE__

// -- LOCAL

// .. REFERENCES

#include "math_vector_2d.h"
#include <assert.h>

// -- GLOBAL

// .. TYPES

class PHYSICS_FLUID_NEIGHBOUR_PARTICLE
{
	// -- PUBLIC

	public:

	// .. CONSTRUCTORS

	PHYSICS_FLUID_NEIGHBOUR_PARTICLE( void ) :
		ParticleIndex( 0 ),
		SmoothingKernel( 0.0f ),
		PoweredTwoSmoothingKernel( 0.0f ),
		Distance( 0.0f )
	{
	}

	// ~~

	PHYSICS_FLUID_NEIGHBOUR_PARTICLE( const PHYSICS_FLUID_NEIGHBOUR_PARTICLE& other ) :
		ParticleIndex( other.ParticleIndex ),
		SmoothingKernel( other.SmoothingKernel ),
		PoweredTwoSmoothingKernel( other.PoweredTwoSmoothingKernel ),
		Distance( other.Distance )
	{
	}

	// ~~

	virtual ~PHYSICS_FLUID_NEIGHBOUR_PARTICLE( void )
	{
	}

	// .. OPERATORS

	PHYSICS_FLUID_NEIGHBOUR_PARTICLE& operator=( const PHYSICS_FLUID_NEIGHBOUR_PARTICLE& other )
	{
		assert( this != &other );

		ParticleIndex = other.ParticleIndex;
		SmoothingKernel = other.SmoothingKernel;
		PoweredTwoSmoothingKernel = other.PoweredTwoSmoothingKernel;
		Distance = other.Distance;

		return *this;
	}

	// .. ACCESSORS

	unsigned int GetParticleIndex( void ) const
	{
		return ParticleIndex;
	}

	// ~~

	void SetParticleIndex( const unsigned int particle_index )
	{
		ParticleIndex = particle_index;
	}

	// ~~

	float GetSmoothingKernel( void ) const
	{
		return SmoothingKernel;
	}

	// ~~

	void SetSmoothingKernel( const float smooething_kernel_value )
	{
		SmoothingKernel = smooething_kernel_value;
	}

	// ~~

	float GetPoweredTwoSmoothingKernel( void ) const
	{
		return PoweredTwoSmoothingKernel;
	}

	// ~~

	void SetPoweredTwoSmoothingKernel( const float powered_two_smooething_kernel_value )
	{
		PoweredTwoSmoothingKernel = powered_two_smooething_kernel_value;
	}

	// ~~

	float GetDistance( void ) const
	{
		return Distance;
	}

	// ~~

	void SetDistance( const float distance_value )
	{
		Distance = distance_value;
	}

	// -- PRIVATE

	private:

	// .. ATTRIBUTES

	float
		SmoothingKernel,
		PoweredTwoSmoothingKernel,
		Distance;
	unsigned int
		ParticleIndex;
};
#endif