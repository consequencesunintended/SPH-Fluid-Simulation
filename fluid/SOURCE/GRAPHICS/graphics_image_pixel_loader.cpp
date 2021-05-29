/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#include "graphics_image_pixel_loader.h"

// -- LOCAL

// .. REFERENCES

#include "platform_file_reader.h"
#include "fundamental_data_types.h"

// -- PUBLIC

// .. FUNCTIONS

void GRAPHICS_IMAGE_PIXEL_LOADER::LoadBMP(
	GRAPHICS_IMAGE_PIXEL_LOADER & image,
	const char * filename
	) 
{
	int 
		dataOffset,
		headerSize,
		width,
		height,
		bytesPerRow,
		size;
	char 
		* pixels3,
		* pixels2;
	int
		index_x,
		index_y,
		index_c;
	PLATFORM_FILE_READER 
		file_reader_engine;

	file_reader_engine.LoadFile( filename );
	file_reader_engine.SkipCharacters( 10 );

	dataOffset = file_reader_engine.readInt();
	headerSize = file_reader_engine.readInt();

	switch( headerSize ) 
	{
		case 40:
			width = file_reader_engine.readInt();
			height = file_reader_engine.readInt();
			break;
		case 12:
			width = file_reader_engine.readShort();
			height = file_reader_engine.readShort();
			break;
	}
	bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	size = bytesPerRow * height;
	pixels3 = new char[ size ];
	file_reader_engine.SeekInBeginning(dataOffset);
	file_reader_engine.ReadCharacters( pixels3 , size);
	pixels2 = new char[ width * height * 3 ];

	FUNDAMENTAL_DATA_TYPES_loop_through_index( index_y, 0, height - 1 ) 
	{
		FUNDAMENTAL_DATA_TYPES_loop_through_index( index_x, 0, width - 1 ) 
		{
			FUNDAMENTAL_DATA_TYPES_loop_through_index( index_c, 0 , 2 )
			{
				pixels2[ 3 * ( width * index_y + index_x ) + index_c ] =
					pixels3[ bytesPerRow * index_y + 3 * index_x + ( 2 - index_c ) ];
			}
		}
	}	
	file_reader_engine.CloseTheFile();
	image = GRAPHICS_IMAGE_PIXEL_LOADER( pixels2, width, height);
	delete [] pixels2;
	delete [] pixels3;
}









