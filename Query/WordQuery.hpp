#ifndef WORDQUERY_HPP
#define WORDQUERY_HPP

#include "Query_base.hpp"

class WordQuery : public Query_base {
    friend class Query;

   private:
    WordQuery(const std::string& s) : query_word(s) { std::cout << "WordQuery constructor" << std::endl; }

    std::string rep() const override { return query_word; }
    TextQuery::QueryResult eval(const TextQuery& tq) const override { return tq.query(query_word); }
    TextQuery::QueryResult eval(const TextQuery& tq, size_t lower, size_t upper) const override { return tq.query(query_word, lower, upper); }

    std::string query_word;
};

#endif