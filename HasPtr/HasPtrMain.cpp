#include <algorithm>
#include <vector>

#include "HasPtr.hpp"
#include "HasPtrPL.hpp"

int main() {
    HasPtr hp, hp2;
    hp = hp2;
    hp = std::move(hp2);
    return 0;
}