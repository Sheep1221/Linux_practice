#include <iostream>
#include <unordered_map>
#include <utility>
#include <chrono>
#include <cstdint>

#define SHIFT 20
#define DIV_ROUND_UP(n, d) (n+d-1)/d

std::unordered_map<int, int> magicNumber;

int getMagic(int d){
    if(magicNumber.count(d) == 0)
        magicNumber[d] = DIV_ROUND_UP((1<<SHIFT), d);
        std::cout<< "magic number of "<< d<< "is: "<< magicNumber[d]<< "\n";
    return magicNumber[d];
}

std::pair<int, int> fast_div(int n, int d){
    int quot = getMagic(d)*n >> SHIFT;
    int rem = n - quot*d;
    return {quot, rem};
}


int main(){
    auto [quot1, rem1] = fast_div(42,8);
    std::cout<< quot1<< " "<< rem1<<"\n";
    
    auto [quot2, rem2] = fast_div(20,6);
    std::cout<< quot2<< " "<< rem2<<"\n";
    
    auto [quot3, rem3] = fast_div(18,6);
    std::cout<< quot3<< " "<< rem3<<"\n";
}
