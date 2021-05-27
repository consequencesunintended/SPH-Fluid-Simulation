/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#include "graphics_marching_squares.h"

// -- LOCAL

// .. REFERENCES

#include "fundamental_data_types.h"
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

VOID GRAPHICS_MARCHING_SQUARES::InterpolateBetweenPoints(
	MATH_POINT_2D & point,
	const MATH_POINT_2D &a,
	const MATH_POINT_2D &b, 
	const REAL32 value1, 
	const REAL32 value2 
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

VOID GRAPHICS_MARCHING_SQUARES::Initialise(
	const REAL32 width,
	const REAL32 height
	)
{
	INDEX
		temp_index_1,
		temp_index_2;
	MATH_POINT_2D
		point;
	REAL32
		initial_position_x,
		initial_position_y;

	Width = width;
	Height = height;
	initial_position_x = -width;
	initial_position_y = height;
	PointTable1.Allocate( COUNTER( width * 2 + 1 ) );

	FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_2, 0, INDEX( height * 2 ) )
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, INDEX( width * 2 ) )
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
	IsInsideSurface = new INT32*[ INDEX( width ) * 2 ] ;
	SurfaceValueTable = new REAL32*[ INDEX( width ) * 2 + 1 ];

	FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, INDEX( width ) * 2 - 1 )
	{
		IsInsideSurface[ temp_index_1 ] = new INT32[ INDEX( width ) * 2 ];
	}

	FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, INDEX( width ) * 2 )
	{
		SurfaceValueTable[ temp_index_1 ] = new REAL32[ INDEX( width ) * 2 + 1 ];
	}
	Reset();
}

// ~~

VOID GRAPHICS_MARCHING_SQUARES::CalculatePoint( 
	const MATH_VECTOR_2D & point,
	const INDEX square_starting_index_x_value,
	const INDEX square_starting_index_y_value
	)
{
	REAL32 value;
	REAL32 h;
	
	h = ( point 
		- PointTable1[ square_starting_index_x_value ][ square_starting_index_y_value ] 
		).GetSquareLength();

	if ( h != 0.0f )
	{
		value = 1.0f / h;
		if ( value < 0.16f )
		{
			value = 0;
		} 
		else
		{
			SurfaceValueTable[ square_starting_index_x_value ][ square_starting_index_y_value ] 
				+= value;
		}
	}
}

// ~~

VOID GRAPHICS_MARCHING_SQUARES::CalculatePoints( 
	const MATH_VECTOR_2D & point,
	const INDEX x_value,
	const INDEX y_value,
	const INT32 range
	)
{
	COUNTER
		counter_value_1,
		counter_value_2;

	FUNDAMENTAL_DATA_TYPES_loop_through_index( counter_value_1, -range, 0 )
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( counter_value_2, 0, range )
		{
			if ( ( x_value + counter_value_1 ) < ( Width * 2 + 1 ) && ( x_value + counter_value_1 ) >= 0 )
			{
				if ( ( y_value + counter_value_2 ) < ( Height * 2 + 1 ) && ( y_value + counter_value_2 ) >= 0 )
				{
				CalculatePoint( point, x_value + counter_value_1, y_value + counter_value_2);
				}
			}
		}
	}
	FUNDAMENTAL_DATA_TYPES_loop_through_index( counter_value_1, -range, 0 )
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( counter_value_2, -range, 0 )
		{
			if ( ( x_value + counter_value_1 ) < ( Width * 2 + 1  ) && ( x_value + counter_value_1 ) >= 0 )
			{
				if ( ( y_value - 1 + counter_value_2 ) < ( Height * 2 + 1 ) && ( y_value - 1 + counter_value_2 ) >= 0 )
				{
					CalculatePoint( point, x_value + counter_value_1, y_value - 1 + counter_value_2);
				}
			}
		}
	}
	FUNDAMENTAL_DATA_TYPES_loop_through_index( counter_value_1, 0, range )
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( counter_value_2, -range, 0 )
		{
			if ( ( x_value + 1 + counter_value_1 ) < ( Width * 2 + 1  ) && ( x_value + 1 + counter_value_1 ) >= 0 )
			{
				if ( ( y_value - 1 + counter_value_2 ) < ( Height * 2 + 1 ) && ( y_value - 1 + counter_value_2 ) >= 0 )
				{
					CalculatePoint( point, x_value + 1 + counter_value_1, y_value - 1 + counter_value_2);
				}
			}
		}
	}
	FUNDAMENTAL_DATA_TYPES_loop_through_index( counter_value_1, 0, range )
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( counter_value_2, 0, range )
		{
			if ( ( x_value + 1 + counter_value_1 ) < ( Width * 2 + 1  ) && ( x_value + 1 + counter_value_1 ) >= 0 )
			{
				if ( ( y_value + counter_value_2 ) < ( Height * 2 + 1 ) && ( y_value + counter_value_2 ) >= 0 )
				{
					CalculatePoint( point, x_value + 1 + counter_value_1, y_value + counter_value_2);
				}

			}
		}
	}
}

