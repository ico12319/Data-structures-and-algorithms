#include <iostream>

template<class T>
void selectionSort(T* arr,int size){
    for(int i = 0;i<size - 1;i++){
        int minIndex = i;
        for(int j = minIndex + 1;j<size;j++){
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
        if(minIndex != i)
            std::swap(arr[i],arr[minIndex]);
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
    selectionSort<int>(arr, size);
    print<int>(arr, size);
}
