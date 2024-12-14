#include "Date.hpp"

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {
    check_overflow();
    check_underflow();
}

void Date::check_overflow() {
    if (day > 30) {
        month += day / 30;
        day %= 30;
    }
    if (month > 12) {
        year += month / 12;
        month %= 12;
    }
}
void Date::check_underflow() {
    if (day < 1) {
        --month;
        day += 30;
    }
    if (month < 1) {
        --year;
        month += 12;
    }
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << d.month << "/" << d.day << "/" << d.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& d) {
    is >> d.year >> d.month >> d.day;
    if (!is) {
        d = Date();
    }
    return is;
}

Date& Date::operator+=(const Date& rhs) & {
    year += rhs.year;
    month += rhs.month;
    check_overflow();
    return *this;
}

Date operator+(const Date& lhs, const Date& rhs) {
    Date temp = lhs;
    temp += rhs;
    return temp;
}

Date& Date::operator-=(const Date& rhs) & {
    year -= rhs.year;
    month -= rhs.month;
    day -= rhs.day;
    check_underflow();
    return *this;
}

Date operator-(const Date& lhs, const Date& rhs) {
    Date temp = lhs;
    temp -= rhs;
    return temp;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}
bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return lhs.year < rhs.year || (lhs.year == rhs.year && lhs.month < rhs.month) || (lhs.month == rhs.month && lhs.day < rhs.day);
}
bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return !(lhs > rhs);
}
bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

Date& Date::operator+=(int d) & {
    day += d;
    check_overflow();
    return *this;
}

Date operator+(const Date& lhs, int d) {
    Date temp = lhs;
    temp += d;
    return temp;
}

Date& Date::operator-=(int d) & {
    day -= d;
    check_underflow();
    return *this;
}

Date operator-(const Date& lhs, int d) {
    Date temp = lhs;
    temp -= d;
    return temp;
}