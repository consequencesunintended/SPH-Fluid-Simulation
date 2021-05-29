#ifndef __GRAPHICS_IMAGE_PIXEL_LOADER__
#define __GRAPHICS_IMAGE_PIXEL_LOADER__

// -- LOCAL

// .. REFERENCES

#include "platform_file_reader.h"
#include "fundamental_data_types.h"

// -- GLOBAL

// .. TYPES

class GRAPHICS_IMAGE_PIXEL_LOADER 
{
		// -- PUBLIC
	public:

		// .. CONSTRUCTORS

		GRAPHICS_IMAGE_PIXEL_LOADER(
			void
			) :
			pixels( 0 ),
			width( 0 ),
			height( 0 )
		{
		}

		// ~~

		virtual ~GRAPHICS_IMAGE_PIXEL_LOADER(
			void
			)
		{
			delete[] pixels;
		}

		// ~~

		GRAPHICS_IMAGE_PIXEL_LOADER( 
			const GRAPHICS_IMAGE_PIXEL_LOADER & other 
			)
			:
			width( other.width ),
			height( other.height )
		{
			int
				index_x,
				index_y,
				index_c;

			pixels = new char[width * height * 3];

			for ( index_y = 0; index_y <= height - 1; index_y++ )
			{
				for ( index_x = 0; index_x <= width - 1; index_x++ )
				{
					for ( index_c = 0; index_c <= 2; index_c++ )
					{
						pixels[3 * (width * index_y + index_x) + index_c ] =
							other.pixels[ 3 * (width * index_y + index_x) + index_c ];
					}
				}
			}
		}

		// ~~

		GRAPHICS_IMAGE_PIXEL_LOADER(
			const char * other_pixels, 
			const int w, 
			const int h
			) : 
			width(w), 
			height(h) 
		{
			int
				index_x,
				index_y,
				index_c;

			pixels = new char[width * height * 3];

			for ( index_y = 0; index_y <= height - 1; index_y++ )
			{
				for ( index_x = 0; index_x <= width - 1; index_x++ )
				{
					for ( index_c = 0; index_c <= 2; index_c++ )
					{
						pixels[3 * (width * index_y + index_x) + index_c ] =
							other_pixels[ 3 * (width * index_y + index_x) + index_c ];
					}
				}
			}				
		}

		// .. OPERATORS

		GRAPHICS_IMAGE_PIXEL_LOADER & operator=(
			const GRAPHICS_IMAGE_PIXEL_LOADER & other
			)
		{
			int
				index_x,
				index_y,
				index_c;

			width = other.width;
			height = other.height;
			pixels = new char[width * height * 3];

			for ( index_y = 0; index_y <= height - 1; index_y++ )
			{
				for ( index_x = 0; index_x <= width - 1; index_x++ )
				{
					for ( index_c = 0; index_c <= 2; index_c++ )
					{
						pixels[ 3 * ( width * index_y + index_x ) + index_c ] =
							other.pixels[ 3 * ( width * index_y + index_x ) + index_c ];
					}
				}
			}

			return *this;
		}

		// .. ACCESSORS

		int GetHeight(
			void
			)
		{
			return height;
		}

		// ~~

		int GetWidth(
			void
			)
		{
			return width;
		}

		// ~~

		const char *GetPixels(
			void
			)
		{
			return pixels;
		}

		// .. FUNCTIONS

		static void LoadBMP(
			GRAPHICS_IMAGE_PIXEL_LOADER & image,
			const char * filename
			);

		// -- PRIVATE

	private:

		// .. ATTRIBUTES

		char * pixels;
		int 
			width,
			height;
};
#endif
