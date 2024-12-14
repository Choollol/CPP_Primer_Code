#include "AndQuery.hpp"
#include "NotQuery.hpp"
#include "OrQuery.hpp"
#include "Query.hpp"

void dynamic_cast_test() {
    Query q1(""), q2("");
    Query_base* qbp = new AndQuery(q1, q2);
    /* delete qbp;
    qbp = new OrQuery(q1, q2);
    delete qbp;
    qbp = new NotQuery(q1); */
    if (AndQuery* aqp = dynamic_cast<AndQuery*>(qbp)) {
        std::cout << ">>> Query_base* cast to AndQuery* <<<" << std::endl;
    }
    else {
        std::cout << ">>> cast failed <<<" << std::endl;
    }
    Query_base* qbp1 = new AndQuery(q1, q2);
    Query_base* qbp2 = new AndQuery(q1, q2);
    if (typeid(*qbp1) == typeid(*qbp2)) {
        std::cout << ">>> qbp1 and qbp2 equal <<<" << std::endl;
    }
    delete qbp1;
    qbp1 = new OrQuery(q1, q2);
    if (typeid(*qbp1) == typeid(AndQuery)) {
        std::cout << ">>> qbp1 points to AndQuery <<<" << std::endl;
    }
    else {
        std::cout << ">>> qbp1 points to type not AndQyery <<<" << std::endl;
    }

    delete qbp;
}

int main() {
    std::ifstream in_file("in.txt");
    TextQuery tq(in_file);
    Query q1 = Query("fiery") & Query("bird") | Query("wind");
    TextQuery::QueryResult qr = q1.eval(tq, 4, 5);
    qr.print(std::cout);
    //dynamic_cast_test();
    return 0;
}