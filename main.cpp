#include <bits/stdc++.h>
using namespace std;

class Calculator
{
public:
    virtual void Put(long long num){

    }

    virtual double Get_Mean(){

    }

    virtual double Get_Variance(){

    }

    virtual void Print(){

    }

private:
    
};


class Naive_Calculator : public Calculator{
    public:
    void Put(long long num){
        nums.push_back(num);
    }

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
    void Print()
    {
        cout << "Naive Mean : " << Get_Mean() << " Naive Variance : " << Get_Variance() << "\n";
        return;
    }
    private :
        vector<long long> nums;
};

class Formula_Calculator : public Calculator{
    public:
    void Put(long long num)
    {   
        current_num = num;
        counts++;
    }
    double Get_Mean()
    {
        auto new_mean = previous_mean + (double) (current_num - previous_mean) / counts;
        previous_mean = new_mean;
        return new_mean;
    }
    double Get_Variance()
    {
        auto new_square_mean = previous_square_mean + (double) ( (current_num*current_num) - previous_square_mean) / counts;
        previous_square_mean = new_square_mean;
        return new_square_mean - (previous_mean) * (previous_mean);
    }
    void Print()
    {
        cout << "Formula Mean : " << Get_Mean() << " Formula Variance : " << Get_Variance() << "\n";
        return;
    }
    private:
    long long counts;
    long long current_num;

    double previous_mean;
    double previous_square_mean;
};

class Welford_Calculator : public Calculator{
    public:
    void Put(long long num)
    {   
        current_num = num;
        counts++;
    }
    double Get_Mean()
    {
        previous_mean = new_mean;
        new_mean = previous_mean + (double) (current_num - previous_mean) / counts;
        return new_mean;
    }
    double Get_Variance()
    {
        auto current_m_value = m_value;
        m_value = current_m_value + (current_num - new_mean) * (current_num - previous_mean);
        return m_value/counts;
    }
    void Print()
    {
        cout << "Welford Mean : " << Get_Mean() << " Welford Variance : " << Get_Variance() << "\n";
        return;
    }
    private:
    long long counts;
    long long current_num;

    double previous_mean;
    double new_mean;

    double m_value;
};


int main()
{
    auto naive_cal = new Naive_Calculator();
    auto formula_cal = new Formula_Calculator();
    auto welford_cal = new Welford_Calculator();
    long long num;
    while (cin >> num)
    {
        naive_cal->Put(num);
        formula_cal->Put(num);
        welford_cal->Put(num);

        naive_cal->Print();
        formula_cal->Print();
        welford_cal->Print();

        cout << endl;
    }
    return 0;
}
