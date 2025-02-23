#include <iostream>
#include <stack>
#include <queue>
//Task
//Until there are bees and bee-eaters available, the program will continue running.
//You need to compare the first group of bees to the last group of bee-eaters (See the Examples):
//They start a fight until at least one of the groups is defeated(reaches zero). One bee-eater can kill up to 7 (seven) bees in a single battle and dies. In case one attacker needs to fight less than 7 bees, it survives while the bees are considered defeated. For the next fight, the attacker will be recovered and able to kill 7 bees again.
//If the bee-eaters from a group win (there are 0 (zero) remaining bees in the corresponding group) add the survived bee-eaters to the next group in their sequence. The defeated bee group is removed.
//If the bees group wins, (there are 0 (zero) remaining bee-eaters from the corresponding group) add the bees that survived to the back of the bees collection. The defeated group of bee-eaters is removed.
//If the result is a draw, remove both groups from their collections and proceed with the next groups in the sequences.

const int beesEatingCount = 7;

int timesDefeated(int bee, int beeEater) {
    return std::min(bee / beesEatingCount, beeEater);
}

void fight(std::queue<int>& bees,std::stack<int>& beeEaters){
    while(!bees.empty() && !beeEaters.empty()){
        int bee = bees.front();
        int beeEater = beeEaters.top();
        
        int times = timesDefeated(bee, beeEater);
        int remainingBees = bee - std::min(bee,beeEater *  beesEatingCount);
        int remainingBeeEaters = beeEater - times;
        
        bees.pop();
        beeEaters.pop();
        
        if(remainingBees > 0){
            bees.push(remainingBees);
        }
        if(remainingBeeEaters > 0){
            if(!beeEaters.empty()){
                int newTop = beeEaters.top() + remainingBeeEaters;
                beeEaters.pop();
                beeEaters.push(newTop);
            }
            else{
                beeEaters.push(remainingBees);
            }
        }
    }
}

void determineWinner(std::queue<int>&bees,std::stack<int>& beeEaters){
    fight(bees, beeEaters);
    if(!bees.empty()){
        std::cout<<"Bees won!"<<std::endl;
        while(!bees.empty()){
            std::cout<<bees.front()<<" ";
            bees.pop();
        }
    }
    else if(!beeEaters.empty()){
        std::cout<<"Bee eaters won!"<<std::endl;
        while(!beeEaters.empty()){
            std::cout<<beeEaters.top()<<" ";
            beeEaters.pop();
        }
    }
    else{
        std::cout<<"Draw!"<<std::endl;
    }
}
int main(int argc, const char * argv[]) {
   
    std::queue<int> bees;
    bees.push(14);
    bees.push(6);
    
    std::stack<int> beeEaters;
    beeEaters.push(1);
    beeEaters.push(3);
    beeEaters.push(2);
    
    determineWinner(bees, beeEaters);
}
