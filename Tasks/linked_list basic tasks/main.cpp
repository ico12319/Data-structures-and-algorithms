#include <iostream>
#include <unordered_set>
#include <queue>

struct node{
    int val;
    node* next;
    
    node(int val) : val(val),next(nullptr){}
};

node* find_middle(node* head){
    node* fast = head->next;
    node* slow = head;
    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

bool contains_cycle_optimal(node* head){
    node* fast = head;
    node* slow = head;
    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
            return true;
    }
    return false;
}

bool contains_cycle(node* head){
    std::unordered_set<node*> seen;
    node* curr = head;
    seen.insert(curr);
    while(curr){
        curr = curr->next;
        if(seen.contains(curr))
            return true;
        seen.insert(curr);
    }
    return false;
}

struct comparator{
    bool operator()(const std::pair<int,int>& p1,const std::pair<int,int>& p2) const{
        return p1.second < p2.second;
    }
};

int most_common_element(node* head){
    std::unordered_map<int,int> freq;
    node* curr = head;
    while(curr){
        freq[curr->val]++;
        curr = curr->next;
    }
    
    std::vector<std::pair<int,int>> temp(freq.begin(),freq.end());
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,comparator>pq(temp.begin(),temp.end());
    return pq.top().first;
}

void print_list(node* head){
    node* curr = head;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
}

node* reverse(node* head){
    node* next = nullptr;
    node* prev = nullptr;
    while(head){
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    head = prev;
    return head;
}


void destroy(node* head){
    node* curr = head;
    while(curr){
        auto to_delete = curr;
        curr = curr->next;
        delete to_delete;
    }
}


void push_back(node*& begin,node*& end,node* to_add){
    if(!begin)
        begin = end = to_add;
    else{
        end->next = to_add;
        end = to_add;
    }
}

node* merge(node* list1,node* list2){
    node* result_begin = nullptr;
    node* result_end = nullptr;
    while(list1 && list2){
        if(list1->val < list2->val){
            push_back(result_begin, result_end, list1);
            list1 = list1->next;
        }
        else{
            push_back(result_begin, result_end, list2);
            list2 = list2->next;
        }
    }
    if(list1)
        push_back(result_begin, result_end, list1);
    if(list2)
        push_back(result_begin, result_end, list2);
    
    return result_begin;
}

// 1 2 3 | 4 5
node* merge_sort(node* list){
    if(!list || !list->next)
        return list;
    node* mid = find_middle(list);
    
    node* left_part = list;
    node* right_part = mid->next;
    mid->next = nullptr;
    
    left_part = merge_sort(left_part);
    right_part = merge_sort(right_part);
    
    return merge(left_part, right_part);
}

template<class predicate>
node* partition(node* list,const predicate& pred){
    node* true_to_pred_begin = nullptr;
    node* true_to_pred_end = nullptr;
    node* false_to_pred_begin = nullptr;
    node* false_to_pred_end = nullptr;
    
    node* curr = list;
    while(curr){
        if(pred(curr->val))
            push_back(true_to_pred_begin, true_to_pred_end, curr);
        else
            push_back(false_to_pred_begin, false_to_pred_end, curr);
        curr = curr->next;
    }
    
    if(true_to_pred_begin)
        true_to_pred_end->next = false_to_pred_begin;
    
    if(false_to_pred_end)
        false_to_pred_end->next = nullptr;
    
    return true_to_pred_begin != nullptr ? true_to_pred_begin : false_to_pred_begin;
}



int main(){
    node* head = new node(0);
    head->next= new node(2);
    head->next->next = new node(4);
    head->next->next->next = new node(6);
    head->next->next->next->next = new node(8);
    head->next->next->next->next->next = new node(12);
    
    head = partition(head, [](int x){return x % 2 == 0;});
    print_list(head);
}
