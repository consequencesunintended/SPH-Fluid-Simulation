/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHYSICS_MOUSE_INTERACTION__
	#define __PHYSICS_MOUSE_INTERACTION__

	// -- LOCAL

	// .. REFERENCES

	#include "fundamental_data_types.h"
	#include "math_vector_2d.h"
	#include "physics_fluid_particle_array.h"
	#include "physics_entity.h"

	// -- GLOBAL

	class PHYSICS_MOUSE_INTERACTION
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		PHYSICS_MOUSE_INTERACTION(
			VOID
			) :
			MouseAttractorVector( MATH_VECTOR_2D( 999.0f, 999.0f ) )
		{
		}

		// ~~

		virtual ~PHYSICS_MOUSE_INTERACTION(
			VOID
			)
		{
		}

		// ~~

		PHYSICS_MOUSE_INTERACTION(
			PHYSICS_MOUSE_INTERACTION & other
			) :
			MouseAttractorVector( other.MouseAttractorVector )
		{
		}

        // .. ACCESSORS

	    VOID SetMouse( 
            const  BOOL attract, 
            const BOOL repel )
	    {
		    IsAttracting = attract;
		    IsRepelling = repel;
	    }

        // ~~

	    VOID SetAttractor( 
            const MATH_VECTOR_2D &attractor 
            )
	    {
		    MouseAttractorVector =  attractor;
	    }

		// .. OPERATIONS

		// It applies the ineraction of mouse according to the 
		// position of the attractor a circular force to the 
		// game_entity with a maximum radius of max_dis_attractor.

		VOID ApplyMouseBehaviour(
			PHYSICS_ENTITY & game_entity,
			const REAL32 max_dis_attractor
			);

		// -- PRIVATE

	private:	

		// .. ATTRIBUTES

	    BOOL 
		    IsAttracting,
		    IsRepelling;
		MATH_VECTOR_2D 
		    MouseAttractorVector;
	};
#endif