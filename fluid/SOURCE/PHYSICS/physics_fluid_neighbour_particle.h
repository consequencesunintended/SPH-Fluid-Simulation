/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHYSICS_FLUID_NEIGHBOUR_PARTICLE__
	#define __PHYSICS_FLUID_NEIGHBOUR_PARTICLE__

    // -- LOCAL

    // .. REFERENCES

	#include "math_vector_2d.h"
	#include "fundamental_data_types.h"
    #include "debug_statements.h"

	// -- GLOBAL

	// .. TYPES

	class PHYSICS_FLUID_NEIGHBOUR_PARTICLE
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		PHYSICS_FLUID_NEIGHBOUR_PARTICLE(
			VOID
			) : 
			ParticleIndex( 0 ),
			SmoothingKernel( 0.0f ),
			PoweredTwoSmoothingKernel( 0.0f ),
			Distance( 0.0f )
		{
		}

		// ~~

		PHYSICS_FLUID_NEIGHBOUR_PARTICLE(
			const PHYSICS_FLUID_NEIGHBOUR_PARTICLE & other
			) : 
			ParticleIndex( other.ParticleIndex ),
			SmoothingKernel( other.SmoothingKernel ),
			PoweredTwoSmoothingKernel( other.PoweredTwoSmoothingKernel ),
			Distance( other.Distance )
		{
		}

		// ~~

		virtual ~PHYSICS_FLUID_NEIGHBOUR_PARTICLE(
			VOID
			)
		{
		}

		// .. OPERATORS

		PHYSICS_FLUID_NEIGHBOUR_PARTICLE & operator=(
			const PHYSICS_FLUID_NEIGHBOUR_PARTICLE & other
			)
		{
			DEBUG_check_this_expression( this != &other );

			ParticleIndex = other.ParticleIndex;
			SmoothingKernel = other.SmoothingKernel;
			PoweredTwoSmoothingKernel = other.PoweredTwoSmoothingKernel;
			Distance = other.Distance;

			return *this;
		}

		// .. ACCESSORS

		INDEX GetParticleIndex(
			VOID
			) const
		{
			return ParticleIndex;
		}

		// ~~

		VOID SetParticleIndex(
			const INDEX particle_index
			)
		{
			ParticleIndex = particle_index;
		}

		// ~~

		REAL32 GetSmoothingKernel(
			VOID
			) const
		{
			return SmoothingKernel;
		}

		// ~~

		VOID SetSmoothingKernel(
			const REAL32 smooething_kernel_value
			)
		{
			SmoothingKernel = smooething_kernel_value;
		}

		// ~~

		REAL32 GetPoweredTwoSmoothingKernel(
			VOID
			) const
		{
			return PoweredTwoSmoothingKernel;
		}

		// ~~

		VOID SetPoweredTwoSmoothingKernel(
			const REAL32 powered_two_smooething_kernel_value
			)
		{
			PoweredTwoSmoothingKernel = powered_two_smooething_kernel_value;
		}

		// ~~

		REAL32 GetDistance(
			VOID
			) const
		{
			return Distance;
		}

		// ~~

		VOID SetDistance(
			const REAL32 distance_value
			)
		{
			Distance = distance_value;
		}

		// -- PRIVATE
		
	private:

		// .. ATTRIBUTES
			
		REAL32 
		  SmoothingKernel,
		  PoweredTwoSmoothingKernel, 
		  Distance; 
		INDEX 
		  ParticleIndex;
	};
#endif