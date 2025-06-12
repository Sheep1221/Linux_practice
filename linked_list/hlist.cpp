#include <iostream>
#include "hlist.h"


// There's no "hlist_add_tail" in Linux Kernal -> higher complexity than "hlist_add_head"
// hlist_add_tail: O(N); hlist_add_head: O(1)
void hlist_add_head(hlist_node* node, hlist_head* head){
    node->next = head->first;
    if(head->first)
        head->first->pprev = &node->next;
    head->first = node;
    node->pprev = &head->first;
    // usage of head->first here? for each node:
    // if node is the first node: node->pprev = &head->first
    // if node is a middle node: node->pprev = &prev_node->next
}

void hlist_del(hlist_node* node){
    *node->pprev = node->next;
    // why don't using node->pprev = &node->next ?
    // -> because we hope that we can also change the head->first if needed
    if(node->next)
        node->next->pprev = node->pprev;
}
