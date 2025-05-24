/*
* 1.Среди всех наборов различных целых положительных чисел, сумма которых равна заданному числу N (1 ≤ N ≤ 10000), 
    найдите тот, который имеет максимальное произведение входящих в него чисел.
    Ввод из файла INPUT.TXT. В единственной строке вводится N.
    Вывод в файл OUTPUT.TXT. В единственной строке выдаются слагаемые через пробел.
  2.Лебедев Д.А. ПС-23
  3.Visual Studio 2019, C++
*/

#include <iostream>
#include <fstream>
#include <set>
int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int num{};
    input >> num;
    if (num == 1)
    {
        output << 1;
        return 0;
    }

    int sum = 0;
    int lastI = 0;
    std::set<int> setOfNums{};
    for (int i = 2;;++i)
    {
        lastI = i;
        sum += i;
        if (sum > num)
        {
            break;
        }
        setOfNums.insert(i);
    }

    int diff = 0;
    if (sum > num)
    {
        diff = lastI - (sum - num);
    }

    for (auto item: setOfNums) 
    {
        if (!setOfNums.count(item + diff))
        {
            setOfNums.insert(item + diff);
            setOfNums.erase(item);
            std::cout << item << " " << item + diff;
            break;
        }
    }

    for (auto item: setOfNums)
    {
        output << item << " ";
    }
    output << "\n";


    return 0;
}

