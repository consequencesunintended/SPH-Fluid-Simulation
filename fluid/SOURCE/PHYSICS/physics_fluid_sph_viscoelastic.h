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

#include "physics_fluid_particle.h"
#include "physics_spring.h"
#include "physics_spring_array.h"
#include "game_thread_pool.h"


// -- GLOBAL

// .. CONSTANTS

// For using this class for fluid simulation
// it must be noticed that the scaling factor
// has to be used for delta time,in integration 
// to get proper results out of the simulation.

constexpr float PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor = 100.0f;

// .. TYPES

class PHSYICS_FLUID_SPH_VISCOELASTIC
{
	// -- PUBLIC
public:

	// .. CONSTRUCTORS

	PHSYICS_FLUID_SPH_VISCOELASTIC( void ) : SpringTable()
	{

	}

	// ~~

	PHSYICS_FLUID_SPH_VISCOELASTIC( const PHSYICS_FLUID_SPH_VISCOELASTIC & other ) : SpringTable( other.SpringTable )
	{
	}

	void PHSYICS_FLUID_SPH_VISCOELASTIC::worker_thread( unsigned int t );
										
	// ~~

	virtual ~PHSYICS_FLUID_SPH_VISCOELASTIC( void );

	// .. OPERATORS

	PHSYICS_FLUID_SPH_VISCOELASTIC & operator=( const PHSYICS_FLUID_SPH_VISCOELASTIC & other )
	{
		assert( this != &other );

		SpringTable = other.SpringTable;

		return *this;
	}

	// .. ACCESSORS

	const PHYSICS_SPRING_ARRAY GetSpringsTable( void ) const
	{
		return SpringTable;
	}

	// ~~

	void SetSpringsTable( const PHYSICS_SPRING_ARRAY & spring_table )
	{
		SpringTable = spring_table;
	}

	// .. OPERATIONS

	void InitialiseSpringTable( const int number_of_particle );

	// ~~

	void CalculateDensityT( std::vector<PHYSICS_FLUID_PARTICLE>& particles_table,
							const float smoothing_radius,
							unsigned int start_range,
							unsigned int end_range );

	// ~~

	void CalculateDensity( std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable, const float smoothing_radius );

	// ~~

	void CalculatePressure(
		std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable,
		const float stifness_parameter,
		const float near_stifness_parameter,
		const float rest_density,
		const float delta_time
		);

	// ~~

	void CalculateViscosity( std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable, const float smoothing_radius, const float delta_time );

	// ~~

	void CalculateViscoElasticity(
		std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable,
		const float smoothing_radius,
		const float coefficient_spring,
		const float yield_ratio,
		const float plasticity_constant,
		const float delta_time
		);

	// ~~

	void InitialisePlasticity( std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable, const float smoothing_radius, const float coefficient_spring );

	// ~~

	void CalculatePlasticity( std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable, const float delta_time );

	// ~~

	void ResetSprings( void );

	// -- PRIVATE

private:

	// .. ATTRIBUTES

	PHYSICS_SPRING_ARRAY	SpringTable;
	GAME_THREAD_POOL		ThreadPool;

};


#endif