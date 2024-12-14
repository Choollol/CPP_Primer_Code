#ifndef BLOBPTR_HPP
#define BLOBPTR_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template <typename>
class Blob;

template <typename T>
class BlobPtr {
    friend bool operator==(const BlobPtr& lhs, const BlobPtr& rhs) {
        return lhs.wptr.lock() == rhs.wptr.lock() && lhs.index == rhs.index;
    }
    friend bool operator<(const BlobPtr& lhs, const BlobPtr& rhs) {
        return lhs.wptr.lock() == rhs.wptr.lock() && lhs.index < rhs.index;
    }

    friend ssize_t operator-(const BlobPtr& lhs, const BlobPtr& rhs) {
        if (lhs.wptr.lock() == rhs.wptr.lock()) {
            return static_cast<ssize_t>(lhs.index) - static_cast<ssize_t>(rhs.index);
        }
    }

   public:
    BlobPtr() : index(0) {}
    BlobPtr(const Blob<T>& b, size_t i = 0) try : wptr(b.data), index(i) {
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    T& operator[](size_t i) { return (*wptr.lock())[i]; }
    const T& operator[](size_t i) const { return (*wptr.lock())[i]; }

    BlobPtr& operator++();
    BlobPtr& operator--();

    BlobPtr operator++(int);
    BlobPtr operator--(int);

    BlobPtr& operator+=(size_t);
    BlobPtr& operator-=(size_t);

    T& operator*();
    T* operator->();

   private:
    std::weak_ptr<std::vector<T>> wptr;
    size_t index;

    std::shared_ptr<std::vector<T>> check(size_t, const std::string&) const;
    std::shared_ptr<std::vector<T>> check_empty(const std::string&) const;
};

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_t i, const std::string& msg) const {
    auto p = wptr.lock();
    if (!p) {
        throw new std::runtime_error("unbound BlobPtr");
    }
    else if (index >= p->size()) {
        throw new std::out_of_range(msg);
    }
    return p;
}

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check_empty(const std::string& oper) const {
    return check(0, oper + " on empty BlobPtr<" + typeid(T).name() + ">");
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
    check(index + 1, "increment past end of BlobPtr");
    ++index;
    return *this;
}
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
    check(index - 1, "decrement past beginning of BlobPtr");
    --index;
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
    BlobPtr temp = *this;
    ++*this;
    return temp;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
    BlobPtr temp = *this;
    --*this;
    return temp;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator+=(size_t n) {
    check(index + n, "compound assignment past end of BlobPtr");
    index += n;
    return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator-=(size_t n) {
    check(index - n, "compound assignment past beginning of BlobPtr");
    index -= n;
    return *this;
}

template <typename T>
T& BlobPtr<T>::operator*() {
    return (*check(index, "invalid dereference on BlobPtr"))[index];
}
template <typename T>
T* BlobPtr<T>::operator->() {
    return &**this;
}

/* template <typename T>
bool operator==(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.index == rhs.index;
} */
template <typename T>
bool operator!=(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
    return !(lhs == rhs);
}

/* template <typename T>
bool operator<(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.index < rhs.index;
} */
template <typename T>
bool operator>(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
    return rhs < lhs;
}
template <typename T>
bool operator<=(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
    return !(lhs > rhs);
}
template <typename T>
bool operator>=(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
    return !(lhs < rhs);
}

template <typename T>
BlobPtr<T> operator+(BlobPtr<T> lhs, size_t n) {
    lhs += n;
    return lhs;
}
template <typename T>
BlobPtr<T> operator-(BlobPtr<T> lhs, size_t n) {
    lhs -= n;
    return lhs;
}
/* template <typename T>
ssize_t operator-(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
    if (lhs.wptr.lock() == rhs.wptr.lock()) {
        return static_cast<ssize_t>(lhs.index) - static_cast<ssize_t>(rhs.index);
    }
} */

#endif