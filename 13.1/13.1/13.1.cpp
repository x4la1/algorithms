#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <windows.h>

const uint64_t C = std::pow(2, 63) - 1;
const uint32_t X = 31;

uint64_t Hash(const std::string& str)
{
	uint64_t result{};
	uint32_t m = str.length();


	for (size_t i = 0; i < str.length(); ++i)
	{
		result = (result + (static_cast<uint64_t>(tolower(str[i])) * static_cast<uint64_t>(std::pow(X, m - i + 1)))) % C;
	}

	return result;
}

bool CompareString(const std::string& str1, const std::string& str2)
{
	for (size_t i = 0; i < str1.length(); ++i)
	{
		if (tolower(str1[i]) != tolower(str2[i]))
		{
			return false;
		}
	}
	return true;
}

std::pair<uint32_t, uint32_t> FindLineAndPosition(uint32_t pos, const std::vector<uint32_t>& vec)
{
	
	if (vec.size() == 1)
	{ 
		return { 1, pos };
	}

	for (size_t i = 0; i < vec.size(); ++i)
	{
		
		if ((i == vec.size() - 1) || (pos < vec[i + 1]))
		{
			return { i + 1, pos - vec[i] + 1 };
		}
	}

	return { vec.size(), pos - vec.back() + 1 };
}


std::vector<std::pair<uint32_t, uint32_t>> FindSubstring(const std::string& pattern, const std::string& filename)
{
	uint64_t patternHash = Hash(pattern);
	std::cout << patternHash << "\n";
	std::vector<std::pair<uint32_t, uint32_t>> result{};
	uint32_t m = pattern.length();
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cout << "cant open\n";
	}
	std::vector<uint32_t> startLinePos = {1};
	std::string currentText;
	uint64_t filePos = 0;
	char ch;

	while (input.get(ch))
	{
		filePos++;
		if (ch == '\n')
		{
			ch = ' ';
			startLinePos.push_back(filePos + 1);
		}
		currentText += tolower(ch);
		if (currentText.length() == m)
		{
			if (Hash(currentText) == patternHash)
			{
				if (CompareString(currentText, pattern))
				{
					uint32_t beginPos = filePos - m + 1;
					result.push_back(FindLineAndPosition(beginPos, startLinePos));
				}
			}
			currentText.erase(0, 1);
		}
	}

	return result;
}

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	std::string pattern;
	std::string filename;
	std::getline(std::cin, pattern);
	std::getline(std::cin, filename);
	std::ofstream out("output.txt");

	auto result = FindSubstring(pattern, filename);
	if (result.empty())
	{
		out << "No\n";
		return 0;
	}

	for (auto item: result)
	{
		out << item.first << " " << item.second << "\n";
	}
	return 0;
}

