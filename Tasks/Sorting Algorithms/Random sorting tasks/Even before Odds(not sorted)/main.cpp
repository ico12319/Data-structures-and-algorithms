#include <iostream>

//Task:
// Given a vector of postive integers, part it so the even numbers are before the odd numbers (the vector is not in sorted state)

bool isEven(int num){
    return !(num & 1);
}

void partition(std::vector<int>& nums){
    int left = 0;
    int right = nums.size() - 1;
    while(true){
        while(left < nums.size() && isEven(nums[left]))
            left++;
        while(right >= 0 && !isEven(nums[right]))
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

    std::vector<int> nums = {2,2,1,0,4,3,5,9,12};
    partition(nums);
    for(const auto& el : nums)
        std::cout<<el<<" ";
    
}
