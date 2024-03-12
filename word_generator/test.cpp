#include <iostream>
#include "words_generator.h"
using namespace std;

int main()
{
    WordsGenerator gen;
    string temp;
    while(cin >> temp)
    {
        cout << gen() << endl;
    }
}