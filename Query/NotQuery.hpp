#ifndef NOTQUERY_HPP
#define NOTQUERY_HPP

#include "Query.hpp"
#include "Query_base.hpp"

class NotQuery : public Query_base {
    friend Query operator~(const Query&);
    friend void dynamic_cast_test();

   private:
    NotQuery(const Query& q) : query(q) { std::cout << "NotQuery constructor" << std::endl; }

    std::string rep() const override { return "~(" + query.rep() + ")"; }

    TextQuery::QueryResult negate(const TextQuery::QueryResult&) const;

    TextQuery::QueryResult eval(const TextQuery&) const override;
    TextQuery::QueryResult eval(const TextQuery&, size_t, size_t) const override;

    Query query;
};

#endif