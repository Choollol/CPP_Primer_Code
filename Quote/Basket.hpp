#ifndef BASKET_HPP
#define BASKET_HPP

#include <memory>
#include <set>

#include "Quote.hpp"

class Basket {
   public:
    void add_item(const Quote&);
    void add_item(Quote&&);
    double total_receipt(std::ostream&) const;

   private:
    static bool compare(std::shared_ptr<Quote> p1, std::shared_ptr<Quote> p2) { return p1->isbn() < p2->isbn(); }
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

#endif