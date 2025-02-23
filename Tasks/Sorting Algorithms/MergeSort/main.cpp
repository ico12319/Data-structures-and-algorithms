#include <iostream>

void merge(int* arr1,size_t size1,const int* arr2,size_t size2,int* buffer){
    int index1 = 0,index2 = 0,resIndex = 0;
    while(index1 < size1 && index2 < size2){
        if(arr1[index1] <= arr2[index2])
            buffer[resIndex++] = arr1[index1++];
        else if(arr1[index1] > arr2[index2])
            buffer[resIndex++] = arr2[index2++];
    }
    while(index1 < size1)
        buffer[resIndex++] = arr1[index1++];
    while(index2 < size2)
        buffer[resIndex++] = arr2[index2++];
}

void mergeSortStep(int* arr,size_t size,int* buffer){
    if(size <= 1)
        return;
    int mid = size / 2;
    mergeSortStep(arr, mid, buffer);
    mergeSortStep(arr + mid, size - mid, buffer + mid);
    merge(arr,mid,arr + mid,size - mid,buffer);
    for(int i = 0;i<size;i++)
        arr[i] = buffer[i];
}

void mergeSort(int* arr,size_t size){
    if(size == 0)
        return;
    
    int* buffer = new int[size];
    mergeSortStep(arr, size, buffer);
    delete[] buffer;
}

int main(int argc, const char * argv[]) {
    int arr[] = {4,3,1,2,4,12};
    mergeSort(arr, 6);
    for(int i = 0;i<6;i++)
        std::cout<<arr[i]<<" ";
}
