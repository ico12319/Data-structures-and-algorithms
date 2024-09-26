#include <iostream>
#include <queue>

// Task
// You are given a queue. Determine whether the given queue is sorted.

template<class T>
bool isQueueSorted(std::queue<T>& q){
    if(q.empty() || q.size() == 1)
        return false;
    T& prev = q.front();
    q.pop();
    
    while(!q.empty()){
        T& curr = q.front();
        q.pop();
        
        if(curr < prev)
            return false;
        
        prev = curr;
    }
    return true;
}

int main(){
    std::queue<int> q;
    q.push(1);
    q.push(43);
    q.push(12);
    std::cout<<isQueueSorted<int>(q)<<std::endl;
    

    
}
