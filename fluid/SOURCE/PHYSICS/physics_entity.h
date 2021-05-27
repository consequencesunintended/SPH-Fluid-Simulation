/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHYSICS_ENTITY__
	#define __PHYSICS_ENTITY__

	// -- LOCAL
	
	// .. REFERENCES

	#include "fundamental_data_types.h"
	#include "math_vector_2d.h"
	#include "debug_statements.h"
	
	// -- GLOBAL

	// .. TYPES

	class PHYSICS_ENTITY
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		PHYSICS_ENTITY(
			VOID
			) :
			Position( 0.0f ),
			OldPosition( 0.0f ),
			Velocity( 0.0f ),
			Force( 0.0f )
		{
		}

		// ~~

		virtual ~PHYSICS_ENTITY(
			VOID
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
			DEBUG_check_this_expression( this != &other );

			Position = other.Position;
			OldPosition = other.OldPosition;
			Velocity = other.Velocity;
			Force = other.Force;

			return *this;
		}

		// .. ACCESSORS

		const MATH_VECTOR_2D & GetPosition(
			VOID
			) const
		{
			return Position;
		}

		// ~~

		VOID SetPosition(
			const MATH_VECTOR_2D & position
			)
		{
			Position = position;
		}

		// ~~

		const MATH_VECTOR_2D & GetForce(
			VOID
			) const
		{
			return Force;
		}

		// ~~

		VOID SetForce(
			const MATH_VECTOR_2D & force
			)
		{
			Force = force;
		}

		// .. OPERATIONS

		VOID AccumalateForce(
			const MATH_VECTOR_2D & force
			)
		{
			Force += force;
		}

		// ~~

		const MATH_VECTOR_2D & GetVelocity(
			VOID
			) const
		{
			return Velocity;
		}

		// ~~

		VOID SetVelocity(
			const MATH_VECTOR_2D & velocity
			)
		{
			Velocity = velocity;
		}

		// ~~

		const MATH_VECTOR_2D & GetOldPosition(
			VOID
			) const
		{
			return OldPosition;
		}

		// ~~

		VOID SetOldPosition(
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