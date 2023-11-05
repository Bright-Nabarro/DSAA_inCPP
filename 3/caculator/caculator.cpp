#include "caculator.h"

Caculator& Caculator::get_instance()
{
	static Caculator instance;
	return instance;
}

double Caculator::exec(std::string own_expr)
{
	Caculator& instance = get_instance();
	const auto& vec_expr = instance.deal_ownstring(own_expr);
	for (auto expr_itr = vec_expr.cbegin(); expr_itr != vec_expr.cend();
		 expr_itr++)
	{
		//数字
		if (expr_itr->second)
			instance.m_postfix.push_back(*expr_itr);
		else
			instance.deal_operators(expr_itr->first);
	}
	while (!instance.m_operators.empty())
	{
		instance.m_postfix.push_back({instance.m_operators.top(), false});
		instance.m_operators.pop();
	}
	double result = instance.caculate_postfix();

	instance.reset();
	return result;
}

void Caculator::deal_operators(const std::string& c)
{
	if (m_operators.empty() || c == "(")
	{
		m_operators.push(c);
		return;
	}

	if (c == ")")
	{
		while (m_operators.top() != "(")
		{
			m_postfix.push_back({m_operators.top(), false});
			m_operators.pop();
		}
		m_operators.pop();
		return;
	}
	while (!m_operators.empty() &&
		   m_precedence[m_operators.top()] <= m_precedence[c])
	{
		m_postfix.push_back({m_operators.top(), false});
		m_operators.pop();
	}
	m_operators.push(c);
}

double Caculator::caculate_postfix()
{
	std::stack<int> nums;
	for (auto expr_itr = m_postfix.cbegin(); expr_itr != m_postfix.cend();
		 expr_itr++)
	{
		if (expr_itr->second)
		{
			int n = stod(expr_itr->first);
			nums.push(n);
		}
		else
		{
			assert(expr_itr->first.size() == 1);
			assert(nums.size() >= 2);
			char the_operator = expr_itr->first[0];
			double num1 = nums.top();
			nums.pop();
			double num2 = nums.top();
			nums.pop();
			double temp_result;
			switch (the_operator)
			{
			case '+':
				temp_result = num1 + num2;
				break;
			case '-':
				temp_result = num1 - num2;
				break;
			case '*':
				temp_result = num1 * num2;
				break;
			case '/':
				temp_result = num1 / num2;
				break;
			default:
				throw std::logic_error("operator: " + expr_itr->first +
									   "is illegal");
			}
			nums.push(temp_result);
		}
	}
	assert(nums.size() == 1);
	return nums.top();
}

std::vector<std::pair<std::string, bool>>
Caculator::deal_ownstring(std::string own_expr) const
{
	std::string num;
	// bool为ture是数字
	std::vector<std::pair<std::string, bool>> vec_expr_Dnum;

	std::string str_c;
	for (char c : own_expr)
	{
		if (c == ' ')
			continue;

		bool is_num = isdigit(c) || c == '.';
		if (is_num)
			num += c;
		else if (!num.empty())
		{
			//查找小数点出现个数
			if (std::count(num.begin(), num.end(), '.') >= 2)
				throw std::invalid_argument("illegal number: " + num);
			vec_expr_Dnum.push_back({num, true});
			num.clear();
		}

		str_c = std::string(1, c);
		if (m_precedence.find(str_c) != m_precedence.end())
		{
			vec_expr_Dnum.push_back({str_c, false});
		}
		else if (!is_num && c != ' ')
			throw std::invalid_argument("illegal argument: " + str_c);
	}
	//表达式以数字或者右括号截尾, 在num中未被插入
	if (num == "")
	{
		if (str_c != ")")
			throw std::invalid_argument("last substring not digit");
	}
	else
		vec_expr_Dnum.push_back({num, true});

	return vec_expr_Dnum;
}

void Caculator::reset()
{
	while (!m_operators.empty())
		m_operators.pop();
	m_postfix.clear();
}