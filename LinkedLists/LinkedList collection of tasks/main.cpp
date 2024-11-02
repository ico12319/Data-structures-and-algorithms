#include <iostream>
#include <unordered_map>

struct ListNode{
    int val;
    ListNode* next;
    
    ListNode(int val) : val(val),next(nullptr){}
    ListNode(int val,ListNode* next) : val(val),next(next){}
};

// Task 1 : Find the most common element in a singly linked list (using map) complexity : O(n)
int findMostCommon(ListNode* head){
    std::unordered_map<int, int> keyOcurr;
    ListNode* curr = head;
    while(curr){
        keyOcurr[curr->val]++;
        curr = curr->next;
    }
    int maxOccur = INT_MIN;
    int mostCommonElement = INT_MIN;
    for(const auto& pair : keyOcurr){
        int currOccur = pair.second;
        if(currOccur > maxOccur){
            maxOccur = currOccur;
            mostCommonElement = pair.first;
        }
    }
    return mostCommonElement;
}

// Task 1* : Find the most common element in a singly linked list (using no additional DS) complexity : O(n^2)
int findMostCommonDummy(ListNode* head){
    if(!head)
        return 0;
    if(!head->next)
        return head->val;
    ListNode* curr = head;
    int maxOccur = INT_MIN;
    int mostCommonElement = INT_MIN;
    while(curr){
        ListNode* inner = head;
        int counter = 0;
        while(inner){
            if(inner->val == curr->val)
                counter++;
            inner = inner->next;
        }
        if(counter > maxOccur){
            maxOccur = counter;
            mostCommonElement = curr->val;
        }
        curr = curr->next;
    }
    return mostCommonElement;
}

//Task 2: Check whether a signly linked list is a palindrome.
ListNode* reverse(ListNode* head){
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    
    while(head){
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    head = prev;
    return prev;
}

bool isPalindrome(ListNode* head){
    ListNode* curr = head;
    ListNode* reversed = reverse(head);
    
    while(curr && reversed){
        if(curr->val != reversed->val)
            return false;
        curr = curr->next;
        reversed = reversed->next;
    }
    return true;
}

void print(ListNode* head){
    ListNode* curr = head;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
    std::cout<<std::endl;
}

// Task3 : Detect a cycle in a linked lsit
bool hasCycle(ListNode* head){
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
            return true;
    }
    return false;
}

//Task4 : Merge two sorted linked lists

ListNode* merge(ListNode* head1,ListNode* head2){
    ListNode* merged = new ListNode(0);
    ListNode* iter = merged;
    ListNode* curr1 = head1;
    ListNode* curr2 = head2;
    
    while(curr1 && curr2){
        if(curr1->val <= curr2->val){
            iter->next = new ListNode(curr1->val);
            curr1 = curr1->next;
        }
        else{
            iter->next = new ListNode(curr2->val);
            curr2 = curr2->next;
        }
        iter = iter->next;
    }
    if(curr1)
        iter->next = curr1;
    if(curr2)
        iter->next = curr2;
    
    ListNode* res = merged->next;
    delete merged;
    return res;
}

//Task5: Remove duplicates from a linked list
ListNode* removeDuplicates(ListNode* head){
    if(!head)
        return nullptr;
    if(!head->next)
        return head;
    ListNode* curr = head;
    while(curr && curr->next){
        if(curr->val == curr->next->val)
            curr->next = curr->next->next;
        else
            curr = curr->next;
    }
    return head;
}

//Task6 : Remove the N-th node from the end of a singly linked list in a single pass.
ListNode* removeNth(ListNode* head,int k){
    if(!head)
        return nullptr;
    if(!head->next && k > 1)
        return nullptr;
    ListNode* curr = head;
    ListNode* nTh = head;
    ListNode* prev = nullptr;
    
    for(int i = 0;i<k;i++){
        if (!curr) return head;
        curr = curr->next;
    }
    while(curr){
        prev = nTh;
        nTh = nTh->next;
        curr = curr->next;
    }
    if(!prev){
        head = head->next;
        delete nTh;
    }
    else{
        ListNode* toDelete = nTh;
        prev->next = toDelete->next;
        delete toDelete;
    }
    return head;
}


