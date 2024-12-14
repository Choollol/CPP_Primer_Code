#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <memory>
#include <set>
#include <string>
#include <vector>

class QueryResult {
   public:
    QueryResult(const std::string& w, std::shared_ptr<std::vector<std::string>> lp,
                std::shared_ptr<std::set<unsigned>> wlp, unsigned wc) : word(w), lines_ptr(lp), word_lines_ptr(wlp), word_count(wc) {}
    std::ostream& print(std::ostream&) const;
    bool check();

    std::set<unsigned>::iterator begin();
    std::set<unsigned>::iterator end();

    std::shared_ptr<std::vector<std::string>> get_file();

   private:
    std::string word;
    std::shared_ptr<std::vector<std::string>> lines_ptr;
    std::shared_ptr<std::set<unsigned>> word_lines_ptr;
    unsigned word_count;
};
#endif