#include<stdio.h>

typedef struct vector_impl vector;
struct vector_impl{
    int values[5];
    vector (*mul)(const vector, const vector);
};

vector mul(vector a, vector b){
    vector vec = {
        .values = {0, 0, 0, 0, 0},
    };
    for(int i=0; i<5; ++i){
        vec.values[i] = a.values[i] * b.values[i];
    }
    return vec;
}

int main(){
    vector a = {
        .values = {5, 4, 3, 4 ,5},
        .mul = mul,
    };
    vector b = {
        .values = {1, 2, 3, 4, 5}
    };
    vector res = {
        .mul = mul,
    };
    res = res.mul(a, b);
    printf("Hello");
    //res.mul(a, b);
    for(int i=0; i<5; ++i){
        printf("%d ", a.values[i]);
    }
    printf("\n");
    for(int i=0; i<5; ++i){
        printf("%d ", res.values[i]);
    }
    printf("\n");
    return 0;
}
