#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <random>
#include <optional>

class WordsGenerator
{
public:
    WordsGenerator();
    WordsGenerator(std::string_view sv, 
                   std::optional<size_t> seed = {});
    WordsGenerator(const WordsGenerator&) = delete;
    WordsGenerator& operator=(const WordsGenerator&) = delete;
    std::string operator()();
private:
    void initial(std::optional<size_t> seed);
private:
    std::ifstream m_in;
    std::vector<std::string> m_table;
    std::mt19937 m_gen;
    std::uniform_int_distribution<size_t> m_dist;
};