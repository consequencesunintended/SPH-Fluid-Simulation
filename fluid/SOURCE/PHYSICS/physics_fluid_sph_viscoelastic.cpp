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

#include "physics_fluid_sph_viscoelastic.h"

#include "physics_fluid_particle.h"
#include "physics_fluid_neighbour_particle.h"
#include "math_vector_2d.h"
#include "physics_spring.h"
#include "physics_spring_array.h"
#include "math_square_root.h"
#include <iostream>
#include <chrono>

using namespace std::chrono;

// -- LOCAL

// .. REFERENCES



// -- PUBLIC


// .. OPERATIONS

void PHSYICS_FLUID_SPH_VISCOELASTIC::InitialiseSpringTable(
	const int number_of_particles
	)
{
	SpringTable.SetMaxNumberOfPoints( number_of_particles );
}
// ~~

void PHSYICS_FLUID_SPH_VISCOELASTIC::CalculateDensityT( std::vector<PHYSICS_FLUID_PARTICLE>& particles_table,
														const float smoothing_radius,
														unsigned int start_range,
														unsigned int end_range 
														)
{
	float								density;
	float								near_density;
	float								squared_distance_between_particle_and_neighbour;
	float								distance_between_particle_and_neighbour;
	float								smoothing_kernel;
	float								powered_two_smoothing_kernel;
	float								powered_three_smoothing_kernel;
	MATH_VECTOR_2D						vector_between_particle_and_neighbour;

	for ( size_t particle_index = start_range; particle_index < end_range; particle_index++ )
	{
		particles_table[particle_index].GetNeighbours().clear();
		density = 0;
		near_density = 0;

		for ( size_t neighbour_index = particle_index + 1; neighbour_index < particles_table.size(); neighbour_index++ )
		{
			PHYSICS_FLUID_NEIGHBOUR_PARTICLE	neighbour_particle;

			vector_between_particle_and_neighbour.SetDifference( particles_table[particle_index].GetPosition(), particles_table[neighbour_index].GetPosition() );

			squared_distance_between_particle_and_neighbour = vector_between_particle_and_neighbour.GetSquareLength();

			if ( squared_distance_between_particle_and_neighbour < smoothing_radius * smoothing_radius )
			{
				distance_between_particle_and_neighbour = MATH_SQUARE_ROOT::GetSquareRoot( squared_distance_between_particle_and_neighbour );
				smoothing_kernel = 1 - distance_between_particle_and_neighbour / smoothing_radius;
				powered_two_smoothing_kernel = smoothing_kernel * smoothing_kernel;
				powered_three_smoothing_kernel = powered_two_smoothing_kernel * smoothing_kernel;
				density += powered_two_smoothing_kernel;
				near_density += powered_three_smoothing_kernel;

				// deviating from the original equation for the sake of multithreading and commenting these two lines out
				// doesn't seem to visually affect the simulation

				//particles_table[neighbour_index].SetDensity( particles_table[neighbour_index].GetDensity() + powered_two_smoothing_kernel );
				//particles_table[neighbour_index].SetNearDensity( particles_table[neighbour_index].GetNearDensity() + powered_three_smoothing_kernel );	

				neighbour_particle.SetParticleIndex( neighbour_index );
				neighbour_particle.SetSmoothingKernel( smoothing_kernel );
				neighbour_particle.SetPoweredTwoSmoothingKernel( powered_two_smoothing_kernel );
				neighbour_particle.SetDistance( distance_between_particle_and_neighbour );
				particles_table[particle_index].GetNeighbours().push_back( neighbour_particle );
			}
		}
		particles_table[particle_index].SetDensity( density );
		particles_table[particle_index].SetNearDensity( near_density );
	}
}
// ~~

void PHSYICS_FLUID_SPH_VISCOELASTIC::worker_thread( std::vector<PHYSICS_FLUID_PARTICLE>& particles_table,
													const float smoothing_radius,
													unsigned int start_range,
													unsigned int end_range,
													unsigned int t )
{
	while ( true )
	{
		mutex_lock.lock();
		bool is_ready = ready_list[t];
		mutex_lock.unlock();

		if ( is_ready )
		{
			CalculateDensityT( particles_table, smoothing_radius, start_range, end_range );

			mutex_lock.lock();
			processed_list[t] =  true ;
			ready_list[t] = false;
			mutex_lock.unlock();
		}
	}
}
PHSYICS_FLUID_SPH_VISCOELASTIC::~PHSYICS_FLUID_SPH_VISCOELASTIC( void )
{
	for ( auto& w : workers )
	{
		w.join();
	}
}

