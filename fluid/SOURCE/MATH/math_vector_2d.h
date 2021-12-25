#pragma once

#include "math_square_root.h"

#include <math.h>  
#include <assert.h>

class MATH_VECTOR_2D
{

public:
	MATH_VECTOR_2D(void) :
		X(0),
		Y(0)
	{
	}

	MATH_VECTOR_2D(const float x_value) :
		X(x_value),
		Y(x_value)
	{
	}

	// ~~

	MATH_VECTOR_2D(const float x_value, const float y_value) :
		X(x_value),
		Y(y_value)
	{
	}

	MATH_VECTOR_2D& operator =(const MATH_VECTOR_2D& other)
	{
		X = other.X;
		Y = other.Y;

		return *this;
	}

	MATH_VECTOR_2D operator +(const MATH_VECTOR_2D& other) const
	{
		return MATH_VECTOR_2D(X + other.X, Y + other.Y);
	}

	MATH_VECTOR_2D operator -(const MATH_VECTOR_2D& other) const
	{
		return MATH_VECTOR_2D(X - other.X, Y - other.Y);
	}

	MATH_VECTOR_2D operator *(const MATH_VECTOR_2D& other) const
	{
		return MATH_VECTOR_2D(X * other.X, Y * other.Y);
	}

	MATH_VECTOR_2D operator /(const MATH_VECTOR_2D& other) const
	{
		return MATH_VECTOR_2D(X / other.X, Y / other.Y);
	}

	void operator +=(const MATH_VECTOR_2D& other)
	{
		X += other.X;
		Y += other.Y;
	}

	void operator -=(const MATH_VECTOR_2D& other)
	{
		X -= other.X;
		Y -= other.Y;
	}

	void operator *=(const MATH_VECTOR_2D& other)
	{
		X *= other.X;
		Y *= other.Y;
	}

	void operator /=(const MATH_VECTOR_2D& other)
	{
		X /= other.X;
		Y /= other.Y;
	}

	bool operator ==(const MATH_VECTOR_2D& other)
	{
		return ((X == other.X) && (Y == other.Y));
	}

	float GetLength(void) const
	{
		return float(sqrt(X * X + Y * Y));
	}

	float GetReciprocalLength(
		void
	) const
	{
		return float(MATH_SQUARE_ROOT::invSquareRoot(X * X + Y * Y));
	}

	float GetSquareLength(void) const
	{
		return (X * X + Y * Y);
	}

	float GetDotProduct(const MATH_VECTOR_2D& other) const
	{
		return X * other.X + Y * other.Y;
	}

	void Assign(const float x_value, const float y_value)
	{
		X = x_value;
		Y = y_value;
	}

	void Reset(void)
	{
		X = 0.0f;
		Y = 0.0f;
	}

	bool normalise(void)
	{
		if (GetLength() != 0.0f)
		{
			const float	inv_length = GetReciprocalLength();
			const float	x = X * inv_length;
			const float	y = Y * inv_length;

			X = x;
			Y = y;

			return true;
		}
		else
		{
			X = 0.0f;
			Y = 0.0f;

			return false;
		}
	}

	void SetDifference(const MATH_VECTOR_2D& first, const MATH_VECTOR_2D& second)
	{
		X = second.X - first.X;
		Y = second.Y - first.Y;
	}
	void RotateD(float degree)
	{
		const float radius = 3.14f * degree / 180.0f;

		RotateR(radius);
	}
	void RotateR(float radius)
	{
		float new_x = cosf(radius) * X - sinf(radius) * Y;
		float new_y = sinf(radius) * X + cosf(radius) * Y;

		X = new_x;
		Y = new_y;
	}

	void Translate(const MATH_VECTOR_2D& translation_vector)
	{
		X += translation_vector.X;
		Y += translation_vector.Y;
	}

	float X;
	float Y;
};

typedef MATH_VECTOR_2D MATH_POINT_2D;


