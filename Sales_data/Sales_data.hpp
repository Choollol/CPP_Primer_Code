#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>

class Sales_data {
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::istream& read(std::istream&, Sales_data&);
    friend std::ostream& print(std::ostream&, const Sales_data&);

    friend std::istream& operator>>(std::istream&, Sales_data&);
    friend std::ostream& operator<<(std::ostream&, const Sales_data&);

    friend bool operator<(const Sales_data&, const Sales_data&);

    friend class std::hash<Sales_data>;

    friend int main();

   public:
    Sales_data() : Sales_data("", 0, 0.0) {}
    explicit Sales_data(const std::string& no) : Sales_data(no, 0, 0.0) {}
    Sales_data(const std::string& no, unsigned us, double price)
        : bookNo(no), units_sold(us), revenue(price * us) {}
    explicit Sales_data(std::istream& is) : Sales_data() { read(is, *this); }

    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);

    Sales_data& operator=(const std::string&) &;

    Sales_data& operator+=(const Sales_data&) &;

    operator std::string() { return bookNo; }
    operator double() { return revenue; }

    double avg_price() const;

   private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

namespace std {

template <>
struct hash<Sales_data> {
    size_t operator()(const Sales_data& data) const {
        return hash<std::string>()(data.bookNo) ^ hash<unsigned>()(data.units_sold) ^ hash<double>()(data.revenue);
    }
};

}  // namespace std

inline Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data temp = lhs;
    temp += rhs;
    return temp;
}

#endif