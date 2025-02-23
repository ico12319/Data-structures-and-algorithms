#include <iostream>

template<class T>
void bubbleSort(T* arr,int size){
    for(int i = 0;i<size - 1;i++){
        bool isSwapped = false;
        for(int j = 0;j<size - i - 1;j++){
            if(arr[j] > arr[j+1]){
                std::swap(arr[j],arr[j+1]);
                isSwapped = true;
            }
        }
        if(!isSwapped)
            return;
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
    bubbleSort<int>(arr, size);
    print<int>(arr, size);
}
