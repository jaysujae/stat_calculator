#include <bits/stdc++.h>
using namespace std;

template <class T>
class Calculator
{
public:
    virtual void Put(T num){
    }

    virtual double Get_Variance(){
        return 0.0;
    }

    virtual void Print(){
    }
};

class Q1_Calculator : public Calculator<uint64_t>{
    private:
        double e_x;
        double e_x_square;
        uint64_t counts;

        void update_e_x(uint64_t num){
            e_x *= (double)(counts-1)/counts;
            e_x += (double)num/counts;
        }
        void update_e_x_square(uint64_t num){
            e_x_square *= (double)(counts-1)/counts;
            e_x_square += (double)(num*num)/counts;
        }
        double get_variance() {
            return e_x_square - e_x * e_x;
        }

    public:
        void Put(uint64_t num)
        {   
            counts++;
            update_e_x(num);
            update_e_x_square(num);
        }
        void Print()
        {
            cout << "Q1 Variance : " << get_variance() << "\n";
            return;
        }
};

class Q2_Calculator : public Calculator<double>{
    private:
        uint64_t counts;
        double e_x;
        double variance_times_counts;

        void update_e_x(double num){
            e_x *= (double)(counts-1)/counts;
            e_x += num/counts;
        }

        double get_variance(){
            return variance_times_counts/counts;
        }

    public:
    void Put(double num)
    {   
        counts++;

        auto old_e_x = e_x;
		update_e_x(num);

		variance_times_counts += (num - e_x) * (num - old_e_x);
    }

    void Print()
    {
        cout << "Q2 Variance : " << get_variance() << "\n";
        return;
    }
};

class Q3_Calculator : public Calculator<double>{
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
        return big_calculator.Get_Variance() + small_calculator.Get_Variance();
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


class Q4_Calculator : public Calculator<double>{
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

    double Get_Variance(uint64_t starting_time){
        auto sum_it = prefix_sum_of_x.lower_bound(starting_time);
        auto square_sum_it = prefix_sum_of_x_square.lower_bound(starting_time);

        return (sum_of_x_square - square_sum_it->second) / counts - pow( (sum_of_x - sum_it->second) / counts, 2);
    }

    void Print()
    {
        cout << " Q4 Variance : " << Get_Variance() << "\n";
        return;
    }

    private:
    uint64_t counts;
    double sample_mean;
    uint64_t current_timestamp;
    map<uint64_t, double> prefix_sum_of_x;
    map<uint64_t, double> prefix_sum_of_x_square;
    uint64_t sum_of_x;
    uint64_t sum_of_x_square;
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
