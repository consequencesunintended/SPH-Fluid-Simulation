#include "physics_spring.h"

// -- PUBLIC

// .. OPERATIONS

void PHYSICS_SPRING::CalculateForce(
	MATH_VECTOR_2D& force,
	const PHYSICS_SPRING& spring,
	const PHYSICS_ENTITY& point1,
	const PHYSICS_ENTITY& point2
)
{
	MATH_VECTOR_2D	vector_between_point1_and_point2;
	float			current_length;

	vector_between_point1_and_point2.SetDifference( point1.Position, point2.Position );

	current_length = vector_between_point1_and_point2.GetLength();
	vector_between_point1_and_point2.normalise();

	force = vector_between_point1_and_point2 * (spring.RestLength - current_length) * spring.Coefficient;
}
