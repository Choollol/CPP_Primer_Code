#include <memory>
#include <vector>

#include "Basket.hpp"
#include "Bulk_quote.hpp"
#include "Limit_quote.hpp"
#include "Quote.hpp"

int main() {
    Quote q("aaa", 20);
    Bulk_quote bq1("bbb", 10, 2, 0.3), bq2("ccc", 20, 4, 0.4), bq3;
    Basket basket;
    basket.add_item(q);
    basket.add_item(bq1);
    basket.add_item(bq2);
    basket.add_item(bq3);
    basket.total_receipt(std::cout);
    return 0;
}