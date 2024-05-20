#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <string_view>
#include <stdexcept>

class Polynomial
{
public:
	Polynomial() = default;
	Polynomial(std::string_view sv);
	template<bool UpperFirst = true>
	void display(std::ostream& os) const;

	Polynomial operator-() const;
	Polynomial operator+(const Polynomial& rhs) const;
	Polynomial operator-(const Polynomial& rhs) const;
	Polynomial operator*(const Polynomial& rhs) const;
	Polynomial operator^(unsigned e) const;

	void operator+=(const Polynomial& rhs);
	void operator-=(const Polynomial& rhs);
	void operator*=(const Polynomial& rhs);
	void operator^=(unsigned e);

	double calculate(double x) const;
private:
	void pattern(const std::vector<std::string>& vecStr);
	std::vector<std::string> spilt(std::string_view sv) const;
	void insert_and_update(double coefficient, double exponent);
	void insert(double coefficient, double exponent);
	void update();
private:
	std::map<double, double> pol;
};

class polynomial_format_error: public std::runtime_error
{
public:
	polynomial_format_error(const char* s): std::runtime_error(s){};
	polynomial_format_error(const std::string& str): std::runtime_error(str){};
};