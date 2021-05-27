/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
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
				VOID
				) :
				pixels( 0 ),
				width( 0 ),
				height( 0 )
			{
			}

			// ~~

			virtual ~GRAPHICS_IMAGE_PIXEL_LOADER(
				VOID
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
				INT32
					index_x,
					index_y,
					index_c;

				pixels = new CHAR[width * height * 3];

				FUNDAMENTAL_DATA_TYPES_loop_through_index( index_y, 0, height - 1 )
				{
					FUNDAMENTAL_DATA_TYPES_loop_through_index( index_x, 0, width - 1 )
					{
						FUNDAMENTAL_DATA_TYPES_loop_through_index( index_c, 0, 2 )
						{
							pixels[3 * (width * index_y + index_x) + index_c ] =
								other.pixels[ 3 * (width * index_y + index_x) + index_c ];
						}
					}
				}
			}

			// ~~

			GRAPHICS_IMAGE_PIXEL_LOADER(
				const CHAR * other_pixels, 
				const INT32 w, 
				const INT32 h
				) : 
				width(w), 
				height(h) 
			{
				INT32
					index_x,
					index_y,
					index_c;

				pixels = new CHAR[width * height * 3];

				FUNDAMENTAL_DATA_TYPES_loop_through_index( index_y, 0, height - 1 )
				{
					FUNDAMENTAL_DATA_TYPES_loop_through_index( index_x, 0, width - 1 )
					{
						FUNDAMENTAL_DATA_TYPES_loop_through_index( index_c, 0, 2 )
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
				INT32
					index_x,
					index_y,
					index_c;

				width = other.width;
				height = other.height;
				pixels = new CHAR[width * height * 3];

				FUNDAMENTAL_DATA_TYPES_loop_through_index( index_y, 0, height - 1 )
				{
					FUNDAMENTAL_DATA_TYPES_loop_through_index( index_x, 0, width - 1 )
					{
						FUNDAMENTAL_DATA_TYPES_loop_through_index( index_c, 0, 2 )
						{
							pixels[ 3 * ( width * index_y + index_x ) + index_c ] =
								other.pixels[ 3 * ( width * index_y + index_x ) + index_c ];
						}
					}
				}

				return *this;
			}

			// .. ACCESSORS

			INT32 GetHeight(
				VOID
				)
			{
				return height;
			}

			// ~~

			INT32 GetWidth(
				VOID
				)
			{
				return width;
			}

			// ~~

			const CHAR *GetPixels(
				VOID
				)
			{
				return pixels;
			}

			// .. FUNCTIONS

			static VOID LoadBMP(
				GRAPHICS_IMAGE_PIXEL_LOADER & image,
				const CHAR * filename
				);

			// -- PRIVATE

		private:

			// .. ATTRIBUTES

			CHAR * pixels;
			INT32 
				width,
				height;
	};
#endif
