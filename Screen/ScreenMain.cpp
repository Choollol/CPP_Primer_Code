#include <iostream>

#include "Screen.hpp"

using get_cursor = char (Screen<10, 8>::*)() const;
using get_pos = char (Screen<10, 8>::*)(Screen<10, 8>::pos, Screen<10, 8>::pos) const;
using set_cursor = Screen<10, 8>& (Screen<10, 8>::*)(char);
using set_pos = Screen<10, 8>& (Screen<10, 8>::*)(Screen<10, 8>::pos, Screen<10, 8>::pos, char);

int main() {
    Screen<10, 8> screen('*');
    const std::string Screen<10, 8>::*p = Screen<10, 8>::data();
    std::cout << screen.*p;

    char (Screen<10, 8>::*pmf)() const = &Screen<10, 8>::get;

    get_cursor gc = &Screen<10, 8>::get;
    get_pos gp = &Screen<10, 8>::get;
    set_cursor sc = &Screen<10, 8>::set;
    set_pos sc = &Screen<10, 8>::set;
    return 0;
}