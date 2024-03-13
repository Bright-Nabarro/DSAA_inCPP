#include <stdexcept>
#include <random>
#include "words_generator.h"
using namespace std;

WordsGenerator::WordsGenerator() :
    m_in{"words_alpha_370104L.txt"}
{
    initial({});
}

WordsGenerator::WordsGenerator(string_view sv, 
                               optional<size_t> seed) :
    m_in{sv.data()}
{
    initial(seed);
}

string WordsGenerator::operator()()
{
    return m_table[m_dist(m_gen)];
}

void WordsGenerator::initial(optional<size_t> seed)
{
    if(!seed)
    {
        random_device rd;
        seed = rd();
    }
    m_gen.seed(seed.value());

    if(m_in.fail())
    {
        throw runtime_error {"cannot open the file"};
    };
    string eachWord;
    while(getline(m_in, eachWord))
    {
        m_table.push_back(std::move(eachWord));
    }
    m_dist = std::uniform_int_distribution<size_t>{0, m_table.size()-1};
}