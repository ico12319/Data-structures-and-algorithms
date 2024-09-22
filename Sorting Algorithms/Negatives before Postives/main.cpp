#include <iostream>
// Task
//Given an array of integers.
//Write a function that runs in O(n) time and uses O(1) space to rearrange the elements so that every negative number appears before every positive number.

void partition(int* arr,int size){
    int pivot = 0;
    int low = 0;
    int high = size - 1;
    
    while(true){
        while(arr[low] < pivot)
            low++;
        while(arr[high] > pivot)
            high--;
        if(arr[high] == arr[low])
            low++;
        if(low < high)
            std::swap(arr[low],arr[high]);
        else
            return;
    }
}

void print(const int* arr,int size){
    for(int i = 0;i<size;i++)
        std::cout<<arr[i]<<" ";
}

int main(){
    int arr[] = {3, 6, -5, -1, 5,-14};
    const int size = 6;
    partition(arr, size);
    print(arr, size);
}
