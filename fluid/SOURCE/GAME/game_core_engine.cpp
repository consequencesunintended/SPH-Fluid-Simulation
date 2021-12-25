// -- LOCAL

// .. REFERENCES

#include "game_core_engine.h"
#include "physics_level_constants.h"
#include "physics_level_fluid_constants.h"

// -- CONSTANTS

constexpr float LOCAL_Margin_with_bottom_of_the_window = 1.0f;

// -- PUBLIC

// .. OPERATIONS

void GAME_CORE_ENGINE::Initialize(
	std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable,
	const float fluid_max_width,
	const float fluid_max_height
)
{
	PhysicsIntegrationEngine = new PHSYICS_INTEGRATION_PREDICTION_RELAXATION();
	FluidMaxHeight = fluid_max_height;
	FluidMaxWidth = fluid_max_width;
	InitialiseParticles( ParticleTable );
}

// ~~

void GAME_CORE_ENGINE::InitialiseParticles( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable )
{
	MATH_VECTOR_2D			position;
	PHYSICS_FLUID_PARTICLE	particle;
	unsigned int			particle_index;

	FluidPositionLoader.LoadPositions( "./DATA/position_map.bmp" );

	particle_index = 0;

	for ( auto& p_tb : FluidPositionLoader.PointTable )
	{
		particle.Position = p_tb;
		particle.OldPosition = particle.Position;
		ParticleTable.push_back( particle );
	}

	particle_index = 0;

	for ( auto& p_tb : ParticleTable )
	{
		ParticleTable[particle_index].ViscosityBeta = GAME_CORE_ENGINE_visocity_beta;
		ParticleTable[particle_index].ViscositySigma = GAME_CORE_ENGINE_visocity_sigma;
	}
	PhysicsFluidEngine.InitialiseSpringTable( (int)ParticleTable.size() );
}

// ~~

void GAME_CORE_ENGINE::Update(
	std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable,
	const float delta_time,
	const bool do_viscosity,
	const bool is_viscoelastic,
	const bool is_plastic
)
{
	int			delta_count;
	bool		ignore_delta_time;

#ifdef NDEBUG
	ignore_delta_time = false;
#else
	ignore_delta_time = true;
#endif

	DeltaValue += delta_time;
	delta_count = 0;

	if ( delta_time / GAME_CORE_ENGINE_delta_time_cap > 5.0f )
	{
		delta_count = int( delta_time / GAME_CORE_ENGINE_delta_time_cap - 5.0f );
	}

	if ( ignore_delta_time )
	{
		delta_count = 0;
	}

	if ( DeltaValue > GAME_CORE_ENGINE_delta_time_cap )
	{
		for ( int i = 0; i <= delta_count; i++ )
		{
			if ( is_viscoelastic )
			{
				CalculateSpringsForViscoelasticity( ParticleTable, GAME_CORE_ENGINE_delta_time_cap );
			}
			if ( is_plastic )
			{
				CalculatePlasticity( ParticleTable, GAME_CORE_ENGINE_delta_time_cap );
			}
			CalculateDensity( ParticleTable, GAME_CORE_ENGINE_delta_time_cap );
			CalculatePressureForce( ParticleTable, GAME_CORE_ENGINE_delta_time_cap );
			UpdateParticlesVelocityAndPosition( ParticleTable, GAME_CORE_ENGINE_delta_time_cap );
		}
		DeltaValue = 0.0f;
	}
}

// ~~

void GAME_CORE_ENGINE::ResetViscoelasticity( void )
{
	PhysicsFluidEngine.ResetSprings();
}

void GAME_CORE_ENGINE::InitialisePlasticity( void )
{
	PhysicsFluidEngine.InitialisePlasticity( ParticleTable, PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius, PHSYICS_LEVEL_FLUID_CONSTANTS_Spring_Coefficient );
}

// -- PRIVATE

// .. OPERATIONS

void GAME_CORE_ENGINE::CalculateDensity( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time )
{

	PhysicsFluidEngine.CalculateDensity( ParticleTable, PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius );
}

// ~~

void GAME_CORE_ENGINE::CalculatePressureForce( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time )
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

void GAME_CORE_ENGINE::UpdateParticlesVelocityAndPosition( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time )
{
	unsigned int	particle_index;
	float			attraction_radius;

	particle_index = 0;

	for ( auto& p_tb : ParticleTable )
	{
		PhysicsIntegrationEngine->UpdateVelocity( p_tb, delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor );
	}

	CalculateViscosity( ParticleTable, delta_time );

	particle_index = 0;

	for ( auto& p_tb : ParticleTable )
	{
		PhysicsIntegrationEngine->UpdatePosition( p_tb, delta_time * PHSYICS_FLUID_SPH_VISCOELASTIC_delta_time_scaling_factor );

		p_tb.Force = PHYSICS_LEVEL_CONSTANTS_Gravity;
	}
	DetectCollision( ParticleTable, FluidMaxWidth, FluidMaxHeight );

	particle_index = 0;
	attraction_radius = FluidMaxWidth / 4.0f;

	for ( auto& p_tb : ParticleTable )
	{
		PhysicsMouseInteraction.ApplyMouseBehaviour( p_tb, attraction_radius );
	}
}

// ~~

void GAME_CORE_ENGINE::DetectCollision( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float widht, const float height )
{
	unsigned int	particle_index;
	MATH_POINT_2D	position;

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

void GAME_CORE_ENGINE::CalculateViscosity( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time )
{
	PhysicsFluidEngine.CalculateViscosity( ParticleTable, PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius, delta_time );
}

// ~~

void GAME_CORE_ENGINE::CalculateSpringsForViscoelasticity( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time )
{
	PhysicsFluidEngine.CalculateViscoElasticity( ParticleTable,
												 PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius,
												 PHSYICS_LEVEL_FLUID_Spring_Coefficient,
												 PHSYICS_LEVEL_FLUID_Yield_Ratio,
												 PHSYICS_LEVEL_FLUID_Plasticity,
												 delta_time
	);
}

// ~~

void GAME_CORE_ENGINE::CalculatePlasticity( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time )
{
	PhysicsFluidEngine.CalculatePlasticity( ParticleTable, delta_time );
}
