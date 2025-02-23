#include <iostream>

//Task:
//Даден е вектор от цели числа. Напишете алгоритъм, който премества всички числа, които са точни квадрати (напр. 1, 4, 9, 16), в началото на вектора.

bool isPerfectSquare(int num){
    if(num < 0) return false;
    int squreRoot = static_cast<int>(std::sqrt(num));
    return squreRoot * squreRoot == num;
}

void partition(std::vector<int>& nums){
    int left = 0;
    int right = nums.size() - 1;
    while(true){
        while(left < nums.size() && isPerfectSquare(nums[left])){
            left++;
        }
        while(right >= 0 && !isPerfectSquare(nums[right])){
            right--;
        }
        
        if(left < right){
            std::swap(nums[left],nums[right]);
            left++;
            right--;
        }
        else
            break;
    }
}
int main(int argc, const char * argv[]) {
    
    std::vector<int> v = {10, 4, 15, 16, 25, 7, 9, 2, 1};
    partition(v);
    for(const auto& el : v)
        std::cout<<el<<" ";
}
