/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
// This class provide the main functions for a Fluid Simulation
// the main algorithm used here is based on a this paper 
// "CLAVET, S., BEAUDOIN, P., AND POULIN, P. 2005. Particle-based 
// viscoelastic Fuid simulation. In SCA 2005, 219–228" There are
// some minor changes in the algorithm which I assume in the paper
// was written differently due to typos. A link to view the paper
// is avaiable here 
// http://www.iro.umontreal.ca/labs/infographie/papers/Clavet-2005-PVFS/pvfs.pdf
// the class can be used for a 3D simulation as well the only changes
// needed is changing the vector class to a 3D vector,the rest of the
// code don't need any changes.
#ifndef __PHSYICS_FLUID_SPH_VISCOELASTIC__
	#define __PHSYICS_FLUID_SPH_VISCOELASTIC__

	// -- LOCAL

	// .. REFERENCES

	#include "debug_statements.h"
	#include "fundamental_data_types.h"
    #include "fundamental_index_array.h"
	#include "physics_fluid_particle.h"
	#include "physics_fluid_particle_array.h"
	#include "physics_spring.h"
	#include "physics_spring_array.h"

	// -- GLOBAL

	// .. CONSTANTS

    // For using this class for fluid simulation
    // it must be noticed that the scaling factor
    // has to be used for delta time,in integration 
    // to get proper results out of the simulation.

	#define PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor 100

	// .. TYPES

	class PHSYICS_FLUID_SPH_VISCOELASTIC
	{
		// -- PUBLIC
	public:

		// .. CONSTRUCTORS

		PHSYICS_FLUID_SPH_VISCOELASTIC(
			VOID
			) :
			SpringTable()
		{
		}

		// ~~

		PHSYICS_FLUID_SPH_VISCOELASTIC(
			const PHSYICS_FLUID_SPH_VISCOELASTIC & other
			) :
			SpringTable( other.SpringTable )
		{
		}

		// ~~

		virtual ~PHSYICS_FLUID_SPH_VISCOELASTIC(
			VOID
			)
		{
		}

		// .. OPERATORS

		PHSYICS_FLUID_SPH_VISCOELASTIC & operator=(
			const PHSYICS_FLUID_SPH_VISCOELASTIC & other
			)
		{
			DEBUG_check_this_expression( this != &other );

			SpringTable = other.SpringTable;

			return *this;
		}

		// .. ACCESSORS

		const PHYSICS_SPRING_ARRAY GetSpringsTable(
			VOID
			) const
		{
			return SpringTable;
		}

		// ~~

		VOID SetSpringsTable(
			const PHYSICS_SPRING_ARRAY & spring_table
			)
		{
			SpringTable = spring_table;
		}

		// .. OPERATIONS

		VOID InitialiseSpringTable(
			const INT32 number_of_particles
			);

		// ~~

		VOID CalculateDensity(
			PHYSICS_FLUID_PARTICLE_ARRAY & particlesTable,
			const REAL32 smoothing_radius
			);

		// ~~

		VOID CalculatePressure(
			PHYSICS_FLUID_PARTICLE_ARRAY & particlesTable,
			const REAL32 stifness_parameter,
			const REAL32 near_stifness_parameter,
			const REAL32 rest_density,
			const REAL32 delta_time
			);

		// ~~

		VOID CalculateViscosity(
			PHYSICS_FLUID_PARTICLE_ARRAY & particlesTable,
			const REAL32 smoothing_radius,
			const REAL32 delta_time
			);

		// ~~

		VOID CalculateViscoElasticity(
			PHYSICS_FLUID_PARTICLE_ARRAY & particlesTable,
			const REAL32 smoothing_radius,
			const REAL32 coefficient_spring,
			const REAL32 yeild_ratio,
			const REAL32 plasticity_constant,
			const REAL32 delta_time
			);

		// ~~

		VOID InitialisePlasticity(
			PHYSICS_FLUID_PARTICLE_ARRAY & particlesTable,
			const REAL32 smoothing_radius,
			const REAL32 coefficient_spring
			);

		// ~~

		VOID CalculatePlasticity(
			PHYSICS_FLUID_PARTICLE_ARRAY & particlesTable,
			const REAL32 delta_time
			);

		// ~~

		VOID ResetSprings(
			VOID
			);

		// -- PRIVATE

	private:

		// .. ATTRIBUTES

		PHYSICS_SPRING_ARRAY 
			SpringTable;
	};
#endif