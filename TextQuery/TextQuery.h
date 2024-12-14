#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>

#include "QueryResult.h"

class TextQuery {
   public:
    TextQuery(std::ifstream& ifs);

    QueryResult query(const std::string&) const;

   private:
    std::shared_ptr<std::vector<std::string>> lines_ptr;
    std::map<std::string, std::shared_ptr<std::set<unsigned>>> word_lines;
    std::map<std::string, unsigned> word_counts;
};
#endif