/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#include "physics_fluid_particle_position_loader.h"

// -- LOCAL

// .. REFERENCES

#include "fundamental_data_types.h"
#include "math_point_2d.h"
#include "graphics_image_pixel_loader.h"

// -- PUBLIC

// .. OPERATIONS

VOID PHYSICS_FLUID_PARTICLE_POSITION_LOADER::LoadPositions(
	const CHAR *bitmap
	)
{
	UINT32
		width,
		height,
		colour;
	GRAPHICS_IMAGE_PIXEL_LOADER 
		image;
	UINT32
		index_x,
		index_y;

	GRAPHICS_IMAGE_PIXEL_LOADER::LoadBMP( image, bitmap );
	width = image.GetWidth();
	height = image.GetHeight();

	FUNDAMENTAL_DATA_TYPES_loop_through_index( index_y, 0, height - 1 )
	{
        FUNDAMENTAL_DATA_TYPES_loop_through_index( index_x, 0, width - 1 )
		{
			colour = image.GetPixels()[3 * (index_y * width + index_x)];

			if ( colour != -1 )
			{
				PointTable.push_back( 
					MATH_POINT_2D( 
						REAL32( INT32(index_x - width / 2 ) ), 
						REAL32( INT32(index_y - height / 2 ) )
						) 
					);
			}
		}
	}
}