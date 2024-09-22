#include <iostream>

template<class T>
void insertionSort(T* arr,int size){
    for(int i = 1;i<size;i++){
        T element = arr[i];
        int index = i - 1;
        while(index >= 0 && arr[index] > element){
            arr[index + 1] = arr[index];
            index--;
        }
        arr[index + 1] = element;
    }
}

template<class T>
void print(const T* arr,int size){
    for(int i = 0;i<size;i++)
        std::cout<<arr[i]<<" ";
}

int main(){
    int arr[] = {3, 6, -5, -1, 5,-14};
    const int size = 6;
    insertionSort<int>(arr, size);
    print<int>(arr, size);
}
