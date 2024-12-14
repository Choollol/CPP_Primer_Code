#ifndef ANDQUERY_HPP
#define ANDQUERY_HPP

#include "BinaryQuery.hpp"

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    friend void dynamic_cast_test();

   private:
    AndQuery(const Query& left, const Query& right) : BinaryQuery(left, right, '&') { std::cout << "AndQuery constructor" << std::endl; }

    TextQuery::QueryResult combine(const TextQuery::QueryResult&, const TextQuery::QueryResult&) const override;

    TextQuery::QueryResult eval(const TextQuery&) const override;
    TextQuery::QueryResult eval(const TextQuery&, size_t, size_t) const override;
};

#endif