/*
    1.Король Камбузии с детства боится несчастливых арифметических прогрессий с разностью 13. Однажды ему представили список расходов на нужды подданных, состоящий из N чисел. Король потребовал оставить только такую начальную часть списка, в которой не скрывается несчастливая арифметическая прогрессия. Либеральная общественность, считаясь с мнением короля, настаивает, тем не менее, на сохранении как можно большей части списка. Найти максимальное значение K такое, что из первых K чисел списка невозможно выделить M чисел, следующих в порядке их нахождения в списке и образующих последовательные члены несчастливой арифметической прогрессии. Выдать члены первой обнаруженной несчастливой прогрессии. 
    Ввод из файла INPUT.TXT. Первая строка содержит два целых положительных числа N и M, разделенных пробелом: N – количество чисел в списке, а M – недопустимое число членов прогрессии. Вторая строка содержит список расходов в виде целых положительных чисел. 
    Ограничения: 2 ≤ N, M ≤ 5000, 1 ≤ Xi ≤ 65000, время 1 с.
    Вывод в файл OUTPUT.TXT. В первой строке выводится единственное число K- максимальное количество начальных чисел списка, не содержащих в качестве подсписка M последовательных членов несчастливой арифметической прогрессии. Во второй строке выводятся через пробел члены первой обнаруженной несчастливой прогрессии. Если ее не обнаружено, вывести No.
    Пример 
    Ввод
    9 3
    5 9 3 22 16 19 35 7 29
    Вывод
    6
    9 22 35
    
    2.Лебедев Д.А.
    3.Visual Studio 2019, C++

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

void Solve(std::vector<int>& nums, int& n, int& m, std::ofstream& output)
{
    std::vector<int> dp(n, 1);
    std::vector<int> prev{};
    int maxLength = n;
    int prevNum{};

    for (int i = 0; i < n; ++i)
    {
        prevNum = nums[i] - 13;
        auto found = std::find(prev.rbegin(), prev.rend(), prevNum);
        if (found != prev.rend())
        {
            size_t index = prev.size() - 1 - std::distance(prev.rbegin(), found);
            dp[i] = dp[index] + 1;
        }
        else
        {
            dp[i] = 1;
        }

        prev.push_back(nums[i]);

        if (dp[i] >= m)
        {
            maxLength = i;
            output << maxLength << "\n";

            int lastNum = nums[i];

            std::vector<int> progression;
            for (int j = 0; j < m; ++j)
            {
                progression.push_back(lastNum);
                lastNum -= 13;
            }

            for (int j = progression.size() - 1; j >= 0; --j)
            {
                output << progression[j] << " ";
            }
            output << "\n";
            break;
        }
    }

    if (maxLength == n)
    {
        output << n << "\n";
        output << "No\n";
    }
}


int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    std::vector<int> nums{};
    int n, m;

    input >> n >> m;
    
    int num{};
    for (int i = 0; i < n; ++i)
    {
        input >> num;
        nums.push_back(num);
    }

    auto start = std::chrono::high_resolution_clock::now();
    Solve(nums, n, m, output);
    auto end = std::chrono::high_resolution_clock::now();
    auto duratation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    output << duratation;

    return 0;
}

