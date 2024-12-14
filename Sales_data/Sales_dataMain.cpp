#include <algorithm>
#include <functional>
#include <numeric>
#include <set>
#include <tuple>

#include "../../test_util.hpp"
#include "Sales_data.hpp"
#include "Sales_data_Exceptions.hpp"

bool compareIsbn(const Sales_data& sd1, const Sales_data& sd2) {
    return sd1.isbn() < sd2.isbn();
}

using match_t = std::tuple<size_t, std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator>;
using match_pair_t = std::pair<size_t, std::pair<std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator>>;

struct Match {
    size_t index;
    std::vector<Sales_data>::const_iterator begin;
    std::vector<Sales_data>::const_iterator end;
};

/* std::vector<match_t> findBook(const std::vector<std::vector<Sales_data>>& files, const std::string& book) {
    std::vector<match_t> matches;
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto it_pair = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);

        if (it_pair.first != it_pair.second) {
            matches.push_back(std::make_tuple(it - files.cbegin(), it_pair.first, it_pair.second));
        }
    }
    return matches;
}

std::vector<match_pair_t> findBook(const std::vector<std::vector<Sales_data>>& files, const std::string& book) {
    std::vector<match_pair_t> matches;
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto it_pair = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);

        if (it_pair.first != it_pair.second) {
            matches.push_back(std::make_pair(it - files.cbegin(), std::make_pair(it_pair.first, it_pair.second)));
        }
    }
    return matches;
}*/

std::vector<Match> findBook(const std::vector<std::vector<Sales_data>>& files, const std::string& book) {
    std::vector<Match> matches;
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto it_pair = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);

        if (it_pair.first != it_pair.second) {
            matches.push_back(Match{static_cast<size_t>(it - files.cbegin()), it_pair.first, it_pair.second});
        }
    }
    return matches;
}

void reportResults(std::istream& is, std::ostream& os, const std::vector<std::vector<Sales_data>>& files) {
    std::string book;
    while (is >> book && book != "q") {
        auto matches = findBook(files, book);
        if (matches.empty()) {
            os << book << " not found" << std::endl;
        }
        else {
            for (auto it = matches.cbegin(); it != matches.cend(); ++it) {
                //os << "Store " << std::get<0>(*it) << " sales: " << std::accumulate(std::get<1>(*it), std::get<2>(*it), Sales_data(book)) << std::endl;
                //os << "Store " << it->first << " sales: " << std::accumulate(it->second.first, it->second.second, Sales_data(book)) << std::endl;
                os << "Store " << it->index << " sales: " << std::accumulate(it->begin, it->end, Sales_data(book)) << std::endl;
            }
        }
    }
}

using avg_price_ptr = double (Sales_data::*)() const;

void first_greater(const std::vector<Sales_data>& vec, double target) {
    std::vector<Sales_data>::const_iterator it =
        std::find_if(vec.cbegin(), vec.cend(),
                     std::bind([target](const Sales_data& item, double d2) { return item.avg_price() >= d2; }, std::placeholders::_1, target));
    if (it != vec.cend()) {
        std::cout << *it << std::endl;
    }
    else {
        std::cout << "not found" << std::endl;
    }
}

int main() {
    /* std::vector<std::vector<Sales_data>> files{{Sales_data("a", 1, 1), Sales_data("b", 2, 2), Sales_data("c", 3, 3)},
                                               {Sales_data("aa", 1, 2), Sales_data("bb", 2, 3), Sales_data("c", 8, 9)},
                                               {Sales_data("aaa", 4, 5), Sales_data("b", 6, 7)}};
    reportResults(std::cin, std::cout, files);
    Sales_data item1("aa", 1, 1), item2("ab", 1, 1);
    //item1 += item2;
    try {
        item1 += item2;
    }
    catch (const isbn_mismatch& e) {
        std::cerr << e.what() << " on " << e.left << " and " << e.right << std::endl;
    }

    const std::string Sales_data::*pBookNo;
    avg_price_ptr p = &Sales_data::avg_price;*/

    std::vector<Sales_data> vec{Sales_data("aa", 10, 9), Sales_data("ab", 20, 10), Sales_data("cc", 30, 12)};

    first_greater(vec, 10);

    return 0;
}