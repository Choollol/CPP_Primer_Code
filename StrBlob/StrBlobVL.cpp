#include "StrBlobVL.hpp"

StrBlobVL::StrBlobVL() : data(std::make_shared<std::vector<std::string>>()) {}
StrBlobVL::StrBlobVL(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlobVL::check(size_t i, const std::string& msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

void StrBlobVL::pop_back() {
    check(0, "pop back on empty StrBlobVL");
    data->pop_back();
}

std::string& StrBlobVL::front() {
    check(0, "front on empty StrBlobVL");
    return data->front();
}
std::string& StrBlobVL::front() const {
    check(0, "front on empty StrBlobVL");
    return data->front();
}
std::string& StrBlobVL::back() {
    check(0, "back on empty StrBlobVL");
    return data->back();
}
std::string& StrBlobVL::back() const {
    check(0, "back on empty StrBlobVL");
    return data->back();
}