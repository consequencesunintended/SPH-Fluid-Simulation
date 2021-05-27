/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHYSICS_FLUID_PARTICLE__
	#define __PHYSICS_FLUID_PARTICLE__

	// --LOCAL

	// .. REFERENCES

	#include "debug_statements.h"
	#include "fundamental_data_types.h"
	#include "math_vector_2d.h"
	#include "physics_entity.h"
	#include "physics_fluid_neighbour_particle.h"
	#include "physics_fluid_neighbour_particle_array.h"

	// -- GLOBAL

	// TYPES

	class PHYSICS_FLUID_PARTICLE :
		public PHYSICS_ENTITY
	{
	public:

		// .. CONSTRUCTORS

		PHYSICS_FLUID_PARTICLE(
			VOID
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
			VOID
			)
		{
		}

		// .. OPERATORS

		PHYSICS_FLUID_PARTICLE & operator=(
			const PHYSICS_FLUID_PARTICLE & other
			)
		{
			DEBUG_check_this_expression( this != &other );

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

		REAL32 GetDensity(
			VOID
			) const
		{
			return Density;
		}

		// ~~

		VOID SetDensity(
			const REAL32 density_value
			)
		{
			Density = density_value;
		}

		// ~~

		REAL32 GetNearDensity(
			VOID
			) const
		{
			return NearDensity;
		}

		// ~~

		VOID SetNearDensity(
			const REAL32 near_density_value
			)
		{
			NearDensity = near_density_value;
		}

		// ~~

		REAL32 GetViscositySigma(
			VOID
			) const
		{
			return ViscositySigma;
		}

		// ~~

		VOID SetViscositySigma(
			const REAL32 viscosity_sigma_value
			)
		{
			ViscositySigma = viscosity_sigma_value;
		}

		// ~~

		REAL32 GetViscosityBeta(
			VOID
			) const
		{
			return ViscosityBeta;
		}

		// ~~

		VOID SetViscosityBeta(
			const REAL32 viscosity_beta_value
			)
		{
			ViscosityBeta = viscosity_beta_value;
		}

		// ~~

		REAL32 GetMass(
			VOID
			) const
		{
			return Mass;
		}

		// ~~

		VOID SetMass(
			const REAL32 mass_value
			)
		{
			Mass = mass_value;
		}



		// ~~

		PHYSICS_FLUID_NEIGHBOUR_PARTICLE_ARRAY & GetNeighbours(
			VOID
			)
		{
			return NeighboursTable;
		}

		// ~~

		PHYSICS_FLUID_NEIGHBOUR_PARTICLE_ARRAY & SetNeighbours(
			const PHYSICS_FLUID_NEIGHBOUR_PARTICLE_ARRAY & neighbours_table
			)
		{
			NeighboursTable = neighbours_table;
		}

		// -- PRIVATE

	private:

		// .. ATTRIBUTES

		REAL32 
			Density, 
			NearDensity, 
			ViscositySigma, 
			ViscosityBeta,
			Mass; 
		PHYSICS_FLUID_NEIGHBOUR_PARTICLE_ARRAY 
			NeighboursTable;
	};
#endif