// Task7 : Find the middle element of a linked list
ListNode* findMiddle(ListNode* head){
    ListNode* fast = head->next;
    ListNode* slow = head;
    
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Task8 : Sort a linked list in ascending order
ListNode* mergeSort(ListNode* head){
    if(!head || !head->next)
        return head;
    
    ListNode* mid = findMiddle(head);
    ListNode* secondPart = mid->next;
    mid->next = nullptr;
    ListNode* left = mergeSort(head);
    ListNode* right = mergeSort(secondPart);
    
    return merge(left, right);
}

// Task9: Add two numbers
ListNode* addTwoNumbers(ListNode* l1,ListNode* l2){
    int carry = 0;
    ListNode* curr1 = l1;
    ListNode* curr2 = l2;
    ListNode* dummy = new ListNode(0);
    ListNode* iter = dummy;
    while(curr1 && curr2){
        int currSum = carry + curr1->val + curr2->val;
        iter->next = new ListNode(currSum % 10);
        carry = currSum / 10;
        iter = iter->next;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    while(curr1){
        if(carry > 0){
            int currSum = curr1->val + carry;
            iter->next = new ListNode(currSum % 10);
            carry = currSum / 10;
        }
        else{
            iter->next = new ListNode(curr1->val);
        }
        iter = iter->next;
        curr1 = curr1->next;
    }
    while(curr2){
        if(carry > 0){
            int currSum = curr2->val + carry;
            iter->next = new ListNode(currSum % 10);
            carry = currSum / 10;
            iter = iter->next;
            curr2 = curr2->next;
        }
        else{
            iter->next = new ListNode(curr2->val);
        }
        iter = iter->next;
        curr2 = curr2->next;
    }
    if(carry > 0)
        iter->next = new ListNode(carry);
    
    ListNode* res = dummy->next;
    delete dummy;
    return res;
        
}

//Task10 : Swap nodes in pairs
ListNode* swapNodes(ListNode* head){
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;
    
    while(prev && prev->next && prev->next->next){
        ListNode* first = prev->next;
        ListNode* second = first->next;
        
        first->next = second->next;
        second->next = first;
        prev->next = second;
        prev = first;
    }
    ListNode* toReturn = dummy->next;
    delete dummy;
    return toReturn;
}


//Task11 : Delete a node from a linked list without having access to its head
void deleteNode(ListNode* node){
    if(!node || !node->next) return;
    
    node->val = node->next->val;
    ListNode* toDelete = node->next;
    node->next = node->next->next;
    delete toDelete;
}

//Task12 : Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.

ListNode* oddsBeforeEvens(ListNode* head){
    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = even;
    while(even && even->next){
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = evenHead;
    return head;
}

bool isEven(int num){
    return !(num & 1);
}
//Task12 : dummy solution (for me)
ListNode* oddsBeforeEvensDummy(ListNode* head){
    ListNode* evens = new ListNode(0);
    ListNode* odds = new ListNode(0);
    ListNode* evenIter = evens;
    ListNode* oddsIter = odds;
    ListNode* curr = head;
    int ind = 1;
    while(curr){
        if(!isEven(ind)){
            oddsIter->next = new ListNode(curr->val);
            oddsIter = oddsIter->next;
        }
        else{
            evenIter->next = new ListNode(curr->val);
            evenIter = evenIter->next;
        }
        curr = curr->next;
        ind++;
    }
    oddsIter->next = evens->next;
    ListNode* toReturn = odds->next;
    delete odds;
    delete evens;
    return toReturn;
}

int main(int argc, const char * argv[]) {
    
    std::time_t currentTime = std::time(nullptr);
    std::cout<<currentTime<<std::endl;
    
}
