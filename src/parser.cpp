/*
        expression     → equality ;
        equality       → comparison ( ( "!=" | "==" ) comparison )* ;
        comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
        term           → factor ( ( "-" | "+" ) factor )* ;
        factor         → unary ( ( "/" | "*" ) unary )* ;
        unary          → ( "!" | "-" ) unary
                            | primary ;
        primary        → NUMBER | STRING | "true" | "false" | "nil"
                            | "(" expression ")" ;
        
        program        → statement* EOF ;
        statement      → exprStmt
                            | printStmt ;
        exprStmt       → expression ";" ;
        printStmt      → "print" expression ";" ;       

        Expr<Object> expression(); 
        Expr<Object> equality(); 
        Expr<Object> comparision();
        Expr<Object> term();
        Expr<Object> factor();
        Expr<Object> unary();
        Expr<Object> primary();
        bool match(std::initializer_list<TokenType> type);
        bool check(TokenType type);
        bool advance();
        bool isAtEnd();
        bool peek();
        bool previous();
        Token consume(TokenType type, std::string match);
        std::runtime_error ParseError(Token token, std::string message);
*/

#include "parser.h"
#include <stdexcept>
#include <string>
#include <iostream>

Expr<Object>* Parser::parse() {
    try {
        return expression();
    } catch(std::runtime_error err) {
        return nullptr;
    }
}

Expr<Object>* Parser::expression() {
    return equality();
}

Expr<Object>* Parser::equality() {
    Expr<Object> *expr = comparision();
    while(match({ BANG_EQUAL, EQUAL_EQUAL })) {
        Token token = previous();
        Expr<Object> *right = comparision();
        expr = new Binary<Object> { expr, token, right };
    }
    return expr;
}

Expr<Object>* Parser::comparision() {
    Expr<Object> *expr = term();
    while(match({ LESS_EQUAL, GREATER_EQUAL, GREATER, LESS })) {
        Token token = previous(); 
        Expr<Object> *right = term();
        expr = new Binary<Object> { expr, token, right };
    }
    return expr;
}

Expr<Object>* Parser::term() {
    Expr<Object> *expr = factor();
    while(match({ PLUS, MINUS })) {
        Token token = previous();
        Expr<Object> *right = factor();
        expr = new Binary<Object> { expr, token, right };
    }
    return expr;
}

Expr<Object>* Parser::factor() {
    Expr<Object> *expr = unary();
    while(match({ STAR, SLASH })) {
        Token token = previous(); 
        Expr<Object> *right = unary();
        expr = new Binary<Object> { expr, token, right };
    }
    return expr;
}

Expr<Object>* Parser::unary() {
    if(match({ BANG, MINUS })) {
        Token token = previous();
        Expr<Object> *right = primary();
        return new Unary<Object> {token, right};
    }
    return primary();
}

Expr<Object>* Parser::primary() {
    if(match({ TokenType::FALSE })) {
        return new Literal<Object> { Object::make_bool_obj(false) };
    }
    if(match({ TokenType::TRUE })) {
        return new Literal<Object> { Object::make_bool_obj(true) };
    }
    if(match({ TokenType::NIL})) {
        return new Literal<Object> { Object::make_nil_obj() };
    }
    if(match({ TokenType::STRING })) {
        return new Literal<Object> { Object::make_str_obj(tokens[current - 1].literal.str) };
    }
    if(match({ TokenType::NUMBER })) {
        return new Literal<Object> { Object::make_num_obj(tokens[current - 1].literal.num) };
    }

    if(match({ TokenType::LEFT_PAREN })) {
        Expr<Object> *expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression\n");
        return new Grouping<Object> {expr};
    }

    throw error(peek(), "Expected expression.");
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for(auto type: types) {
        if(check(type)) {
            advance();
            return true;
        }
        return false;
    }
    return true;
}

bool Parser::check(TokenType type) {
    if(isAtEnd()) return false;
    return type == peek().type;
}

Token Parser::advance() {
    if(!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() {
    return peek().type == TOKEN_EOF;
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current-1];
}

Token Parser::consume(TokenType token, std::string message) {
    if(check(token)) return advance();

    throw error(peek(), message);     
}

std::runtime_error Parser::error(Token token, std::string message) {
    if(token.type == TOKEN_EOF)
        throw std::runtime_error(std::to_string(token.line) + " at end " + message);
    throw std::runtime_error(std::to_string(token.line) + " at " + token.lexeme);
}
