#include "OrQuery.hpp"

Query operator|(const Query& lhs, const Query& rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs), DebugDelete());
}

TextQuery::QueryResult OrQuery::combine(const TextQuery::QueryResult& left, const TextQuery::QueryResult& right) const {
    std::set<size_t> ret_lines(left.cbegin(), left.cend());

    ret_lines.insert(right.cbegin(), right.cend());

    return TextQuery::QueryResult(rep(), left.get_file(), std::make_shared<std::set<size_t>>(ret_lines));
}
TextQuery::QueryResult OrQuery::eval(const TextQuery& tq) const {
    TextQuery::QueryResult left = lhs.eval(tq);
    TextQuery::QueryResult right = rhs.eval(tq);

    return combine(left, right);
}
TextQuery::QueryResult OrQuery::eval(const TextQuery& tq, size_t lower, size_t upper) const {
    TextQuery::QueryResult left = lhs.eval(tq, lower, upper);
    TextQuery::QueryResult right = rhs.eval(tq, lower, upper);

    return combine(left, right);
}