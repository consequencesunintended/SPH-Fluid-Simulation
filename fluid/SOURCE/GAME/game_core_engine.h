/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __GAME_CORE_ENGINE__
	#define	__GAME_CORE_ENGINE__

    // -- LOCAL

    // .. REFERENCES

    #include "fundamental_data_types.h"
    #include "math_vector_2d.h"
    #include "physics_entity.h"
    #include "physics_collision_2d.h"
    #include "physics_fluid_particle.h"
    #include "physics_fluid_particle_array.h"
	#include "physics_fluid_particle_position_loader.h"
    #include "physics_fluid_sph_viscoelastic.h"
	#include "physics_integration.h"
    #include "physics_integration_prediction_relaxation.h"
	#include "physics_mouse_interaction.h"
    #include "physics_spring.h"
    #include "physics_spring_array.h"

    // -- GLOBAL

    // .. CONSTANTS

    #define    GAME_CORE_ENGINE_visocity_sigma         0.001f           
    #define    GAME_CORE_ENGINE_visocity_beta          0.001f 
	#define    GAME_CORE_ENGINE_delta_time_cap		   0.01f

    // .. TYPES

    class GAME_CORE_ENGINE
    {
        // -- PUBLIC

    public:

        PHYSICS_FLUID_PARTICLE_ARRAY 
            ParticleTable;

		// .. CONSTRUCTORS

	    GAME_CORE_ENGINE(
			VOID
			):
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

		virtual ~GAME_CORE_ENGINE(
			VOID
			)
		{
			delete PhysicsIntegrationEngine;
		}

		// ~~

	    GAME_CORE_ENGINE(
			const GAME_CORE_ENGINE & other
			) :
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

		GAME_CORE_ENGINE & operator=(
			const GAME_CORE_ENGINE & other
			)
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

	    VOID SetMouse( 
            const BOOL attract, 
            const BOOL repel 
			)
	    {
			PhysicsMouseInteraction.SetMouse( attract, repel );
	    }

        // ~~

	    VOID SetAttractor( 
            const MATH_VECTOR_2D &attractor 
            )
	    {
			PhysicsMouseInteraction.SetAttractor( attractor );
	    }

        // .. OPERATIONS

	    VOID Initialize(
		    const REAL32 fluid_max_width, 
            const REAL32 fluid_max_height  
            );


        // ~~

        VOID Update(
            const REAL32 delta_time,
            const BOOL do_viscosity,
            const BOOL is_viscoelastic,
            const BOOL is_plastic
            );

        // ~~

        VOID ResetViscoelasticity(
            VOID
            );

		// ~~

		VOID InitialisePlasticity(
			VOID
			);

        // -- PRIVATE

    private:

        // .. OPERATIONS

	    VOID InitialiseParticles( 
            VOID 
            );

        // ~~

	    VOID CalculateDensity( 
            const REAL32 delta_time 
            );

        // ~~

	    VOID CalculatePressureForce( 
            const REAL32 delta_time  
            );

         // ~~

	    VOID UpdateParticlesVelocityAndPosition( 
            const REAL32 delta_time  
            );

         // ~~

	    VOID DetectCollision( 
            const REAL32 width, REAL32 height 
            );

         // ~~

	    VOID CalculateViscosity( 
            const REAL32 delta_time  
            );

         // ~~

	    VOID CalculateSpringsForViscoelasticity( 
            const REAL32 delta_time  
            );

		// ~~

		VOID CalculatePlasticity(
			const REAL32 delta_time
			);

        // .. ATTRIBUTES

		PHYSICS_FLUID_PARTICLE_POSITION_LOADER
			FluidPositionLoader;
	    PHYSICS_COLLISION_2D 
		    PhysicsCollision2DEngine;
	    PHSYICS_FLUID_SPH_VISCOELASTIC 
		    PhysicsFluidEngine;
	    PHYSICS_INTEGRATION 
		    * PhysicsIntegrationEngine;
	    PHYSICS_SPRING_ARRAY 
		    SpringTable;
		PHYSICS_MOUSE_INTERACTION
			PhysicsMouseInteraction;
	    REAL32
		    FluidMaxWidth,
		    FluidMaxHeight,
			DeltaValue;
    };
#endif