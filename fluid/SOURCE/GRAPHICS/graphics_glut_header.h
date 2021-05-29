#include "glut.h"
#include <windows.h>

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

	void glutPrint(
		float x, 
		float y, 
		LPVOID font, 
		char * text, 
		float r, 
		float g, 
		float b, 
		float a
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