#include "NotQuery.hpp"

Query operator~(const Query& query) {
    return std::shared_ptr<Query_base>(new NotQuery(query));
}

TextQuery::QueryResult NotQuery::negate(const TextQuery::QueryResult& result) const {
    size_t sz = result.get_file()->size();
    std::set<size_t> ret_lines;
    auto it = result.cbegin(), end = result.cend();
    for (size_t i = 1; i < sz; ++i) {
        if (it == end || *it != i) {
            ret_lines.insert(i);
        }
        else {
            ++it;
        }
    }
    return TextQuery::QueryResult(rep(), result.get_file(), std::make_shared<std::set<size_t>>(ret_lines));
}

TextQuery::QueryResult NotQuery::eval(const TextQuery& tq) const {
    TextQuery::QueryResult result = query.eval(tq);
    return negate(result);
}

TextQuery::QueryResult NotQuery::eval(const TextQuery& tq, size_t lower, size_t upper) const {
    TextQuery::QueryResult result = query.eval(tq, lower, upper);
    return negate(result);
}