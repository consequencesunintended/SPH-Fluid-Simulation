#include "graphics_marching_squares.h"

// -- LOCAL

// .. REFERENCES

#include "math_vector_2d.h"

// .. CONSTANTS

// Each square is created from four points
// these constants are just for readibility
// purposes.

#define LOCAL_square_point_1 temp_index_1][temp_index_2 
#define LOCAL_square_point_2 temp_index_1][temp_index_2+1 
#define LOCAL_square_point_3 temp_index_1+1][temp_index_2+1 
#define LOCAL_square_point_4 temp_index_1+1][ temp_index_2 

// -- PUBLIC

// .. INQUERIES

// If a point is not inside the IsoSurfaces this function
// find a point between pointA( not inside the IsoSurface ) 
// and PointB( inside the IsoSurface ) through a linear
// interpolation.

void GRAPHICS_MARCHING_SQUARES::InterpolateBetweenPoints(
	MATH_POINT_2D & point,
	const MATH_POINT_2D &a,
	const MATH_POINT_2D &b, 
	const float value1, 
	const float value2 
	) const
{
	if ( ( value2 - value1 ) != 0.0f )
	{
		point = a +  ( b - a ) * ( GRAPHICS_MARCHING_SQUARE_threshold - value1 ) / ( value2 - value1 );
	}
	else
	{
		point = a;
	}
}

// .. OPERATIONS

void GRAPHICS_MARCHING_SQUARES::Initialise( const float width, const float height )
{
	unsigned int	temp_index_1;
	unsigned int	temp_index_2;
	MATH_POINT_2D	point;
	float			initial_position_x;
	float			initial_position_y;

	Width = width;
	Height = height;
	initial_position_x = -width;
	initial_position_y = height;
	PointTable1.resize( int( width * 2 + 1 ) );

	for ( temp_index_2 = 0; temp_index_2 <= unsigned int( height * 2 ); temp_index_2++ )
	{
		for ( temp_index_1 = 0; temp_index_1 <= unsigned int( width * 2 ); temp_index_1++ )
		{
			point.Assign( initial_position_x , initial_position_y ); 
			PointTable1[ temp_index_1 ].push_back( point );
			initial_position_x += 1.0f;
			if ( initial_position_x > width )
			{
				initial_position_x = -width;
				initial_position_y -= 1.0f;
			}
		}
	}
	IsInsideSurface = new int*[ unsigned int( width ) * 2 ] ;
	SurfaceValueTable = new float*[ unsigned int( width ) * 2 + 1 ];

	for ( temp_index_1 = 0; temp_index_1 <= unsigned int( width ) * 2 - 1; temp_index_1++ )
	{
		IsInsideSurface[ temp_index_1 ] = new int[ unsigned int( width ) * 2 ];
	}

	for ( temp_index_1 = 0; temp_index_1 <= unsigned int( width ) * 2; temp_index_1++ )
	{
		SurfaceValueTable[ temp_index_1 ] = new float[ unsigned int( width ) * 2 + 1 ];
	}
	Reset();
}

// ~~

void GRAPHICS_MARCHING_SQUARES::CalculatePoint( 
	const MATH_VECTOR_2D & point,
	const unsigned int square_starting_index_x_value,
	const unsigned int square_starting_index_y_value
	)
{
	float value;
	float h;
	
	h = ( point - PointTable1[ square_starting_index_x_value ][ square_starting_index_y_value ] ).GetSquareLength();

	if ( h != 0.0f )
	{
		constexpr float SMOOTHNESS_threshold = 0.20f;
		value = 1.0f / h;
			
		if ( value > SMOOTHNESS_threshold )
		{
			SurfaceValueTable[ square_starting_index_x_value ][ square_starting_index_y_value ] += value;
		}
	}
}

// ~~

