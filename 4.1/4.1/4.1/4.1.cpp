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

