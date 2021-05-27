/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __FUNDAMENTAL_DELTA_TIME__
	#define __FUNDAMENTAL_DELTA_TIME__

	// -- LOCAL

	// .. REFERENCES

	#include "fundamental_data_types.h"

	// -- GLOBAL

	// .. TYPES

	class FUNDAMENTAL_DELTA_TIME
	{
			// -- PUBLIC

		public:

			// .. CONSTRUCTORS

			FUNDAMENTAL_DELTA_TIME(
				VOID
				)
			{
			}

			// ~~

			virtual ~FUNDAMENTAL_DELTA_TIME(
				VOID
				)
			{
			}

			// .. FUNCTIONS

			static const REAL32 GetDeltaTime(
				VOID
				)
			{
				QueryPerformanceCounter( &EndTime );
				DeltaTime = REAL32( EndTime.QuadPart - StartTime.QuadPart ) 
					/ REAL32( Frequency.QuadPart );
				QueryPerformanceFrequency( &Frequency );
				QueryPerformanceCounter( &StartTime );

				return DeltaTime;
			}

			// -- PRIVATE
		
		private:

			// .. VARIABLES

			static REAL32 DeltaTime;
			static LARGE_INTEGER Frequency ;
			static LARGE_INTEGER StartTime;
			static LARGE_INTEGER EndTime;
	};
#endif

// .. VARIABLES

REAL32 FUNDAMENTAL_DELTA_TIME::DeltaTime = 0.0f;
LARGE_INTEGER FUNDAMENTAL_DELTA_TIME::Frequency = LARGE_INTEGER();
LARGE_INTEGER FUNDAMENTAL_DELTA_TIME::StartTime = LARGE_INTEGER();
LARGE_INTEGER FUNDAMENTAL_DELTA_TIME::EndTime = LARGE_INTEGER();