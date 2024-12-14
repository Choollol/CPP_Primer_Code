#include "../../test_util.hpp"
#include "QueryResult.hpp"

std::set<size_t>::iterator TextQuery::QueryResult::begin() {
    return word_lines_ptr->begin();
}
std::set<size_t>::iterator TextQuery::QueryResult::end() {
    return word_lines_ptr->end();
}

std::set<size_t>::const_iterator TextQuery::QueryResult::cbegin() const {
    return word_lines_ptr->cbegin();
}
std::set<size_t>::const_iterator TextQuery::QueryResult::cend() const {
    return word_lines_ptr->cend();
}

std::shared_ptr<std::vector<std::string>> TextQuery::QueryResult::get_file() const {
    return std::shared_ptr<std::vector<std::string>>(lines_ptr);
}

bool TextQuery::QueryResult::check() {
    return word_lines_ptr != nullptr;
}

std::ostream& TextQuery::QueryResult::print(std::ostream& os) const {
    os << word << " occurs " << word_lines_ptr->size() << make_plural(" time", word_lines_ptr->size(), "s") << '\n';
    for (auto it = word_lines_ptr->begin(); it != word_lines_ptr->end(); ++it) {
        os << "\t(line " << *it << ") " << (*lines_ptr)[*it - 1] << '\n';
    }
    return os;
}