// ~~

VOID GRAPHICS_MARCHING_SQUARES::Reset(
	VOID
	)
{
	INDEX
		temp_index_1,
		temp_index_2;

	FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, INDEX( Width ) * 2 )
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_2, 0, INDEX( Height ) * 2 )
		{
			SurfaceValueTable[temp_index_1][temp_index_2] = 0.0f;
		}
	}
	FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, INDEX( Width ) * 2 - 1 )
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_2, 0, INDEX( Height ) * 2 - 1 )
		{
			IsInsideSurface[temp_index_1][temp_index_2] = 0;
		}
	}

	PointTable2.clear();
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

VOID GRAPHICS_MARCHING_SQUARES::GeneratePoints(
	VOID
	)
{
	INDEX
		temp_index_1,
		temp_index_2,
		index_x,
		index_y;
	MATH_VECTOR_2D 
		result;

	FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, Width * 2 - 1 )
	{
		index_x = temp_index_1;

		FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_2, 0, Height * 2 - 1 )
		{
			index_y = temp_index_2;

			if ( 
				SurfaceValueTable[ LOCAL_square_point_1 ]  
				> GRAPHICS_MARCHING_SQUARE_threshold 
				)
			{
				// Operator OR with 0001 is been used to show 
				// that the first point of the square is inside 
				// the IsoSurface.

				IsInsideSurface[ index_x ][ index_y ] |= 1;
			}
			if ( 
				SurfaceValueTable[ LOCAL_square_point_2 ]  
				> GRAPHICS_MARCHING_SQUARE_threshold 
				)
			{
				// Operator OR with 0010 is been used to show 
				// that the second point of the square is inside 
				// the IsoSurface.

				IsInsideSurface[ index_x ][ index_y ] |= 2;
			}
			if ( 
				SurfaceValueTable[ LOCAL_square_point_3 ]  
				> GRAPHICS_MARCHING_SQUARE_threshold 
				)
			{
				// Operator OR with 0100 is been used to show 
				// that the third point of the square is inside 
				// the IsoSurface.

				IsInsideSurface[ index_x ][ index_y ] |= 4;
			}
			if ( 
				SurfaceValueTable[LOCAL_square_point_4 ]  
				> GRAPHICS_MARCHING_SQUARE_threshold
				)
			{
				// Operator OR with 0100 is been used to show 
				// that the fourth point of the square is inside 
				// the IsoSurface.

				IsInsideSurface[ index_x ][ index_y ] |= 8;
			}
		}
	}

	FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, Width * 2 - 1 )
	{
		index_x = temp_index_1;

		FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_2, 0, Height * 2 - 1 )
		{
			index_y = temp_index_2;

			switch( IsInsideSurface[ index_x ][ index_y ] )
			{
			case 15 :
				{
					PolygonVertexCountTable.push_back( 4 );
					PointTable2.push_back( 
						PointTable1[ LOCAL_square_point_1 ] 
						);
					PointTable2.push_back( 
						PointTable1[ LOCAL_square_point_2 ] 
						);
					PointTable2.push_back( 
						PointTable1[ LOCAL_square_point_3 ] 
						);
					PointTable2.push_back( 
						PointTable1[ LOCAL_square_point_4 ] 
						);
					break;
				}

			case 14:
				{
					PolygonVertexCountTable.push_back( 5 );
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_2 ]
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
						PointTable1[LOCAL_square_point_4 ]
						);
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_4 ]
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_4 ]
						);
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_4 ]
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_2 ]
						);

					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_4 ]
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_3 ], 
						PointTable1[ LOCAL_square_point_4 ],
						SurfaceValueTable[ LOCAL_square_point_3 ], 
						SurfaceValueTable[ LOCAL_square_point_4 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_2 ]
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);

					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_2 ], 
						PointTable1[ LOCAL_square_point_3 ],
						SurfaceValueTable[ LOCAL_square_point_2 ], 
						SurfaceValueTable[ LOCAL_square_point_3 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_1 ], 
						PointTable1[ LOCAL_square_point_2 ],
						SurfaceValueTable[ LOCAL_square_point_1 ], 
						SurfaceValueTable[ LOCAL_square_point_2 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
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
					PointTable2.push_back(
						result
						);
					InterpolateBetweenPoints( 
						result,
						PointTable1[ LOCAL_square_point_4 ], 
						PointTable1[ LOCAL_square_point_1 ],
						SurfaceValueTable[ LOCAL_square_point_4 ], 
						SurfaceValueTable[ LOCAL_square_point_1 ]
						);
					PointTable2.push_back(
						result
						);
					PointTable2.push_back(
						PointTable1[ LOCAL_square_point_1 ]
						);
					break;
				}
			}
		}
	}
}