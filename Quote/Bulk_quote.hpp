#ifndef BULK_QUOTE_HPP
#define BULK_QUOTE_HPP

#include "Disc_quote.hpp"
#include "Quote.hpp"

class Bulk_quote : public Disc_quote {
   public:
    using Disc_quote::Disc_quote;

    Bulk_quote(const Bulk_quote&);
    Bulk_quote& operator=(const Bulk_quote&);
    Bulk_quote(Bulk_quote&&);
    Bulk_quote& operator=(Bulk_quote&&);

    double net_price(size_t n) const override;

    std::ostream& debug(std::ostream&) const override;

    Bulk_quote* clone() const& override { return new Bulk_quote(*this); }
    Bulk_quote* clone() && override { return new Bulk_quote(std::move(*this)); }
};

#endif