void PHSYICS_FLUID_SPH_VISCOELASTIC::CalculateDensity( std::vector<PHYSICS_FLUID_PARTICLE> & particles_table, const float smoothing_radius )
{
	bool		threaded = true;
	static bool thread_created = false;
	int			num_particles = particles_table.size();

	//auto start = high_resolution_clock::now();

	if ( threaded )
	{
		int num_threads = std::thread::hardware_concurrency();

		if ( !thread_created )
		{			
			ready_list.resize( num_threads );
			processed_list.resize( num_threads );

			for ( int t = 0; t < num_threads; t++ )
			{
				workers.push_back( std::thread( &PHSYICS_FLUID_SPH_VISCOELASTIC::worker_thread, this, 
										std::ref( particles_table ), 
										smoothing_radius,
										t * num_particles / num_threads,
										(t + 1) == num_threads ? num_particles : (t + 1) * num_particles / num_threads,
										t
										));
			}
			thread_created = true;
		}
		for ( int t = 0; t < num_threads; t++ )
		{
			mutex_lock.lock();
			ready_list[t] = true;
			mutex_lock.unlock();
		}

		bool processed = false;

		while ( !processed )
		{
			bool done = true;

			for ( int t = 0; t < num_threads; t++ )
			{
				bool v;
				
				mutex_lock.lock();
				v = processed_list[t];
				mutex_lock.unlock();

				if ( v == false )
				{
					done = false;
				}
			}

			if ( done )
			{
				processed = true;
			}
		}
		for ( int t = 0; t < num_threads; t++ )
		{
			mutex_lock.lock();
			processed_list[t] = false;
			mutex_lock.unlock();
		}
	}
	else
	{
		CalculateDensityT( particles_table, smoothing_radius, 0, particles_table.size() );
	}

	//auto end = high_resolution_clock::now();
	//std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//std::cout << duration.count() << std::endl;
}

// ~~

void PHSYICS_FLUID_SPH_VISCOELASTIC::CalculatePressure(
	std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable,
	const float stifness_parameter,
	const float near_stifness_parameter,
	const float rest_density,
	const float delta_time
	)
{	
	unsigned int						neighbour_index;	 
	MATH_VECTOR_2D						particle_pressure_force;
	MATH_VECTOR_2D						vector_between_particle_and_neighbour;
	MATH_VECTOR_2D						neighbour_pressure_force;
	PHYSICS_FLUID_NEIGHBOUR_PARTICLE	neigbour_particle; 
	float								pressure;
	float								near_pressure;
	float								smoothing_kernel;
	float								powered_two_smoothing_kernel;
	float								pressure_scalar_value;

	for ( unsigned int prticle_index = 0; prticle_index < particlesTable.size(); prticle_index++ )
	{
		pressure = stifness_parameter * (particlesTable[prticle_index].GetDensity() - rest_density);
		near_pressure =  near_stifness_parameter * particlesTable[prticle_index].GetNearDensity();
		particle_pressure_force.Reset();		

		for ( unsigned int neighbour_table_index = 0; neighbour_table_index < particlesTable[prticle_index].GetNeighbours().size(); neighbour_table_index++ )
		{
			neigbour_particle = particlesTable[prticle_index].GetNeighbours()[neighbour_table_index];
			neighbour_index = neigbour_particle.GetParticleIndex();     
			smoothing_kernel = neigbour_particle.GetSmoothingKernel();
			powered_two_smoothing_kernel = neigbour_particle.GetPoweredTwoSmoothingKernel();  
			vector_between_particle_and_neighbour.SetDifference( particlesTable[prticle_index].GetPosition(), particlesTable[neighbour_index].GetPosition() );
			pressure_scalar_value = (pressure) * smoothing_kernel + (near_pressure) * powered_two_smoothing_kernel;
			pressure_scalar_value *= delta_time * delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor;

			if ( neigbour_particle.GetDistance() != 0 )
			{
				neighbour_pressure_force = vector_between_particle_and_neighbour / neigbour_particle.GetDistance() * pressure_scalar_value; 
			}
			else
			{
				neighbour_pressure_force.Reset();
			}
			particlesTable[neighbour_index].AccumalateForce( neighbour_pressure_force );
			particle_pressure_force -= neighbour_pressure_force ;
		}
		particlesTable[prticle_index].AccumalateForce( particle_pressure_force );
	}
}

// ~~

