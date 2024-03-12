#include <string_view>
#include "three_hash.h"
#define DPRINT(x) cout << x << endl
using namespace std;

pair<bool, size_t> linear_probing (int x, vector<optional<int>>& hashTable)
{
    size_t collision = 0;
    size_t pos = x % hashTable.size(), posI = pos;
    do {
        if(!hashTable[posI].has_value())
        {
            hashTable[posI] = x;
            return {true, collision};
        }
        else
        {
            ++collision;
            ++posI;
            if(posI >= hashTable.size())
                posI -= hashTable.size();
            if(posI == pos)
                break;
        }
    } while(posI != pos);

    return {false, collision};
}

pair<bool, size_t> quadratic_probing (int x, vector<optional<int>>& hashTable)
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

pair<bool, size_t> double_hashing
    (int x, vector<optional<int>>& hashTable, function<size_t(int)> hashFunc)
{
    size_t collision = 0;
    size_t pos = x % hashTable.size(), posI = pos;
    do {
        if(!hashTable[posI].has_value())
        {
            hashTable[posI] = x;
            return {true, collision};
        }
        else
        {
            ++collision;
			//need optimization
            posI += hashFunc(x);
            if(posI >= hashTable.size())
                posI -= hashTable.size();
            if(posI == pos)
                break;
        }
    } while(posI != pos);

    return {false, collision};
}

//if hash failed, first return false, second return collision counts
pair<bool, size_t> quadratic_probing (string_view x, vector<optional<string>>& hashTable,
     function<size_t(const string&, size_t)> hashFunc)
{
    size_t collision {0};
    size_t pos {hashFunc(x.data(), hashTable.size())};
    size_t posI {pos};
	size_t bias {1};
    do {
        if(!hashTable[posI].has_value())
        {
            hashTable[posI] = x.data();
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
