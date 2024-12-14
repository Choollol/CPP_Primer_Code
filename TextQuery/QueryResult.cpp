#include <iostream>

#include "QueryResult.h"
#include "test_util.hpp"

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

std::string make_plural(const std::string& s, unsigned n, const std::string& suff) {
    if (n > 1) {
        return s + suff;
    }
    return s;
}

std::ostream& QueryResult::print(std::ostream& os) const {
    os << word << " occurs " << word_count << make_plural(" time", word_count, "s") << '\n';
    for (auto it = word_lines_ptr->begin(); it != word_lines_ptr->end(); ++it) {
        os << "\t(line " << *it << ") " << (*lines_ptr)[*it - 1] << '\n';
    }
    return os;
}
