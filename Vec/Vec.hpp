#ifndef VEC_HPP
#define VEC_HPP

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>

template <typename T>
class Vec {
    friend bool operator==(const Vec& lhs, const Vec& rhs) {
        T* it1 = lhs.begin();
        T* it2 = rhs.begin();
        for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return false;
            }
        }
        return it1 == lhs.end() && it2 == rhs.end();
    }
    friend bool operator!=(const Vec& lhs, const Vec& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Vec& lhs, const Vec& rhs) {
        T* it1 = lhs.begin();
        T* it2 = rhs.begin();
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
    friend bool operator>(const Vec& lhs, const Vec& rhs) {
        return rhs < lhs;
    }
    friend bool operator<=(const Vec& lhs, const Vec& rhs) {
        return !(lhs > rhs);
    }
    friend bool operator>=(const Vec& lhs, const Vec& rhs) {
        return !(lhs < rhs);
    }

   public:
    Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(std::initializer_list<T> il);

    Vec(const Vec&);
    Vec& operator=(const Vec&);
    Vec(Vec&&);
    Vec& operator=(Vec&&);
    ~Vec() { free(); }

    Vec& operator=(std::initializer_list<T> il);

    void push_back(const T&);
    void pop_back();

    template <typename... Args>
    void emplace_back(Args&&... args);

    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    T* begin() const { return elements; }
    T* end() const { return first_free; }

    void reserve(size_t);
    void resize(size_t, const T&);

    T& operator[](size_t i) { return elements[i]; }
    const T& operator[](size_t i) const { return elements[i]; }

   private:
    static std::allocator<T> alloc;
    T* elements;
    T* first_free;
    T* cap;

    void check_alloc() {
        if (size() == capacity()) {
            reallocate();
        }
    }
    std::pair<T*, T*> copy_alloc(const T*, const T*);
    void reallocate(size_t = 0);
    void free();
    void set_nullptr() { elements = first_free = cap = nullptr; }

    void copy_vec(const Vec&, bool = false);
};

template <typename T>
std::allocator<T> Vec<T>::alloc;

template <typename T>
Vec<T>::Vec(std::initializer_list<T> il) {
    std::pair<T*, T*> data = copy_alloc(il.begin(), il.end());
    elements = data.first;
    first_free = cap = data.second;
}

template <typename T>
std::pair<T*, T*> Vec<T>::copy_alloc(const T* b, const T* e) {
    T* it = alloc.allocate(e - b);
    return {it, std::uninitialized_copy(b, e, it)};
}

template <typename T>
void Vec<T>::reallocate(size_t n) {
    size_t sz = 1;
    if (n > 0) {
        sz = n;
    }
    else if (size()) {
        sz = size() * 2;
    }
    T* dest = alloc.allocate(sz);
    T* temp_elem = elements;
    T* it = dest;
    for (size_t i = 0; i < size(); ++i) {
        alloc.construct(it++, std::move(*temp_elem++));
    }
    free();
    elements = dest;
    first_free = it;
    cap = elements + sz;
}

template <typename T>
void Vec<T>::free() {
    if (elements) {
        auto p = first_free;
        while (p != elements) {
            alloc.destroy(--p);
        }
        std::cout << capacity() << ' ' << size() << std::endl;
        alloc.deallocate(elements, capacity());
        std::cout << "deallocated" << std::endl;
    }
}

template <typename T>
void Vec<T>::copy_vec(const Vec& rhs, bool doFree) {
    std::pair<T*, T*> data = copy_alloc(rhs.begin(), rhs.end());
    if (doFree) {
        free();
    }
    elements = data.first;
    first_free = cap = data.second;
}

template <typename T>
Vec<T>::Vec(const Vec& rhs) {
    copy_vec(rhs);
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& rhs) {
    copy_vec(rhs, true);
    return *this;
}

template <typename T>
Vec<T>::Vec(Vec&& rhs) : elements(std::move(rhs.elements)), first_free(std::move(rhs.first_free)), cap(std::move(rhs.cap)) {
    rhs.set_nullptr();
}

template <typename T>
Vec<T>& Vec<T>::operator=(Vec&& rhs) {
    elements = std::move(rhs.elements);
    first_free = std::move(rhs.first_free);
    cap = std::move(rhs.cap);
    rhs.set_nullptr();
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::operator=(std::initializer_list<T> il) {
    *this = Vec(il);
    return *this;
}

template <typename T>
void Vec<T>::push_back(const T& t) {
    check_alloc();
    alloc.construct(first_free++, t);
}

template <typename T>
void Vec<T>::pop_back() {
    if (size() == 0) {
        throw new std::out_of_range("pop_back() on empty Vec");
    }
    alloc.destroy(--first_free);
}

template <typename T>
template <typename... Args>
void Vec<T>::emplace_back(Args&&... args) {
    check_alloc();
    alloc.construct(first_free++, std::forward<Args>(args)...);
}

template <typename T>
void Vec<T>::reserve(size_t n) {
    if (n > capacity()) {
        reallocate(n);
    }
}

template <typename T>
void Vec<T>::resize(size_t n, const T& t) {
    if (n < size()) {
        for (size_t i = size() - n; i != 0; --i) {
            pop_back();
        }
    }
    else if (n > size()) {
        for (size_t i = n - size(); i != 0; --i) {
            push_back(t);
        }
    }
}

template <typename T>
bool operator==(const Vec<T>& lhs, const Vec<T>& rhs) {
    T* it1 = lhs.begin();
    T* it2 = rhs.begin();
    for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        if (*it1 != *it2) {
            return false;
        }
    }
    return it1 == lhs.end() && it2 == rhs.end();
}
template <typename T>
bool operator!=(const Vec<T>& lhs, const Vec<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const Vec<T>& lhs, const Vec<T>& rhs) {
    T* it1 = lhs.begin();
    T* it2 = rhs.begin();
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
template <typename T>
bool operator>(const Vec<T>& lhs, const Vec<T>& rhs) {
    return rhs < lhs;
}
template <typename T>
bool operator<=(const Vec<T>& lhs, const Vec<T>& rhs) {
    return !(lhs > rhs);
}
template <typename T>
bool operator>=(const Vec<T>& lhs, const Vec<T>& rhs) {
    return !(lhs < rhs);
}

#endif