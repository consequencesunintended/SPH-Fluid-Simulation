/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHYSICS_SPRING_ARRAY__
	#define __PHYSICS_SPRING_ARRAY__

	// --LOCAL

	// .. REFERENCES

	#include "fundamental_data_types.h"
	#include "fundamental_array_type.h"
	#include "physics_spring.h"
	#include "physics_entity.h"
	#include "fundamental_bool_array_array.h"

	// -- GLOBAL

	// .. TYPES

	class PHYSICS_SPRING_ARRAY:
		public FUNDAMENTAL_ARRAY_TYPE<PHYSICS_SPRING>
	{
		// -- PUBLIC

	public:

		// .. CONSTRUCTORS

		PHYSICS_SPRING_ARRAY(
			VOID
			) :
			ExistenceTable()
		{

		}

		// ~~

		PHYSICS_SPRING_ARRAY(
			const PHYSICS_SPRING_ARRAY & other
			) :
			ExistenceTable( other.ExistenceTable )
		{

		}

		// ~~

		virtual ~PHYSICS_SPRING_ARRAY(
			VOID
			)
		{
		}
		
		// .. OPERATORS

		PHYSICS_SPRING_ARRAY & operator=(
			const PHYSICS_SPRING_ARRAY & other
			)
		{
			ExistenceTable = other.ExistenceTable;
		}

		// .. ACCESSORS

		const FUNDAMENTAL_BOOL_ARRAY_ARRAY & GetExistenceTable(
			VOID
			) const
		{
			return ExistenceTable;
		}

		// ..

		VOID SetExistenceTable(
			const FUNDAMENTAL_BOOL_ARRAY_ARRAY &existence_table
			)
		{
			ExistenceTable = existence_table;
		}

		// .. OPERATIONS

		VOID SetItemInExistenceTable(
			const INDEX index_x,
			const INDEX index_y,
			BOOL item
			)
		{
			ExistenceTable[ index_x ][ index_y ] = item;
		}

		// ~~

        VOID SetMaxNumberOfPoints(
            const UINT32 size
            )
        {
			UINT32
				counter;
			ExistenceTable.Allocate( size );

            FUNDAMENTAL_DATA_TYPES_loop_through_index( counter, 0, size - 1 )
            {
				ExistenceTable[ counter ].Allocate( size );
            }
        }
		// -- PRIVATE

	private:

		// .. ATTRIBUTES

		FUNDAMENTAL_BOOL_ARRAY_ARRAY
			ExistenceTable;
	};
#endif