#include <iostream>
#include <string>
#include "hlist.h"

#define container_of(ptr, type, member) \ 
    ((type*)((char*)(ptr) - offsetof(type, member)))
#define HASH_VALUE 5381
#define TABLE_SIZE 16

struct MyEntry{
    std::string key;
    hlist_node node;
    int value;

    MyEntry(const std::string& k): key(k){}
};

unsigned int hashing_string(const std::string& str){
    unsigned long hash = HASH_VALUE;
    for(char c:str){
        hash = (hash<<5)+hash+c;
    }
    return static_cast<unsigned int>(hash);
}

class hash_map{
private:
    hlist_head table[TABLE_SIZE];

public:
    int insert();
    void printall();
    int& operator[](const std::string& key);

};

int main(){
    hash_map mapp;
    std::cout<< mapp["apple"]<< "\n";
    mapp["apple"] = 50;
    std::cout<< mapp["apple"]<< "\n";
    mapp["banana"] = 30;
    std::cout<< mapp["banana"]<< "\n";
    mapp["peach"] = 20;
    std::cout<< mapp["peach"]<< "\n";
    std::cout<< mapp["banana"]<< "\n";
    mapp["grape"] = 10;
    std::cout<< mapp["grape"]<< "\n";
}

int& hash_map::operator[](const std::string& key){
    unsigned int hash = hashing_string(key) % TABLE_SIZE;
    hlist_node* node = table[hash].first;
    std::cout<< "hash of "<< key<< " = "<< hash<< "\n";

    while(node){
        MyEntry* entry = container_of(node, MyEntry, node);
        if(entry->key == key)
            return entry->value;
        node = node->next;
        std::cout<< "collapse!!!"<< "\n";
    }
    
    // if the key not existed, create new map
    MyEntry* new_entry = new MyEntry(key);
    hlist_add_head(&new_entry->node, &table[hash]);
    return new_entry->value;
}



