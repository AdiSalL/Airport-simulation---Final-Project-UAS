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

    int selectionSort(int arr[], int length) {
        for(int i = 0; i < length - 1; i++) {
            int min = arr[i];
            for(int j = i + 1; j < length; j++) {
                if(arr[j] < arr[min]) {
                    min = j;
                }
            }
            int temp = arr[i];
            arr[i] = array[min];
            array[min] = temp;
        }
    }

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

    int sequentialSearch(int arr[], int length, int target) {
        for(int i = 0; i < length; i++) {
            if(arr[i] == target) {
                return i + 1;
            }
        }
    }

    int binarySearch(int arr[], int length, int target) {
        int mid = length / 2;
        
        for(int i = 0; i < length; i++) {
            if(target == mid) {
                return mid;
            }else if() {
                
            }
        }
    }


int main() {
int arr[] = {
    201, 90, 85, 22, 23, 25, 54, 32, 12, 90, 1,
    67, 43, 99, 76, 55, 12, 200, 111, 80, 39,
    14, 77, 88, 66, 123, 45, 34, 78, 91, 102,
    150, 120, 135, 118, 107, 119, 108, 87, 61,
    72, 29, 93, 144, 160, 59, 38, 13, 24, 31,
    174, 180, 190, 86, 21, 36, 33, 17, 9, 7,
    16, 8, 5, 3, 6, 2, 4, 10, 11, 19,
    26, 27, 28, 30, 35, 37, 40, 42, 44, 46,
    48, 49, 50, 52, 53, 56, 57, 58, 60, 62,
    63, 64, 65, 68, 69, 70, 71, 73, 74, 75
};

    int length = sizeof(arr) / sizeof(arr[0]);
    
    cout << "sebelum perulangan" << endl;
    for(int i = 0; i < length; i++ ) {
        cout << arr[i] << endl;
    }
    bubbleSort(arr, length);
    
    cout << "setelah pengurutan perulangan" << endl;
    for(int i = 0; i < length; i++ ) {
        cout << arr[i] << endl;
    }

    
    cout << "201 ada di " << sequentialSearch(arr, length, 201) << endl;
}

