/*
	1)Требуется найти все вхождения образца в текстовом файле методом Рабина-Карпа. В файле нет переноса слов. Образец может включать пробелы и переходить с одной строки файла на другую. Конец строки файла может интерпретироваться как пробел. Результаты поиска не должны зависеть от регистра букв, то есть каждая буква в образце и файле может быть как строчной, так  и прописной. Файл не должен полностью загружаться в оперативную память.
	Ввод из файла INPUT.TXT. Первая строка файла является образцом и имеет длину от 1 до 255. Вторая строка задает имя текстового файла.
	Вывод в файл OUTPUT.TXT. Вывести в каждой строке через пробел последовательность номеров строк и позиций в строке, начиная с которых образец входит в текст. Нумерация строк и позиций в строке начинается с 1. Если вхождений нет, вывести No.
	2)Лебедев Денис ПС-23
	3)Visual Studio C++
	4)https://ru.wikipedia.org/wiki/%D0%A1%D0%BA%D0%BE%D0%BB%D1%8C%D0%B7%D1%8F%D1%89%D0%B8%D0%B9_%D1%85%D0%B5%D1%88
*/
//чекать первый символ строки а потом увеличивать позицию

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>

const uint64_t C = std::pow(2, 63) - 1;
const uint32_t X = 31;

char ProcessChar(char ch)
{
	if (ch == '\n')
	{
		return ' ';
	}

	return tolower(ch);
}

uint64_t Hash(const std::string& str)
{
	uint64_t result{};
	uint32_t m = str.length();

	for (size_t i = 0; i < str.length(); ++i)
	{
		result = (result * X + (static_cast<uint64_t>(ProcessChar(str[i])))) % C;
	}

	return result;
}

bool StringCompare(const std::string& str1, const std::string& str2)
{
	for (size_t i = 0; i < str1.length(); ++i)
	{
		if (ProcessChar(str1[i]) != ProcessChar(str2[i]))
		{
			return false;
		}
	}
	return true;
}

std::vector<std::pair<uint32_t, uint32_t>> FindSubstring(const std::string& pattern, const std::string& filename)
{
	std::ifstream input(filename);
	input.imbue(std::locale("Russian_Russia.1251"));

	uint64_t patternHash = Hash(pattern);
	uint32_t m = pattern.length();
	uint64_t powX = 1;
	for (uint32_t i = 0; i < m - 1; ++i)
	{
		powX = (powX * X) % C;
	}
	uint64_t currentHash;

	std::vector<std::pair<uint32_t, uint32_t>> result{};
	std::pair<uint32_t, uint32_t> position = { 1, 1 };
	std::string currentText;
	char ch;


	for (uint32_t i = 0; i < m && input.get(ch); ++i)
	{
		currentText += ch;
	}
	currentHash = Hash(currentText);

	if (currentHash == patternHash && StringCompare(currentText, pattern))
	{
		result.push_back(position);
	}

	if (currentText[0] == '\n')
	{
		position.first += 1;
		position.second = 1;
	}
	else
	{
		position.second += 1;
	}
	currentHash = (currentHash + C - (static_cast<uint64_t>(ProcessChar(currentText[0])) * powX) % C) % C;
	currentText.erase(0, 1);


	while (input.get(ch))
	{
		currentText += ch;
		currentHash = (currentHash * X + static_cast<uint64_t>(ProcessChar(ch))) % C;

		if (currentText.length() == m)
		{
			if (currentHash == patternHash)
			{
				if (StringCompare(currentText, pattern))
				{
					result.push_back(position);
				}
			}

			if (currentText[0] == '\n')
			{
				position.first += 1;
				position.second = 1;
			}
			else
			{
				position.second += 1;
			}
			currentHash = (currentHash + C - (static_cast<uint64_t>(ProcessChar(currentText[0])) * powX) % C) % C;
			currentText.erase(0, 1);
		}
	}

	return result;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::ifstream inputFile("INPUT.txt");
	inputFile.imbue(std::locale("Russian_Russia.1251"));
	std::string pattern;
	std::string filename;
	std::getline(inputFile, pattern);
	std::getline(inputFile, filename);
	std::ofstream out("OUTPUT.txt");

	auto start = std::chrono::high_resolution_clock::now();
	auto result = FindSubstring(pattern, filename);
	
	if (result.empty())
	{
		out << "No\n";
		return 0;
	}

	for (auto item : result)
	{
		out << item.first << " " << item.second << "\n";
	}
	
	auto end = std::chrono::high_resolution_clock::now();
	auto duratation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << duratation;
	return 0;
}
