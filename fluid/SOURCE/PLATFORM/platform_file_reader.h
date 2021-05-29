#ifndef __PLATFORM_FILE_READER__
#define __PLATFORM_FILE_READER__
	

#include <assert.h>
#include <fstream>
using namespace std;

class PLATFORM_FILE_READER
{
public:
	void LoadFile(
		const char * file_name
		)
	{
		input.open( file_name, ifstream::binary );
	}

	void ReadCharacters(
		char * characters,
		int num_of_characters
		)
	{
		input.read( characters, num_of_characters );
	}

	void SkipCharacters(
		int num_of_characters
		)
	{
		input.ignore( num_of_characters );
	}

	int toInt(const char* bytes) 
	{
		return (int)(((unsigned char)bytes[3] << 24) |
						((unsigned char)bytes[2] << 16) |
						((unsigned char)bytes[1] << 8) |
						(unsigned char)bytes[0]);
	}

	short toShort(const char* bytes) 
	{
		return (short)(((unsigned char)bytes[1] << 8) |
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

	void CloseTheFile(
		void
		)
	{
		input.close();
	}

	void SeekInBeginning( int data )
	{
		input.seekg(data, ios_base::beg);
	}
private:
	ifstream input;
};
#endif