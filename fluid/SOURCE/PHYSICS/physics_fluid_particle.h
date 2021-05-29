#ifndef __PHYSICS_FLUID_PARTICLE__
#define __PHYSICS_FLUID_PARTICLE__

// --LOCAL

// .. REFERENCES

#include "fundamental_data_types.h"
#include "math_vector_2d.h"
#include "physics_entity.h"
#include "physics_fluid_neighbour_particle.h"
#include <assert.h>
#include <vector>

// -- GLOBAL

// TYPES

class PHYSICS_FLUID_PARTICLE :
	public PHYSICS_ENTITY
{
public:

	// .. CONSTRUCTORS

	PHYSICS_FLUID_PARTICLE(
		void
		) :
		PHYSICS_ENTITY(),
		Density( 0.0f ),
		NearDensity( 0.0f ),
		Mass( 0.0f ),
		ViscositySigma( 0.0f ),
		ViscosityBeta( 0.0f ),
		NeighboursTable()
	{
	}

	// ~~

	PHYSICS_FLUID_PARTICLE(
		const PHYSICS_FLUID_PARTICLE & other
		) :
		PHYSICS_ENTITY( other ),
		Density( other.Density ),
		NearDensity( other.NearDensity ),
		Mass( other.Mass ),
		ViscositySigma( other.ViscositySigma ),
		ViscosityBeta( other.ViscosityBeta ),
		NeighboursTable( other.NeighboursTable )
	{
	}

	// ~~

	virtual ~PHYSICS_FLUID_PARTICLE(
		void
		)
	{
	}

	// .. OPERATORS

	PHYSICS_FLUID_PARTICLE & operator=(
		const PHYSICS_FLUID_PARTICLE & other
		)
	{
		assert( this != &other );

		PHYSICS_ENTITY::operator=( other );
		Density = other.Density;
		NearDensity = other.NearDensity;
		Mass = other.Mass;
		ViscositySigma = other.ViscositySigma;
		ViscosityBeta = other.ViscosityBeta;
		NeighboursTable = other.NeighboursTable;

		return *this;
	}

	// .. ACCESSORS

	float GetDensity(
		void
		) const
	{
		return Density;
	}

	// ~~

	void SetDensity(
		const float density_value
		)
	{
		Density = density_value;
	}

	// ~~

	float GetNearDensity(
		void
		) const
	{
		return NearDensity;
	}

	// ~~

	void SetNearDensity(
		const float near_density_value
		)
	{
		NearDensity = near_density_value;
	}

	// ~~

	float GetViscositySigma(
		void
		) const
	{
		return ViscositySigma;
	}

	// ~~

	void SetViscositySigma(
		const float viscosity_sigma_value
		)
	{
		ViscositySigma = viscosity_sigma_value;
	}

	// ~~

	float GetViscosityBeta(
		void
		) const
	{
		return ViscosityBeta;
	}

	// ~~

	void SetViscosityBeta(
		const float viscosity_beta_value
		)
	{
		ViscosityBeta = viscosity_beta_value;
	}

	// ~~

	float GetMass(
		void
		) const
	{
		return Mass;
	}

	// ~~

	void SetMass(
		const float mass_value
		)
	{
		Mass = mass_value;
	}



	// ~~

	std::vector<PHYSICS_FLUID_NEIGHBOUR_PARTICLE>  & GetNeighbours(
		void
		)
	{
		return NeighboursTable;
	}

	// ~~

	std::vector<PHYSICS_FLUID_NEIGHBOUR_PARTICLE>  & SetNeighbours(
		const std::vector<PHYSICS_FLUID_NEIGHBOUR_PARTICLE>  & neighbours_table
		)
	{
		NeighboursTable = neighbours_table;
	}

	// -- PRIVATE

private:

	// .. ATTRIBUTES

	float 
		Density, 
		NearDensity, 
		ViscositySigma, 
		ViscosityBeta,
		Mass; 
	std::vector<PHYSICS_FLUID_NEIGHBOUR_PARTICLE>  
		NeighboursTable;
};
#endif