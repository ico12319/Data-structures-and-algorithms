#include <iostream>
#include <stack>
#include <queue>

// Custom ball game created for queue and stack practise

std::stack<int> fillStackData(std::vector<int>& sequence){
    const size_t size = sequence.size();
    std::stack<int> strength;
    for(int i = 0;i<size;i++)
        strength.push(sequence[i]);
    return strength;
}

std::queue<int> fillQueueData(std::vector<int>& sequence){
    const size_t size = sequence.size();
    std::queue<int> accuracy;
    for(int i = 0;i<size;i++)
        accuracy.push(sequence[i]);
    return accuracy;
}

void play(std::vector<int>& sequence1,std::vector<int>& sequence2){
    std::stack<int> strength = fillStackData(sequence1);
    std::queue<int> accuracy = fillQueueData(sequence2);
    int goalsScored = 0;
    
    while(!strength.empty() && !accuracy.empty()){
        int currStrength = strength.top();
        int currAccuracy = accuracy.front();
        int sum = currStrength + currAccuracy;
        if(sum == 100){
            goalsScored++;
            strength.pop();
            accuracy.pop();
        }
        else if(sum < 100){
            if(currStrength < currAccuracy)
                strength.pop();
            else if(currStrength > currAccuracy)
                accuracy.pop();
            else{
                strength.pop();
                strength.push(sum);
                accuracy.pop();
            }
        }
        else{
            currStrength-=10;
            strength.pop();
            strength.push(currStrength);
            accuracy.pop();
            accuracy.push(currAccuracy);
            
        }
    }
    
    if(goalsScored == 3)
        std::cout<<"Paul scored a hat-trick!"<<std::endl;
    else if(goalsScored == 0)
        std::cout<<"Paul failed to score a single goal."<<std::endl;
    else if(goalsScored > 3)
        std::cout<<"Paul performed remarkably well!"<<std::endl;
    else if(goalsScored < 3)
        std::cout<<"Paul failed to make a hat-trick"<<std::endl;
    
    if(goalsScored > 0)
        std::cout<<"Goals scored: " << goalsScored<<std::endl;
    
    if(strength.size() > 0){
        std::cout<<"Strength values left: ";
        while(!strength.empty()){
            std::cout<<strength.top()<<" ";
            strength.pop();
        }
    }
    if(accuracy.size() > 0){
        std::cout<<"Accuracy values left: ";
        while(!accuracy.empty()){
            std::cout<<accuracy.front()<<" ";
            accuracy.pop();
        }
    }
    
}


int main(int argc, const char * argv[]) {
    std::vector<int> seq1 = {10,20,30,40};
    std::vector<int> seq2 = {60,70,80,90};
    play(seq1, seq2);
}
