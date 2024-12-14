#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token {
   public:
    Token() : tok(INT), ival(0) {}

    Token(const Token& rhs) : tok(rhs.tok) { copyUnion(rhs); }
    Token& operator=(const Token&);

    Token(Token&& rhs) : tok(std::move(rhs.tok)) { copyUnion(std::move(rhs)); }
    Token& operator=(Token&&);

    ~Token();

    Token& operator=(int);
    Token& operator=(double);
    Token& operator=(char);
    Token& operator=(const std::string&);

   private:
    enum { INT,
           DOUBLE,
           CHAR,
           STR } tok;
    union {
        int ival;
        double dval;
        char cval;
        std::string sval;
    };

    void copyUnion(const Token& rhs);
    void copyUnion(Token&& rhs);
    void free();
};

#endif