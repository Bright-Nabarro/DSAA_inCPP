#include <fstream>
#include <random>
#include <vector>
#include <numeric>
using namespace std;

void fshu(auto& gen, const size_t scale, ofstream& outFile)
{
	vector<int> v(scale);
	iota(begin(v), end(v), 1);
	for(int i = v.size()-1; i > 0; --i)
	{
		uniform_int_distribution<int> dist {0, i};
		int j = dist(gen);
		std::swap(v[i], v[j]);
	}
	for(auto x : v)
		outFile << x << ' ';
}

void fgen(auto& gen, auto& dist, const size_t scale, ofstream& outFile)
{
	vector<long> randomSequence(scale);

	for(size_t i = 0; i < scale; i++)
	{
		randomSequence[i] = dist(gen);
	}

	for(auto x : randomSequence)
		outFile << x << ' ';
}

int main()
{
	random_device rd;
	mt19937 gen{rd()};
	const size_t scale1 {100};
	uniform_int_distribution<int> dist1 {0, 100};
	ofstream outFile1 { "seq/random1.txt" };
	fshu(gen, scale1, outFile1);

	const size_t scale2 { 100'000 };
	uniform_int_distribution<long> dist3 {-1'000'000, 1'000'000};
	ofstream outFile2 { "seq/random2.txt" };
	fgen(gen, dist3, scale2, outFile2);
}