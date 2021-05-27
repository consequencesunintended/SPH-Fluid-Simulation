/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#include "glut.h"
#include <windows.h>
#include "fundamental_data_types.h"

namespace GLUT_FUNCTIONS
{
	LPVOID GlutFonts[7] = 
		{ 
		GLUT_BITMAP_9_BY_15, 
		GLUT_BITMAP_8_BY_13, 
		GLUT_BITMAP_TIMES_ROMAN_10, 
		GLUT_BITMAP_TIMES_ROMAN_24, 
		GLUT_BITMAP_HELVETICA_10, 
		GLUT_BITMAP_HELVETICA_12, 
		GLUT_BITMAP_HELVETICA_18 
		}; 

	VOID glutPrint(
		REAL32 x, 
		REAL32 y, 
		LPVOID font, 
		CHAR * text, 
		REAL32 r, 
		REAL32 g, 
		REAL32 b, 
		REAL32 a
		) 
	{ 
		glColor4f(r,g,b,a); 
		glRasterPos2f(x,y); 

		while ( * text) 
		{ 
			glutBitmapCharacter(font, * text); 
			text++; 
		}
	}  
}