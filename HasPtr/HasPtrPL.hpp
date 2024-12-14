#ifndef HASPTRPL_H
#define HASPTRPL_H

#include <string>

class HasPtrPL {
   public:
    HasPtrPL(const std::string& s = std::string()) : ps(new std::string(s)), i(0), ref_count(new size_t(1)) {}

    HasPtrPL(HasPtrPL&);
    HasPtrPL& operator=(const HasPtrPL&);
    ~HasPtrPL();

   private:
    std::string* ps;
    int i;
    size_t* ref_count;
};

#endif