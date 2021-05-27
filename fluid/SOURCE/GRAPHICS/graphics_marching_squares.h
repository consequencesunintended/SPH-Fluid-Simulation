/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __GRAPHICS_MARCHING_SQUARES__
	#define __GRAPHICS_MARCHING_SQUARES__

	// -- LOCAL

	// .. REFERENCES

	#include "fundamental_data_types.h"
	#include "math_vector_2d.h"
	#include "math_point_2d.h"
	#include "math_point_2d_array.h"
    #include "math_point_2d_array_array.h"
	#include "fundamental_index_array.h"

	// -- GLOBAL

	// .. CONSTANTS

	#define GRAPHICS_MARCHING_SQUARE_threshold 1.55f

	// .. TYPES	

	class GRAPHICS_MARCHING_SQUARES
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		GRAPHICS_MARCHING_SQUARES(
			VOID
			) :
			IsInsideSurface( 0 ),
			SurfaceValueTable( 0 ),
			Width( 0.0f ),
			Height( 0.0f ),
			PointTable2(),
			PointTable1(),
			PolygonVertexCountTable()
		{
		}

		// ~~

		virtual ~GRAPHICS_MARCHING_SQUARES(
			VOID
			)
		{
			INDEX
				temp_index;

			FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index, 0 , INDEX( Width ) * 2 )
			{
				delete [] SurfaceValueTable[ temp_index ];
			}
			FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index, 0 , INDEX( Width ) * 2 - 1 )
			{
				delete [] IsInsideSurface[ temp_index ];
			}
			delete SurfaceValueTable;
			delete IsInsideSurface;
		}

		// ~~

		GRAPHICS_MARCHING_SQUARES(
			const GRAPHICS_MARCHING_SQUARES & other
			) :
			Width( other.Width ),
			Height( other.Height ),
			PointTable2( other.PointTable2 ),
			PointTable1( other.PointTable1 ),
			PolygonVertexCountTable( other.PolygonVertexCountTable )
		{
			INDEX
				temp_index_1,
				temp_index_2;

			FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, Width * 2 )
			{
				FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_2, 0, Height * 2 )
				{
					SurfaceValueTable[temp_index_1][temp_index_2] 
						= other.SurfaceValueTable[temp_index_1][temp_index_2];
				}
			}
			FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_1, 0, Width * 2 - 1 )
			{
				FUNDAMENTAL_DATA_TYPES_loop_through_index( temp_index_2, 0, Height * 2 - 1 )
				{
					IsInsideSurface[temp_index_1][temp_index_2] 
						= other.IsInsideSurface[temp_index_1][temp_index_2]; 
				}
			}
		}

		// .. OPERATORS

		GRAPHICS_MARCHING_SQUARES & operator=(
			const GRAPHICS_MARCHING_SQUARES & other
			)
		{
			IsInsideSurface = other.IsInsideSurface;
			SurfaceValueTable = other.SurfaceValueTable;
			Width = other.Width;
			Height = other.Height;
			PointTable2 = other.PointTable2;
			PointTable1 = other.PointTable1;
			PolygonVertexCountTable = other.PolygonVertexCountTable;
		}

		// .. ACCESSORS

		const MATH_POINT_2D_ARRAY & GetPointTable(
			VOID
			) const
		{
			return PointTable2;
		}

		// ~~

		VOID SetPointTable(
			const MATH_POINT_2D_ARRAY & point_table
			)
		{
			PointTable2 = point_table;
		}

		// ~~

		const FUNDAMENTAL_INDEX_ARRAY & GetPolygonVertexCountTable(
			VOID
			) const
		{
			return PolygonVertexCountTable;
		}

		// ~~

		VOID SetPolygonVertexCountTable(
			const FUNDAMENTAL_INDEX_ARRAY & polygon_vertex_count_table
			)
		{
			PolygonVertexCountTable = polygon_vertex_count_table;
		}

		// .. INQURIES

		// If a point is not inside the IsoSurfaces this function
		// find a point between pointA( not inside the IsoSurface ) 
		// and PointB( inside the IsoSurface ) through a linear
		// interpolation.

		VOID InterpolateBetweenPoints(
			MATH_POINT_2D & point,
			const MATH_POINT_2D & a,
			const MATH_POINT_2D & b, 
			const REAL32 value1, 
			const REAL32 value2 
			) const;

		// .. OPERATIONS
	
		VOID Reset(
			VOID
			);

		// ~~

		VOID Initialise(
			const REAL32 width,
			const REAL32 height
			);

		// ~~

		VOID CalculatePoint( 
			const MATH_VECTOR_2D & point,
			const INDEX square_starting_index_x_value,
			const INDEX square_starting_index_y_value
			);

		// ~~

		VOID CalculatePoints( 
			const MATH_VECTOR_2D & point,
			const INDEX x_value,
			const INDEX y_value,
			const INT32 range
			);

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

		VOID GeneratePoints(
			VOID
			);

		// -- PUBLIC

	private:

		// .. ATTRIBUTES

		INT32
			**IsInsideSurface;
		REAL32 
			**SurfaceValueTable,
			Width,
			Height;
		MATH_POINT_2D_ARRAY
			PointTable2;
		MATH_POINT_2D_ARRAY_ARRAY
			PointTable1;
		FUNDAMENTAL_INDEX_ARRAY
			PolygonVertexCountTable;
	};
#endif