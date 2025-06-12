
// usage of hlist: to delete a node in O(1) time (used in hash table in Linux Kernal)
// Deletion in basic link list need O(N) time (to find PrevNode->next==TargetNode)
// Here mimic the implement in Linux Kernal
struct hlist_node{
    int val;
    hlist_node *next, **pprev;
    hlist_node() :val(0), next(nullptr), pprev(nullptr){}
    hlist_node(int x) :val(x), next(nullptr), pprev(nullptr){}
};

struct hlist_head{
    hlist_node* first;
    hlist_head(): first(nullptr) {}
    bool empty() const {
        return first == nullptr;
    }
};


void hlist_add_head(hlist_node* node, hlist_head* head);


void hlist_del(hlist_node* node);