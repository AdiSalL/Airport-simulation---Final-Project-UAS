#include <iostream>

using namespace std;

// int reverseDigits(int n) {
//     int revNum = 0;

//     while (n > 0)
//     {
//         revNum = revNum * 10 + n % 10;
//         n = n / 10;
//     }
//     return revNum;
// }

void reverseDigits(int n, int &revNum, int &basePos) {
    if(n > 0) {
        reverseDigits(n / 10, revNum, basePos);
        revNum += (n % 10) * basePos;
        basePos *= 10;
    }
}

int main() {
    int n = 4562;
    int revNum = 0;
    int basePos = 1;

    reverseDigits(24123, revNum, basePos);
    cout << revNum;
    return 0;
}