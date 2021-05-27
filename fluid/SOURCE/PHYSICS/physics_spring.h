/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHYSICS_SPRING__
	#define __PHYSICS_SPRING__

	// -- LOCAL
	
	// .. REFERENCES

	#include "physics_entity.h"
	#include "fundamental_data_types.h"
    #include "debug_statements.h"
	
	// -- GLOBAL

	// .. TYPES

	class PHYSICS_SPRING
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		PHYSICS_SPRING(
			VOID
			) :
			Point1Index( 0 ),
			Point2Index(0 ),
			RestLength( 0.0f ),
			Coefficient( 0.0f )
		{
		}

		// ~~

		PHYSICS_SPRING(
			const PHYSICS_SPRING &other
			) :
			Point1Index( other.Point1Index),
			Point2Index( other.Point2Index),
			RestLength( other.RestLength ),
			Coefficient( other.Coefficient )
		{
		}

		// ~~

		virtual ~PHYSICS_SPRING(
			VOID
			)
		{
		}

		// .. OPERATORS

		PHYSICS_SPRING & operator=(
			const PHYSICS_SPRING & other
			)
		{
            DEBUG_check_this_expression( this != &other );

			Point1Index = other.Point1Index;
			Point2Index = other.Point2Index;
			RestLength = other.RestLength;
			Coefficient = other.Coefficient;

			return *this;
		}

		// .. ACCESSORS

		INT32 GetPoint1Index(
			VOID
			) const
		{
			return Point1Index;
		}

		// ~~

		VOID SetPoint1Index(
			INT32 point1_index
			)
		{
			Point1Index = point1_index;
		}

		// ~~

		INT32 GetPoint2Index(
			VOID
			) const
		{
			return Point2Index;
		}

		// ~~

		VOID SetPoint2Index(
			INT32 point2_index
			)
		{
			Point2Index = point2_index;
		}

		// ~~

		REAL32 GetRestLength(
			VOID
			) const
		{
			return RestLength;
		}

		// ~~

		VOID SetCoefficient(
			const REAL32 coefficient
			)
		{
			Coefficient = coefficient;
		}

		// ~~

		REAL32 GetCoefficient(
			VOID
			) const
		{
			return Coefficient;
		}

		// ~~

		VOID SetCoefficientOfDamping(
			const REAL32 coefficientOfDamping
			)
		{
			CoefficientOfDamping = CoefficientOfDamping;
		}

		// ~~

		REAL32 GetCoefficientOfDamping(
			VOID
			) const
		{
			return CoefficientOfDamping;
		}

		// ~~

		VOID SetRestLength(
			const REAL32 rest_length
			)
		{
			RestLength = rest_length;
		}

		// .. FUNCTIONS

		static 	VOID CalculateForce(
			MATH_VECTOR_2D & force,
			const PHYSICS_SPRING & spring,
			const PHYSICS_ENTITY & point1,
			const PHYSICS_ENTITY & point2
			);

		// -- PRIVATE

	private:

		// .. ATTRIBUTES
		INT32
			Point1Index,
			Point2Index;
		REAL32
			RestLength,
			Coefficient,
			CoefficientOfDamping;
	};
#endif