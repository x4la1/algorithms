/*
	1)8.3. Матрица (8)
В матрице A размера NN числа от 1 до N2. Каждое число записано ровно один раз. Даны две матрицы размера N  N: Top и Left. Значение Topi j определяет количество чисел, больших Ai j и расположенных выше по столбцу, Lefti j - количество чисел, больших Ai j и расположенных левее по строке. Найти возможные значения матрицы A. Если решений несколько, вывести любое.
Ввод из файла INPUT.TXT. В первой строке N (1 ≤ N ≤100), затем N строк матрицы Top (числа через пробел), затем N строк матрицы Left. Числа в обеих матрицах от 0 до N.
Вывод в файл OUTPUT.TXT матрицы A – N строк, числа в строке через пробел. Если решений нет, вывести 0.
	2)Visual Studio C++
	3)Лебедев Денис ПС-23

*/


#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <chrono>

using Table = std::vector<std::vector<uint32_t>>;
using PairTable = std::vector<std::vector<std::pair<uint32_t, uint32_t>>>;

int32_t FindMinInVectorOfInversions(std::vector<int32_t>& vec)
{
	for (int i = vec.size() - 1; i >= 0; --i)
	{
		if (vec[i] == i)
		{
			return i;
		}
	}


	return -1;
}

std::pair<int32_t, int32_t> FindMinPos(Table& Top, Table& Left)
{
	std::vector<std::pair<int32_t, int32_t>> minTop;
	std::vector<std::pair<int32_t, int32_t>> minLeft;
	std::vector<int32_t> buff;
	int32_t temp;
	std::pair<uint32_t, uint32_t> finalPair = {1000000, 1000000 };

	//left
	for (uint32_t i = 0; i < Left.size(); ++i)
	{
		for (uint32_t j = 0; j < Left[i].size(); ++j)
		{
			buff.push_back(Left[i][j]);
		}
		temp = FindMinInVectorOfInversions(buff);
		if (temp == -1)
		{
			buff.clear();
			continue;
		}
		minLeft.push_back({ i, temp });
		buff.clear();
	}
	buff.clear();

	//top
	for (uint32_t i = 0; i < Top.size(); ++i)//N*(N + N) = N^2
	{
		for (uint32_t j = 0; j < Top[i].size(); ++j)
		{
			buff.push_back(Top[j][i]);
		}
		temp = FindMinInVectorOfInversions(buff);
		if (temp == -1)
		{
			buff.clear();
			continue;
		}
		minTop.push_back({ temp, i });
		buff.clear();
	}

	

	for (uint32_t i = 0; i < minTop.size(); ++i) //N^2
	{
		for (uint32_t j = 0; j < minLeft.size(); ++j)
		{
			if (minTop[i].first == minLeft[j].first && minTop[i].second == minLeft[j].second)
			{
				finalPair = { minTop[i].first, minTop[i].second };
				break;
			}
		}
	}

	if (finalPair.first == 1000000 || finalPair.second == 1000000)
	{
		return finalPair;
	}

	Top[finalPair.first][finalPair.second] = -1;
	Left[finalPair.first][finalPair.second] = -1;

	for (uint32_t i = finalPair.first + 1; i < Top.size(); ++i)
	{
		if (Top[i][finalPair.second] != -1)
		{
			Top[i][finalPair.second] += 1;
		}
	}

	for (uint32_t i = finalPair.second + 1; i < Left.size(); ++i)
	{
		if (Left[finalPair.first][i] != -1)
		{
			Left[finalPair.first][i] += 1;
		}
	}
	return finalPair;
}

std::vector<std::pair<uint32_t, uint32_t>> FindMinPositions(Table& Top, Table& Left)
{
	std::vector<std::pair<uint32_t, uint32_t>> result;
	std::pair<uint32_t, uint32_t> pair;

	for (uint32_t i = 0; i < Top.size() * Top.size(); ++i)
	{
		pair = FindMinPos(Top, Left);
		if (pair.first == 1000000 || pair.second == 1000000)
		{
			return {};
		}
		result.push_back(pair);
	}

	return result;
}

int main() //заранее найти позиции
{
	
	
	
	std::ifstream input("INPUT.TXT");
	std::ofstream output("OUTPUT.TXT");
	uint32_t N;
	input >> N;

	Table Top(N, std::vector<uint32_t>(N));
	Table Left(N, std::vector<uint32_t>(N));
	PairTable MegaTable(N, std::vector<std::pair<uint32_t, uint32_t>>(N));
	Table A(N, std::vector<uint32_t>(N, 0));

	for (uint32_t i = 0; i < N; ++i)
	{
		for (uint32_t j = 0; j < N; ++j)
		{
			input >> Top[i][j];
		}
	}

	for (uint32_t i = 0; i < N; ++i)
	{
		for (uint32_t j = 0; j < N; ++j)
		{
			input >> Left[i][j];
		}
	}
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::pair<uint32_t, uint32_t>> pairs = FindMinPositions(Top, Left);
	if (pairs.empty())
	{
		output << 0 << "\n";
		return 0;
	}

	std::pair<uint32_t, uint32_t> pair;
	for (uint32_t k = 1; k <= N * N; ++k)
	{
		pair = pairs[k - 1];
		if (A[pair.first][pair.second] != 0)
		{
			output << 0;
			return 0;
		}

		A[pair.first][pair.second] = k;
	}

	for (uint32_t i = 0; i < N; ++i)
	{
		for (uint32_t j = 0; j < N; ++j)
		{
			output << A[i][j] << " ";
		}
		output << "\n";
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duratation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << duratation;
}


