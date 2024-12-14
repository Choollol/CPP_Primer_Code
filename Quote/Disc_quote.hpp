#ifndef DISC_QUOTE_HPP
#define DISC_QUOTE_HPP

#include "Quote.hpp"

class Disc_quote : public Quote {
   public:
    Disc_quote() = default;
    Disc_quote(std::string bn, double pr, size_t q, double disc) : Quote(bn, pr), qty(q), discount(disc) {}

    Disc_quote(const Disc_quote&);
    Disc_quote& operator=(const Disc_quote&);
    Disc_quote(Disc_quote&&);
    Disc_quote& operator=(Disc_quote&&);

    double net_price(size_t) const override = 0;

   protected:
    size_t qty = 0;
    double discount = 0.0;
};

#endif