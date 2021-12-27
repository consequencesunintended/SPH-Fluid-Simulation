#ifndef __GRAPHICS_COLOR__
#define __GRAPHICS_COLOR__

// -- LOCAL

// .. REFERENCES


// -- GLOBAL

// .. TYPES

class GRAPHICS_COLOUR 
{
	// -- PUBLIC

public:

	// .. CONSTRCUTORS

	GRAPHICS_COLOUR( void ) 
	{ 
		Assign(0.0, 0.0, 0.0, 0.0);
	}

	// ~~

	virtual ~GRAPHICS_COLOUR( void )
	{
	}

	// ~~

	GRAPHICS_COLOUR(
		const float r, 
		const float g,
		const float b,
		const float a
		) 
	{
		Assign(r, g, b, a);
	}

	// ~~

	GRAPHICS_COLOUR( const float* rgba ) 
	{
		Assign( rgba[0], rgba[1], rgba[2], rgba[3] );
	}

	// ~~

	GRAPHICS_COLOUR( const GRAPHICS_COLOUR & other ) 
	{
		RGBA[ 0 ] = other.RGBA[ 0 ];
		RGBA[ 1 ] = other.RGBA[ 1 ];
		RGBA[ 2 ] = other.RGBA[ 2 ];
		RGBA[ 3 ] = other.RGBA[ 3 ];
	}

	// .. OPERATORS

	GRAPHICS_COLOUR & operator=( const GRAPHICS_COLOUR & other )
	{
		assert( this != &other );

		RGBA[ 0 ] = other.RGBA[ 0 ];
		RGBA[ 1 ] = other.RGBA[ 1 ];
		RGBA[ 2 ] = other.RGBA[ 2 ];
		RGBA[ 3 ] = other.RGBA[ 3 ];

		return *this;
	}

	// ~~

	const float& operator[]( unsigned int index ) const
	{
		return RGBA[index];
	}

	// ~~

	float& operator []( unsigned int index )
	{
		return RGBA[index];
	}

	// .. ACCESSORS

	const float* GetRGBA( void ) const 
	{
		return RGBA;
	}

	// .. OPERATIONS

	void Assign( 
		const float r, 
		const float g, 
		const float b, 
		const float a 
		) 
	{
		RGBA[ 0 ] = r;
		RGBA[ 1 ] = g;
		RGBA[ 2 ] = b;
		RGBA[ 3 ] = a;
	}

	// .. FUNCTIONS

	static GRAPHICS_COLOUR Black( void )
	{
		return GRAPHICS_COLOUR( 0.0f, 0.0f, 0.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOUR Grey( void ) 
	{
		return GRAPHICS_COLOUR( 0.5f, 0.5f, 0.5f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOUR White( void )
	{
		return GRAPHICS_COLOUR( 1.0f, 1.0f, 1.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOUR Red( void ) 
	{
		return GRAPHICS_COLOUR( 1.0f, 0.0f, 0.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOUR Green( void ) 
	{
		return GRAPHICS_COLOUR( 0.0f, 1.0f, 0.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOUR Blue( void ) 
	{
		return GRAPHICS_COLOUR( 0.0f, 0.0f, 1.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOUR Yellow( void ) 
	{
		return GRAPHICS_COLOUR( 1.0f, 1.0f, 0.0f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOUR Brown( void ) 
	{
		return GRAPHICS_COLOUR( 0.2f, 0.1f, 0.1f, 1.0f );
	}

	// ~~

	static GRAPHICS_COLOUR Null( void ) 
	{
		return GRAPHICS_COLOUR( 0.0f, 0.0f, 0.0f, 0.0f );
	}

	// -- PRIVATE

private:

	// .. ATTRIBUTES

	float RGBA[ 4 ];
};
#endif


