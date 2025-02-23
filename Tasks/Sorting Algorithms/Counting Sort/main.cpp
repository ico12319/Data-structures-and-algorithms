#include <iostream>

constexpr size_t MAX_NUMBER = 10;
constexpr size_t MIN_NUMBER = 1;
void countingSort(int* arr,size_t size){
    int count[MAX_NUMBER] {0};
    for(int i = 0;i<size;i++)
        count[arr[i] - MIN_NUMBER]++;
    
    for(int i = 1;i<MAX_NUMBER;i++)
        count[i]+=count[i-1];
    
    int* res = new int[size];
    for(int i = size - 1;i>=0;i--){
        int currNumber = arr[i];
        int index = --count[arr[i] - MIN_NUMBER];
        res[index] = currNumber;
    }
    for(int i = 0;i<size;i++)
        arr[i] = res[i];
    delete[]res;
}

int main(int argc, const char * argv[]) {
    int arr[] = {1,5,2,9,1,2,1,10};
    countingSort(arr, 8);
    for(int i = 0;i<8;i++)
        std::cout<<arr[i]<<" ";
}
