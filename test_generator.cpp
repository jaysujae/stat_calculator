#include <bits/stdc++.h>
using namespace std;
int main() {
    cout << fixed;
    for(int i = 0 ; i < 10000 ; i++){
        double num = ((double) rand() / (RAND_MAX));
        if(i % 100 == 1){
            num += 10000;
        }
        cout << num << "\n";
    }
    return 0;
}