#include "Bulk_quote.hpp"

double Bulk_quote::net_price(size_t n) const {
    return n * price * (n >= qty ? 1 - discount : 1);
}

std::ostream& Bulk_quote::debug(std::ostream& os) const {
    Quote::debug(os);
    os << "  min_qty: " << qty << "  discount: " << discount;
    return os;
}

Bulk_quote::Bulk_quote(const Bulk_quote& rhs) : Disc_quote(rhs) {
    std::cout << "Bulk_quote copy constructor" << std::endl;
}
Bulk_quote& Bulk_quote::operator=(const Bulk_quote& rhs) {
    std::cout << "Bulk_quote copy assignment" << std::endl;
    Disc_quote::operator=(rhs);
    return *this;
}
Bulk_quote::Bulk_quote(Bulk_quote&& rhs) : Disc_quote(std::move(rhs)) {
    std::cout << "Bulk_quote move constructor" << std::endl;
}
Bulk_quote& Bulk_quote::operator=(Bulk_quote&& rhs) {
    std::cout << "Bulk_quote move assignment" << std::endl;
    Disc_quote::operator=(std::move(rhs));
    return *this;
}
