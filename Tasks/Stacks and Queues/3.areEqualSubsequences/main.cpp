#include <iostream>
#include <queue>

//Write a function that takes an array of integers and checks whether the subsequence formed only by the positive numbers in the array is the same as the subsequence formed by the negative numbers in the array (after multiplying all the numbers in one of the subsequences by -1).
//The solution should be implemented using a queue!


bool areSameSigns(int num1,int num2){
    return (num1 > 0 && num2 > 0) || (num1 < 0 && num2 < 0);
}

bool areEqualSubsequences(const int* arr,size_t size){
    std::queue<int> temp;
    for(int i = 0;i<size;i++){
        if(arr[i] == 0)
            return false;
        
        if(temp.empty()){
            temp.push(arr[i]);
            continue;
        }
        
        int currInArr = arr[i];
        int currInQueue = temp.front();
        if(areSameSigns(currInArr, currInQueue)){
            temp.push(arr[i]);
        }
        else{
            if(-currInArr != currInQueue)
                return false;
            else
                temp.pop();
        }
    }
    return temp.size() == 0;
}

int main(int argc, const char * argv[]) {
    int arr[] = { 1, 5, -1, 4, -5, 9, 8, -4, -9, 18, -8, -18, -7, 7 };
    std::cout<<areEqualSubsequences(arr, 14)<<std::endl;
}
