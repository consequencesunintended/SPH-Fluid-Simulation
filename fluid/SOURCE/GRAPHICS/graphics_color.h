#ifndef __GRAPHICS_COLOR__
#define __GRAPHICS_COLOR__

// -- LOCAL

// .. REFERENCES

#include "fundamental_data_types.h"


// -- GLOBAL

// .. TYPES

class GRAPHICS_COLOR 
{
	// -- PUBLIC

public:

	// .. CONSTRCUTORS

	GRAPHICS_COLOR(
		void
		) 
	{ 
		Assign(0.0, 0.0, 0.0, 0.0);
	}

	// ~~

	virtual ~GRAPHICS_COLOR(
		void
		)
	{
	}

	// ~~

	GRAPHICS_COLOR(
		const FLOAT r, 
		const FLOAT g, 
		const FLOAT b, 
		const FLOAT a
		) 
	{
		Assign(r, g, b, a);
	}

	// ~~

	GRAPHICS_COLOR( 
		const FLOAT * rgba 
		) 
	{
		Assign( rgba[0], rgba[1], rgba[2], rgba[3] );
	}

	// ~~

	GRAPHICS_COLOR(
		const GRAPHICS_COLOR & other 
		) 
	{
		RGBA[ 0 ] = other.RGBA[ 0 ];
		RGBA[ 1 ] = other.RGBA[ 1 ];
		RGBA[ 2 ] = other.RGBA[ 2 ];
		RGBA[ 3 ] = other.RGBA[ 3 ];
	}

	// .. OPERATORS

	GRAPHICS_COLOR & operator=(
		const GRAPHICS_COLOR & other 
		)
	{
		assert( this != &other );

		RGBA[ 0 ] = other.RGBA[ 0 ];
		RGBA[ 1 ] = other.RGBA[ 1 ];
		RGBA[ 2 ] = other.RGBA[ 2 ];
		RGBA[ 3 ] = other.RGBA[ 3 ];

		return *this;
	}

	// ~~

	const FLOAT & operator[](
		unsigned int index 
		) const
	{
		return RGBA[index];
	}

	// ~~

	FLOAT & operator [](
		unsigned int index 
		)
	{
		return RGBA[index];
	}

	// .. ACCESSORS

	const FLOAT * GetRGBA(
		void
		) const 
	{
		return RGBA;
	}

	// .. OPERATIONS

	void Assign( 
		const FLOAT r, 
		const FLOAT g, 
		const FLOAT b, 
		const FLOAT a 
		) 
	{
		RGBA[ 0 ] = r;
		RGBA[ 1 ] = g;
		RGBA[ 2 ] = b;
		RGBA[ 3 ] = a;
	}

	// .. FUNCTIONS

	static GRAPHICS_COLOR Black(
		void
		)
	{
		return GRAPHICS_COLOR( 0.0f, 0.0f, 0.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOR Grey(
		void
		) 
	{
		return GRAPHICS_COLOR( 0.5f, 0.5f, 0.5f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOR White(
		void
		)
	{
		return GRAPHICS_COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOR Red(
		void
		) 
	{
		return GRAPHICS_COLOR( 1.0f, 0.0f, 0.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOR Green(
		void
		) 
	{
		return GRAPHICS_COLOR( 0.0f, 1.0f, 0.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOR Blue(
		void
		) 
	{
		return GRAPHICS_COLOR( 0.0f, 0.0f, 1.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOR Yellow(
		void
		) 
	{
		return GRAPHICS_COLOR( 1.0f, 1.0f, 0.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOR Brown(
		void
		) 
	{
		return GRAPHICS_COLOR( 0.2f, 0.1f, 0.1f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOR Null(
		void
		) 
	{
		return GRAPHICS_COLOR( 0.0f, 0.0f, 0.0f, 0.0f );
	}

	// -- PRIVATE

private:

	// .. ATTRIBUTES

	FLOAT RGBA[ 4 ];
};
#endif


