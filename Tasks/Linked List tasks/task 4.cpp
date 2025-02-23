#include <iostream>
#include <list>
#include <queue>

//Задача 4: Даден е списък l с елементи опашки от естествени числа.Да се дефинира функция, която връща дали последователната конкатенация на всички опашки образува сортирана редица.Да се реши с константна памет и да не се променят входните данни!

bool is_sorted_queue(std::queue<int>& q,int& last_el){
    if(q.empty()) return true;
    
    for(int i = 0;i<q.size();i++){
        int curr = q.front();
        q.pop();
        
        if(i == q.size()) last_el = curr;
        if(i!=q.size() && curr > q.front()) return false;
       
        q.push(curr);
    }
    return true;
}

bool is_sorted_sequence_of_queues(std::list<std::queue<int>>& list){
    int last_el = INT_MIN;
    for(auto it = list.begin();it!=list.end();it++){
        if(it!=list.begin() && last_el > (*it).front()) return false;
        
        if(!is_sorted_queue(*it, last_el)) return false;
    }
    return true;
}


int main(int argc, const char * argv[]) {
    std::queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    
    std::queue<int> q2;
    q2.push(6);
    q2.push(9);
    q2.push(10);
    
    std::queue<int> q3;
    q3.push(0);
    q3.push(22);
    q3.push(33);
    
    std::list<std::queue<int>> queues;
    queues.push_back(q1);
    queues.push_back(q2);
    queues.push_back(q3);
    
    std::cout<<is_sorted_sequence_of_queues(queues)<<std::endl;
}
