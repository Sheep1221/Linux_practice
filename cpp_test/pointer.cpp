#include <iostream>

int main(){
    int a[10];
    for(int i=0; i<10; ++i){
        a[i] = 2*i;
    }

    std::cout<< "a[8]= "<< a[8]<< "\n";
    std::cout<< "*a+8= "<< *a+8<< "\n";
    std::cout<< "*(a+8)= "<< *(a+8)<< "\n";
}
