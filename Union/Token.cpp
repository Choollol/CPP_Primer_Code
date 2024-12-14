#include "Token.hpp"

Token& Token::operator=(const Token& rhs) {
    if (tok == STR) {
        if (rhs.tok == STR) {
            sval = rhs.sval;
        }
        else {
            free();
        }
    }
    else {
        copyUnion(rhs);
    }
    tok = rhs.tok;
    return *this;
}

Token& Token::operator=(Token&& rhs) {
    if (this != &rhs) {
        this->~Token();
        tok = std::move(rhs.tok);
        copyUnion(std::move(rhs));
    }
    return *this;
}

Token& Token::operator=(int i) {
    free();
    ival = i;
    tok = INT;
    return *this;
}

Token& Token::operator=(double d) {
    free();
    dval = d;
    tok = DOUBLE;
    return *this;
}

Token& Token::operator=(char c) {
    free();
    cval = c;
    tok = CHAR;
    return *this;
}

Token& Token::operator=(const std::string& s) {
    if (tok == STR) {
        sval = s;
    }
    else {
        new (&sval) std::string(s);
        tok = STR;
    }
    return *this;
}

Token::~Token() {
    free();
}

void Token::copyUnion(const Token& rhs) {
    switch (tok) {
        case INT:
            ival = rhs.ival;
            break;
        case DOUBLE:
            dval = rhs.dval;
            break;
        case CHAR:
            cval = rhs.cval;
            break;
        case STR:
            new (&sval) std::string(rhs.sval);
            break;
    }
}

void Token::copyUnion(Token&& rhs) {
    switch (tok) {
        case INT:
            ival = rhs.ival;
            break;
        case DOUBLE:
            dval = rhs.dval;
            break;
        case CHAR:
            cval = rhs.cval;
            break;
        case STR:
            sval = std::move(rhs.sval);
    }
}

inline void Token::free() {
    if (tok == STR) {
        sval.~basic_string();
    }
}