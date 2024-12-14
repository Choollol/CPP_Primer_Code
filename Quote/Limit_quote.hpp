#ifndef LIMIT_QUOTE_HPP
#define LIMIT_QUOTE_HPP

#include "Disc_quote.hpp"
#include "Quote.hpp"


class Limit_quote : public Disc_quote {
   public:
    Limit_quote(const std::string& bn, double pr, int mq, double disc) : Disc_quote(bn, pr, mq, disc) {}

    double net_price(size_t) const override;

    std::ostream& debug(std::ostream&) const override;

   private:
    size_t max_qty;
    double discount;
};

#endif