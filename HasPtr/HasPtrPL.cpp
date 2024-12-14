#include "HasPtrPL.hpp"

HasPtrPL::HasPtrPL(HasPtrPL& other) : ps(other.ps), i(other.i), ref_count(other.ref_count) {
    --*ref_count;
}

HasPtrPL& HasPtrPL::operator=(const HasPtrPL& other) {
    ++*other.ref_count;
    if (--*ref_count == 0) {
        delete ps;
        delete ref_count;
    }
    ps = other.ps;
    i = other.i;
    ref_count = other.ref_count;
    return *this;
}

HasPtrPL::~HasPtrPL() {
    if (--*ref_count == 0) {
        delete ps;
        delete ref_count;
    }
}
