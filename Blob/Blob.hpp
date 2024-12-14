#ifndef BLOB_HPP
#define BLOB_HPP

#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "BlobPtr.hpp"
#include "SharedPtr.hpp"

template <typename>
class BlobPtr;

template <typename T>
class Blob {
    friend class BlobPtr<T>;

    friend bool operator==(const Blob& lhs, const Blob& rhs) {
        return *lhs->data == *rhs->data;
    }
    friend bool operator<(const Blob& lhs, const Blob& rhs) {
        return *lhs->data < *rhs->data;
    }
    friend std::ostream& operator<<(std::ostream& os, const Blob& rhs) {
        for (size_t i = 0; i < rhs.size(); ++i) {
            os << rhs[i] << ' ';
        }
        os << std::endl;
        return os;
    }

   public:
    Blob();
    Blob(std::initializer_list<T>);

    template <typename It>
    Blob(It b, It e);

    size_t size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    void push_back(const T&);
    void push_back(T&&);
    void pop_back();

    T& front();
    T& back();

    const T& front() const;
    const T& back() const;

    BlobPtr<T> begin();
    BlobPtr<T> end();

    BlobPtr<T> cbegin() const;
    BlobPtr<T> cend() const;

    T& operator[](size_t i) { return (*data)[i]; }
    const T& operator[](size_t i) const { return (*data)[i]; }

   private:
    //std::shared_ptr<std::vector<T>> data;
    SharedPtr<std::vector<T>> data;

    void check(size_t, const std::string&) const;
    void empty_check(const std::string&) const;
};

template <typename T>
Blob<T>::Blob() try : data(makeShared<std::vector<T>>()) {
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) try : data(makeShared<std::vector<T>>(il)) {
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}

template <typename T>
template <typename It>
Blob<T>::Blob(It b, It e) try : data(makeShared<std::vector<T>>(b, e)) {
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}

template <typename T>
void Blob<T>::check(size_t i, const std::string& msg) const {
    if (i >= size()) {
        throw new std::out_of_range(msg);
    }
}

template <typename T>
void Blob<T>::empty_check(const std::string& oper) const {
    check(0, oper + " on empty Blob<" + typeid(T).name() + ">");
}

template <typename T>
void Blob<T>::push_back(const T& t) {
    data->push_back(t);
}

template <typename T>
void Blob<T>::push_back(T&& t) {
    data->push_back(std::move(t));
}

template <typename T>
void Blob<T>::pop_back() {
    empty_check(__func__);
    data->pop_back();
}

template <typename T>
T& Blob<T>::front() {
    empty_check(__func__);
    return data->back();
}
template <typename T>
T& Blob<T>::back() {
    empty_check(__func__);
    return data->back();
}
template <typename T>
const T& Blob<T>::front() const {
    empty_check(__func__);
    return data->front();
}
template <typename T>
const T& Blob<T>::back() const {
    empty_check(__func__);
    return data->back();
}

template <typename T>
BlobPtr<T> Blob<T>::begin() {
    return BlobPtr(*this, 0);
}
template <typename T>
BlobPtr<T> Blob<T>::end() {
    return BlobPtr(*this, size());
}

template <typename T>
BlobPtr<T> Blob<T>::cbegin() const {
    return BlobPtr(*this, 0);
}
template <typename T>
BlobPtr<T> Blob<T>::cend() const {
    return BlobPtr(*this, size());
}

/* template <typename T>
bool operator==(const Blob<T>& lhs, const Blob<T>& rhs) {
    return *lhs->data == *rhs->data;
} */
template <typename T>
bool operator!=(const Blob<T>& lhs, const Blob<T>& rhs) {
    return !(lhs == rhs);
}

/* template <typename T>
bool operator<(const Blob<T>& lhs, const Blob<T>& rhs) {
    return *lhs->data < *rhs->data;
} */
template <typename T>
bool operator>(const Blob<T>& lhs, const Blob<T>& rhs) {
    return rhs < lhs;
}
template <typename T>
bool operator<=(const Blob<T>& lhs, const Blob<T>& rhs) {
    return !(lhs > rhs);
}
template <typename T>
bool operator>=(const Blob<T>& lhs, const Blob<T>& rhs) {
    return !(lhs < rhs);
}

#endif