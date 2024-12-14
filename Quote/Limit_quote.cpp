#include "Limit_quote.hpp"

double Limit_quote::net_price(size_t n) const {
    double ret = 0;
    ret += std::min(n, qty) * price * (1 - discount);
    n -= max_qty;
    if (n > 0) {
        ret += price * n;
    }
    return ret;
}

std::ostream& Limit_quote::debug(std::ostream& os) const {
    Quote::debug(os);
    os << "  max_qty: " << qty << "  discount: " << discount;
    return os;
}