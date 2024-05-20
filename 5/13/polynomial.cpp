#include <regex>
#include <cstdlib>
#include <cmath>
#include <format>
#include "polynomial.h"
using namespace std;

template<bool UpperFirst>
void Polynomial::display(std::ostream& os) const
{
	auto display_term =
	[this, &os](auto itr, auto begin)
	{
		if(itr != begin && itr->first > 0)
			os << '+';
		
		if(itr->first == 0)
		{
			os << itr->second;
			return;
		}

		if(itr->second != 1)
			os << itr->second;
		os << 'x';
		if(itr->first != 1)
		{
			os << "^" << itr->first;
		}
	};

	if constexpr(UpperFirst)
	{
		for(auto itr {pol.crbegin()}; itr != pol.crend(); ++itr)
			display_term(itr, pol.crbegin());
	}
	else
	{
		for(auto itr {pol.cbegin()}; itr != pol.cend(); ++itr)
			display_term(itr, pol.cbegin());
	}
}

template void Polynomial::display<true>(ostream& os) const;
template void Polynomial::display<false>(ostream& os) const;

Polynomial::Polynomial(string_view sv)
{
	pattern(spilt(sv));
	update();
}

Polynomial Polynomial::operator-() const
{
	Polynomial ret{*this};
	for(auto& x: ret.pol)
	{
		x.second = -x.second;
	}

	return ret;
}

Polynomial Polynomial::operator+(const Polynomial& rhs) const
{
	Polynomial ret;
	for(auto itr{pol.cbegin()}; itr != pol.cend(); ++itr)
		ret.pol[itr->first] += itr->second;
	
	for(auto itr{rhs.pol.cbegin()}; itr != rhs.pol.cend(); ++itr)
		ret.pol[itr->first] += itr->second;
	
	ret.update();
	return ret;
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const
{
	Polynomial ret;
	for(auto itr{pol.cbegin()}; itr != pol.cend(); ++itr)
		ret.pol[itr->first] -= itr->second;
	
	for(auto itr{rhs.pol.cbegin()}; itr != rhs.pol.cend(); ++itr)
		ret.pol[itr->first] -= itr->second;
	
	ret.update();
	return ret;
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const
{
	Polynomial ret;
	for(auto itrL{pol.cbegin()}; itrL != pol.cend(); ++itrL)
	{
		for(auto itrR{rhs.pol.cbegin()}; itrR != rhs.pol.cend(); ++itrR)
		{
			double exponent = itrL->first + itrR->first;
			double coefficient = itrL->second * itrR->second;
			ret.insert(coefficient, exponent);
		}
	}
	ret.update();
	return ret;
}

Polynomial Polynomial::operator^(unsigned e) const
{
	Polynomial ret{*this};
	for(unsigned i{0}; i < e; i++)
	{
		ret *= *this;
	}
	return ret;
}

void Polynomial::operator+=(const Polynomial& rhs)
{
	*this = *this + rhs;
}

void Polynomial::operator-=(const Polynomial& rhs)
{
	*this = *this - rhs;
}

void Polynomial::operator^=(unsigned e)
{
	*this = *this ^ e;
}

void Polynomial::pattern(const vector<string>& vecStr)
{
	regex patt {R"((-?\d*)x(\^\d+)?|(\d))"};
	//[0]: all, [1]: coefficient, [2]: exponent, [3]: constent(if it is)
	for(auto str: vecStr)
	{
		double coefficient;
		double exponent;
		cmatch matches;
		if(!regex_search(str.data(), matches, patt))
		{
			throw polynomial_format_error{
				format("term: {} cannot recognized", str.data())
			};
		}
		//constent
		if(matches[3].length() != 0)
		{
			char* end;
			coefficient = strtod(matches[3].first, &end);
			if(matches[3].first == end)
				throw polynomial_format_error{
					format("{} cannot cvt to double", matches[3].first)
				};
			insert(coefficient, 0);
			continue;
		}

		if(matches[1].length() == 0)
			coefficient = 1;
		else
		{
			char* end;
			coefficient = strtod(matches[1].first, &end);
			if(matches[1].first == end)
				throw polynomial_format_error{
					format("coefficient: {} cannot cvt to double", matches[1].first)
				};
		}

		if(matches[2].length() == 0)
			exponent = 1;
		else
		{
			char* end;
			exponent = strtod(matches[2].first+1, &end);
			if(matches[2].first == end)
				throw polynomial_format_error{
					format("coefficient: {} cannot cvt to double", matches[2].first)
				};
		}
		insert(coefficient, exponent);
	}
}

vector<string> Polynomial::spilt(string_view sv) const
{
	vector<string> ret;
	size_t pos{0};
	for(size_t i {0}; i < sv.length(); i++)
	{
		if(sv[i] == '+')
		{
			ret.push_back(string{sv.data()+pos, i-pos});
			pos = i+1;
		}
		else if(sv[i] == '-')
		{
			ret.push_back(string{sv.data()+pos, i-pos});
			pos = i;
		}
	}
	ret.push_back(string{sv.data()+pos, sv.length()-pos});
	return ret;
}

void Polynomial::insert_and_update(double coefficient, double exponent)
{
	auto itr = pol.find(exponent);
	
	if(itr == pol.end())
		itr = pol.emplace(exponent, coefficient).first;
	else
		itr->second += coefficient;

	if(itr->second == 0)
		pol.erase(itr);
}

void Polynomial::insert(double coefficient, double exponent)
{
	pol[exponent] += coefficient;
}

void Polynomial::update()
{
	for(auto itr{pol.begin()}; itr != pol.end();)
	{
		if(itr->second == 0)
		{
			itr = pol.erase(itr);
			continue;
		}
		++itr;
	}
}

double Polynomial::calculate(double x) const
{
	double ret{0};
	for(auto term: pol)
	{
		ret += term.second * pow(x, term.first);
	}
	return ret;
}