#include <string>
#include <random>
#include <iostream>
#include "three_hash.h"     //only use quadaric probing
#include "../../word_generator/words_generator.h"
#include "../testPrimer/next_prime.h"
using namespace std;

size_t hash_by_default(const string& key, size_t tableSize)
{
    size_t hashVal {0};
    for(char ch: key)
        hashVal = 37*hashVal + ch;
    return hashVal % tableSize;
}

size_t hash_alternative(const string& key, size_t tableSize)
{
    unsigned int hashVal {216136261};

    for(char ch: key)
        hashVal = (hashVal ^ ch) * 16777619;
    return hashVal % tableSize;
}

int main()
{
    WordsGenerator gen;
    size_t tableSize {next_prime(20'000'000)};
    vector<optional<string>> hashTable1(tableSize), hashTable2(tableSize);
    size_t collosion1, collosion2;
    size_t failed1, failed2;
    for(size_t i{0}; i < 10'000'000; ++i)
    {
        string word {gen()};
        auto defaultH { quadratic_probing(word, hashTable1, hash_by_default)};
        collosion1 += defaultH.second;
        if(!defaultH.first)
            ++failed1;

        auto alterH { quadratic_probing(word, hashTable2, hash_alternative)};
        collosion2 += alterH.second;
        if(!defaultH.first)
            ++failed2;
    }
    cout << "default hash statgy: "
         << "\t\tfailed:" << failed1
         << "\tcollision:" << collosion1 << endl;

    cout << "alternative hash statgy: "
         << "\tfailed:" << failed2
         << "\tcollision:" << collosion2 << endl;
}
