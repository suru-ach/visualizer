#ifndef PARSER_H_
#define PARSER_H_

#include "Expr.h"
#include "Stmt.h"
#include "token.h"
#include <cstddef>
#include <fstream>
#include <initializer_list>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

using std::vector;
using std::shared_ptr;

class Node {
public:
    Token token;
    Node* right;
    Node* left;
    Node(Token token, Node* left, Node* right): token{token}, right{right}, left{left} {}
    Node(Token token, Node* left): token{token}, right{nullptr}, left{left} {}
    Node(Token token): token{token}, right{nullptr}, left{nullptr} {}
};

class Parser {
    public:
        Parser(vector<Token> tokens_)
            :tokens{tokens_}, current{0} { }
        ~Parser();
        vector<Token> tokens;
        int current;
        Node* parse();
        vector<Node*> statements;
        //shared_ptr<Stmt<Object>> statement();
        //shared_ptr<Stmt<Object>> varDecl();
        //shared_ptr<Stmt<Object>> declaration();
        //shared_ptr<Stmt<Object>> printStatement();
        //shared_ptr<Stmt<Object>> expressionStatement();
        Node* expression(); 
        Node* equality(); 
        Node* comparision();
        Node* term();
        Node* factor();
        Node* unary();
        Node* primary();
        bool match(std::initializer_list<TokenType> type);
        bool check(TokenType type);
        Token advance();
        bool isAtEnd();
        Token peek();
        Token previous();
        Token consume(TokenType type, std::string match);
        std::runtime_error error(Token token, std::string message);
        std::string traverser(Node* root);
};

/*
class Parser {
    public:
        Parser(vector<Token> tokens_)
            :tokens{tokens_}, current{0} { }
        ~Parser();
        vector<Token> tokens;
        int current;
        vector<shared_ptr<Stmt<Object>>> parse();
        vector<shared_ptr<Stmt<Object>>> statements;
        shared_ptr<Stmt<Object>> statement();
        shared_ptr<Stmt<Object>> varDecl();
        shared_ptr<Stmt<Object>> declaration();
        shared_ptr<Stmt<Object>> printStatement();
        shared_ptr<Stmt<Object>> expressionStatement();
        shared_ptr<Expr<Object>> expression(); 
        shared_ptr<Expr<Object>> equality(); 
        shared_ptr<Expr<Object>> comparision();
        shared_ptr<Expr<Object>> term();
        shared_ptr<Expr<Object>> factor();
        shared_ptr<Expr<Object>> unary();
        shared_ptr<Expr<Object>> primary();
        bool match(std::initializer_list<TokenType> type);
        bool check(TokenType type);
        Token advance();
        bool isAtEnd();
        Token peek();
        Token previous();
        Token consume(TokenType type, std::string match);
        std::runtime_error error(Token token, std::string message);
};
*/

#endif // !PARSER_H_
