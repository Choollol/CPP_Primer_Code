#ifndef BINARYQUERY_HPP
#define BINARYQUERY_HPP

#include "Query.hpp"
#include "Query_base.hpp"

class BinaryQuery : public Query_base {
   protected:
    BinaryQuery(const Query& s1, const Query& s2, char oper) : lhs(s1), rhs(s2), op(oper) {
        std::cout << "BinaryQuery constructor" << std::endl;
    }

    std::string rep() const override { return "(" + lhs.rep() + " " + op + " " + rhs.rep() + ")"; }

    virtual TextQuery::QueryResult combine(const TextQuery::QueryResult&, const TextQuery::QueryResult&) const = 0;

    Query lhs;
    Query rhs;
    char op;
};

#endif