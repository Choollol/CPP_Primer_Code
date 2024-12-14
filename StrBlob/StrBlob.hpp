#ifndef STRBLOB_H
#define STRBLOB_H

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "ConstStrBlobPtr.hpp"
#include "StrBlobPtr.hpp"


class StrBlob {
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
    friend bool operator==(const StrBlob&, const StrBlob&);
    friend bool operator!=(const StrBlob&, const StrBlob&);

    friend bool operator<(const StrBlob&, const StrBlob&);
    friend bool operator>(const StrBlob&, const StrBlob&);
    friend bool operator<=(const StrBlob&, const StrBlob&);
    friend bool operator>=(const StrBlob&, const StrBlob&);

   public:
    StrBlob();
    StrBlob(std::initializer_list<std::string>);
    size_t size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string& s);
    void push_back(std::string&&);
    void pop_back();

    std::string& front();
    std::string& front() const;
    std::string& back();
    std::string& back() const;

    StrBlobPtr begin();
    StrBlobPtr end();

    std::string& operator[](size_t i) { return (*data)[i]; }
    const std::string& operator[](size_t i) const { return (*data)[i]; }

   private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_t, const std::string&) const;
};

bool operator==(const StrBlob&, const StrBlob&);
bool operator!=(const StrBlob&, const StrBlob&);

#endif