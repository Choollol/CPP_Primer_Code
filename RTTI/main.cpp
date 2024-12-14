#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

struct C {};

template <typename T>
void print(const T& t) {
    std::cout << t.name() << std::endl;
}

template <typename T, typename... Args>
void print(const T& t, const Args&... args) {
    std::cout << t.name() << ", ";
    print(args...);
}

int main() {
    int n;
    long long ll;
    unsigned long long ull;
    size_t sz;
    const std::string& s = "aa";
    int* ip;
    long long& llr = ll;
    std::vector<std::string> vec;
    C c;
    print(typeid(int), typeid(n), typeid(ll), typeid(ull), typeid(sz), typeid(std::string), typeid(s), typeid(ip), typeid(llr), typeid(vec), typeid(c));
    return 0;
}