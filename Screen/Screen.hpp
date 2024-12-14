#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>

/* template <std::string::size_type width, std::string::size_type height>
std::ostream& operator<<(std::ostream&, const Screen<width, height>&);

template <std::string::size_type width, std::string::size_type height>
std::istream& operator>>(std::istream&, const Screen<width, height>&); */

template <std::string::size_type width, std::string::size_type height>
class Screen {
    friend std::ostream& operator<<(std::ostream& os, const Screen& screen) {
        for (pos i = 0; i < width * height; ++i) {
            os << screen.contents[i];
            if ((i + 1) % width == 0) {
                os << '\n';
            }
        }
        os << std::endl;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, const Screen& screen) {
        char c;
        for (pos i = 0; i < width; ++i) {
            for (pos j = 0; j < height; ++j) {
                while (!isprint(c = is.get()))
                    ;
                screen.set(j, i, c);
            }
        }
        return is;
    }

    friend int main();

   public:
    static const std::string Screen::*data() { return &Screen::contents; }

    using pos = std::string::size_type;

    explicit Screen(char c = ' ') : contents(width * height, c) {}

    char get() const { return contents[cursor]; }
    char get(pos y, pos x) const { return contents[width * y + x]; }

    Screen& set(char c) {
        contents[cursor] = c;
        return *this;
    }
    Screen& set(pos y, pos x, char c) {
        contents[width * y + x] = c;
        return *this;
    }

    Screen& move(pos y, pos x) {
        cursor = width * y + x;
        return *this;
    }

   private:
    pos cursor = 0;
    std::string contents;
};

/* template <std::string::size_type width, std::string::size_type height>
std::ostream& operator<<(std::ostream& os, const Screen<width, height>& screen) {
    for (typename Screen<width, height>::pos i = 0; i < width * height; ++i) {
        os << screen.contents[i];
        if ((i + 1) % width == 0) {
            os << '\n';
        }
    }
    os << std::endl;
    return os;
} 

template <std::string::size_type width, std::string::size_type height>
std::istream& operator>>(std::istream& is, const Screen<width, height>& screen) {
    char c;
    for (typename Screen<width, height>::pos i = 0; i < width; ++i) {
        for (typename Screen<width, height>::pos j = 0; j < height; ++j) {
            while (!isprint(c = is.get()))
                ;
            screen.set(j, i, c);
        }
    }
    return is;
} */

#endif