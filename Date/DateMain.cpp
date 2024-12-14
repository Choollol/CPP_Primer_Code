#include "Date.hpp"

int main() {
    Date d1(2023, 1, 0), d2(2024, 12, 31);
    std::cout << d1 << " " << d2 << '\n';
    std::cout << (d1 < d2);
    return 0;
}