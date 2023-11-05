#pragma once
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

class Caculator
{
	//单列, 对外只允许一个函数
  public:
	static double exec(std::string own_expr);
	Caculator(const Caculator&) = delete;
	Caculator& operator=(const Caculator&) = delete;

  private:
	Caculator() = default;
	//获取唯一实例
	static Caculator& get_instance();
	//处理操作符
	void deal_operators(const std::string& c);
	//计算
	double caculate_postfix();
	//处理own_expr,将其压入对应的栈
	std::vector<std::pair<std::string, bool>>
	deal_ownstring(std::string own_string) const;
	//重置栈
	void reset();

	std::stack<std::string> m_operators;
	std::vector<std::pair<std::string, bool>> m_postfix;
	std::map<std::string, int> m_precedence{{"*", 1}, {"/", 1}, {"+", 2},
											{"-", 2}, {")", 3}, {"(", 3}};
};