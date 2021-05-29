// -- LOCAL

// .. REFERENCES

#include "game_core_engine.h"
#include "physics_level_constants.h"
#include "physics_level_fluid_constants.h"

// -- CONSTANTS

#define LOCAL_Margin_with_bottom_of_the_window 1.0f

// -- PUBLIC

// .. OPERATIONS

void GAME_CORE_ENGINE::Initialize( 
    const float fluid_max_width,
    const float fluid_max_height
    )
{
	PhysicsIntegrationEngine = new PHSYICS_INTEGRATION_PREDICTION_RELAXATION();
	FluidMaxHeight = fluid_max_height;
	FluidMaxWidth = fluid_max_width;
	InitialiseParticles();
}

// ~~

void GAME_CORE_ENGINE::InitialiseParticles(
	void
    )
{
    MATH_VECTOR_2D 
        position;
    PHYSICS_FLUID_PARTICLE 
        particle;
    unsigned int
        particle_index;

	FluidPositionLoader.LoadPositions(
		"./DATA/position_map.bmp"
		);

    particle_index = 0;

	for( auto &p_tb: FluidPositionLoader.GetPointTable() )
	{
		particle.SetPosition( p_tb );
		particle.SetOldPosition( particle.GetPosition() );
		ParticleTable.push_back( particle );
	}

    particle_index = 0;

	for ( auto& p_tb : ParticleTable )
    {
	    ParticleTable[ particle_index ].SetViscosityBeta( GAME_CORE_ENGINE_visocity_beta );
	    ParticleTable[ particle_index ].SetViscositySigma( GAME_CORE_ENGINE_visocity_sigma );
    }
	PhysicsFluidEngine.InitialiseSpringTable( ParticleTable.size() );
}

// ~~

void GAME_CORE_ENGINE::Update(
    const float delta_time,
    const bool do_viscosity,
    const bool is_viscoelastic,
    const bool is_plastic
    )
{
	int
		counter,
		counter2;

	DeltaValue += delta_time;
	counter = 0;

	if ( delta_time / GAME_CORE_ENGINE_delta_time_cap > 5.0f )
	{
		counter = int( delta_time / GAME_CORE_ENGINE_delta_time_cap - 5.0f );
	}

	if ( DeltaValue > GAME_CORE_ENGINE_delta_time_cap )
	{
		for ( counter2 = 0; counter2 <= counter; counter2++ )
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

void GAME_CORE_ENGINE::ResetViscoelasticity(
    void
    )
{
    PhysicsFluidEngine.ResetSprings();
}

void GAME_CORE_ENGINE::InitialisePlasticity(
	void
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

void GAME_CORE_ENGINE::CalculateDensity( 
	const float delta_time  
	)
{

	PhysicsFluidEngine.CalculateDensity(
		ParticleTable,
		PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius
		);
}

// ~~

void GAME_CORE_ENGINE::CalculatePressureForce( 
    const float delta_time  
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

void GAME_CORE_ENGINE::UpdateParticlesVelocityAndPosition( 
    const float delta_time  
    )
{
	unsigned int 
		particle_index;
	float
		attraction_radius;

	particle_index = 0;

	for ( auto& p_tb : ParticleTable )
	{
		PhysicsIntegrationEngine->UpdateVelocity(
			p_tb,
			delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor
			);
	}

	CalculateViscosity(
		delta_time
		);

	particle_index = 0;

	for ( auto& p_tb : ParticleTable )
	{
		PhysicsIntegrationEngine->UpdatePosition(
			p_tb,
			delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor
			);

		p_tb.SetForce( PHYSICS_LEVEL_CONSTANTS_Gravity );
	}
	DetectCollision( FluidMaxWidth, FluidMaxHeight );

	particle_index = 0;
	attraction_radius = FluidMaxWidth / 4.0f;

	for ( auto& p_tb : ParticleTable )
	{
		PhysicsMouseInteraction.ApplyMouseBehaviour( p_tb, attraction_radius );
	}
}

// ~~

void GAME_CORE_ENGINE::DetectCollision( 
    const float widht, 
    const float height  
    )
{
	unsigned int
		particle_index;
	MATH_POINT_2D
		position;

	particle_index = 0;
	position.Assign( 0.0f, 0.0f );

	for ( auto& p_tb : ParticleTable )
	{
			PhysicsCollision2DEngine.CheckForWall( 
				p_tb,
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

void GAME_CORE_ENGINE::CalculateViscosity( 
    const float delta_time  
	)
{
	PhysicsFluidEngine.CalculateViscosity(
		ParticleTable,
		PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius,
		delta_time
		);
}

// ~~

void GAME_CORE_ENGINE::CalculateSpringsForViscoelasticity(
    const float delta_time 
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

void GAME_CORE_ENGINE::CalculatePlasticity(
	const float delta_time
	)
{
	PhysicsFluidEngine.CalculatePlasticity(
		ParticleTable,
		delta_time
		);
}
