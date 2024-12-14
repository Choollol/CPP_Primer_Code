#ifndef ORQUERY_HPP
#define ORQUERY_HPP

#include "BinaryQuery.hpp"

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    friend void dynamic_cast_test();

   private:
    OrQuery(const Query& left, const Query& right) : BinaryQuery(left, right, '|') { std::cout << "OrQuery constructor" << std::endl; }

    TextQuery::QueryResult combine(const TextQuery::QueryResult&, const TextQuery::QueryResult&) const override;

    TextQuery::QueryResult eval(const TextQuery&) const override;
    TextQuery::QueryResult eval(const TextQuery&, size_t, size_t) const override;
};

#endif