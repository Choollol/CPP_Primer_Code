#ifndef STRBLOBVL_H
#define STRBLOBVL_H

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "StrBLobPtr.hpp"

class StrBlobVL {
    friend class StrBlobPtr;

   public:
    StrBlobVL();
    StrBlobVL(std::initializer_list<std::string>);

    StrBlobVL(StrBlobVL& other) : data(new std::vector<std::string>(*other.data)) {}
    StrBlobVL& operator=(StrBlobVL& other) { data = std::make_shared<std::vector<std::string>>(*other.data); }

    size_t size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string& s) { data->push_back(s); }
    void pop_back();

    std::string& front();
    std::string& front() const;
    std::string& back();
    std::string& back() const;

    StrBlobPtr begin();
    StrBlobPtr end();

   private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_t, const std::string&) const;
};
#endif