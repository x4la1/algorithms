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

