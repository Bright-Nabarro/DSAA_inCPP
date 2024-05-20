#include "cubic_probing.h"

std::pair<bool, size_t> quadratic_probing
    (int x, std::vector<std::optional<int>>& hashTable)
{
	size_t collision {0};
	size_t pos {x % hashTable.size()}, posI {pos};
	size_t bias {1};
	do {
		if(!hashTable[posI].has_value())
		{
			hashTable[posI] = x;
			return {true, collision};
		}
		else
		{
			++collision;
			posI += bias;
			bias += 2;
			if(posI >= hashTable.size())
				posI -= hashTable.size();
			if(posI == pos)
				break;
		}
	} while(posI != pos);
	return {false, collision};
}

std::pair<bool, size_t> cubic_probing
    (int x, std::vector<std::optional<int>>& hashTable)
{
	size_t collision {0};
	size_t bias{1};
	size_t pos { x % hashTable.size() }, posI{pos};
	do {
		if(!hashTable[posI].has_value())
		{
			hashTable[posI] = x;
			return {true, collision};
		}
		else
		{
			++collision;
			posI += bias*bias*bias;
			posI = (posI > 0) ? posI : posI % hashTable.size();
			bias++;
		}
	} while(posI != pos);
	return { false, collision };
}
