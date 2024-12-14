#include <algorithm>
#include <sstream>

#include "QueryResult.hpp"
#include "TextQuery.hpp"

std::string filter_str(std::string& s) {
    std::string result;
    for (const char& c : s) {
        if (!std::ispunct(c)) {
            result += std::tolower(c);
        }
    }
    return result;
}

TextQuery::TextQuery(std::ifstream& ifs) : lines_ptr(std::make_shared<std::vector<std::string>>()) {
    std::string line;
    size_t line_number = 1;
    while (std::getline(ifs, line)) {
        lines_ptr->push_back(line);
        std::istringstream iss(line);
        std::string s;
        while (iss >> s) {
            s = filter_str(s);
            if (word_lines[s] == nullptr) {
                word_lines[s] = std::make_shared<std::set<size_t>>();
            }
            word_lines[s]->insert(line_number);
            //++word_counts[s];
        }

        ++line_number;
    }
}

TextQuery::QueryResult TextQuery::query(const std::string& s) const {
    auto it = word_lines.find(s);
    if (it == word_lines.end()) {
        return QueryResult(s, lines_ptr, nullptr);
    }
    return QueryResult(s, lines_ptr, it->second);
}

TextQuery::QueryResult TextQuery::query(const std::string& s, size_t lower, size_t upper) const {
    auto it = word_lines.find(s);
    if (it == word_lines.end()) {
        return QueryResult(s, lines_ptr, nullptr);
    }
    std::shared_ptr<std::set<size_t>> lines = it->second;
    auto b = std::find_if(lines->begin(), lines->end(), [lower](size_t n) -> bool { return n >= lower; });
    auto e = std::find_if(lines->rbegin(), lines->rend(), [upper](size_t n) -> bool { return n <= upper; }).base();
    return QueryResult(s, lines_ptr, std::make_shared<std::set<size_t>>(b, e));
}