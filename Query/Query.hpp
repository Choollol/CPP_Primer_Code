#ifndef QUERY_HPP
#define QUERY_HPP

#include <memory>
#include <string>

#include "DebugDelete.hpp"
#include "QueryResult.hpp"
#include "Query_base.hpp"
#include "WordQuery.hpp"

class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

   public:
    Query(const std::string&);

    TextQuery::QueryResult eval(const TextQuery& tq) const { return q->eval(tq); }
    TextQuery::QueryResult eval(const TextQuery& tq, size_t lower, size_t upper) const { return q->eval(tq, lower, upper); }
    std::string rep() const { return q->rep(); }

   private:
    Query(std::shared_ptr<Query_base> p) : q(p) { std::cout << "Query shared_ptr constructor" << std::endl; }
    std::shared_ptr<Query_base> q;
};

#endif
