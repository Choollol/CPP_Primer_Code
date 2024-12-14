#include <iostream>

#include "Vec.hpp"

int main() {
    Vec<int> vec1{1, 2, 3};
    Vec<int> vec2{1, 2, 3, 4};
    vec1.emplace_back(4);
    std::cout << (vec1 == vec2) << std::endl;
    return 0;
}