#include <iostream>
// Task 1: Add only unique
std::vector<int> addOnlyUnique(const std::vector<int>& nums,size_t size,int target,size_t& newSize){
    std::vector<int> res;
    for(int i = 0;i<size;i++){
        if(nums[i]!=target){
            res.push_back(nums[i]);
            newSize++;
        }
    }
    return res;
}

void print(const std::vector<int>& nums,size_t size){
    for(int i = 0;i<size;i++)
        std::cout<<nums[i]<<" ";
    std::cout<<std::endl;
}

//Task2: Plus one
std::vector<int>plusOne(std::vector<int>& digits){
    const size_t size = digits.size();
    for(size_t i = size - 1;i>=0;i--){
        if(digits[i] < 9){
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    digits.insert(digits.begin(), 1);
    return digits;
}

//Task3: Two Sum
std::vector<std::pair<int,int>> fillVector(const std::vector<int>& nums){
    const size_t size = nums.size();
    std::vector<std::pair<int,int>> numsInd;
    for(int i = 0;i<size;i++){
        numsInd.push_back({nums[i],i});
    }
    return numsInd;
}

int binarySearch(std::vector<std::pair<int,int>>& numsInd,int target){
    const int size = numsInd.size();
    int left = 0;
    int right = size - 1;
    while(right >= left){
        int mid = left + (right - left) / 2;
        if(numsInd[mid].first == target)
            return mid;
        else if(numsInd[mid].first > target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

std::vector<int> twoSum(std::vector<int>& nums,int targetSum){
    const size_t size = nums.size();
    std::vector<std::pair<int,int>> numsInd = fillVector(nums);
    std::sort(numsInd.begin(),numsInd.end());
    for(int i = 0;i<size;i++){
        int neededNum = targetSum - numsInd[i].first;
        int neededNumIndex = binarySearch(numsInd, neededNum);
        if(neededNumIndex != -1)
            return std::vector<int> {numsInd[i].second,numsInd[neededNumIndex].second};
    }
    return {};
}


int main(int argc, const char * argv[]) {
    std::vector<int> nums = {2,7,11,15,3};
    std::vector<int> ind = twoSum(nums, 9);
    std::cout<<ind[0]<<" " << ind[1]<<std::endl;
}
