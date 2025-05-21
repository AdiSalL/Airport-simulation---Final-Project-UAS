#include <iostream>

using namespace std;

    int insertionSort(int arr[], int length) {
        for(int i = 0; i < length; i++) {
            int temp = arr[i];
            int j = i - 1;
            while(j >= 0 && arr[j] > temp) {
                arr[j + 1] = arr[j];     
                j--;
            }
            arr[j + 1] = temp;
        } 
    };

    int bubbleSort(int arr[], int length) {
        for(int i = 0; i < length - 1; i++) {
            for(int j = 0; j < length - i - 1; j++) {
                if(arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

int main() {
    int arr[] = {201, 90, 85, 22, 23 , 25, 54, 32, 12, 90, 1};
    int length = sizeof(arr) / sizeof(arr[0]);
    
    cout << "sebelum perulangan" << endl;
    for(int i = 0; i < length; i++ ) {
        cout << arr[i] << endl;
    }
    bubbleSort(arr, length);

    
    cout << "setelang perulangan" << endl;
    for(int i = 0; i < length; i++ ) {
        cout << arr[i] << endl;
    }
}