void PHSYICS_FLUID_SPH_VISCOELASTIC::CalculateViscosity(
	std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable,
	const float smoothing_radius,
	const float delta_time
	)
{	
	unsigned int						prticle_index;
	unsigned int						neighbour_table_index;
	unsigned int						neighbour_index;
	PHYSICS_FLUID_NEIGHBOUR_PARTICLE	neighbour_particle;
	float								length;
	float								q;
	float								inward_radial_velocity;	 
	MATH_VECTOR_2D						vector_between_particle_and_neighbour;
	MATH_VECTOR_2D						normalised_vector_between_particle_and_neighbour;
	MATH_VECTOR_2D						impulses;

		
	for ( prticle_index = 0; prticle_index < particlesTable.size(); prticle_index++ )
	{		
		for ( neighbour_table_index = 0; neighbour_table_index < particlesTable[prticle_index].GetNeighbours().size(); neighbour_table_index++ )
		{
			neighbour_particle = particlesTable[prticle_index].GetNeighbours()[neighbour_table_index];
			neighbour_index = neighbour_particle.GetParticleIndex();    
			vector_between_particle_and_neighbour = particlesTable[neighbour_index].GetPosition() - particlesTable[prticle_index].GetPosition();
			length = neighbour_particle.GetDistance();		
			q = length / smoothing_radius;
      

			normalised_vector_between_particle_and_neighbour = (vector_between_particle_and_neighbour / length);
			inward_radial_velocity  = ( particlesTable[prticle_index].GetVelocity() - particlesTable[neighbour_index].GetVelocity() ).GetDotProduct( normalised_vector_between_particle_and_neighbour );

			if( inward_radial_velocity > 0.0f)
			{
				impulses = (normalised_vector_between_particle_and_neighbour 
					* (particlesTable[neighbour_index].GetViscositySigma() 
					* inward_radial_velocity + particlesTable[neighbour_index].GetViscosityBeta() 
					* inward_radial_velocity * inward_radial_velocity)) 
					* (1 - q);
				 impulses *= delta_time 
					 * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor;
				 particlesTable[prticle_index].SetVelocity( particlesTable[prticle_index].GetVelocity() - impulses );
				 particlesTable[neighbour_index].SetVelocity( particlesTable[neighbour_index].GetVelocity()+ impulses );
			}
		}
	}
}

// ~~

void PHSYICS_FLUID_SPH_VISCOELASTIC::CalculateViscoElasticity(
	std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable,
	const float smoothing_radius,
	const float coefficient_spring,
	const float yield_ratio,
	const float plasticity_constant,
	const float delta_time
	)
{
	PHYSICS_FLUID_NEIGHBOUR_PARTICLE	neighbour_particle;
	PHYSICS_SPRING						spring;	
	unsigned int						particle_index;
	unsigned int						neighbour_index;
	unsigned int						spring_index;
	unsigned int						spring_point1_index;
	unsigned int						spring_point2_index;
	float								rest_length;
	float								tolerable_deformation;
	float								distance_between_particle_and_neighbour;
	MATH_VECTOR_2D 						spring_force;
	MATH_VECTOR_2D						spring_displacement;

	
	for ( particle_index = 0; particle_index < particlesTable.size(); particle_index++ )
	{		
		for ( neighbour_index = 0; neighbour_index < particlesTable[particle_index].GetNeighbours().size(); neighbour_index++ )
		{
			neighbour_particle = particlesTable[particle_index].GetNeighbours()[neighbour_index];
      
			if ( !SpringTable.GetExistenceTable()[particle_index][neighbour_particle.GetParticleIndex()] ) 
			{
				SpringTable.SetItemInExistenceTable( particle_index, neighbour_particle.GetParticleIndex(), true );
				spring.SetPoint1Index( particle_index );
				spring.SetPoint2Index( neighbour_particle.GetParticleIndex() );
				spring.SetRestLength( smoothing_radius );
				spring.SetCoefficient( coefficient_spring );
				SpringTable.push_back( spring );
			}
		}
	}
	
	for ( spring_index = 0; spring_index < SpringTable.size(); spring_index++ )
	{
		spring_point1_index = SpringTable[spring_index].GetPoint1Index();
		spring_point2_index = SpringTable[spring_index].GetPoint2Index();
		rest_length = SpringTable[spring_index].GetRestLength();
		tolerable_deformation = yield_ratio * rest_length;
		distance_between_particle_and_neighbour = (particlesTable[spring_point2_index].GetPosition() - particlesTable[spring_point1_index].GetPosition()).GetLength();

		if ( distance_between_particle_and_neighbour > ( rest_length + tolerable_deformation) )
		{
			SpringTable[spring_index].SetRestLength( SpringTable[spring_index].GetRestLength() + ( delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor ) * plasticity_constant * ( distance_between_particle_and_neighbour - rest_length - tolerable_deformation ) );
		} 
		else if ( distance_between_particle_and_neighbour < (rest_length - tolerable_deformation ))
		{
			SpringTable[spring_index].SetRestLength( SpringTable[spring_index].GetRestLength() - ( delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor ) * plasticity_constant * (rest_length - tolerable_deformation - distance_between_particle_and_neighbour ) );
		}

		if ( SpringTable[spring_index].GetRestLength() > smoothing_radius )
		{
			SpringTable.SetItemInExistenceTable( SpringTable[spring_index].GetPoint1Index(), SpringTable[spring_index].GetPoint2Index(), false );
			SpringTable.erase( SpringTable.begin() + spring_index );
			spring_index--;
		}
	}
	
	for ( spring_index = 0; spring_index < SpringTable.size(); spring_index++ )
	{
		spring_point1_index = SpringTable[spring_index].GetPoint1Index();
		spring_point2_index = SpringTable[spring_index].GetPoint2Index();
		rest_length = SpringTable[spring_index].GetRestLength();
		PHYSICS_SPRING::CalculateForce( spring_force, SpringTable[spring_index], particlesTable[spring_point1_index], particlesTable[spring_point2_index] );
		spring_displacement = spring_force 
			* ( 1.0f - rest_length / smoothing_radius )
			* delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor 
			* delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor;

		particlesTable[spring_point1_index].SetPosition( particlesTable[spring_point1_index].GetPosition() - spring_displacement );
		particlesTable[spring_point2_index].SetPosition( particlesTable[spring_point2_index].GetPosition() + spring_displacement );
	}
}

