#ifndef __PHYSICS_SPRING_ARRAY__
#define __PHYSICS_SPRING_ARRAY__

// --LOCAL

// .. REFERENCES

#include "fundamental_data_types.h"
#include "physics_spring.h"
#include "physics_entity.h"

// -- GLOBAL

// .. TYPES

class PHYSICS_SPRING_ARRAY:
	public std::vector<PHYSICS_SPRING>
{
	// -- PUBLIC

public:

	// .. CONSTRUCTORS

	PHYSICS_SPRING_ARRAY(
		void
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
		void
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

	const std::vector<std::vector<bool>> & GetExistenceTable(
		void
		) const
	{
		return ExistenceTable;
	}

	// ..

	void SetExistenceTable(
		const std::vector<std::vector<bool>>&existence_table
		)
	{
		ExistenceTable = existence_table;
	}

	// .. OPERATIONS

	void SetItemInExistenceTable(
		const unsigned int index_x,
		const unsigned int index_y,
		bool item
		)
	{
		ExistenceTable[ index_x ][ index_y ] = item;
	}

	// ~~

    void SetMaxNumberOfPoints(
        const unsigned int size
        )
    {
		unsigned int
			counter;
		ExistenceTable.resize( size );

        FUNDAMENTAL_DATA_TYPES_loop_through_index( counter, 0, size - 1 )
        {
			ExistenceTable[ counter ].resize( size );
        }
    }
	// -- PRIVATE

private:

	// .. ATTRIBUTES

std::vector<std::vector<bool>>
		ExistenceTable;
};
#endif