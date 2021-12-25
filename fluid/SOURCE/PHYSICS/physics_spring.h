#ifndef __PHYSICS_SPRING__
#define __PHYSICS_SPRING__


#include "physics_entity.h"
#include <assert.h>

struct PHYSICS_SPRING
{
	static 	void CalculateForce(
		MATH_VECTOR_2D & force,
		const PHYSICS_SPRING & spring,
		const PHYSICS_ENTITY & point1,
		const PHYSICS_ENTITY & point2
		);

	size_t	Point1Index;
	size_t	Point2Index;
	float	RestLength;
	float	Coefficient;
	float	CoefficientOfDamping;
};
#endif