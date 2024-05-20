#include <cassert>
#include <vector>
#include <set>
#include <random>
#include "string_hash.h"
#include "words_generator.h"
using namespace std;

vector<string> vec_str
{
	"abc",
	"defg",
	"hijk",
	"lmn",
	"opq",
	"rst",
	"uvw",
	"xyz",
};

void test_ini()
{
	StrHashTable table1;
	StrHashTable table2{97};
	assert(table1.size() == 0);
	assert(table2.size() == 0);
}

void test_insert_contains()
{
	StrHashTable t1;
	assert(t1.insert("abc"));
	assert(t1.contains("abc"));
	assert(!t1.insert("abc"));

	StrHashTable t2;
	for(auto x: vec_str)
	{
		assert(t2.insert(x));
		assert(!t2.insert(x));
	}
	for(auto x: vec_str)
	{
		assert(t2.contains(x));
	}

	WordsGenerator wordGen;
	StrHashTable t3;
	set<string> setStr;
	for(size_t i = 0; i < 100'000; i++)
		setStr.insert(wordGen());

	for(auto& x: setStr)
	{
		assert(t3.insert(x));
		assert(!t3.insert(x));
	}
	for(auto& x: setStr)
	{
		t3.contains(x);
	}
	assert(t3.size() == setStr.size());
}

void test_remove()
{
	StrHashTable t1;
	assert(t1.insert("abc"));
	assert(t1.remove("abc"));
	assert(!t1.remove("abc"));
	assert(!t1.contains("abc"));

	StrHashTable t2;
	for(auto& x: vec_str)
	{
		t2.insert(x);
	}
	for(auto& x: vec_str)
	{
		assert(t2.remove(x));
	}
	for(auto& x: vec_str)
	{
		assert(!t2.contains(x));
		assert(!t2.remove(x));
	}

	WordsGenerator wordGen;
	StrHashTable t3;
	set<string> setStr;
	for(size_t i = 0; i < 100'000; i++)
		setStr.insert(wordGen());

	for(auto& x: setStr)
	{
		assert(t3.insert(x));
	}
	for(auto& x: setStr)
	{
		assert(t3.contains(x));
		assert(t3.remove(x));
		assert(!t3.contains(x));
	}
	assert(t3.size() == 0);
}

void test_insert_remove()
{
	static random_device rd;
	static mt19937 gen{rd()};
	bernoulli_distribution dist;
	
	StrHashTable table;
	WordsGenerator wordGen;
	set<string> set_str, input;
	for(size_t i = 0; i < 10'000; i++)
		set_str.insert(wordGen());
	auto itr1 = set_str.begin();
	auto itr2 = input.begin();

	while(!set_str.empty())
	{
		if(!input.empty() && dist(gen))
		{
			assert(table.remove(*itr2));
			input.erase(itr2);
			itr2 = input.begin();
		}
		else
		{
			assert(table.insert(*itr1));
			set_str.erase(itr1);
			itr1 = set_str.begin();
			if(set_str.empty())
				break;
			input.insert(*itr1);
			itr2 = input.begin();
		}
	}
}

int main()
{
	test_ini();
	test_insert_contains();
	test_remove();
	test_insert_remove();
}