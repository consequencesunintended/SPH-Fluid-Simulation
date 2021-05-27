/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHYSICS_FLUID_PARTICLE_POSITION_LOADER__
	#define __PHYSICS_FLUID_PARTICLE_POSITION_LOADER__

	// -- LOCAL

	// .. REFERENCES

	#include "fundamental_data_types.h"
	#include "debug_statements.h"
	#include "graphics_image_pixel_loader.h"
	#include "math_point_2d_array.h"
	#include "math_vector_2d.h"

	// -- GLOBAL

	// .. TYPES

	class PHYSICS_FLUID_PARTICLE_POSITION_LOADER
	{
		// -- PUBLIC
	public:

		// .. CONSTRUCTORS

		PHYSICS_FLUID_PARTICLE_POSITION_LOADER(
			VOID
			) :
			PointTable()
		{
		}

		// ~~

		virtual ~PHYSICS_FLUID_PARTICLE_POSITION_LOADER(
			VOID
			)
		{
		}
		
		// ~~

		PHYSICS_FLUID_PARTICLE_POSITION_LOADER(
			const PHYSICS_FLUID_PARTICLE_POSITION_LOADER & other
			) :
			PointTable( other.PointTable )
		{
		}

		// .. OPERATORS

		PHYSICS_FLUID_PARTICLE_POSITION_LOADER & operator=(
			const PHYSICS_FLUID_PARTICLE_POSITION_LOADER & other
			)
		{
			DEBUG_check_this_expression( this != &other );

			PointTable = other.PointTable;

			return *this;
		}

		// .. ACCESSORS

		const MATH_POINT_2D_ARRAY & GetPointTable(
			VOID
			) const
		{
			return PointTable;
		}

		// ~~

		VOID SetPointTable(
			const MATH_POINT_2D_ARRAY &point_table
			)
		{
			PointTable = point_table;
		}

		// .. OPERATIONS

		VOID LoadPositions(
			const CHAR * bitmap
			);

		// -- PRIVATE

	private:

		// .. ATTRIBUTES

		MATH_POINT_2D_ARRAY
			PointTable;
	};
#endif