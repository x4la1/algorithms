/*
	1)Написать программу для игры слитки, рассмотренной в настоящем разделе.
	Ввод из файла INPUT.TXT. В первой строке находится количество слитков N. Во второй строке идут через пробел N натуральных чисел (N ≤ 200), задающих стоимости слитков в порядке слева направо. Стоимость каждого слитка не превосходит 106.
	Вывод в файл OUTPUT.TXT. Вывести через пробел два числа: суммы стоимостей слитков, которые может гарантировать каждый игрок при правильной игре.
	2)Лебедев Денис ПС-23
	3)Visual Studio C++
*/
//out of range

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

const uint32_t MAX_C = 91;

int main()
{
	std::fstream input("input.txt");
	uint32_t N;
	input >> N;
	std::vector<uint32_t> bars(N + 1);
	uint32_t bar;
	for (auto i = 1; i <= N; ++i)
	{
		input >> bars[i];
	}

	std::vector<uint64_t> R(N + 1, 0);
	R[N] = bars[N];
	for (uint32_t K = N - 1; K >= 1; --K)
	{
		R[K] = R[K + 1] + bars[K];
	}

	std::vector<std::vector<uint64_t>> S(N + 1, std::vector<uint64_t>(MAX_C + 1, 0));
	for (uint32_t M = 1; M <= MAX_C; ++M)
	{
		S[N][M] = bars[N];
	}

	for (uint32_t K = N - 1; K >= 1; --K)
	{
 		for (uint32_t M = 1; M <= MAX_C; ++M)
		{
			if (K + 2 * M >= N)
			{
				S[K][M] = R[K];
			}
			else
			{
				uint64_t minimum = 1e10;
				uint32_t maxL = std::min(2 * M, std::min(N - K, MAX_C));
				for (uint32_t L = 1; L <= maxL; ++L)
				{
					uint64_t opponentScore = S[K + L][L];
					minimum = std::min(minimum, opponentScore);
				}
				S[K][M] = R[K] - minimum;
			}
		}
	}

	std::fstream output("output.txt");
	std::cout << S[1][1] << " " << R[1] - S[1][1] << "\n";
}
