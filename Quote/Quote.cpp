#include "Quote.hpp"

std::ostream& Quote::debug(std::ostream& os) const {
    os << "bookNo: " << bookNo << "  price: " << price;
    return os;
}

Quote::Quote(const Quote& rhs) : bookNo(rhs.bookNo), price(rhs.price) {
    std::cout << "Quote copy constructor" << std::endl;
}
Quote& Quote::operator=(const Quote& rhs) {
    std::cout << "Quote copy assignment" << std::endl;
    bookNo = rhs.bookNo;
    price = rhs.price;
    return *this;
}
Quote::Quote(Quote&& rhs) : bookNo(std::move(rhs.bookNo)), price(std::move(rhs.price)) {
    std::cout << "Quote move constructor" << std::endl;
}
Quote& Quote::operator=(Quote&& rhs) {
    std::cout << "Quote move assignment" << std::endl;
    bookNo = std::move(rhs.bookNo);
    price = std::move(rhs.price);
    return *this;
}