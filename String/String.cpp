#include <iostream>

#include "String.hpp"

std::allocator<char> String::alloc;

String::~String() {
    free();
}

String::String(const char* s) : String() {
    if (s) {
        while (*s) {
            push_back(*s++);
        }
    }
}

void String::check_alloc() {
    if (size() == capacity()) {
        reallocate();
    }
}

void String::reallocate(size_t n) {
    size_t sz = size() * 2;
    if (n > 0) {
        sz = n;
    }
    else if (!sz) {
        sz = 1;
    }
    char* dest = alloc.allocate(sz);
    char* it = dest;
    char* temp_first_elem = first_element;
    for (size_t i = size(); i > 0; --i) {
        alloc.construct(it++, *temp_first_elem++);
    }
    free();
    first_element = dest;
    first_free = it;
    cap = first_element + sz;
}

void String::free() {
    if (first_element) {
        while (first_free != first_element) {
            alloc.destroy(--first_free);
        }
        alloc.deallocate(first_element, capacity());
    }
}

std::pair<char*, char*> String::copy_alloc(const char* b, const char* e) {
    char* new_begin = alloc.allocate(e - b);
    return {new_begin, std::uninitialized_copy(b, e, new_begin)};
}
String::String(const String& rhs) {
    std::pair<char*, char*> data = copy_alloc(rhs.begin(), rhs.end());
    first_element = data.first;
    first_free = data.second;
    std::cout << "String copy constructor" << std::endl;
}

String& String::operator=(const String& rhs) {
    std::pair<char*, char*> data = copy_alloc(rhs.begin(), rhs.end());
    free();
    first_element = data.first;
    first_free = data.second;
    std::cout << "String copy assignment" << std::endl;
    return *this;
}

String::String(String&& rhs) : first_element(rhs.first_element), first_free(rhs.first_free), cap(rhs.cap) {
    rhs.set_nullptr();
    std::cout << "String move constructor" << std::endl;
}

String& String::operator=(String&& rhs) {
    if (this != &rhs) {
        free();
        first_element = rhs.first_element;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.set_nullptr();
        std::cout << "String move assignment" << std::endl;
    }
    return *this;
}

char String::operator[](size_t i) {
    return *(first_element + i);
}

void String::push_back(char c) {
    check_alloc();
    alloc.construct(first_free++, c);
}

void String::pop_back() {
    if (size() > 0) {
        alloc.destroy(first_free--);
    }
    else {
        throw new std::out_of_range("pop_back on empty String");
    }
}
void String::set_nullptr() {
    first_element = first_free = cap = nullptr;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    for (char* it = s.begin(); it != s.end(); ++it) {
        os << *it;
    }
    return os;
}

bool operator==(const String& lhs, const String& rhs) {
    char* it1 = lhs.begin();
    char* it2 = rhs.begin();
    for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        if (*it1 != *it2) {
            return false;
        }
    }
    return it1 == lhs.end() && it2 == rhs.end();
}
bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs) {
    char* it1 = lhs.begin();
    char* it2 = rhs.begin();
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
bool operator>(const String& lhs, const String& rhs) {
    return rhs < lhs;
}
bool operator<=(const String& lhs, const String& rhs) {
    return !(lhs > rhs);
}
bool operator>=(const String& lhs, const String& rhs) {
    return !(lhs < rhs);
}