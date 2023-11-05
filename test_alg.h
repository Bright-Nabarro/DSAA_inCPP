#ifndef TEST_ALG_H
#define TEST_ALG_H
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T> class my_alg_test
{
  private:
	std::vector<int> amount_N;
	std::vector<int> runtimes;
	const std::function<T> alg;

  public:
	my_alg_test(std::function<T> alg);
	my_alg_test(std::function<T> alg, int start, int step, int frequency = 10);
	my_alg_test(std::function<T> alg, std::vector<int> amount_N);

	// Big-five all default
	my_alg_test(const my_alg_test&) = default;
	my_alg_test(my_alg_test&&) = default;
	~my_alg_test() = default;
	my_alg_test& operator=(const my_alg_test&) = default;
	my_alg_test& operator=(my_alg_test&&) = default;

	//
	void change_amount_N(int start, int step, int frequency = 10);
	void change_amount_N(std::vector<int> amount_N);
	std::vector<int> test_alg();
	//指定最小测试次数, least_times为start的倍数
	std::vector<int> test_alg(int least_times);
	// interface
	const std::vector<int> alg_amount_N() const { return amount_N; }
	const std::vector<int> alg_runtimes() const { return runtimes; }
	void output_minus(int setN = 10) const;
};

template <typename T>
my_alg_test<T>::my_alg_test(std::function<T> alg)
	: alg(alg), amount_N(10), runtimes(10)
{
	//默认测试范围1000 -> 10000, 步长1000
	for (int i = 1000; i <= 10000; i += 1000)
		amount_N[i] = i;
}

template <typename T>
my_alg_test<T>::my_alg_test(std::function<T> alg, int start, int step,
							int frequency)
	: alg(alg), amount_N(frequency), runtimes(frequency)
{
	for (auto& x : amount_N)
	{
		x = start;
		start += step;
	}
}

template <typename T>
my_alg_test<T>::my_alg_test(std::function<T> alg, std::vector<int> amount_N)
	: alg(alg), amount_N(amount_N), runtimes(amount_N.size())
{
}

template <typename T>
void my_alg_test<T>::change_amount_N(int start, int step, int frequency)
{
	this->amount_N.resize(frequency);
	for (auto& x : amount_N)
	{
		x = start;
		start += step;
	}
}

template <typename T>
void my_alg_test<T>::change_amount_N(std::vector<int> amount_N)
{
	this->amount_N = amount_N;
}

template <typename T> std::vector<int> my_alg_test<T>::test_alg()
{
	for (int i = 0; i < amount_N.size(); i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		alg(amount_N[i]);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		runtimes[i] = duration.count();
	}
	return runtimes;
}

template <typename T> std::vector<int> my_alg_test<T>::test_alg(int least_times)
{
	auto least_N = least_times * amount_N[0];
	int test_times = 1;
	for (int i = 0; i < amount_N.size(); i++)
	{
		//判断提前
		if (least_N > amount_N[i])
			int test_times =
				std::ceil(static_cast<double>(least_N) / amount_N[i]);

		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < test_times; i++)
			alg(amount_N[i]);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		runtimes[i] = duration.count();
	}
	return runtimes;
}

template <typename T> void my_alg_test<T>::output_minus(int setN) const
{
	for (auto x : amount_N)
		std::cout << std::setw(setN) << x;
	std::cout << std::endl;
	for (auto x : runtimes)
	{
		auto minus_second = static_cast<double>(x) / 1000;
		std::cout << std::setw(setN) << std::fixed << std::setprecision(3)
				  << minus_second;
	}
	std::cout << std::endl;
}

//独立函数, 测试单个N的函数
template <typename T> long test_single(std::function<T> alg, int amount)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < amount; i++)
		alg();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	return duration.count();
}

#endif // TEST_ALG_H