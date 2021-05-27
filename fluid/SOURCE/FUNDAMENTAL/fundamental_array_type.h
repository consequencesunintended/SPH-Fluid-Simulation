/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __FUNDAMENTAL_ARRAY_TYPE__
	#define __FUNDAMENTAL_ARRAY_TYPE__

	// -- LOCAL

	// .. REFERENCES

	#include <vector>
	#include "fundamental_data_types.h"
	using namespace std;

	// -- GLOBAL

	template < class my_type >
	class FUNDAMENTAL_ARRAY_TYPE
		: private vector< my_type >
	{
		// -- PUBLIC

	public:
		// .. CONSTRUCTORS
	
		FUNDAMENTAL_ARRAY_TYPE(
			VOID
			) : 
			vector< my_type >()
		{
		}

		// ~~

		FUNDAMENTAL_ARRAY_TYPE(
			const FUNDAMENTAL_ARRAY_TYPE & other
			) : 
			vector< my_type >( other )
		{
		}

		// ~~
		
		virtual ~FUNDAMENTAL_ARRAY_TYPE(
			VOID
			)
		{
		}

		// .. OPERATORS

		FUNDAMENTAL_ARRAY_TYPE & operator=(
			const FUNDAMENTAL_ARRAY_TYPE & other
			)
		{
			vector< my_type >::operator =( other );

			return *this;
		}

		// ~~

		my_type & operator[](
			const INDEX index
			) 
		{
			return vector< my_type >::operator []( index );
		}

		// ~~

		const my_type & operator[](
			const INDEX index
			) const
		{
			return vector< my_type >::operator []( index );
		}

		// .. OPERATIONS

		const VOID clear(
			VOID
			)
		{
			vector< my_type >::clear();
		}

		// ~~

		VOID push_back(
			const my_type & item
			)
		{
			vector< my_type >::push_back( item );
		}

		// ~~

		VOID erase(
			const UINT32 index
			)
		{
			vector< my_type >::erase( vector< my_type >::begin() + index );
		}

		// ~~

		VOID Allocate(
			const COUNTER memory_units
			)
		{
			COUNTER
				index;

			FUNDAMENTAL_DATA_TYPES_loop_through_index( index, 0, memory_units )
			{
				vector< my_type >::push_back( my_type() );
			}
		}

		// .. INQUERIES

		const UINT32 size(
			VOID
			) const
		{
			return vector< my_type >::size();
		}
	};
#endif