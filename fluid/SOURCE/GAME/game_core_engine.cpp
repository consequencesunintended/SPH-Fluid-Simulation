/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#include "fundamental_data_types.h"

// -- LOCAL

// .. REFERENCES

#include "game_core_engine.h"
#include "physics_level_constants.h"
#include "physics_level_fluid_constants.h"

// -- CONSTANTS

#define LOCAL_Margin_with_bottom_of_the_window 1.0f

// -- PUBLIC

// .. OPERATIONS

VOID GAME_CORE_ENGINE::Initialize( 
    const REAL32 fluid_max_width,
    const REAL32 fluid_max_height
    )
{
	PhysicsIntegrationEngine = new PHSYICS_INTEGRATION_PREDICTION_RELAXATION();
	FluidMaxHeight = fluid_max_height;
	FluidMaxWidth = fluid_max_width;
	InitialiseParticles();
}

// ~~

VOID GAME_CORE_ENGINE::InitialiseParticles(
	VOID
    )
{
    MATH_VECTOR_2D 
        position;
    PHYSICS_FLUID_PARTICLE 
        particle;
    INDEX
        particle_index;

	FluidPositionLoader.LoadPositions(
		"./DATA/position_map.bmp"
		);

    particle_index = 0;

	FUNDAMENTAL_DATA_TYPES_loop_through_table( particle_index, FluidPositionLoader.GetPointTable() )
	{
		particle.SetPosition( FluidPositionLoader.GetPointTable()[ particle_index ] );
		particle.SetOldPosition( particle.GetPosition() );
		ParticleTable.push_back( particle );
	}

    particle_index = 0;

    FUNDAMENTAL_DATA_TYPES_loop_through_table( particle_index, ParticleTable )
    {
	    ParticleTable[ particle_index ].SetViscosityBeta( GAME_CORE_ENGINE_visocity_beta );
	    ParticleTable[ particle_index ].SetViscositySigma( GAME_CORE_ENGINE_visocity_sigma );
    }
	PhysicsFluidEngine.InitialiseSpringTable( ParticleTable.size() );
}

// ~~

VOID GAME_CORE_ENGINE::Update(
    const REAL32 delta_time,
    const BOOL do_viscosity,
    const BOOL is_viscoelastic,
    const BOOL is_plastic
    )
{
	COUNTER
		counter,
		counter2;

	DeltaValue += delta_time;
	counter = 0;

	if ( delta_time / GAME_CORE_ENGINE_delta_time_cap > 5.0f )
	{
		counter = INT32( delta_time / GAME_CORE_ENGINE_delta_time_cap - 5.0f );
	}

	if ( DeltaValue > GAME_CORE_ENGINE_delta_time_cap )
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( counter2, 0, counter )
		{
			if ( is_viscoelastic )
			{
				CalculateSpringsForViscoelasticity( GAME_CORE_ENGINE_delta_time_cap );
			}
			if ( is_plastic )
			{
				CalculatePlasticity( GAME_CORE_ENGINE_delta_time_cap );
			}
			CalculateDensity( GAME_CORE_ENGINE_delta_time_cap );
			CalculatePressureForce( GAME_CORE_ENGINE_delta_time_cap );
			UpdateParticlesVelocityAndPosition( GAME_CORE_ENGINE_delta_time_cap );
		}
		DeltaValue = 0.0f;
	}
}

// ~~

VOID GAME_CORE_ENGINE::ResetViscoelasticity(
    VOID
    )
{
    PhysicsFluidEngine.ResetSprings();
}

VOID GAME_CORE_ENGINE::InitialisePlasticity(
	VOID
	)
{
	PhysicsFluidEngine.InitialisePlasticity(
		ParticleTable,
		PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius,
		0.09f
		);
}

// -- PRIVATE

// .. OPERATIONS

VOID GAME_CORE_ENGINE::CalculateDensity( 
	const REAL32 delta_time  
	)
{

	PhysicsFluidEngine.CalculateDensity(
		ParticleTable,
		PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius
		);
}

// ~~

VOID GAME_CORE_ENGINE::CalculatePressureForce( 
    const REAL32 delta_time  
    )
{
	PhysicsFluidEngine.CalculatePressure(
		ParticleTable,
		PHSYICS_LEVEL_FLUID_Stifness_K,
		PHSYICS_LEVEL_FLUID_Near_Stifness_Near_K,
		PHSYICS_LEVEL_FLUID_Rest_Density,
		delta_time
		);
}

// ~~

VOID GAME_CORE_ENGINE::UpdateParticlesVelocityAndPosition( 
    const REAL32 delta_time  
    )
{
	INDEX 
		particle_index;
	REAL32
		attraction_radius;

	particle_index = 0;

	FUNDAMENTAL_DATA_TYPES_loop_through_table( particle_index, ParticleTable )
	{
		PhysicsIntegrationEngine->UpdateVelocity(
			ParticleTable[particle_index],
			delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor
			);
	}

	CalculateViscosity(
		delta_time
		);

	particle_index = 0;

	FUNDAMENTAL_DATA_TYPES_loop_through_table( particle_index, ParticleTable )
	{
		PhysicsIntegrationEngine->UpdatePosition(
			ParticleTable[particle_index],
			delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor
			);

		ParticleTable[particle_index].SetForce( PHYSICS_LEVEL_CONSTANTS_Gravity );	
	}
	DetectCollision( FluidMaxWidth, FluidMaxHeight );

	particle_index = 0;
	attraction_radius = FluidMaxWidth / 4.0f;

	FUNDAMENTAL_DATA_TYPES_loop_through_table( particle_index, ParticleTable )
	{
		PhysicsMouseInteraction.ApplyMouseBehaviour( ParticleTable[ particle_index ], attraction_radius );
	}
}

// ~~

VOID GAME_CORE_ENGINE::DetectCollision( 
    const REAL32 widht, 
    const REAL32 height  
    )
{
	INDEX
		particle_index;
	MATH_POINT_2D
		position;

	particle_index = 0;
	position.Assign( 0.0f, 0.0f );

	FUNDAMENTAL_DATA_TYPES_loop_through_table( particle_index, ParticleTable )
	{
			PhysicsCollision2DEngine.CheckForWall( 
				ParticleTable[particle_index],
				PHYSICS_LEVEL_CONSTANTS_Wall_Spring_Coefficient,
				position,
				-widht,
				+widht,
				-height + LOCAL_Margin_with_bottom_of_the_window,
				+height
				);
	}
}

// ~~

VOID GAME_CORE_ENGINE::CalculateViscosity( 
    const REAL32 delta_time  
	)
{
	PhysicsFluidEngine.CalculateViscosity(
		ParticleTable,
		PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius,
		delta_time
		);
}

// ~~

VOID GAME_CORE_ENGINE::CalculateSpringsForViscoelasticity(
    const REAL32 delta_time 
    )
{
	PhysicsFluidEngine.CalculateViscoElasticity(
		ParticleTable,
		PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius,
		PHSYICS_LEVEL_FLUID_Spring_Coefficient,
		PHSYICS_LEVEL_FLUID_Yield_Ratio,
		PHSYICS_LEVEL_FLUID_Plasticity,
		delta_time
		);
}

// ~~

VOID GAME_CORE_ENGINE::CalculatePlasticity(
	const REAL32 delta_time
	)
{
	PhysicsFluidEngine.CalculatePlasticity(
		ParticleTable,
		delta_time
		);
}
