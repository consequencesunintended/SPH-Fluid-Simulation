#ifndef __GRAPHICS_MARCHING_SQUARES__
#define __GRAPHICS_MARCHING_SQUARES__

	// -- LOCAL

	// .. REFERENCES

	#include "math_vector_2d.h"
	#include "math_point_2d.h"
	#include <vector>

	// -- GLOBAL

	// .. CONSTANTS

	constexpr float GRAPHICS_MARCHING_SQUARE_threshold = 1.55f;

	// .. TYPES	

	class GRAPHICS_MARCHING_SQUARES
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		GRAPHICS_MARCHING_SQUARES(
			void
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
			void
			)
		{
			unsigned int
				temp_index;

			for ( temp_index = 0; temp_index <= unsigned int( Width ) * 2; temp_index++ )
			{
				delete [] SurfaceValueTable[ temp_index ];
			}
			for ( temp_index = 0; temp_index <= unsigned int( Width ) * 2 - 1; temp_index++ )
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
			unsigned int
				temp_index_1,
				temp_index_2;

			for ( temp_index_1 = 0; temp_index_1 <= Width * 2; temp_index_1++ )
			{
				for ( temp_index_2 = 0; temp_index_2 <= Height * 2; temp_index_2++ )
				{
					SurfaceValueTable[temp_index_1][temp_index_2] 
						= other.SurfaceValueTable[temp_index_1][temp_index_2];
				}
			}
			for ( temp_index_1 = 0; temp_index_1 <= Width * 2 - 1; temp_index_1++ )
			{
				for ( temp_index_2 = 0; temp_index_2 <= Height * 2 - 1; temp_index_2++ )
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

		const std::vector<MATH_POINT_2D> & GetPointTable(
			void
			) const
		{
			return PointTable2;
		}

		// ~~

		void SetPointTable(
			const std::vector<MATH_POINT_2D> & point_table
			)
		{
			PointTable2 = point_table;
		}

		// ~~

		const std::vector<unsigned int> & GetPolygonVertexCountTable(
			void
			) const
		{
			return PolygonVertexCountTable;
		}

		// ~~

		void SetPolygonVertexCountTable(
			const std::vector<unsigned int> & polygon_vertex_count_table
			)
		{
			PolygonVertexCountTable = polygon_vertex_count_table;
		}

		// .. INQURIES

		// If a point is not inside the IsoSurfaces this function
		// find a point between pointA( not inside the IsoSurface ) 
		// and PointB( inside the IsoSurface ) through a linear
		// interpolation.

		void InterpolateBetweenPoints(
			MATH_POINT_2D & point,
			const MATH_POINT_2D & a,
			const MATH_POINT_2D & b, 
			const float value1, 
			const float value2 
			) const;

		// .. OPERATIONS
	
		void Reset(
			void
			);

		// ~~

		void Initialise(
			const float width,
			const float height
			);

		// ~~

		void CalculatePoint( 
			const MATH_VECTOR_2D & point,
			const unsigned int square_starting_index_x_value,
			const unsigned int square_starting_index_y_value
			);

		// ~~

		void CalculatePoints( 
			const MATH_VECTOR_2D & point,
			const unsigned int x_value,
			const unsigned int y_value,
			const int range
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

		void GeneratePoints(
			void
			);

		// -- PUBLIC

	private:

		// .. ATTRIBUTES

		int
			**IsInsideSurface;
		float 
			**SurfaceValueTable,
			Width,
			Height;
		std::vector<MATH_POINT_2D>
			PointTable2;
		std::vector < std::vector<MATH_POINT_2D>>
			PointTable1;
		std::vector<unsigned int>
			PolygonVertexCountTable;
	};
#endif