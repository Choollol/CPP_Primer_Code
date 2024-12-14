#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

void test_manips() {
    std::cout << std::boolalpha << true << ' ' << false << std::noboolalpha << std::endl;
    std::cout << std::showbase << std::hex << 20 << 900 << '\n'
              << std::oct << 20 << 900 << std::dec << std::noshowbase << std::endl;
    std::cout << std::showpoint << 9.0 << std::showpos << 20.9 << std::noshowpoint << std::noshowpos << std::endl;
    std::cout << std::left << std::setw(10) << "asd" << std::internal << std::setw(10) << "asd" << std::endl;
    std::cout << std::right << std::setfill('*') << std::setw(20) << "aa" << std::endl;
    std::cout << std::scientific << 123192387.1827382 << '\n'
              << std::flush << std::uppercase << std::hexfloat << 8329.12323 << std::defaultfloat << std::nouppercase << std::endl;
}

void sqrt2() {
    std::cout << std::setw(16) << "default format: " << std::setw(24) << 100 * sqrt(2.0) << '\n'
              << std::setw(16) << "scientific: " << std::setw(24) << std::scientific << 100 * sqrt(2.0) << '\n'
              << std::setw(16) << "fixed decimal: " << std::setw(24) << std::fixed << 100 * sqrt(2.0) << '\n'
              << std::setw(16) << "hexadecimal: " << std::setw(24) << std::hexfloat << 100 * sqrt(2.0) << '\n'
              << std::setw(16) << "use defaults: " << std::setw(24) << std::defaultfloat << 100 * sqrt(2.0)
              << "\n\n";
}

void unformatted() {
    std::ifstream in_file("in.txt");
    constexpr size_t sz = 12;
    char s[sz];
    int c;
    while (in_file.getline(s, sz, ' ')) {
        std::cout << s << ' ' << in_file.gcount() << std::endl;
    }
}

void line_locs() {
    std::fstream file("in.txt", std::fstream::ate | std::fstream::in | std::fstream::out);
    std::streampos end_pos = file.tellg();
    std::streampos offset = 0;
    file.seekg(0, std::fstream::beg);
    std::string line;
    while (file && file.tellg() != end_pos && std::getline(file, line)) {
        offset += line.size() + 1;
        std::cout << static_cast<char>(file.peek()) << ' ' << line << '\n';
        std::streampos read_pos = file.tellg();
        file.seekp(0, std::fstream::end);
        file << offset;
        if (read_pos != end_pos) {
            file << ' ';
        }
        file.seekg(read_pos);
    }
}

int main() {
    //test_manips();
    //sqrt2();
    //unformatted();
    line_locs();
    return 0;
}