#ifndef QUERYRESULT_HPP
#define QUERYRESULT_HPP

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "TextQuery.hpp"

class TextQuery::QueryResult {
   public:
    QueryResult() = default;
    QueryResult(const std::string& w, std::shared_ptr<std::vector<std::string>> lp,
                std::shared_ptr<std::set<size_t>> wlp) : word(w), lines_ptr(lp), word_lines_ptr(wlp) {}
    std::ostream& print(std::ostream&) const;
    bool check();

    std::set<size_t>::iterator begin();
    std::set<size_t>::iterator end();
    std::set<size_t>::const_iterator cbegin() const;
    std::set<size_t>::const_iterator cend() const;

    std::shared_ptr<std::vector<std::string>> get_file() const;

   private:
    std::string word;
    std::shared_ptr<std::vector<std::string>> lines_ptr;
    std::shared_ptr<std::set<size_t>> word_lines_ptr;
};

#endif