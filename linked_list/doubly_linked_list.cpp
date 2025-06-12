#include <iostream>

struct dll_node{
    int val;
    dll_node* prev;
    dll_node* next;
    dll_node(): val(0), prev(nullptr), next(nullptr){};
    dll_node(int x): val(x), prev(nullptr), next(nullptr){};
};

class DoublyLinkedList{
private:
    dll_node* root;
    dll_node* back = root;

public:
    DoublyLinkedList(): root(nullptr){}
    ~DoublyLinkedList(){
        dll_node* temp = root;
        while(temp){
            dll_node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
    void appendNode(int x){
        dll_node* temp = new dll_node(x);
        if(!root){
            root = temp;
            back = root;
            return;
        }
        temp->prev = back;
        back->next = temp;
        back = back->next;
    }
    int removeNode(int x){
        dll_node* temp = root;
        while(temp && temp->val!=x)
            temp = temp->next;
        if(!temp){
            std::cout<< x<< " not found\n";
            return -1;    
        }
        if(temp->prev)
            temp->prev->next = temp->next;
        else
            root = temp->next;
        if(temp->next)
            temp->next->prev = temp->prev;
        else
            back = temp->prev;
        
        delete temp;

        return 0;
    }
    void showAll(){
        dll_node* temp = root;
        while(temp){
            std::cout<< temp->val<<" ";
            temp = temp->next;
        }
        std::cout<< "\n";
    }


};

int main(){
    DoublyLinkedList list;
    list.appendNode(2);
    list.appendNode(5);
    list.appendNode(10);
    list.appendNode(50);
    list.showAll();
    list.removeNode(2);
    list.showAll();
    list.removeNode(50);
    list.showAll();
    list.appendNode(100);
    list.showAll();
}
