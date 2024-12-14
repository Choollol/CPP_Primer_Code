#ifndef TEXTQUERY_HPP
#define TEXTQUERY_HPP

#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>

class TextQuery {
   public:
    class QueryResult;

    TextQuery(std::ifstream& ifs);

    QueryResult query(const std::string&) const;
    QueryResult query(const std::string&, size_t, size_t) const;

   private:
    std::shared_ptr<std::vector<std::string>> lines_ptr;
    std::map<std::string, std::shared_ptr<std::set<size_t>>> word_lines;
    //std::map<std::string, size_t> word_counts;
};
#endif