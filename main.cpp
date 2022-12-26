#include <bits/stdc++.h>
using namespace std;

class Calculator
{
public:
    double Naive_Get_Mean()
    {
        long long sum = 0;
        for (auto &num : nums)
        {
            sum += num;
        }
        return (double)sum / nums.size();
    }
    double Naive_Get_Variance()
    {
        auto mean = Naive_Get_Mean();
        double difference_sum = 0;
        for (auto &num : nums)
        {
            difference_sum += ((double)num - mean) * ((double)num - mean);
        }
        return (double)difference_sum / nums.size();
    }
    double Formula_Get_Mean()
    {
        auto new_mean = previous_mean + (double) (current_num - previous_mean) / counts;
        previous_mean = new_mean;
        return new_mean;
    }
    double Formula_Get_Variance()
    {
        auto new_square_mean = previous_square_mean + (double) ( (current_num*current_num) - previous_square_mean) / counts;
        previous_square_mean = new_square_mean;
        return new_square_mean - (previous_mean) * (previous_mean);
    }
    void Put(long long num)
    {
        nums.push_back(num);
        current_num = num;
        counts++;
    }
    void Print_Naive()
    {
        cout << "Naive Mean : " << Naive_Get_Mean() << " Naive Variance : " << Naive_Get_Variance() << "\n";
        return;
    }
    void Print_Formula()
    {
        cout << "Formula Mean : " << Formula_Get_Mean() << " Formula Variance : " << Formula_Get_Variance() << "\n";
        return;
    }

private:
    vector<long long> nums;
    
    long long counts;
    long long current_num;

    double previous_mean;
    double previous_square_mean;
};

int main()
{
    auto cal = new Calculator();
    long long num;
    while (cin >> num)
    {
        cal->Put(num);
        cal->Print_Naive();
        cal->Print_Formula();
        cout << endl;
    }
    return 0;
}
