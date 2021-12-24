#ifndef __MATH_SQUARE_ROOT__
#define __MATH_SQUARE_ROOT__

#include <stdint.h>

class MATH_SQUARE_ROOT
{
	// -- PUBLIC

public:

	// .. CONSTRUCTORS

	MATH_SQUARE_ROOT(
		void
		)
	{
	}

	// ~~

	MATH_SQUARE_ROOT(
		MATH_SQUARE_ROOT & other
		)
	{
	}

	// ~~

	virtual ~MATH_SQUARE_ROOT(
		void
		)
	{
	}

	// .. OPERATORS

	MATH_SQUARE_ROOT & operator=(
		const MATH_SQUARE_ROOT & other
		)
	{
		return *this;
	}

	// .. FUNCTIONS

	// The Code and Algorithm used here is
	// based on :
	// http://ilab.usc.edu/wiki/index.php/Fast_Square_Root
	// this method is faster than the normal square root
	// used in the standard library.

	static float GetSquareRoot( const float value )
	{
		union
		{
			int i;
			float value;
		} u;
		u.value = value;
		u.i = ( 1 << 29 ) + ( u.i >> 1 ) - ( 1 << 22 ); 
		return u.value;
	}

	static float invSquareRoot( const float value)
	{
		union {
			float f;
			uint32_t i;
		} conv;

		float x2;
		const float threehalfs = 1.5F;

		x2 = value * 0.5F;
		conv.f = value;
		conv.i = 0x5f3759df - (conv.i >> 1);
		conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
		return conv.f;
	}
};
#endif