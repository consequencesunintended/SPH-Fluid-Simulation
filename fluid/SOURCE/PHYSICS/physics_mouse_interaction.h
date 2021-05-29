#ifndef __PHYSICS_MOUSE_INTERACTION__
#define __PHYSICS_MOUSE_INTERACTION__

// -- LOCAL

// .. REFERENCES

#include "math_vector_2d.h"
#include "physics_entity.h"

// -- GLOBAL

class PHYSICS_MOUSE_INTERACTION
{
	// -- PUBLIC

public:

	// .. CONSTRUCTORS

	PHYSICS_MOUSE_INTERACTION(
		void
		) :
		MouseAttractorVector( MATH_VECTOR_2D( 999.0f, 999.0f ) )
	{
	}

	// ~~

	virtual ~PHYSICS_MOUSE_INTERACTION(
		void
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

	void SetMouse( 
        const  bool attract, 
        const bool repel )
	{
		IsAttracting = attract;
		IsRepelling = repel;
	}

    // ~~

	void SetAttractor( 
        const MATH_VECTOR_2D &attractor 
        )
	{
		MouseAttractorVector =  attractor;
	}

	// .. OPERATIONS

	// It applies the ineraction of mouse according to the 
	// position of the attractor a circular force to the 
	// game_entity with a maximum radius of max_dis_attractor.

	void ApplyMouseBehaviour(
		PHYSICS_ENTITY & game_entity,
		const float max_dis_attractor
		);

	// -- PRIVATE

private:	

	// .. ATTRIBUTES

	bool 
		IsAttracting,
		IsRepelling;
	MATH_VECTOR_2D 
		MouseAttractorVector;
};
#endif