#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


int main() {
    std::vector<std::string> vec{"a", "", "b", ""};
    std::cout << std::count_if(vec.begin(), vec.end(), std::mem_fn(&std::string::empty));
    return 0;
}