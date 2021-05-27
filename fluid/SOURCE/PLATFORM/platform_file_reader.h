/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PLATFORM_FILE_READER__
	#define __PLATFORM_FILE_READER__
	

	#include <assert.h>
	#include <fstream>
	#include "fundamental_data_types.h"
	using namespace std;

	class PLATFORM_FILE_READER
	{
	public:
		VOID LoadFile(
			const CHAR * file_name
			)
		{
			input.open( file_name, ifstream::binary );
		}

		VOID ReadCharacters(
			CHAR * characters,
			INT32 num_of_characters
			)
		{
			input.read( characters, num_of_characters );
		}

		VOID SkipCharacters(
			INT32 num_of_characters
			)
		{
			input.ignore( num_of_characters );
		}

		INT32 toInt(const char* bytes) 
		{
			return (INT32)(((unsigned char)bytes[3] << 24) |
						 ((unsigned char)bytes[2] << 16) |
						 ((unsigned char)bytes[1] << 8) |
						 (unsigned char)bytes[0]);
		}

		INT16 toShort(const char* bytes) 
		{
			return (INT16)(((unsigned char)bytes[1] << 8) |
						   (unsigned char)bytes[0]);
		}

		int readInt( ) 
		{
			char buffer[4];
			ReadCharacters(buffer, 4);
			return toInt(buffer);
		}
		
		short readShort( )
		{
			char buffer[2];
			ReadCharacters(buffer, 2);
			return toShort(buffer);
		}

		VOID CloseTheFile(
			VOID
			)
		{
			input.close();
		}

		VOID SeekInBeginning( int data )
		{
			input.seekg(data, ios_base::beg);
		}
	private:
		ifstream input;
	};
#endif