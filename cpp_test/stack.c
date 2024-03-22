int funcB(int a) {
    return a + 1;
}

int funcA(int b) {
    return funcB(b);
}

int main() {
    int a = funcA(1);
    return 0;
}
