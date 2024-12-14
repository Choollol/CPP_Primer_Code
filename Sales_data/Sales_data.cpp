#include "Sales_data.hpp"
#include "Sales_data_Exceptions.hpp"

inline double Sales_data::avg_price() const {
    return units_sold ? revenue / units_sold : 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::istream& read(std::istream& is, Sales_data& item) {
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

std::istream& operator>>(std::istream& is, Sales_data& item) {
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is) {
        item.revenue = item.units_sold * price;
    }
    else {
        item = Sales_data();
    }
    return is;
}

Sales_data& Sales_data::operator=(const std::string& s) & {
    *this = Sales_data();
    bookNo = s;
    return *this;
}

Sales_data& Sales_data::operator+=(const Sales_data& rhs) & {
    if (bookNo == rhs.bookNo) {
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
    }
    else {
        throw isbn_mismatch("ISBN mismatch", bookNo, rhs.bookNo);
    }
    return *this;
}

/* Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data temp = lhs;
    temp += rhs;
    return temp;
} */

bool operator<(const Sales_data& lhs, const Sales_data& rhs) {
    return lhs.bookNo < rhs.bookNo || (lhs.bookNo == rhs.bookNo && lhs.avg_price() < rhs.avg_price());
}