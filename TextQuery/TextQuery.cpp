#include <sstream>

#include "QueryResult.h"
#include "TextQuery.h"

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

QueryResult TextQuery::query(const std::string& s) const {
    auto it = word_lines.find(s);
    if (it == word_lines.end()) {
        return QueryResult(s, lines_ptr, nullptr, 0);
    }
    return QueryResult(s, lines_ptr, it->second, word_counts.at(s));
}