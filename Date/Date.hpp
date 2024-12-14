#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>

class Date {
    friend std::ostream& operator<<(std::ostream&, const Date&);
    friend std::istream& operator>>(std::istream&, Date&);
    friend bool operator==(const Date&, const Date&);
    friend bool operator!=(const Date&, const Date&);

    friend bool operator<(const Date&, const Date&);
    friend bool operator>(const Date&, const Date&);
    friend bool operator<=(const Date&, const Date&);
    friend bool operator>=(const Date&, const Date&);

    friend Date operator+(const Date& lhs, const Date& rhs);
    friend Date operator-(const Date& lhs, const Date& rhs);

    friend Date operator+(const Date& lhs, int);
    friend Date operator-(const Date& lhs, int);

   public:
    Date(int = 1990, int = 1, int = 1);

    Date& operator+=(const Date&) &;
    Date& operator-=(const Date&) &;

    Date& operator+=(int) &;
    Date& operator-=(int) &;

    explicit operator bool() { return *this == Date(); }

   private:
    int year;
    int month;
    int day;

    void check_overflow();
    void check_underflow();
};

#endif