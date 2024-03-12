#include <iostream>
#include <optional>
#include <vector>
#include <array>
#include <functional>
#include <random>
#include "three_hash.h"
using namespace std;


void print_hash(const vector<optional<int>>& hashTable)
{
    for(size_t i {0}; i < hashTable.size(); ++i)
    {
        cout << i << "\t"; 
        if(hashTable[i].has_value())
            cout << hashTable[i].value();
        cout << endl;
    }
}

template<size_t N>
void test(function<pair<bool, size_t>(int, vector<optional<int>>&)> hash_method, 
		const array<int, N>& arr, size_t hashTableSize = 10, bool showProcess = false)
{
    vector<optional<int>> hashTable(hashTableSize);
    size_t fail {0}, totalCollision {0};
    for(int x: arr)
    {
        auto ret = hash_method(x, hashTable);   
        if(!ret.first)
            ++fail;
        totalCollision += ret.second;
		if (showProcess)
		{
			cout << "-----------------------------------------------------------\n";
        	print_hash(hashTable);
			cout << "-----------------------------------------------------------\n";
		}
    }
    cout << "fail:              " << fail << endl;
    cout << "total collision:   " << totalCollision << endl;
    print_hash(hashTable);
}

int main()
{
	random_device rd;
	mt19937 gen{rd()};
	uniform_int_distribution<int> dist{1, 9999};
	array<int, 10> a1;
	for(auto& x: a1)
		x = dist(gen);

	auto bound_double_hashing = bind(double_hashing, placeholders::_1,
			placeholders::_2, [](int x) { return 11-(x%11); } );

	test(bound_double_hashing, a1, 19, true);
}

