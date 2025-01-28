#include <iostream>

// quick sort for vectors
template<class T>
size_t partition(std::vector<T>& arr,size_t low,size_t high){
    if(low >= high)
        return low;
    if(arr[low] > arr[high])
        std::swap(arr[low],arr[high]);
    T& pivot = arr[high];
    size_t left = low;
    size_t right = high;
    while(true){
        while(arr[++left] < pivot);
        while(arr[--right] > pivot){
            if(left >= right)
                break;
        }
        if(left < right)
            std::swap(arr[left],arr[right]);
        else
            break;
    }
    std::swap(arr[left],pivot);
    return left;
}

template<class T>
void quick_sort(std::vector<T>& arr,size_t low,size_t high){
    if(low >= high)
        return;
    size_t pivot_index = partition(arr, low,high);
    quick_sort(arr,low,pivot_index - 1);
    quick_sort(arr,pivot_index + 1, high);
}

template<class T>
void quick_sort(std::vector<T>& arr){
    if(!arr.empty())
        quick_sort(arr, 0, arr.size() - 1);
}


//quick sort for array
template<class T>
size_t partition(T* arr,size_t size){
    if(arr[0] > arr[size - 1])
        std::swap(arr[0],arr[size - 1]);
    size_t left = 0;
    size_t right = size - 1;
    T& pivot = arr[right];
    while(true){
        while(arr[++left] < pivot);
        while(arr[--right] > pivot){
            if(left >= right)
                break;
        }
        if(left >= right)
            break;
        std::swap(arr[left], arr[right]);
    }
    std::swap(arr[left],pivot);
    return left;
}

template<class T>
void quick_sort(T* arr,size_t size){
    if(size <= 1)
        return;
    size_t pivot_index = partition(arr, size);
    quick_sort(arr,pivot_index);
    quick_sort(arr + pivot_index + 1, size - pivot_index - 1);
}

int main(int argc, const char * argv[]) {
    std::vector<int> v = {4,3,5,1,0};
    quick_sort<int>(v);
    for(const auto& el : v)
        std::cout<<el<<" ";
    std::cout<<std::endl;
    int arr[] = {4,3,5,1,0};
    quick_sort(arr, 5);
    for(int i = 0;i<5;i++)
        std::cout<<arr[i]<<" ";
}
