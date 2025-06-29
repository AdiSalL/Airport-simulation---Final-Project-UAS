#include <iostream>
#include <cmath> // use cmath for std::abs

using namespace std;

int closestNumber(int n, int m) {
    int closest = 0 ;
    int minDifference = INT_MAX;

    for(int i = n - m; i <= n + m; i++) {
        if(i % m == 0) {
            int difference = std::abs(n - i);

            if(difference < minDifference || (difference == minDifference && i > closest)) {
                closest = i;
                minDifference = difference;
            }
        }
    }
    return closest;
}

int main() {
    int n = 13, m = 4;
    cout << closestNumber(n, m) << endl;
    return 0;
}
