#include <iostream>
#include <queue>
#include <list>

// Task
// Given a list with elements that are queues of natural numbers. Define a function that returns whether the consecutive concatenation of all the queues forms a sorted sequence."

bool isQueueSorted(std::queue<int>& q,int& last){
    const size_t qSize = q.size();
    if(qSize == 0 || qSize == 1)
        return false;
    
    for(int i = 0;i<qSize;i++){
        int curr = q.front();
        q.pop();
        if(i + 1 == qSize)
            last = curr;
        
        if(i + 1!=qSize && curr > q.front())
            return false;
        
        q.push(curr);
    }
    return true;
}

bool isListSorted(std::list<std::queue<int>>& l){
    if(l.empty() || l.size() == 1)
        return false;
    
    int last = INT_MIN;
    for(auto it = l.begin();it!=l.end();it++){
        if(it != l.begin()){
            if(!(*it).empty() && last > (*it).front())
                return false;
        }
        if(!isQueueSorted((*it), last)){
            return false;
        }
    }
    
    return true;
}

int main(){
   
    std::queue<int> q1;
    q1.push(12);
    q1.push(56);
    
    std::queue<int> q2;
    q2.push(76);
    q2.push(102);
    q2.push(103);
    
    std::queue<int> q3;
    q3.push(222);
    q3.push(223);
    q3.push(224);
    
    std::list<std::queue<int>> l;
    l.push_front(q1);
    l.push_back(q2);
    l.push_back(q3);
    
    std::cout<<isListSorted(l)<<std::endl;

    
}
