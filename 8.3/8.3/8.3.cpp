#include <iostream>
#include <vector>
#include <fstream>

using Table = std::vector<std::vector<uint32_t>>;

int32_t FindMinInVectorOfInversions(const std::vector<int32_t>& vec, uint32_t cnt)
{
	for (int i = vec.size() - 1; i >= 0; --i)
	{
		if (vec[i] < 0)
		{
			continue;
		}
		if (vec[i] == i)
		{
			return i;
		}
	}
	return -1;
}

std::pair<int32_t, int32_t> FindMinPosition(const Table& Top, const Table& Left, const Table& A)
{
	std::vector<std::pair<int32_t, int32_t>> minTop;
	std::vector<std::pair<int32_t, int32_t>> minLeft;
	std::vector<int32_t> buff;
	int32_t temp;

	//left
	for (uint32_t i = 0; i < Left.size(); ++i)
	{
		for (uint32_t j = 0; j < Left[i].size(); ++j)
		{
			if (A[i][j] != 0)
			{
				continue;
			}
			buff.push_back(Left[i][j]);
		}
		temp = FindMinInVectorOfInversions(buff);
		if (temp == -1)
		{
			return std::pair<int32_t, int32_t>(-1, -1);
		}
		minLeft.push_back({ i, temp });
		buff.clear();
	}
	uint32_t cnt = 0;
	//top
	for (uint32_t i = 0; i < Top.size(); ++i)//N*(N + N) = N^2
	{
		for (uint32_t j = 0; j < Top[i].size(); ++j)
		{
			if (A[j][i] != 0)
			{
				cnt++;
				continue;
			}
			buff.push_back(Top[j][i]);
		}
		temp = FindMinInVectorOfInversions(buff);
		if (temp == -1)
		{
			return std::pair<int32_t, int32_t>(-1, -1);
		}
		minTop.push_back({ temp, i });
		buff.clear();
	}

	for (uint32_t i = 0; i < minTop.size(); ++i)
	{
		for (uint32_t j = 0; j < minLeft.size(); ++j)
		{
			if (minTop[i].first == minLeft[j].first && minTop[i].second == minLeft[j].second)
			{
				return { minTop[i].first, minTop[i].second };
			}
		}
	}


}

int main()
{
	std::ifstream input("INPUT.TXT");
	std::ofstream output("OUTPUT.TXT");
	uint32_t N;
	input >> N;

	Table Top(N, std::vector<uint32_t>(N));
	Table Left(N, std::vector<uint32_t>(N));
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

	for (uint32_t k = 0; k <= N * N; ++k)
	{
		auto position = FindMinPosition(Top, Left, A);
		if (A[position.first][position.second] != 0)
		{
			output << 0 << "\n";
			return 0;
		}
		A[position.first][position.second] = k;
	}

	for (uint32_t i = 0; i < N; ++i)
	{
		for (uint32_t j = 0; j < N; ++j)
		{
			output << A[i][j] << " ";
		}
		output << "\n";
	}
}


