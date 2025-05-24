/*
	1.В последовательности чисел a1, a2, a3, ... задан первый член, а остальные вычисляются по формуле ai = (ai - 1)2 mod M + 1. Найти N-й член последовательности.
	Ограничения: 1 ≤ M ≤ 10000,  2 ≤ N ≤ 10^18, 0 ≤ a1 ≤ M.
	Ввод из файла INPUT.TXT. В первой строке находятся числа M, N и a1 , разделённые пробелом.
	Вывод в файл OUTPUT.TXT. Вывести одно число - aN.
	Примеры 
	Ввод 1      Ввод 2
	10000 3 4   7777 2000000000 0
	Вывод 1     Вывод 2
	290         3834

	2.Лебедев Д.А ПС-23
	3.Visual Studio 2019, C++
*/

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

int FindNum(int m, uint64_t n, int a1)
{
	int current = a1;
	std::vector<int> nums{ a1 };
	bool isCycle = false;
	std::vector<int> cycle{};
	int beginCyclePosition{};
	std::vector<int>::iterator position{};
	int passedNums = 1;

	for (uint64_t i = 1; i < n; ++i)
	{
		current = (current * current) % m + 1;
		position = std::find(nums.begin(), nums.end(), current);

		if (position != nums.end())
		{
			beginCyclePosition = std::distance(nums.begin(), position);
			isCycle = true;

			for (int j = beginCyclePosition; j < nums.size(); ++j)
			{
				cycle.push_back(nums[j]);
			}

			break;
		}

		passedNums += 1;
		nums.push_back(current);
	}

	if (isCycle == false)
	{
		return current;
	}
	int numberPosition = (n - beginCyclePosition - 1) % cycle.size();

	return cycle.at(numberPosition);
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	uint64_t n{};
	int result, m, a{};
	input >> m >> n >> a;

	auto start = std::chrono::high_resolution_clock::now();
	result = FindNum(m, n, a);
	auto end = std::chrono::high_resolution_clock::now();
	auto duratation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	output << result << "\n";
	output << duratation << "\n";
	return 0;
}
