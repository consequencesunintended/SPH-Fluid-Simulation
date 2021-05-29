// This class is the base interface of all integration classes
// It is a self explenatory class, the only thing that is worth
// mentioning is that some classes come with a scale factor for
// their delta time that should be passed to the delta time of
// their integration to get the desired results.
#ifndef __PHYSICS_INTEGRATION__
#define __PHYSICS_INTEGRATION__

// -- LOCAL

// .. REFERENCES

#include "physics_entity.h"
#include <assert.h>

// -- GLOBAL

// .. CONSTANTS

// .. TYPES

class PHYSICS_INTEGRATION
{
	// -- PUBLIC

public:

	// .. CONSTRUCTORS

	PHYSICS_INTEGRATION(
		void
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
		void
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

	virtual void UpdateVelocity(
		PHYSICS_ENTITY & game_entity,
		const float delta_time
		) = 0;

	// ~~

	virtual void UpdatePosition(
		PHYSICS_ENTITY & game_entity,
		const float delta_time
		) = 0;

	// .. FUNCTIONS

	// -- PRIVATE

private:

	// .. ATTRIBUTES

	// .. VARIABLES

};
#endif