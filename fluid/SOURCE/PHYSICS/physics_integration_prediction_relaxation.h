
// This is an integration based on the paper published by
// "CLAVET, S., BEAUDOIN, P., AND POULIN, P. 2005. Particle-based 
// viscoelastic ?uid simulation. In SCA 2005, 219–228" A link to 
// view the paper  is avaiable here 
// http://www.iro.umontreal.ca/labs/infographie/papers/Clavet-2005-PVFS/pvfs.pdf


#ifndef __PHSYICS_INTEGRATION_PREDICTION_RELAXATION__
#define __PHSYICS_INTEGRATION_PREDICTION_RELAXATION__

// -- LOCAL

// .. REFERENCES

#include "fundamental_data_types.h"
#include "physics_integration.h"
#include "physics_entity.h"

// -- GLOBAL

// .. TYPES

class PHSYICS_INTEGRATION_PREDICTION_RELAXATION
	: public PHYSICS_INTEGRATION
{
	// -- PUBLIC
public:

	// .. CONSTRUCTORS

	PHSYICS_INTEGRATION_PREDICTION_RELAXATION(
		void
		) :
		PHYSICS_INTEGRATION()
	{
	}

	// ~~

	PHSYICS_INTEGRATION_PREDICTION_RELAXATION(
		const PHSYICS_INTEGRATION_PREDICTION_RELAXATION & other
		) :
		PHYSICS_INTEGRATION( other )
	{
	}

	// ~~

	virtual ~PHSYICS_INTEGRATION_PREDICTION_RELAXATION(
		void
		)
	{
	}

	// .. OPERATORS

	PHSYICS_INTEGRATION_PREDICTION_RELAXATION & operator=(
		const PHSYICS_INTEGRATION_PREDICTION_RELAXATION & other
		)
	{
		assert( this != &other );

		return *this;
	}


	// .. OPERATIONS

	virtual void UpdateVelocity(
		PHYSICS_ENTITY & game_entit,
		const float delta_time
		);

	// ~~

	virtual void UpdatePosition(
		PHYSICS_ENTITY & game_entity,
		const float delta_time
		);
};
#endif