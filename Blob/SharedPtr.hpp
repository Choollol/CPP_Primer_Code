#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

#include <functional>

#include "DebugDelete.hpp"

template <typename T>
class SharedPtr {
    using deleter_type = std::function<void(T*)>;

   public:
    SharedPtr() = default;
    explicit SharedPtr(T t, deleter_type d = DebugDelete()) : pointer(new T(t)), ref_count(new size_t(1)), deleter(d) {}
    explicit SharedPtr(T* p, deleter_type d = DebugDelete()) : pointer(p), ref_count(new size_t(1)), deleter(d) {}
    template <typename... Args>
    SharedPtr(Args&&... args) : pointer(new T(std::forward<Args>(args)...)), ref_count(new size_t(1)) {}

    SharedPtr(const SharedPtr&);
    SharedPtr& operator=(const SharedPtr&);

    SharedPtr(SharedPtr&&);
    SharedPtr& operator=(SharedPtr&&);

    ~SharedPtr() { dec_ref(); }

    T& operator*() const { return *pointer; }
    T* operator->() const { return pointer; }

    T* get() const { return pointer; }

    size_t use_count() { return *ref_count; }

   private:
    T* pointer;
    deleter_type deleter = DebugDelete();
    size_t* ref_count;

    void dec_ref();
    void set_nullptr() {
        pointer = nullptr;
        ref_count = nullptr;
    }
};

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& rhs) : pointer(rhs.pointer), ref_count(rhs.ref_count), deleter(rhs.deleter) {
    ++*ref_count;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& rhs) {
    ++*ref_count;

    dec_ref();

    pointer = rhs.pointer;
    ref_count = rhs.ref_count;
    deleter = rhs.deleter;

    return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& rhs) : pointer(std::move(rhs.pointer)), ref_count(std::move(rhs.ref_count)), deleter(std::move(rhs.deleter)) {
    ++*ref_count;
    rhs.set_nullptr();
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& rhs) {
    if (*this != rhs) {
        dec_ref();
        pointer = std::move(rhs.pointer);
        ref_count = std::move(rhs.ref_count);
        ++*ref_count;
        rhs.set_nullptr();
    }
    return *this;
}

template <typename T>
void SharedPtr<T>::dec_ref() {
    if (pointer) {
        --*ref_count;
        if (*ref_count == 0) {
            deleter(pointer);
            delete ref_count;
        }
        set_nullptr();
    }
}

template <typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args) {
    T t = T(std::forward<Args>(args)...);
    return SharedPtr<T>(t);
}

#endif