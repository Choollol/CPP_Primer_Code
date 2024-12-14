#ifndef QUOTE_HPP
#define QUOTE_HPP

#include <iostream>
#include <memory>
#include <string>

class Quote {
   public:
    Quote() = default;
    Quote(const std::string& bn, double pr) : bookNo(bn), price(pr) {}

    Quote(const Quote&);
    Quote& operator=(const Quote&);
    Quote(Quote&&);
    Quote& operator=(Quote&&);
    virtual ~Quote() = default;

    std::string isbn() const { return bookNo; }

    virtual double net_price(size_t n) const { return n * price; }

    virtual std::ostream& debug(std::ostream&) const;

    virtual Quote* clone() const& { return new Quote(*this); }
    virtual Quote* clone() && { return new Quote(std::move(*this)); }

   private:
    std::string bookNo;

   protected:
    double price = 0.0;
};

#endif