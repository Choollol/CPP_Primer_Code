#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>

class String {
    friend std::ostream& operator<<(std::ostream&, const String& s);
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);

    friend bool operator<(const String&, const String&);
    friend bool operator>(const String&, const String&);
    friend bool operator<=(const String&, const String&);
    friend bool operator>=(const String&, const String&);

   public:
    String() : first_element(nullptr), first_free(nullptr), cap(nullptr) {}
    String(const char* s);

    String(const String&);
    String& operator=(const String&);
    String(String&&);
    String& operator=(String&&);
    ~String();

    size_t size() const { return first_free - first_element; }
    size_t capacity() const { return cap - first_element; }

    char& operator[](size_t i) { return first_element[i]; }
    const char& operator[](size_t i) const { return first_element[i]; }

    void push_back(char);
    void pop_back();

    char* begin() const { return first_element; }
    char* end() const { return first_free; }

   private:
    static std::allocator<char> alloc;

    char* first_element;
    char* first_free;
    char* cap;

    void free();
    void check_alloc();
    void reallocate(size_t n = 0);
    std::pair<char*, char*> copy_alloc(const char*, const char*);
    void set_nullptr();
};

std::ostream& operator<<(std::ostream&, const String& s);

#endif