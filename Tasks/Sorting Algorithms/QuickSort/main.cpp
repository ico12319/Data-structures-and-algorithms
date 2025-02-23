#include <iostream>

template<class T>
int partition(T* arr,int size){
    T pivot = arr[size / 2];
    int i = 0;
    int j = size - 1;
    
    while(true){
        while(arr[i] < pivot)
            i++;
        while(arr[j] > pivot)
            j--;
        if(arr[i] == arr[j])
            i++;
        if(i < j)
            std::swap(arr[i],arr[j]);
        else
            return j;
    }
}

template<class T>
void quickSort(T* arr,int size){
    if(size <= 1)
        return;
    int pivotIndex = partition<T>(arr, size);
    quickSort<T>(arr,pivotIndex);
    quickSort<T>(arr + pivotIndex + 1,size - pivotIndex - 1);
}

template<class T>
void print(const T* arr,int size){
    for(int i = 0;i<size;i++)
        std::cout<<arr[i]<<" ";
}

int main(){
    int arr[] = {1, 5, -1, 4, -5, 9, 8, -4, -9, 18, -8, -18, -7, 7};
    const size_t size = 14;
    std::cout<<partition<int>(arr, size)<<std::endl;
    quickSort<int>(arr, size);
    print<int>(arr, size);
}
