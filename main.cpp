#include <bits/stdc++.h>
using namespace std;

class Calculator
{
public:
    virtual void Put(double num){

    }

    virtual double Get_Mean(){
        return 0.0;
    }

    virtual double Get_Variance(){
        return 0.9;
    }

    virtual void Print(){

    }

private:
    
};


class Naive_Calculator : public Calculator{
    public:
    void Put(double num){
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
        vector<double> nums;
};

class Formula_Calculator : public Calculator{
    public:
    void Put(double num)
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
    double current_num;

    double previous_mean;
    double previous_square_mean;
};

class Welford_Calculator : public Calculator{
    public:
    void Put(double num)
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
    double current_num;

    double previous_mean;
    double new_mean;

    double m_value;
};

struct stat{
    double mean;
    long long counts;
    double m_value;

    stat operator+(const stat& b) const
    {
        auto total_counts = counts + b.counts;
        auto delta = b.mean - mean;
        auto new_mean = mean + (delta)*(b.counts) / total_counts;
        auto new_m_value = m_value + b.m_value + 
                  delta * delta * counts * b.counts / total_counts;
    
        return stat{
            new_mean, total_counts, new_m_value
        };
    }
};

class Special_Calculator : public Calculator{
    public:

    Special_Calculator(long long o, double m): order(o), small_numbers_mean(m){

    }
    void Put(double num)
    {   
        num -= small_numbers_mean;
        num /= order;
        if( num < 1){
            small_numbers_stat.counts++;
            return;
        }
        big_numbers_stat.counts++;
        auto previous_mean = big_numbers_stat.mean;
        auto new_mean = previous_mean + (double) (num - previous_mean) / (big_numbers_stat.counts);
        auto m_value = big_numbers_stat.m_value + (num - new_mean) * (num - previous_mean);
        big_numbers_stat.mean = new_mean;
        big_numbers_stat.m_value = m_value;
    }
    double Get_Mean()
    {
        auto combined = (small_numbers_stat+big_numbers_stat);
        return combined.mean * order + small_numbers_mean;
    }
    double Get_Variance()
    {
        auto combined = (small_numbers_stat+big_numbers_stat);
        return (combined.m_value / combined.counts) * order * order;
    }

    void Print()
    {
        cout << "Special Mean : " << Get_Mean() << " Special Variance : " << Get_Variance() << "\n";
        return;
    }

    private:
    long long order;
    double small_numbers_mean;

    stat small_numbers_stat;
    stat big_numbers_stat;
};


int main()
{
    auto naive_cal = new Naive_Calculator();
    auto formula_cal = new Formula_Calculator();
    auto welford_cal = new Welford_Calculator();
    auto special_cal = new Special_Calculator(100, 0.5);
    double num;
    cout << fixed;

    while (cin >> num)
    {
        naive_cal->Put(num);
        formula_cal->Put(num);
        welford_cal->Put(num);
        special_cal->Put(num);

        naive_cal->Print();
        formula_cal->Print();
        welford_cal->Print();
        special_cal->Print();

        cout << endl;
    }
    return 0;
}
