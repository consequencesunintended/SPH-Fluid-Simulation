#ifndef __PHYSICS_SPRING_ARRAY__
#define __PHYSICS_SPRING_ARRAY__

#include "physics_spring.h"
#include "physics_entity.h"


struct PHYSICS_SPRING_ARRAY : public std::vector<PHYSICS_SPRING>
{
	void SetItemInExistenceTable(const size_t index_x, const size_t index_y, bool item)
	{
		ExistenceTable[index_x][index_y] = item;
	}

	void SetMaxNumberOfPoints(const unsigned int size)
	{
		unsigned int counter;

		ExistenceTable.resize(size);

		for (counter = 0; counter <= size - 1; counter++)
		{
			ExistenceTable[counter].resize(size);
		}
	}
	std::vector<std::vector<bool>> ExistenceTable;
};
#endif