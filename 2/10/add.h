#ifndef ADD_H
#define ADD_H
#include <list>
#include <string>
using std::list;
using std::string;

string add_list_imp(string num1, string num2)
{
	int carry = 0; //进位
	int n1 = num1.size(), n2 = num2.size();
	int n = n1 > n2 ? n1 : n2; // n为最大位
	list<char> result;
	for (int i = 0; i < n; i++)
	{
		int digit1 = i < n1 ? num1[n1 - 1 - i] - '0' : 0;
		int digit2 = i < n2 ? num2[n2 - 1 - i] - '0' : 0;
		int sum = carry + digit1 + digit2;
		carry = sum / 10;
		result.insert(result.begin(), sum % 10 + '0');
	}
	if (carry > 0)
		result.insert(result.begin(), '1');
	return string(result.cbegin(), result.cend());
}

string add_string_imp(string num1, string num2)
{
	int carry = 0; //进位
	int n1 = num1.size(), n2 = num2.size();
	int n = n1 > n2 ? n1 : n2; // n为最大位
	string result;
	for (int i = 0; i < n; i++)
	{
		int digit1 = i < n1 ? num1[n1 - 1 - i] - '0' : 0;
		int digit2 = i < n2 ? num2[n2 - 1 - i] - '0' : 0;
		int sum = carry + digit1 + digit2;
		carry = sum / 10;
		result.insert(result.begin(), sum % 10 + '0');
	}
	if (carry > 0)
		result.insert(result.begin(), '1');
	return result;
}

#endif // ADD_H