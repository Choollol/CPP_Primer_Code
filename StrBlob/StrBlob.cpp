#include "../../test_util.hpp"
#include "StrBlob.hpp"
#include "StrBlobPtr.hpp"

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_t i, const std::string& msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

inline void StrBlob::push_back(const std::string& s) {
    data->push_back(s);
}

inline void StrBlob::push_back(std::string&& s) {
    data->push_back(std::move(s));
}

void StrBlob::pop_back() {
    check(0, "pop back on empty StrBlob");
    data->pop_back();
}

std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}
std::string& StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

StrBlobPtr StrBlob::begin() {
    return StrBlobPtr(*this, 0);
}
StrBlobPtr StrBlob::end() {
    return StrBlobPtr(*this, data->size());
}

bool operator==(const StrBlob& lhs, const StrBlob& rhs) {
    return *lhs.data == *rhs.data;
}
bool operator!=(const StrBlob& lhs, const StrBlob& rhs) {
    return !(lhs == rhs);
}

bool operator<(const StrBlob& lhs, const StrBlob& rhs) {
    return *lhs.data < *rhs.data;
}
bool operator>(const StrBlob& lhs, const StrBlob& rhs) {
    return rhs < lhs;
}
bool operator<=(const StrBlob& lhs, const StrBlob& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const StrBlob& lhs, const StrBlob& rhs) {
    return !(lhs < rhs);
}