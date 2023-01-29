#include <bits/stdc++.h>
using namespace std;

struct mean{
    uint64_t counts;
    double value;

    mean operator + (double num) {
        auto new_counts = counts+1;
        auto new_value = value * (counts) / (new_counts) + num / new_counts;
        mean result = mean{counts+1, new_value};
        return result;
    }

    //weighted mean
    mean operator + (mean other){
        mean res;
        res.counts = counts + other.counts;
        res.value = value * ((double)counts / res.counts) + other.value * ((double)other.counts / res.counts);
        return res;
    }
    mean operator - (mean other){
        mean res;
        res.counts = counts - other.counts;
        res.value = value * ((double)counts / res.counts) - other.value * ((double)other.counts / res.counts);
        return res;
    }
    mean& operator += (double num) {
        counts += 1;
        value *= (double)(counts - 1)/counts;
        value += (double)num/counts;
        return *this;
    }
};

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
        mean x;
        mean x_square;
        uint64_t counts;

        void update_mean_x(uint64_t num){
            x += num;
            return;
        }
        void update_mean_x_square(uint64_t num){
            x_square += num*num;
            return;
        }

    public:
        void Put(uint64_t num)
        {   
            counts++;
            update_mean_x(num);
            update_mean_x_square(num);
        }
        double Get_Variance() {
            return x_square.value - x.value * x.value;
        }
        void Print()
        {
            cout << "Q1 Variance : " << Get_Variance() << "\n";
            return;
        }


    Q1_Calculator operator + (Q1_Calculator &other) {
         Q1_Calculator res;
         res.counts = counts + other.counts;
         res.x = x + other.x;
         res.x_square = x_square + other.x_square;
         return res;
    }
};

class Q2_Calculator : public Calculator<double>{
    private:
        uint64_t counts;
        mean x;
        double variance_times_counts;
        
        void update_mean_x(uint64_t num){
            x += num;
            return;
        }

    public:
    void Put(double num)
    {   
        counts++;
        auto old_mean_x = x;
		update_mean_x(num);
		variance_times_counts += (num - x.value) * (num - old_mean_x.value);
    }

    double Get_Variance(){
        return variance_times_counts/counts;
    }

    void Print()
    {
        cout << "Q2 Variance : " << Get_Variance() << "\n";
        return;
    }

};

//Q3 Calculator uses integer calculator Q1, because practically we can ignore small floating number.
class Q3_Calculator : public Calculator<double>{
    private:
        Q1_Calculator big_calculator;
        Q1_Calculator small_calculator;
        int border_line = 1000;

    public:
        void Put(double num)
        {   
            if(num > border_line){
                big_calculator.Put(num);
                return;
            }
            small_calculator.Put(num);
        }
        double Get_Variance()
        {
            return (big_calculator + small_calculator).Get_Variance();
        }
        void Print()
        {
            cout << "Q3 Variance : " << Get_Variance() << "\n";
            return;
        }
};


class Q4_Calculator : public Calculator<double>{
    private:
    uint64_t current_timestamp;
    vector<pair<uint64_t, mean>> mean_x_window = vector<pair<uint64_t, mean>>();
    vector<pair<uint64_t, mean>> mean_x_square_window;
    int capacity = 1000;

    mean get_last_mean_x(){
        if(mean_x_window.size() == 0){
            return mean{0, 0};
        }
        return mean_x_window.back().second;
    }
    mean get_last_mean_x_square(){
        if(mean_x_square_window.size() == 0){
            return mean{0, 0};
        }
        return mean_x_square_window.back().second;
    }

    public:

    void Put(double num)
    {   
        current_timestamp++;
 
        mean_x_window.push_back({current_timestamp, get_last_mean_x() + num});
        mean_x_square_window.push_back({current_timestamp, get_last_mean_x_square() + num*num});

        if(mean_x_window.size() > capacity){
            mean_x_window.erase(mean_x_window.begin());
            mean_x_square_window.erase(mean_x_square_window.begin());
            return;
        }
    }

    double Get_Variance(uint64_t starting_time)
    {
        int diff = current_timestamp - starting_time;
        auto loc = (int)mean_x_window.size() - diff;
        if(loc < 0){
            loc = 0;
        }
        auto mean_x_by_loc = mean_x_window[loc].second;
        auto mean_x_square_by_loc = mean_x_square_window[loc].second;

        auto mean_x_from_loc = get_last_mean_x() - mean_x_by_loc;
        auto mean_x_square_from_loc = get_last_mean_x_square() - mean_x_square_by_loc;

        return mean_x_square_from_loc.value - mean_x_from_loc.value * mean_x_from_loc.value;
    }

    void Print()
    {
        cout << "Q4 Variance : " << Get_Variance(current_timestamp - 10) << "\n";
        return;
    }
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
