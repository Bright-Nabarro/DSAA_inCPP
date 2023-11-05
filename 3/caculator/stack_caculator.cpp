#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>

class Caculator
{
  private:
	std::stack<char> m_operators;
	std::stack<std::string> m_postfix;
	std::map<char, int> m_precedence{
		std::pair<char, int>('*', 1), std::pair<char, int>('/', 1),
		std::pair<char, int>('+', 2), std::pair<char, int>('-', 2),
		std::pair<char, int>(')', 3), std::pair<char, int>('(', 3)};

	void deal_operators();
	int caculate_m_postfix();

  public:
	Caculator() = default;

	Caculator(const Caculator&) = delete;
	Caculator& operator=(Caculator&) = delete;
	int caculate();
};

int Caculator::caculate_m_postfix()
{

	if (m_precedence.find(m_postfix.top()[0]) == m_precedence.end())
		return std::stoi(m_postfix.top());

	assert(m_postfix.top().size() == 1);
	char the_operator = m_postfix.top()[0];
	m_postfix.pop();
	int num1 = caculate_m_postfix();
	m_postfix.pop();
	int num2 = caculate_m_postfix();
	m_postfix.pop();
	switch (the_operator)
	{
	case '+':
		m_postfix.push(std::to_string(num1 + num2));
		return 0;
	case '-':
		m_postfix.push(std::to_string(num1 - num2));
		return 0;
	case '*':
		m_postfix.push(std::to_string(num1 * num2));
		return 0;
	case '/':
		m_postfix.push(std::to_string(num1 / num2));
		return 0;
	default:
		throw std::logic_error("the_operator doesn't match");
	}
}

void Caculator::deal_operators()
{
	char c = m_operators.top();
	m_postfix.push(std::string(1, c));
	caculate_m_postfix();
	m_operators.pop();
	while (!m_operators.empty())
	{
		if (m_precedence[m_operators.top()] > m_precedence[c] ||
			m_operators.top() != '(')
			return;
		if (m_operators.top() == ')')
		{
			char c;
			while ((c = m_operators.top()) != '(')
			{
				m_postfix.push(std::string(1, c));
				caculate_m_postfix();
				m_operators.pop();
			}
		}
		char temp = m_operators.top();
		m_postfix.push(std::string(1, c));
		caculate_m_postfix();
		m_operators.pop();
	}
}

int Caculator::caculate()
{
	std::string expression;
	std::cin >> expression;

	std::string num{};
	bool isfirst = true;
	for (char c : expression)
	{
		if (isdigit(c) || c == '.')
			num += c;
		else if (!num.empty())
		{
			m_postfix.push(num);
			caculate_m_postfix();
			num.clear();
		}
		if (m_precedence.find(c) != m_precedence.end())
		{
			m_operators.push(c);
			if (isfirst)
				isfirst = false;
			else
				deal_operators();
		}
		//		else if (c != ' ')
		//		{
		//			throw std::logic_error("invalid expression");
		//		}
	}
	if (!num.empty())
	{
		m_postfix.push(num);
		caculate_m_postfix();
		num.clear();
	}
	if (!m_operators.empty())
	{
		deal_operators();
	}
	assert(m_postfix.size() == 1);
	return std::stoi(m_postfix.top());
}

int main()
{
	while (true)
	{
		Caculator c;
		std::cout << c.caculate() << std::endl;
	}
}