void GRAPHICS_MARCHING_SQUARES::CalculatePoints( 
	const MATH_VECTOR_2D & point,
	const unsigned int x_value,
	const unsigned int y_value,
	const int range
	)
{
	int counter_value_1;
	int counter_value_2;

	auto check_range = [&]( const int new_x, const int new_y )
	{
		if ( (new_x) < (Width * 2 + 1) && (new_x) >= 0 )
		{
			if ( (new_y) < (Height * 2 + 1) && (new_y) >= 0 )
			{
				return true;
			}
		}
		return false;
	};

	for ( counter_value_1 = -range; counter_value_1 <= 0; counter_value_1++ )
	{
		for ( counter_value_2 = 0; counter_value_2 <= range; counter_value_2++ )
		{
			if ( check_range( x_value + counter_value_1, y_value + counter_value_2 ) )
			{
				CalculatePoint( point, x_value + counter_value_1, y_value + counter_value_2 );
			}
		}
	}
	for ( counter_value_1 = -range; counter_value_1 <= 0; counter_value_1++ )
	{
		for ( counter_value_2 = -range; counter_value_2 <= 0; counter_value_2++ )
		{
			if ( check_range( x_value + counter_value_1, y_value - 1 + counter_value_2 ) )
			{
				CalculatePoint( point, x_value + counter_value_1, y_value - 1 + counter_value_2 );
			}
		}
	}
	for ( counter_value_1 = 0; counter_value_1 <= range; counter_value_1++ )
	{
		for ( counter_value_2 = -range; counter_value_2 <= 0; counter_value_2++ )
		{
			if ( check_range( x_value + 1 + counter_value_1, y_value - 1 + counter_value_2 ) )
			{
				CalculatePoint( point, x_value + 1 + counter_value_1, y_value - 1 + counter_value_2 );
			}
		}
	}
	for ( counter_value_1 = 0; counter_value_1 <= range; counter_value_1++ )
	{
		for ( counter_value_2 = 0; counter_value_2 <= range; counter_value_2++ )
		{
			if ( check_range( x_value + 1 + counter_value_1, y_value + counter_value_2 ) )
			{
				CalculatePoint( point, x_value + 1 + counter_value_1, y_value + counter_value_2 );
			}
		}
	}
}

// ~~

void GRAPHICS_MARCHING_SQUARES::Reset(
	void
	)
{
	unsigned int
		temp_index_1,
		temp_index_2;

	for ( temp_index_1 = 0; temp_index_1 <= unsigned int( Width ) * 2; temp_index_1++ )
	{
		for ( temp_index_2 = 0; temp_index_2 <= unsigned int( Height ) * 2; temp_index_2++ )
		{
			SurfaceValueTable[temp_index_1][temp_index_2] = 0.0f;
		}
	}
	for ( temp_index_1 = 0; temp_index_1 <= unsigned int( Width ) * 2 - 1; temp_index_1++ )
	{
		for ( temp_index_2 = 0; temp_index_2 <= unsigned int( Height ) * 2 - 1; temp_index_2++ )
		{
			IsInsideSurface[temp_index_1][temp_index_2] = 0;
		}
	}

	MainTable.clear();
	PolygonVertexCountTable.clear();
}

// ~~

// This is the main function for generating the marching
// squares. The since is been divided to small grids in the
// initialisation then according to the particle point for
// each point on the grid the distance of the point from the
// particle is been calculated( CalulatePoint() ) and the
// value is been stored in SurfaceValueTable and then
// according to the marching square algorithm this value
// is been compared to for points of each small square of
// the grid and a value is been given the each square which
// is been stored in IsInssideSurface to realise which point
// is in and which one is not.

