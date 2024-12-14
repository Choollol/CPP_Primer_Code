#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "StrBlob.hpp"

class StrBlobPtr {
    friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);

    friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>=(const StrBlobPtr&, const StrBlobPtr&);

    friend StrBlobPtr operator+(StrBlobPtr, size_t);
    friend StrBlobPtr operator-(StrBlobPtr, size_t);
    friend ssize_t operator-(const StrBlobPtr&, const StrBlobPtr&);

   public:
    StrBlobPtr() : index(0) {}
    StrBlobPtr(StrBlob& b, size_t i = 0) : wptr(b.data), index(i) {}

    StrBlobPtr& incr();
    std::string& deref() const;

    std::string& operator[](size_t i) { return (*wptr.lock())[i]; }
    const std::string& operator[](size_t i) const { return (*wptr.lock())[i]; }

    StrBlobPtr& operator++();
    StrBlobPtr& operator--();

    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);

    StrBlobPtr& operator+=(size_t);
    StrBlobPtr& operator-=(size_t);

    std::string& operator*();
    std::string* operator->();

   private:
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t index;

    std::shared_ptr<std::vector<std::string>> check(size_t i) const;
};

#endif