#include <iostream>
#include <vector>

#include "String.hpp"

int main(int argc, char* argv[]) {
    /* std::vector<String> vec;
    String s("aa");
    vec.push_back(s);
    std::cout << vec.capacity() << std::endl;
    vec.push_back("a");
    std::cout << vec.capacity() << std::endl;
    vec.push_back("aa");
    std::cout << vec.capacity() << std::endl; */
    String s1("aa"), s2("aaa");
    std::cout << (s1 < s2);
    return 0;
}