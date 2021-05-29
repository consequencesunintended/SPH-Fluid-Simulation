#ifndef __PHYSICS_SPRING__
#define __PHYSICS_SPRING__

// -- LOCAL
	
// .. REFERENCES

#include "physics_entity.h"
#include "fundamental_data_types.h"
#include <assert.h>

// -- GLOBAL

// .. TYPES

class PHYSICS_SPRING
{
	// -- PUBLIC

public:

	// .. CONSTRUCTORS

	PHYSICS_SPRING(
		void
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
		void
		)
	{
	}

	// .. OPERATORS

	PHYSICS_SPRING & operator=(
		const PHYSICS_SPRING & other
		)
	{
		assert( this != &other );

		Point1Index = other.Point1Index;
		Point2Index = other.Point2Index;
		RestLength = other.RestLength;
		Coefficient = other.Coefficient;

		return *this;
	}

	// .. ACCESSORS

	int GetPoint1Index(
		void
		) const
	{
		return Point1Index;
	}

	// ~~

	void SetPoint1Index(
		int point1_index
		)
	{
		Point1Index = point1_index;
	}

	// ~~

	int GetPoint2Index(
		void
		) const
	{
		return Point2Index;
	}

	// ~~

	void SetPoint2Index(
		int point2_index
		)
	{
		Point2Index = point2_index;
	}

	// ~~

	float GetRestLength(
		void
		) const
	{
		return RestLength;
	}

	// ~~

	void SetCoefficient(
		const float coefficient
		)
	{
		Coefficient = coefficient;
	}

	// ~~

	float GetCoefficient(
		void
		) const
	{
		return Coefficient;
	}

	// ~~

	void SetCoefficientOfDamping(
		const float coefficientOfDamping
		)
	{
		CoefficientOfDamping = CoefficientOfDamping;
	}

	// ~~

	float GetCoefficientOfDamping(
		void
		) const
	{
		return CoefficientOfDamping;
	}

	// ~~

	void SetRestLength(
		const float rest_length
		)
	{
		RestLength = rest_length;
	}

	// .. FUNCTIONS

	static 	void CalculateForce(
		MATH_VECTOR_2D & force,
		const PHYSICS_SPRING & spring,
		const PHYSICS_ENTITY & point1,
		const PHYSICS_ENTITY & point2
		);

	// -- PRIVATE

private:

	// .. ATTRIBUTES
	int
		Point1Index,
		Point2Index;
	float
		RestLength,
		Coefficient,
		CoefficientOfDamping;
};
#endif