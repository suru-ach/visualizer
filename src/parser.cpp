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
#include "Stmt.h"
#include "token.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

using std::shared_ptr;

vector<shared_ptr<Stmt<Object>>> Parser::parse() {

    try {
        while(!isAtEnd()) {
            statements.push_back(statement());
        }
        // expression();
    } catch(std::runtime_error err) {
        return {};
    }
    return statements;
}

shared_ptr<Stmt<Object>> Parser::statement() {
    if(match({PRINT})) return printStatement();
    
    return expressionStatement();
}

shared_ptr<Stmt<Object>> Parser::printStatement() {
    std::cout << "print statement called\n";
    shared_ptr<Expr<Object>> value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return shared_ptr<Stmt<Object>> (new Print<Object>{value});
}

shared_ptr<Stmt<Object>> Parser::expressionStatement() {
    shared_ptr<Expr<Object>> value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return shared_ptr<Stmt<Object>> (new Expression<Object>{value});
}

shared_ptr<Expr<Object>> Parser::expression() {
    std::cout << "expression called\n";
    return equality();
}

shared_ptr<Expr<Object>> Parser::equality() {
    std::cout << "equality called\n";
    shared_ptr<Expr<Object>>expr = comparision();
    while(match({ BANG_EQUAL, EQUAL_EQUAL })) {
        Token token = previous();
        shared_ptr<Expr<Object>>right = comparision();
        expr = shared_ptr<Expr<Object>> (new Binary<Object> { expr, token, right });
    }
    return expr;
}

shared_ptr<Expr<Object>> Parser::comparision() {
    std::cout << "equality called\n";
    shared_ptr<Expr<Object>>expr = term();
    while(match({ LESS_EQUAL, GREATER_EQUAL, GREATER, LESS })) {
        Token token = previous(); 
        shared_ptr<Expr<Object>>right = term();
        expr = shared_ptr<Expr<Object>> (new Binary<Object> { expr, token, right });
    }
    return expr;
}

shared_ptr<Expr<Object>> Parser::term() {
    std::cout << "term called\n";
    shared_ptr<Expr<Object>>expr = factor();
    while(match({ PLUS, MINUS })) {
        Token token = previous();
        shared_ptr<Expr<Object>>right = factor();
        expr = shared_ptr<Expr<Object>> (new Binary<Object> { expr, token, right });
    }
    return expr;
}

shared_ptr<Expr<Object>> Parser::factor() {
    std::cout << "factor called\n";
    shared_ptr<Expr<Object>>expr = unary();
    while(match({ STAR, SLASH })) {
        Token token = previous(); 
        shared_ptr<Expr<Object>>right = unary();
        expr = shared_ptr<Expr<Object>> (new Binary<Object> { expr, token, right });
    }
    return expr;
}

shared_ptr<Expr<Object>> Parser::unary() {
    std::cout << "unary called\n";
    if(match({ BANG, MINUS })) {
        Token token = previous();
        shared_ptr<Expr<Object>>right = primary();
        return shared_ptr<Expr<Object>> (new Unary<Object> {token, right});
    }
    return primary();
}

shared_ptr<Expr<Object>> Parser::primary() {
    std::cout << "primary called\n";
    if(match({ TokenType::FALSE })) {
        return shared_ptr<Expr<Object>> (new Literal<Object> { Object::make_bool_obj(false) });
    }
    if(match({ TokenType::TRUE })) {
        return shared_ptr<Expr<Object>> (new Literal<Object> { Object::make_bool_obj(true) });
    }
    if(match({ TokenType::NIL})) {
        return shared_ptr<Expr<Object>> (new Literal<Object> { Object::make_nil_obj() });
    }
    if(match({ TokenType::STRING })) {
        return shared_ptr<Expr<Object>> (new Literal<Object> { Object::make_str_obj(tokens[current - 1].literal.str) });
    }
    if(match({ TokenType::NUMBER })) {
        return shared_ptr<Expr<Object>> (new Literal<Object> { Object::make_num_obj(tokens[current - 1].literal.num) });
    }

    if(match({ TokenType::LEFT_PAREN })) {
        shared_ptr<Expr<Object>>expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression\n");
        return shared_ptr<Expr<Object>> (new Grouping<Object> {expr});
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

