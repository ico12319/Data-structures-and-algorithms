#include <iostream>


template<class T>
void merge(const T* arr1,const T* arr2,size_t size1,size_t size2,T* buffer){
    size_t iter1 = 0;
    size_t iter2 = 0;
    size_t result_iter = 0;
    
    while(iter1 < size1 && iter2 < size2){
        if(arr1[iter1] < arr2[iter2])
            buffer[result_iter++] = arr1[iter1++];
        else
            buffer[result_iter++] = arr2[iter2++];
    }
    while(iter1 < size1)
        buffer[result_iter++] = arr1[iter1++];
    while(iter2 < size2)
        buffer[result_iter++] = arr2[iter2++];
}

template<class T>
void merge_sort_step(T* arr,size_t size,T* buffer){
    if(size <= 1)
        return;
    auto mid = size / 2;
    merge_sort_step(arr,mid, buffer);
    merge_sort_step(arr + mid, size - mid, buffer + mid);
    
    merge(arr,arr + mid,mid,size - mid,buffer);
    for(int i = 0;i<size;i++)
        arr[i] = buffer[i];
}

template<class T>
void merge_sort(T* arr,size_t size){
    T* buffer = new T[size];
    merge_sort_step(arr, size, buffer);
    delete[] buffer;
}

int main(int argc, const char * argv[]) {
    int arr[] = {9,1,1,0,0,5,12};
    merge_sort(arr, 7);
    for(int i = 0;i<7;i++)
        std::cout<<arr[i]<<" ";
}
