#include "StrBlobPtr.hpp"

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(size_t i) const {
    std::shared_ptr<std::vector<std::string>> p = wptr.lock();
    if (!p) {
        throw std::runtime_error("unbound StrBlobPtr");
    }
    else if (index >= p->size()) {
        throw std::out_of_range("StrBlobPtr index out of range");
    }
    return p;
}
std::string& StrBlobPtr::deref() const {
    auto p = check(index);
    return (*p)[index];
}
StrBlobPtr& StrBlobPtr::incr() {
    check(index);
    ++index;
    return *this;
}

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.index == rhs.index;
}
bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return !(lhs == rhs);
}

bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.index < rhs.index;
}

bool operator>(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return rhs < lhs;
}

bool operator<=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return !(lhs > rhs);
}
bool operator>=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return !(lhs < rhs);
}

StrBlobPtr& StrBlobPtr::operator++() {
    check(index);
    ++index;
    return *this;
}
StrBlobPtr& StrBlobPtr::operator--() {
    --index;
    check(index);
    return *this;
}

StrBlobPtr StrBlobPtr::operator++(int) {
    StrBlobPtr temp = *this;
    ++*this;
    return temp;
}
StrBlobPtr StrBlobPtr::operator--(int) {
    StrBlobPtr temp = *this;
    --*this;
    return temp;
}
StrBlobPtr operator+(StrBlobPtr lhs, size_t n) {
    lhs += n;
    return lhs;
}
StrBlobPtr& StrBlobPtr::operator+=(size_t n) {
    while (n--) {
        ++*this;
    }
    return *this;
}
StrBlobPtr operator-(StrBlobPtr lhs, size_t n) {
    lhs -= n;
    return lhs;
}
StrBlobPtr& StrBlobPtr::operator-=(size_t n) {
    while (n--) {
        --*this;
    }
    return *this;
}
ssize_t operator-(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return lhs.index - rhs.index;
}
std::string& StrBlobPtr::operator*() {
    auto p = check(index);
    return (*p)[index];
}
std::string* StrBlobPtr::operator->() {
    auto p = check(index);
    return &this->operator*();
}