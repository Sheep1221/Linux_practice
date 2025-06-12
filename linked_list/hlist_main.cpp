#include "hlist.h"
#include <iostream>


// why we use this wrapper?
// since we have no distructor with the struct
struct MyNode : public hlist_node {
    int value;
    MyNode(int val) : value(val) {}
};

void print_hlist(hlist_head* head) {
    hlist_node* cur = head->first;
    while (cur) {
        MyNode* node = static_cast<MyNode*>(cur);
        std::cout << node->value << " -> ";
        cur = cur->next;
    }
    std::cout << "NULL\n";
}

int main() {
    hlist_head list;

    MyNode a(1), b(2), c(3);

    hlist_add_head(&a, &list);
    hlist_add_head(&b, &list);
    hlist_add_head(&c, &list);

    std::cout << "Initial list:\n";
    print_hlist(&list);  // Output: 3 -> 2 -> 1 -> NULL

    hlist_del(&b);
    std::cout << "After deleting node with value 2:\n";
    print_hlist(&list);  // Output: 3 -> 1 -> NULL

    hlist_del(&c);
    std::cout << "After deleting node with value 3:\n";
    print_hlist(&list);  // Output: 1 -> NULL

    hlist_del(&a);
    std::cout << "After deleting node with value 1:\n";
    print_hlist(&list);  // Output: NULL

    return 0;
}