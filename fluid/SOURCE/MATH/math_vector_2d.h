/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __MATH_VECTOR_2D__
	#define __MATH_VECTOR_2D__

    // -- LOCAL

    // .. REFERENCES

	#include "debug_statements.h"
	#include "fundamental_data_types.h"
	#include "math_square_root.h"

	// .. TYPES

	class MATH_VECTOR_2D
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		MATH_VECTOR_2D(
			VOID
			) :
			X( 0 ),
			Y( 0 )
		{	
		}

		// ~~
		
		MATH_VECTOR_2D(
			const REAL32 x_value
			) :
			X( x_value ),
			Y( x_value )
		{ 
		}

		// ~~

		MATH_VECTOR_2D(
			const REAL32 x_value, 
			const REAL32 y_value
			) :
			X( x_value ),
			Y( y_value )
		{ 
		}

		// ~~
		
		MATH_VECTOR_2D(
			const MATH_VECTOR_2D & other
			) :
			X( other.X ),
			Y( other.Y )
		{ 
		}

		// ~~

		virtual ~MATH_VECTOR_2D(
			VOID
			)
		{
		}

		// .. OPERATORS

		MATH_VECTOR_2D & operator =(
			const MATH_VECTOR_2D & other
			)
		{ 
			DEBUG_check_this_expression( this != &other );

			X = other.X; 
			Y = other.Y; 

			return *this;
		}

		// ~~

		MATH_VECTOR_2D operator +(
			const MATH_VECTOR_2D & other
			) const
		{ 
				return MATH_VECTOR_2D( X + other.X, Y + other.Y ); 
		}

		// ~~

		MATH_VECTOR_2D operator -(
			const MATH_VECTOR_2D & other
			) const 
		{ 
			return MATH_VECTOR_2D( X - other.X, Y - other.Y ); 
		}

		// ~~

		MATH_VECTOR_2D operator *(
			const MATH_VECTOR_2D & other
			) const
		{ 
				return MATH_VECTOR_2D( X * other.X, Y * other.Y ); 
		}

		// ~~

		MATH_VECTOR_2D operator /(
			const MATH_VECTOR_2D & other
			) const
		{ 
			return MATH_VECTOR_2D( X / other.X, Y / other.Y ); 
		}

		// ~~

		VOID operator +=(
			const MATH_VECTOR_2D & other
			) 
		{ 
			X += other.X; 
			Y += other.Y; 
		}

		// ~~

		VOID operator -=(
			const MATH_VECTOR_2D & other
			) 
		{ 
			X -= other.X; 
			Y -= other.Y; 
		}

		// ~~

		VOID operator *=(
			const MATH_VECTOR_2D & other
			) 
		{ 
			X *= other.X; 
			Y *= other.Y; 
		}

		// ~~

		VOID operator /=(
			const MATH_VECTOR_2D & other
			)
		{ 
			X /= other.X; 
			Y /= other.Y; 
		}

		// ~~

		BOOL operator ==(
			const MATH_VECTOR_2D & other
			)
		{ 
			return ( ( X == other.X ) && ( Y == other.Y ) ); 
		}

		// .. INQUIRIES

		REAL32 GetLength(
			VOID
			) const
		{ 
			return MATH_SQUARE_ROOT::GetSquareRoot( X * X + Y * Y ); 
		}

		// ~~

		REAL32 GetSquareLength(
			VOID
			) const
		{ 
			return ( X * X + Y * Y ); 
		}

		// ~~

		REAL32 GetDotProduct( 
			const MATH_VECTOR_2D & other 
			) const
		{
			return X * other.X + Y * other.Y;
		}

		// .. OPERATIONS

		VOID Assign(
			const REAL32 x_value,
			const REAL32 y_value
			)
		{
			X = x_value;
			Y = y_value;
		}
		
		// ~~

		void Reset(
			VOID
			)
		{
			X = 0.0f;
			Y = 0.0f;
		}

		// ~~

		BOOL normalise(
			VOID
			)
		{
			if ( GetLength() != 0.0f )
			{
				X = X / GetLength(); 
				Y = Y / GetLength();

				return true;
			}
			else
			{
				X = 0.0f; 
				Y = 0.0f;

				return false;
			}
		}

		// ~~

		VOID SetDifference(
			const MATH_VECTOR_2D & first,
			const MATH_VECTOR_2D & second
			)
		{
			X = second.X - first.X;
			Y = second.Y - first.Y;
		}

		// .. ATTRIBUTES

		REAL32 
			X,
			Y;
	};
#endif

