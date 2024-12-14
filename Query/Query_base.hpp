#ifndef QUERY_BASE_HPP
#define QUERY_BASE_HPP

#include <string>

#include "QueryResult.hpp"
#include "TextQuery.hpp"

class Query_base {
    friend class Query;
    friend void dynamic_cast_test();

   protected:
    virtual ~Query_base() = default;

   private:
    virtual TextQuery::QueryResult eval(const TextQuery&) const = 0;
    virtual TextQuery::QueryResult eval(const TextQuery&, size_t, size_t) const = 0;
    virtual std::string rep() const = 0;
};

#endif