#include <algorithm>
#include <cstring>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

#include "test_util.hpp"

class QueryResult;

class TextQuery {
   public:
    TextQuery(std::ifstream& ifs);

    QueryResult query(const std::string&) const;

   private:
    std::shared_ptr<std::vector<std::string>> lines_ptr;
    std::map<std::string, std::shared_ptr<std::set<unsigned>>> word_lines;
    std::map<std::string, unsigned> word_counts;
};

TextQuery::TextQuery(std::ifstream& ifs) : lines_ptr(std::make_shared<std::vector<std::string>>()) {
    std::string line;
    size_t line_number = 1;
    while (std::getline(ifs, line)) {
        lines_ptr->push_back(line);
        std::istringstream iss(line);
        std::string s;
        while (iss >> s) {
            if (word_lines[s] == nullptr) {
                word_lines[s] = std::make_shared<std::set<unsigned>>();
            }
            word_lines[s]->insert(line_number);
            ++word_counts[s];
        }

        ++line_number;
    }
}

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

std::set<unsigned>::iterator QueryResult::begin() {
    return word_lines_ptr->begin();
}
std::set<unsigned>::iterator QueryResult::end() {
    return word_lines_ptr->end();
}

std::shared_ptr<std::vector<std::string>> QueryResult::get_file() {
    return std::make_shared<std::vector<std::string>>(lines_ptr);
}

bool QueryResult::check() {
    return word_lines_ptr != nullptr;
}

std::ostream& QueryResult::print(std::ostream& os) const {
    os << word << " occurs " << word_count << make_plural(" time", word_count, "s") << '\n';
    for (auto it = word_lines_ptr->begin(); it != word_lines_ptr->end(); ++it) {
        os << "\t(line " << *it << ") " << (*lines_ptr)[*it - 1] << '\n';
    }
    return os;
}

QueryResult TextQuery::query(const std::string& s) const {
    auto it = word_lines.find(s);
    if (it == word_lines.end()) {
        return QueryResult(s, lines_ptr, nullptr, 0);
    }
    return QueryResult(s, lines_ptr, it->second, word_counts.at(s));
}

void runQueries(std::ifstream& infile) {
    TextQuery tq(infile);
    while (true) {
        std::cout << "Enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") {
            break;
        }
        QueryResult qr = tq.query(s);
        if (qr.check()) {
            qr.print(std::cout) << std::endl;
        }
        else {
            std::cout << "Word not found\n";
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream ifs("in2.txt");
    runQueries(ifs);
    return 0;
}
