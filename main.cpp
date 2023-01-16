#include <bits/stdc++.h>
using namespace std;

class Integer_Calculator
{
public:
    virtual void Put(long long num){
    }

    virtual double Get_Variance(){
        return 0.0;
    }

    virtual void Print(){
    }
};

class Float_Calculator
{
public:
    virtual void Put(double num){
    }

    virtual double Get_Variance(){
        return 0.0;
    }

    virtual void Print(){
    }
};

class Q1_Calculator : public Integer_Calculator{
    public:
    void Put(long long num)
    {   
        sum_of_x += num;
        sum_of_x_square += num*num;
        counts++;
    }
    double Get_Variance()
    {
        return sum_of_x_square / counts - pow(sum_of_x / counts, 2);
    }
    void Print()
    {
        cout << "Q1 Variance : " << Get_Variance() << "\n";
        return;
    }
    private:
    long long sum_of_x;
    long long sum_of_x_square;
    long long counts;
};

class Q2_Calculator : public Float_Calculator{
    public:
    void Put(double num)
    {   
        counts++;

        auto old_mean = mean;
		mean = mean + (num - mean) / counts;
		m_value = m_value +(num - mean) * (num - old_mean);
    }
    double Get_Variance()
    {
        return m_value/counts;
    }
    void Print()
    {
        cout << "Q2 Variance : " << Get_Variance() << "\n";
        return;
    }
    private:
    long long counts;
    double mean;
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

class Q3_Calculator : public Float_Calculator{
    public:

    void Put(double num)
    {   
        if(num > 1000){
            big_calculator.Put(num);
            return;
        }
        small_calculator.Put(num);
    }
    double Get_Variance()
    {
        big_calculator.Get_Variance() + small_calculator.Get_Variance();
    }

    void Print()
    {
        cout << "Q3 Variance : " << Get_Variance() << "\n";
        return;
    }

    private:
    Q2_Calculator big_calculator;
    Q2_Calculator small_calculator;
};


class Q4_Calculator : public Float_Calculator{
    public:

    void Put(double num)
    {   
        current_timestamp++;
        counts++;

        num -= sample_mean;

        sum_of_x += num;
        sum_of_x_square += num * num;

        prefix_sum_of_x[current_timestamp] = sum_of_x;
        prefix_sum_of_x_square[current_timestamp] = sum_of_x_square;
    }
    double Get_Variance()
    {
        return sum_of_x_square / counts - pow(sum_of_x / counts, 2);
    }

    double Get_Variance(long long starting_time){
        auto sum_it = prefix_sum_of_x.lower_bound(starting_time);
        auto square_sum_it = prefix_sum_of_x_square.lower_bound(starting_time);

        return square_sum_it->second / counts - pow(sum_it->second/ counts, 2);
    }

    void Print()
    {
        cout << " Q4 Variance : " << Get_Variance() << "\n";
        return;
    }

    private:
    long long counts;
    double sample_mean;
    long long current_timestamp;
    map<long long, double> prefix_sum_of_x;
    map<long long, double> prefix_sum_of_x_square;
    long long sum_of_x;
    long long sum_of_x_square;
};


int main()
{
    auto Q1_cal = new Q1_Calculator();
    auto Q2_cal = new Q2_Calculator();
    auto Q3_cal = new Q3_Calculator();
    auto Q4_cal = new Q4_Calculator();
    double num;
    cout << fixed;

    while (cin >> num)
    {
        Q1_cal->Put(num);
        Q2_cal->Put(num);
        Q3_cal->Put(num);
        Q4_cal->Put(num);

        Q1_cal->Print();
        Q2_cal->Print();
        Q3_cal->Print();
        Q4_cal->Print();

        cout << endl;
    }
    return 0;
}
