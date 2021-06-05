
#ifndef __GAME_CORE_ENGINE__
#define	__GAME_CORE_ENGINE__

// -- LOCAL

// .. REFERENCES

#include "math_vector_2d.h"
#include "physics_entity.h"
#include "physics_collision_2d.h"
#include "physics_fluid_particle.h"
#include "physics_fluid_particle_position_loader.h"
#include "physics_fluid_sph_viscoelastic.h"
#include "physics_integration.h"
#include "physics_integration_prediction_relaxation.h"
#include "physics_mouse_interaction.h"
#include "physics_spring.h"
#include "physics_spring_array.h"

// -- GLOBAL

// .. CONSTANTS

constexpr float   GAME_CORE_ENGINE_visocity_sigma = 0.001f;           
constexpr float   GAME_CORE_ENGINE_visocity_beta = 0.001f; 
constexpr float   GAME_CORE_ENGINE_delta_time_cap = 0.01f;

// .. TYPES

class GAME_CORE_ENGINE
{
    // -- PUBLIC

public:

    std::vector<PHYSICS_FLUID_PARTICLE> ParticleTable;

	// .. CONSTRUCTORS

	GAME_CORE_ENGINE( void ):
		FluidPositionLoader( PHYSICS_FLUID_PARTICLE_POSITION_LOADER() ),
		PhysicsCollision2DEngine( PHYSICS_COLLISION_2D() ), 
		PhysicsFluidEngine( PHSYICS_FLUID_SPH_VISCOELASTIC() ),
		PhysicsIntegrationEngine( 0 ),
		SpringTable( PHYSICS_SPRING_ARRAY() ),
		FluidMaxWidth( 0.0f ),
		FluidMaxHeight( 0.0f ),
		DeltaValue( 0.0f )
	{
	}

	// ~~

	virtual ~GAME_CORE_ENGINE( void )
	{
		delete PhysicsIntegrationEngine;
	}

	// ~~

	GAME_CORE_ENGINE( const GAME_CORE_ENGINE & other ) :
		FluidPositionLoader( other.FluidPositionLoader ),
		PhysicsCollision2DEngine( other.PhysicsCollision2DEngine ), 
		PhysicsFluidEngine( other.PhysicsFluidEngine ),
		PhysicsIntegrationEngine( other.PhysicsIntegrationEngine ),
		SpringTable( other.SpringTable ),
		FluidMaxWidth( other.FluidMaxWidth ),
		FluidMaxHeight( other.FluidMaxHeight ),
		DeltaValue( other.DeltaValue )
	{
	}

	// .. OPERATORS

	GAME_CORE_ENGINE & operator=( const GAME_CORE_ENGINE & other )
	{
		FluidPositionLoader = other.FluidPositionLoader;
		PhysicsCollision2DEngine = other.PhysicsCollision2DEngine; 
		PhysicsFluidEngine = other.PhysicsFluidEngine;
		PhysicsIntegrationEngine = other.PhysicsIntegrationEngine;
		SpringTable = other.SpringTable;
		FluidMaxWidth = other.FluidMaxWidth;
		FluidMaxHeight = other.FluidMaxHeight;
		DeltaValue = other.DeltaValue;
	}

    // ~~

	void SetMouse( const bool attract, const bool repel )
	{
		PhysicsMouseInteraction.SetMouse( attract, repel );
	}

    // ~~

	void SetAttractor( const MATH_VECTOR_2D &attractor )
	{
		PhysicsMouseInteraction.SetAttractor( attractor );
	}

    // .. OPERATIONS

	void Initialize( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float fluid_max_width, const float fluid_max_height );


    // ~~

    void Update(
		std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable,
        const float delta_time,
        const bool do_viscosity,
        const bool is_viscoelastic,
        const bool is_plastic
        );

    // ~~

    void ResetViscoelasticity( void );

	// ~~

	void InitialisePlasticity( void );

    // -- PRIVATE

private:

    // .. OPERATIONS

	void InitialiseParticles( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable );

    // ~~

	void CalculateDensity( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time );

    // ~~

	void CalculatePressureForce( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time );

        // ~~

	void UpdateParticlesVelocityAndPosition( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time  );

        // ~~

	void DetectCollision( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float width, float height );

        // ~~

	void CalculateViscosity( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time );

        // ~~

	void CalculateSpringsForViscoelasticity( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time );

	// ~~

	void CalculatePlasticity( std::vector<PHYSICS_FLUID_PARTICLE>& ParticleTable, const float delta_time );

    // .. ATTRIBUTES

	PHYSICS_FLUID_PARTICLE_POSITION_LOADER	FluidPositionLoader;
	PHYSICS_COLLISION_2D					PhysicsCollision2DEngine;
	PHSYICS_FLUID_SPH_VISCOELASTIC			PhysicsFluidEngine;
	PHYSICS_INTEGRATION*					PhysicsIntegrationEngine;
	PHYSICS_SPRING_ARRAY					SpringTable;
	PHYSICS_MOUSE_INTERACTION				PhysicsMouseInteraction;	
	float									FluidMaxWidth;
	float									FluidMaxHeight;
	float									DeltaValue;
};
#endif