#include "Disc_quote.hpp"

Disc_quote::Disc_quote(const Disc_quote& rhs) : Quote(rhs), qty(rhs.qty), discount(rhs.discount) {
    std::cout << "Disc_quote copy consructor" << std::endl;
}
Disc_quote& Disc_quote::operator=(const Disc_quote& rhs) {
    std::cout << "Disc_quote copy assignment" << std::endl;
    Quote::operator=(rhs);
    qty = rhs.qty;
    discount = rhs.discount;
    return *this;
}
Disc_quote::Disc_quote(Disc_quote&& rhs) : Quote(std::move(rhs)), qty(std::move(rhs.qty)), discount(std::move(rhs.discount)) {
    std::cout << "Disc_quote move consructor" << std::endl;
}
Disc_quote& Disc_quote::operator=(Disc_quote&& rhs) {
    std::cout << "Disc_quote move assignment" << std::endl;
    Quote::operator=(std::move(rhs));
    qty = std::move(rhs.qty);
    discount = std::move(rhs.discount);
    return *this;
}