// ~~

void PHSYICS_FLUID_SPH_VISCOELASTIC::ResetSprings( void )
{
	SpringTable.clear();
}


// ~~

void PHSYICS_FLUID_SPH_VISCOELASTIC::InitialisePlasticity(
	std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable,
	const float smoothing_radius,
	const float coefficient_spring
	)
{
	PHYSICS_FLUID_NEIGHBOUR_PARTICLE	neighbour_particle;
	PHYSICS_SPRING						spring;
	unsigned int						particle_index_1;
	unsigned int						particle_index_2;
	float								distance_between_particle_and_neighbour;
	MATH_VECTOR_2D 						vector_between_particle_and_neighbour;

	ResetSprings();
	
	for ( particle_index_1 = 0; particle_index_1 < particlesTable.size(); particle_index_1++ )
	{		
		for ( particle_index_2 = 0; particle_index_2 < particlesTable.size(); particle_index_2++ )
		{
  			vector_between_particle_and_neighbour.SetDifference( particlesTable[ particle_index_1 ].GetPosition(), particlesTable[ particle_index_2 ].GetPosition() );
			distance_between_particle_and_neighbour = vector_between_particle_and_neighbour.GetLength();

			if ( distance_between_particle_and_neighbour < smoothing_radius )
			{
				spring.SetPoint1Index( particle_index_1 );
				spring.SetPoint2Index( particle_index_2 );
				spring.SetRestLength( distance_between_particle_and_neighbour );
				spring.SetCoefficient( coefficient_spring );
				SpringTable.push_back( spring );
			}
		}
	}
}

// ~~

void PHSYICS_FLUID_SPH_VISCOELASTIC::CalculatePlasticity( std::vector<PHYSICS_FLUID_PARTICLE> & particlesTable, const float delta_time )
{
	PHYSICS_SPRING	spring;
	unsigned int	spring_index;
	unsigned int	spring_point1_index;
	unsigned int	spring_point2_index;
	float			restLength;
	MATH_VECTOR_2D 	spring_force;
	MATH_VECTOR_2D	spring_displacement;
	
	for ( spring_index = 0; spring_index < SpringTable.size(); spring_index++ )
	{
		spring_point1_index = SpringTable[spring_index].GetPoint1Index();
		spring_point2_index = SpringTable[spring_index].GetPoint2Index();
		restLength = SpringTable[spring_index].GetRestLength();

		PHYSICS_SPRING::CalculateForce( spring_force, SpringTable[spring_index], particlesTable[spring_point1_index], particlesTable[spring_point2_index]);

		spring_displacement = spring_force * delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor;

		particlesTable[spring_point1_index].SetPosition( particlesTable[spring_point1_index].GetPosition() - spring_displacement );
		particlesTable[spring_point2_index].SetPosition( particlesTable[spring_point2_index].GetPosition() + spring_displacement );
	}
}