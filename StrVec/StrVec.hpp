#ifndef STRVEC_H
#define STRVEC_H

#include <memory>
#include <string>

class StrVec {
    friend bool operator==(const StrVec&, const StrVec&);
    friend bool operator<(const StrVec&, const StrVec&);
    friend std::ostream& operator<<(std::ostream&, const StrVec&);

   public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string> il);

    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    StrVec(StrVec&&);
    StrVec& operator=(StrVec&&);
    ~StrVec();

    StrVec& operator=(std::initializer_list<std::string> il);

    void push_back(const std::string&);
    void pop_back();

    template <typename... Args>
    void emplace_back(Args&&... args) { push_back(std::string(std::forward<Args>(args)...)); }

    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string* begin() const { return elements; }
    std::string* end() const { return first_free; }

    void reserve(size_t);
    void resize(size_t, const std::string&);

    std::string& operator[](size_t i) { return elements[i]; }
    const std::string& operator[](size_t i) const { return elements[i]; }

   private:
    static std::allocator<std::string> alloc;
    std::string* elements;
    std::string* first_free;
    std::string* cap;

    void check_alloc() {
        if (size() == capacity()) {
            reallocate();
        }
    }
    std::pair<std::string*, std::string*> copy_alloc(const std::string*, const std::string*);
    void reallocate(size_t = 0);
    void free();
    void set_nullptr();

    void* operator new(size_t);
    void operator delete(void*) noexcept;
};

#endif