#include <bits/stdc++.h>
using namespace std;

class Calculator
{
public:
    double Get_Mean()
    {
        long long sum = 0;
        for (auto &num : nums)
        {
            sum += num;
        }
        return (double)sum / nums.size();
    }
    double Get_Variance()
    {
        auto mean = Get_Mean();
        double difference_sum = 0;
        for (auto &num : nums)
        {
            difference_sum += ((double)num - mean) * ((double)num - mean);
        }
        return (double)difference_sum / nums.size();
    }
    void Put(long long num)
    {
        nums.push_back(num);
    }
    void Print()
    {
        cout << "Current Mean : " << Get_Mean() << " Current Variance : " << Get_Variance() << "\n";
        return;
    }

private:
    vector<long long> nums;
};

int main()
{
    auto cal = new Calculator();
    long long num;
    while (cin >> num)
    {
        cal->Put(num);
        cal->Print();
    }
    return 0;
}
