#ifndef HASPTR_H
#define HASPTR_H

#include <iostream>
#include <string>

class HasPtr {
    friend void swap(HasPtr&, HasPtr&);

   public:
    HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(HasPtr&& p) noexcept : ps(p.ps), i(p.i) { p.ps = 0; }
    HasPtr(const char* s) : ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr&);
    HasPtr& operator=(HasPtr&);
    HasPtr& operator=(HasPtr&&);
    bool operator<(const HasPtr& other) const {
        std::cout << "compared" << std::endl;
        return *ps < *other.ps;
    }

    ~HasPtr();

   private:
    std::string* ps;
    int i;
};
#endif