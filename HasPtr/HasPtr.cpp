#include <algorithm>
#include <iostream>
#include <vector>

#include "HasPtr.hpp"

inline void swap(HasPtr& lhs, HasPtr& rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "swapped" << std::endl;
}

HasPtr::HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {}

HasPtr& HasPtr::operator=(HasPtr& rhs) {
    std::string* temp = new std::string(*rhs.ps);
    delete ps;
    ps = temp;
    i = rhs.i;
    std::cout << "HasPtr copy assignment" << std::endl;
    return *this;
}

HasPtr& HasPtr::operator=(HasPtr&& rhs) {
    std::string* temp = rhs.ps;
    delete ps;
    ps = temp;
    i = rhs.i;
    rhs.ps = nullptr;
    std::cout << "HasPtr move assignment" << std::endl;
    return *this;
}

HasPtr::~HasPtr() {
    delete ps;
}
