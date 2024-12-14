#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "StrVec.hpp"

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(std::initializer_list<std::string> il) {
    std::pair<std::string*, std::string*> data = copy_alloc(il.begin(), il.end());
    elements = data.first;
    first_free = cap = data.second;
}

void StrVec::push_back(const std::string& s) {
    check_alloc();
    //alloc.construct(first_free++, s);
    new (first_free++) std::string(s);
}
void StrVec::pop_back() {
    if (size() > 0) {
        //alloc.destroy(first_free--);
        first_free->~basic_string();
        --first_free;
    }
    else {
        throw new std::out_of_range("pop_back on empty StrVec");
    }
}

std::pair<std::string*, std::string*> StrVec::copy_alloc(const std::string* b, const std::string* e) {
    //std::string* it = alloc.allocate(e - b);
    std::string* it = new std::string[e - b]();  //static_cast<std::string*>(operator new(e - b));
    return {it, std::uninitialized_copy(b, e, it)};
}

void StrVec::reallocate(size_t n) {
    size_t sz = 1;
    if (n > 0) {
        sz = n;
    }
    else if (size()) {
        sz = size() * 2;
    }
    //std::string* dest = alloc.allocate(sz);
    std::string* dest = new std::string[sz]();  // static_cast<std::string*>(operator new(sz));
    std::string* it = dest;
    std::string* temp_elem = elements;
    for (size_t i = 0; i < size(); ++i) {
        //alloc.construct(it++, std::move(*temp_elem++));
        new (it++) std::string(std::move(*temp_elem++));
    }
    free();
    elements = dest;
    first_free = it;
    cap = elements + sz;
}
void StrVec::free() {
    if (elements) {
        while (first_free != elements) {
            //alloc.destroy(--first_free);
            (--first_free)->~basic_string();
        }
        //std::for_each(elements, first_free, [](std::string* p) { alloc.destroy(p); });
        //alloc.deallocate(elements, capacity());
        delete[] elements;
    }
}

StrVec::StrVec(const StrVec& rhs) {
    std::pair<std::string*, std::string*> data = copy_alloc(rhs.begin(), rhs.end());
    elements = data.first;
    first_free = cap = data.second;
}
StrVec& StrVec::operator=(const StrVec& rhs) {
    std::pair<std::string*, std::string*> data = copy_alloc(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
StrVec::StrVec(StrVec&& rhs) : elements(std::move(rhs.elements)), first_free(std::move(rhs.first_free)), cap(std::move(rhs.cap)) {
    rhs.set_nullptr();
}
StrVec& StrVec::operator=(StrVec&& rhs) {
    free();
    elements = std::move(rhs.elements);
    first_free = std::move(rhs.first_free);
    cap = std::move(rhs.cap);
    rhs.set_nullptr();
    return *this;
}
StrVec::~StrVec() {
    free();
}

void StrVec::reserve(size_t sz) {
    if (sz > capacity()) {
        reallocate(sz);
    }
}

void StrVec::resize(size_t sz, const std::string& s = std::string()) {
    if (sz < size()) {
        for (size_t i = size() - sz; i > 0; --i) {
            pop_back();
        }
    }
    else {
        for (size_t i = sz - size(); i > 0; --i) {
            push_back(s);
        }
    }
}
void StrVec::set_nullptr() {
    elements = first_free = cap = nullptr;
}

bool operator==(const StrVec& lhs, const StrVec& rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}
bool operator!=(const StrVec& lhs, const StrVec& rhs) {
    return !(lhs == rhs);
}
bool operator<(const StrVec& lhs, const StrVec& rhs) {
    std::string* it1 = lhs.begin();
    std::string* it2 = rhs.begin();
    for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        if (*it1 < *it2) {
            return true;
        }
        else if (*it1 > *it2) {
            return false;
        }
    }
    return it1 == lhs.end() && it2 != rhs.end();
}
bool operator>(const StrVec& lhs, const StrVec& rhs) {
    return rhs < lhs;
}
bool operator<=(const StrVec& lhs, const StrVec& rhs) {
    return !(lhs > rhs);
}
bool operator>=(const StrVec& lhs, const StrVec& rhs) {
    return !(lhs < rhs);
}

StrVec& StrVec::operator=(std::initializer_list<std::string> il) {
    *this = StrVec(il);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const StrVec& vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        os << *it << ' ';
    }
    os << std::endl;
    return os;
}

void* StrVec::operator new(size_t sz) {
    void* p = malloc(sz);
    if (!p) {
        throw std::bad_alloc();
    }
    return p;
}

void StrVec::operator delete(void* p) noexcept {
    ::free(p);
}