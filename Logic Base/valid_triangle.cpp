#include <iostream>

using namespace std;

bool checkValidity(int a, int b, int c) {
    if(a + b <= c || b + c <= a || a + c <= b) {
        return false;
    }else {
        return true;
    }
}

int main() {
    int a =7, b = 10, c = 5;
    if(checkValidity(a, b, c)) {
        cout << "Valid" << endl;
    }else {
        cout << "Invalid" << endl;
    }
}