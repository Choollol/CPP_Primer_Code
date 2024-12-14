#include "Basket.hpp"

double print_total(std::ostream& os, const Quote& item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << "\n# sold: " << n << "\nTotal due: " << ret << std::endl;
    return ret;
}

void Basket::add_item(const Quote& q) {
    items.insert(std::shared_ptr<Quote>(q.clone()));
}

void Basket::add_item(Quote&& q) {
    items.insert(std::shared_ptr<Quote>(std::move(q).clone()));
}

double Basket::total_receipt(std::ostream& os) const {
    double sum = 0.0;
    for (auto it = items.cbegin(); it != items.cend(); it = items.upper_bound(*it)) {
        sum += print_total(os, **it, items.count(*it));
    }
    os << "Total sale: " << sum << std::endl;
    return sum;
}