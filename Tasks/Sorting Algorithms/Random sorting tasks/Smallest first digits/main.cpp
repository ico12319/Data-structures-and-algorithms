#include <iostream>

//Task:
// Даден е вектор от цели положителни числа. Напишете програма, която пренарежда вектора така, че числата, започващи с по-малка първа цифра, да са в началото на масива. Алгоритъмът да работи in-place и със сложност O(n).

constexpr size_t SIZE = 9;
void customSort(std::vector<int>& nums){
    std::vector<int> count(SIZE,0);
    for(int i = 0;i<nums.size();i++)
        count[(std::to_string(nums[i])[0] - '0') - 1]++;
    for(int i = 1;i<SIZE;i++)
        count[i] += count[i-1];
    
    int index = 0;
    while(index < nums.size()){
        size_t correctIndex = count[(std::to_string(nums[index])[0] - '0') - 1] - 1;
        if(index == correctIndex || count[(std::to_string(nums[index])[0] - '0') - 1] <= index)
            index++;
        else{
            std::swap(nums[index],nums[correctIndex]);
            count[(std::to_string(nums[correctIndex])[0] - '0') - 1]--;
        }
    }
}

int main(int argc, const char * argv[]) {
   
    std::vector<int> nums = {234, 567, 89, 1234, 91, 45};
    customSort(nums);
    for(const auto& el : nums)
        std::cout<<el<<" ";
    
}
