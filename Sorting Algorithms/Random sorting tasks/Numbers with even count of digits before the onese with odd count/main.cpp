#include <iostream>

//Task:
//Даден е вектор от цели положителни числа. Напишете програма, която разделя масива на две части, като първата част съдържа всички числа с четен брой цифри, а втората част - всички с нечетен брой.


int digitsCount(int num){
    int count = 0;
    while(num!=0){
        count++;
        num/=10;
    }
    return count;
}

bool isEven(int num){
    return !(num & 1);
}

void partition(std::vector<int>& nums){
    int left = 0;
    int right = nums.size() - 1;
    
    while(true){
        while(left < right && isEven(digitsCount(nums[left])))
            left++;
        while(right >= 0 && !isEven(digitsCount(nums[right])))
            right--;
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
    std::vector<int> v = {10, 2, 12, 12, 4, 100, 102020};
    partition(v);
    for(const auto& el : v)
        std::cout<<el<<" ";
}
