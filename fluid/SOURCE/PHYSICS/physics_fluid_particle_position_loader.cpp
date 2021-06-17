#include "physics_fluid_particle_position_loader.h"

// -- LOCAL

// .. REFERENCES

#include "math_point_2d.h"
#include "graphics_image_pixel_loader.h"

// -- PUBLIC

// .. OPERATIONS

void PHYSICS_FLUID_PARTICLE_POSITION_LOADER::LoadPositions( const char *bitmap )
{
	unsigned int				width;
	unsigned int				height;
	unsigned int				colour;
	GRAPHICS_IMAGE_PIXEL_LOADER	image;
	unsigned int				index_x;
	unsigned int				index_y;

	GRAPHICS_IMAGE_PIXEL_LOADER::LoadBMP( image, bitmap );
	width = image.GetWidth();
	height = image.GetHeight();

	for ( index_y = 0; index_y <= height - 1; index_y++ )
	{
		for ( index_x = 0; index_x <= width - 1; index_x++ )
		{
			colour = image.GetPixels()[3 * (index_y * width + index_x)];

			if ( colour != -1 )
			{
				PointTable.push_back( MATH_POINT_2D( float( int(index_x - width / 2 ) ), float( int(index_y - height / 2 ) ) ) );
			}
		}
	}
}