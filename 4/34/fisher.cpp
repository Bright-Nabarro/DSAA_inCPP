#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iostream>
using namespace std;

template<typename Ty, typename Gen>
void shuffle_alg(vector<Ty>& vtr, Gen gen)	//θ(N)
{
	for(size_t i = vtr.size(); static_cast<int>(i) != -1; i--)
	{
		uniform_int_distribution<size_t> dist{0, i};
		std::swap(vtr[dist(gen)], vtr[i]);
	}
}

int main()
{
	random_device rd;
	mt19937 gen{ rd() };
	vector<int> vec(20);
	iota(begin(vec), end(vec), 1);
	copy(begin(vec), end(vec), ostream_iterator<int>(cout, " "));
	cout << '\n';
	shuffle_alg(vec, gen);
	copy(begin(vec), end(vec), ostream_iterator<int>(cout, " "));
	cout << '\n';
}