void GRAPHICS_MARCHING_SQUARES::GeneratePoints( void )
{	
	unsigned int	temp_index_1;
	unsigned int	temp_index_2;
	unsigned int	index_x;
	unsigned int	index_y;	 
	MATH_VECTOR_2D	result;

	for ( temp_index_1 = 0; temp_index_1 <= unsigned int( Width ) * 2 - 1; temp_index_1++ )
	{
		index_x = temp_index_1;

		for ( temp_index_2 = 0; temp_index_2 <= unsigned int( Height ) * 2 - 1; temp_index_2++ )
		{
			index_y = temp_index_2;

			if ( SurfaceValueTable[ LOCAL_square_point_1 ]  > GRAPHICS_MARCHING_SQUARE_threshold )
			{
				// Operator OR with 0001 is been used to show 
				// that the first point of the square is inside 
				// the IsoSurface.

				IsInsideSurface[ index_x ][ index_y ] |= 1;
			}
			if ( SurfaceValueTable[ LOCAL_square_point_2 ]  > GRAPHICS_MARCHING_SQUARE_threshold )
			{
				// Operator OR with 0010 is been used to show 
				// that the second point of the square is inside 
				// the IsoSurface.

				IsInsideSurface[ index_x ][ index_y ] |= 2;
			}
			if ( SurfaceValueTable[ LOCAL_square_point_3 ]  > GRAPHICS_MARCHING_SQUARE_threshold 
				)
			{
				// Operator OR with 0100 is been used to show 
				// that the third point of the square is inside 
				// the IsoSurface.

				IsInsideSurface[ index_x ][ index_y ] |= 4;
			}
			if ( SurfaceValueTable[LOCAL_square_point_4 ]  > GRAPHICS_MARCHING_SQUARE_threshold )
			{
				// Operator OR with 0100 is been used to show 
				// that the fourth point of the square is inside 
				// the IsoSurface.

				IsInsideSurface[ index_x ][ index_y ] |= 8;
			}
		}
	}
	for ( temp_index_1 = 0; temp_index_1 <= unsigned int( Width ) * 2 - 1; temp_index_1++ )
	{
		index_x = temp_index_1;

		for ( temp_index_2 = 0; temp_index_2 <= unsigned int( Height ) * 2 - 1; temp_index_2++ )
		{
			index_y = temp_index_2;

			switch( IsInsideSurface[ index_x ][ index_y ] )
			{
			case 15 :
				{
					PolygonVertexCountTable.push_back( 4 );
					MainTable.push_back( PointTable1[ LOCAL_square_point_1 ] );
					MainTable.push_back( PointTable1[ LOCAL_square_point_2 ] );
					MainTable.push_back( PointTable1[ LOCAL_square_point_3 ] );
					MainTable.push_back( PointTable1[ LOCAL_square_point_4 ] );
					break;
				}

			case 14:
				{
					PolygonVertexCountTable.push_back( 5 );
					InterpolateBetweenPoints( result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					MainTable.push_back( result );
					MainTable.push_back( PointTable1[ LOCAL_square_point_2 ] );
					MainTable.push_back( PointTable1[ LOCAL_square_point_3 ] );
					MainTable.push_back( PointTable1[LOCAL_square_point_4 ] );
						break;
				}

			case 13:
				{
					PolygonVertexCountTable.push_back( 5 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					MainTable.push_back( result );
					MainTable.push_back( PointTable1[ LOCAL_square_point_3 ] );
					MainTable.push_back( PointTable1[ LOCAL_square_point_4 ] );
					MainTable.push_back( PointTable1[ LOCAL_square_point_1 ] );
						break;
				}

			case 12:
				{
					PolygonVertexCountTable.push_back( 4 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					MainTable.push_back( result );
					MainTable.push_back( PointTable1[ LOCAL_square_point_3 ] );
					MainTable.push_back( PointTable1[ LOCAL_square_point_4 ] );
						break;
				}

			case 11:
				{
					PolygonVertexCountTable.push_back( 5 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_2 ]
						);
					break;
				}

			case 10:
				{
					PolygonVertexCountTable.push_back( 6 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_2 ]
						);

					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_4 ]
						);
					break;
				}

			case 9:
				{
					PolygonVertexCountTable.push_back( 4 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
						break;
				}

			case 8:
				{
					PolygonVertexCountTable.push_back( 3 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_4 ]
						);
					break;
				}

			case 7:
				{
					PolygonVertexCountTable.push_back( 5 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_2 ]
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_3 ]
						);
					break;
				}

			case 6:
				{
					PolygonVertexCountTable.push_back( 4 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_3 ]
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_2 ]
					);
					break;
				}

			case 5:
				{
					PolygonVertexCountTable.push_back( 6 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);

					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_3 ]
						);
					break;
				}
				
			case 4:
				{
					PolygonVertexCountTable.push_back( 3 );
					InterpolateBetweenPoints( result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_3 ]
						);
					break;
				}

			case 3:
				{
					PolygonVertexCountTable.push_back( 4 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_2 ]
						);
					break;
				}

			case 2:
				{
					PolygonVertexCountTable.push_back( 3 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_2 ]
						);
					break;
				}

			case 1:
				{
					PolygonVertexCountTable.push_back( 3 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					MainTable.push_back(
						result
						);
					MainTable.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
					break;
				}
			}
		}
	}
}