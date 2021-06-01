#ifndef __FUNDAMENTAL_DELTA_TIME__
#define __FUNDAMENTAL_DELTA_TIME__


#include <Windows.h>
// -- LOCAL

// .. REFERENCES

// -- GLOBAL

// .. TYPES

class FUNDAMENTAL_DELTA_TIME
{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		FUNDAMENTAL_DELTA_TIME( void )
		{
		}

		// ~~

		virtual ~FUNDAMENTAL_DELTA_TIME( void )
		{
		}

		// .. FUNCTIONS

		static const float GetDeltaTime( void )
		{
			QueryPerformanceCounter( &EndTime );
			DeltaTime = float( EndTime.QuadPart - StartTime.QuadPart ) 
				/ float( Frequency.QuadPart );
			QueryPerformanceFrequency( &Frequency );
			QueryPerformanceCounter( &StartTime );

			return DeltaTime;
		}

		// -- PRIVATE
		
	private:

		// .. VARIABLES

		static float DeltaTime;
		static LARGE_INTEGER Frequency ;
		static LARGE_INTEGER StartTime;
		static LARGE_INTEGER EndTime;
};
#endif

// .. VARIABLES

float FUNDAMENTAL_DELTA_TIME::DeltaTime = 0.0f;
LARGE_INTEGER FUNDAMENTAL_DELTA_TIME::Frequency = LARGE_INTEGER();
LARGE_INTEGER FUNDAMENTAL_DELTA_TIME::StartTime = LARGE_INTEGER();
LARGE_INTEGER FUNDAMENTAL_DELTA_TIME::EndTime = LARGE_INTEGER();