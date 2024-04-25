#ifndef PARSER_H_
#define PARSER_H_

#include "Expr.h"
#include <initializer_list>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

using std::vector;

class Parser {
    public:
        Parser(vector<Token> tokens_)
            :tokens{tokens_}, current{0} { }
        vector<Token> tokens;
        int current;
        Expr<Object> *parse();
        Expr<Object> *expression(); 
        Expr<Object> *equality(); 
        Expr<Object> *comparision();
        Expr<Object> *term();
        Expr<Object> *factor();
        Expr<Object> *unary();
        Expr<Object> *primary();
        bool match(std::initializer_list<TokenType> type);
        bool check(TokenType type);
        Token advance();
        bool isAtEnd();
        Token peek();
        Token previous();
        Token consume(TokenType type, std::string match);
        std::runtime_error error(Token token, std::string message);
};

#endif // !PARSER_H_
