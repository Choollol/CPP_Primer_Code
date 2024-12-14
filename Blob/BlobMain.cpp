#include "Blob.hpp"
#include "SharedPtr.hpp"

int main() {
    std::vector<int> vec = {1, 2, 3};
    Blob<int> b(vec.begin(), vec.end());
    std::cout << b;
    return 0;
}