#include <iostream>
#include <vector>
#include <string_view>
using namespace std;

vector<size_t> build_next(string_view patt)
{
	vector<size_t> next(patt.size()+1);
	int len{0};
	next[0] = next[1] = len;

	size_t i{1}, pre{0};
	while(i < patt.size())
	{
		if(patt[i] == patt[pre])
		{
			len++;
			pre++;
		}
		//分为两种，一种len == 0时直接写回
		//一种len != 0时需要重新进行迭代，并且不增加 i
		//如果len等于0之后直接重新迭代，i会一直不更新
		else
		{
			len = next[pre];
			pre = next[pre];
			if(len != 0)
				continue;
		}
		next[i+1] = len;
		i++;
	}
	return next;
}

vector<size_t> kmp_search(string_view main, string_view patt)
{
	vector<size_t> ret;

	auto next { build_next(patt) };
	size_t i {0}, j {0};
	
	while(i < main.length())
	{
		if(main[i] == patt[j])
		{
			i++;
			j++;
		}
		else if(j == 0)
		{
			i++;
		}
		else
		{
			j = next[j];
		}

		if(j == patt.length())
		{
			size_t pos = i - j;
			ret.push_back(pos);
			j = 0;
			i = pos + 1;
		}
	}

	return ret;
}

int main()
{
	string_view main1 {"AABAACAADAABAABA"};
	string_view patt1 {"AABA"};
	auto m { build_next(patt1) };
	for(auto x: m)
		cout << x << ' ';
	cout << endl;
	auto r1 { kmp_search(main1, patt1) };
	for(auto x: r1)
	{
		cout << x << ':';
		cout << main1.substr(x, patt1.length()) << endl;
	}
}
