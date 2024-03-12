#include <iostream>
#include <random>
#include "three_hash.h"
using namespace std;

template<size_t N>
//   fail  , collison
pair<size_t, size_t> test_collision(
    size_t hashTableSize,
    function<pair<bool, size_t>(int, vector<optional<int>>&)> hashStrategy,
    const array<int, N>& sequence)
{
    vector<optional<int>> hashTable(hashTableSize);
    size_t fail{0}, collision{0};
    for(int x: sequence)
    {
        auto ret {hashStrategy(x, hashTable)};
        if(!ret.first)
            ++fail;
        collision += ret.second;
    }
    return {fail, collision};
}

auto doubleRet(auto testFunc, size_t primeNumber, size_t hashTableSize, auto& seq)
{
    auto bindingDoubleHashing = bind(double_hashing, placeholders::_1, 
            placeholders::_2, [&](int x){return primeNumber-x%primeNumber;});
    return testFunc(hashTableSize, bindingDoubleHashing, seq);
}

int main()
{
    random_device rd;
    mt19937 gen{rd()};
    uniform_int_distribution<int> dist {0, 1999999};
    array<int, 100000> seq;
    for(auto& x: seq)
        x = dist(gen);
    
    const size_t hashTableSize {201119};
    auto simDoubleRet = [&](size_t primeNumber){
        return doubleRet(test_collision<100000>, primeNumber,
                         hashTableSize, seq);
    };

    auto linerRet = test_collision(hashTableSize, linear_probing, seq);
    auto quadraticRet = test_collision(hashTableSize, quadratic_probing, seq);
    auto doubleRet_7 = simDoubleRet(7);   
    auto doubleRet_13 = simDoubleRet(13);   
    auto doubleRet_97 = simDoubleRet(97);
    auto doubleRet_509 = simDoubleRet(509);

    cout << "hash table size: " << hashTableSize << "\tinsert "
         << seq.size() << " elements " << endl;

    cout << "liner result:"
         << "\t\tfail: " << linerRet.first
         << "\tcoll: " << linerRet.second << endl;

    cout << "quadratic result:"
         << "\tfail: " << quadraticRet.first
         << "\tcoll: " << quadraticRet.second << endl;

    cout << "double_hash(7) ret:"
         << "\tfail: " << doubleRet_7.first
         << "\tcoll: " << doubleRet_7.second << endl;

    cout << "double_hash(13) ret:"
         << "\tfail: " << doubleRet_13.first
         << "\tcoll: " << doubleRet_13.second << endl;

    cout << "double_hash(97) ret:"
         << "\tfail: " << doubleRet_97.first
         << "\tcoll: " << doubleRet_97.second << endl;

    cout << "double_hash(509) ret:"
         << "\tfail: " << doubleRet_509.first
         << "\tcoll: " << doubleRet_509.second << endl;

}