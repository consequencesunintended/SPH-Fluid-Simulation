/*
Alex Nasser
www.alexnasser.co.uk
14-2-2011 18:59:23
*/
// This class is the base interface of all integration classes
// It is a self explenatory class, the only thing that is worth
// mentioning is that some classes come with a scale factor for
// their delta time that should be passed to the delta time of
// their integration to get the desired results.
#ifndef __PHYSICS_INTEGRATION__
	#define __PHYSICS_INTEGRATION__

	// -- LOCAL

	// .. REFERENCES

	#include "debug_statements.h"
	#include "fundamental_data_types.h"
	#include "physics_entity.h"

	// -- GLOBAL

	// .. CONSTANTS

	// .. TYPES

	class PHYSICS_INTEGRATION
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		PHYSICS_INTEGRATION(
			VOID
			)
		{
		}

		// ~~

		PHYSICS_INTEGRATION(
			const PHYSICS_INTEGRATION & other
			)
		{
		}

		// ~~

		virtual ~PHYSICS_INTEGRATION(
			VOID
			)
		{
		}

		// .. OPERATORS

		PHYSICS_INTEGRATION & operator=(
			const PHYSICS_INTEGRATION & other
			)
		{
			return *this;
		}

		// .. ACCESSORS

		// .. INQUERIES

		// .. OPERATIONS

		virtual VOID UpdateVelocity(
			PHYSICS_ENTITY & game_entity,
			const REAL32 delta_time
			) = 0;

		// ~~

		virtual VOID UpdatePosition(
			PHYSICS_ENTITY & game_entity,
			const REAL32 delta_time
			) = 0;

		// .. FUNCTIONS

		// -- PRIVATE

	private:

		// .. ATTRIBUTES

		// .. VARIABLES

	};
#endif