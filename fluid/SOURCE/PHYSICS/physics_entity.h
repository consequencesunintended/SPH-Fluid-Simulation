#ifndef __PHYSICS_ENTITY__
#define __PHYSICS_ENTITY__

// -- LOCAL
	
// .. REFERENCES

#include "math_vector_2d.h"
#include <assert.h>

// -- GLOBAL

// .. TYPES

class PHYSICS_ENTITY
{
	// -- PUBLIC

public:

	// .. CONSTRUCTORS

	PHYSICS_ENTITY(
		void
		) :
		Position( 0.0f ),
		OldPosition( 0.0f ),
		Velocity( 0.0f ),
		Force( 0.0f )
	{
	}

	// ~~

	virtual ~PHYSICS_ENTITY(
		void
		)
	{
	}

	// ~~

	PHYSICS_ENTITY(
		const PHYSICS_ENTITY & other
		) :
		Position( other.Position ),
		OldPosition( other.OldPosition ),
		Velocity( other.Velocity ),
		Force( other.Force )
	{
	}

	// .. OPERATORS

	const PHYSICS_ENTITY & operator=(
		const PHYSICS_ENTITY & other
		)
	{
		assert( this != &other );

		Position = other.Position;
		OldPosition = other.OldPosition;
		Velocity = other.Velocity;
		Force = other.Force;

		return *this;
	}

	// .. ACCESSORS

	const MATH_VECTOR_2D & GetPosition(
		void
		) const
	{
		return Position;
	}

	// ~~

	void SetPosition(
		const MATH_VECTOR_2D & position
		)
	{
		Position = position;
	}

	// ~~

	const MATH_VECTOR_2D & GetForce(
		void
		) const
	{
		return Force;
	}

	// ~~

	void SetForce(
		const MATH_VECTOR_2D & force
		)
	{
		Force = force;
	}

	// .. OPERATIONS

	void AccumalateForce(
		const MATH_VECTOR_2D & force
		)
	{
		Force += force;
	}

	// ~~

	const MATH_VECTOR_2D & GetVelocity(
		void
		) const
	{
		return Velocity;
	}

	// ~~

	void SetVelocity(
		const MATH_VECTOR_2D & velocity
		)
	{
		Velocity = velocity;
	}

	// ~~

	const MATH_VECTOR_2D & GetOldPosition(
		void
		) const
	{
		return OldPosition;
	}

	// ~~

	void SetOldPosition(
		const MATH_VECTOR_2D & old_position
		)
	{
		OldPosition = old_position;
	}

	// -- PROTECTED

protected:

	// .. ATTRIBUTES

	MATH_VECTOR_2D
		Velocity,
		Position,
		Force,
		OldPosition;
};
#endif