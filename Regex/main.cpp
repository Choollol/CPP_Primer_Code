#include <iostream>
#include <regex>
#include <sstream>
#include <string>

void grammar_rule() {
    std::regex r("[[:alpha:]]*[^c]ei[[:alpha:]]*", std::regex::icase);
    std::string file("friend freind neighbor nieghbor albiet albeit being bieng receive recieve");
    constexpr size_t edge_len = 20;
    for (std::sregex_iterator it(file.begin(), file.end(), r), end; it != end; ++it) {
        size_t pref_size = it->prefix().length();
        size_t pref_index = pref_size > edge_len ? pref_size - edge_len : 0;
        std::cout << it->prefix().str().substr(pref_index) << "\n\t\t>>> " << it->str() << " <<<\n"
                  << it->suffix().str().substr(0, edge_len) << '\n';
    }
}

bool is_phone_valid(const std::smatch& sm) {
    if (sm[1].matched) {
        return sm[3].matched && sm[4] == " ";
    }
    else {
        return !sm[3].matched;
    }
}

void phone_nums() {
    std::regex r("(\\()?(\\d{3})(\\))?([-. ])?( *)(\\d{3})([-. ])?( *)(\\d{4})");
    std::string file("(510) 960-9887\n(123 456 7890\n(123)      123      1234");
    std::istringstream is(file);
    std::string s;
    while (std::getline(is, s)) {
        for (std::sregex_iterator it(s.begin(), s.end(), r), end; it != end; ++it) {
            std::string validity = is_phone_valid(*it) ? "valid" : "invalid";
            std::cout << it->str() << " is " << validity << std::endl;
        }
    }
}

void zip_codes() {
    std::regex r("(\\d{5})(-)?(\\d{4})?");
    std::string file("12345\n12345-1231\n123456789");
    std::istringstream is(file);
    std::string s;
    while (std::getline(is, s)) {
        for (std::sregex_iterator it(s.begin(), s.end(), r), end; it != end; ++it) {
            std::cout << it->str() << std::endl;
        }
    }
}

void reformat_phone_nums() {
    std::string file("morgan (201) 555-0168 862-555-0123\ndrew (973)555.0130\nlee (609) 555-0132 2015550175 800.555-0100");
    std::string pattern("(\\()?(\\d{3})(\\))?([-. ])?( *)(\\d{3})([-. ])?( *)(\\d{4})");
    std::regex r(pattern);
    std::string format("$2.$6.$9");
    std::istringstream is(file);
    std::string s;
    std::smatch sm;
    while (std::getline(is, s)) {
        //std::cout << std::regex_replace(s, r, format) << std::endl;
        /* if (std::regex_search(s, sm, r)) {
            std::cout << sm.prefix() << sm.format(format) << std::endl;
        } */
        if (std::regex_search(s, sm, r)) {
            std::cout << sm.prefix();
        }
        int skip = 1;
        for (std::sregex_iterator it(s.cbegin(), s.cend(), r), end; it != end; ++it) {
            if (skip) {
                --skip;
            }
            else {
                std::cout << it->format(format) << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void reformat_zip_code() {
    std::string file("12345\n12345-1231\n123456789");
    std::string pattern = "(\\d{5})(-)?(\\d{4})?";
    std::regex r(pattern);
    std::string format("$1-$3");
    std::istringstream is(file);
    std::string s;
    while (std::getline(is, s)) {
        for (std::sregex_iterator it(s.begin(), s.end(), r), end; it != end; ++it) {
            std::string zip;
            if ((*it)[3].matched) {
                zip = it->format(format);
            }
            else {
                zip = it->str();
            }
            std::cout << zip << std::endl;
        }
    }
}

int main() {
    reformat_zip_code();
    return 0;
}