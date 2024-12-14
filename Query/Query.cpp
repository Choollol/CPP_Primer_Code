#include "Query.hpp"

Query::Query(const std::string& s) : q(new WordQuery(s), DebugDelete()) { std::cout << "Query constructor" << std::endl; }