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
        bool match(vector(std::initializer_list<TokenType> type);
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
#include "lox.h"
#include "token.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

#define ALLOW_DEBUG 1

string Parser::traverser(Node* root) {
    if(!root) return "";
    string res = "{\"name\":\"" + root->token.lexeme + "\"";
    if(root->left && root->right) {
        res += ",\"children\": [";
        res += traverser(root->left) +  ","; 
        res += traverser(root->right);
        res += "]";
    }else if(root->left) {
		res += ",\"children\": [";
		res += traverser(root->left);
		res += "]";
	}else if(root->right) {
		res += ",\"children\": [";
		res += traverser(root->right);
		res += "]";
	}
    res += "}";
    return res;
}

void recursive_delete(Node* root) {
    if(!root) return;
    recursive_delete(root->left);
    recursive_delete(root->right);
    delete (root->left);
    delete (root->right);
}

Parser::~Parser() {
    for(auto stmt: statements) {
        recursive_delete(stmt);
    }    
}

vector<Node*> Parser::parse() {
    try {
        vector<Node*> statements;
        while(!isAtEnd()) {
            Node* expr = declaration();
            std::cout << traverser(expr);
            statements.push_back(expr);
        }
        //return expression();
    } catch(std::runtime_error error) {
        std::cerr << error.what() << std::endl;
    }
    return {};
}

Node* Parser::varDecl() {
    Token name = consume(IDENTIFIER, "Expect variable name.");
    Node* vardec = new Node(name);
    
    if(match(vector({ EQUAL }))) {
        vardec->left = expression();   
    }

    consume(SEMICOLON, "Expect ';' after value");
    return vardec;
}

Node* Parser::declaration() {
    if(match(vector({ VAR }))) return varDecl();

    return statement();
}
        
Node* Parser::statement() {
    if(match({ TokenType::PRINT })) return printStatement();
    if(match({ TokenType::IF })) return ifStmt();
    if(match({ TokenType::WHILE })) return whileStatement();
    if(match({ TokenType::LEFT_BRACE })) return blockStatement();
    if(match({ TokenType::SWITCH })) return switchStatement();
    if(match({ TokenType::BREAK })) return breakStatement();
    return expressionStatement();
}

/*
private Stmt whileStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'while'.");
    Expr condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after condition.");
    Stmt body = statement();

    return new Stmt.While(condition, body);
  } */

Node* Parser::switchStatement() {
    bool key = true;    
    consume(LEFT_PAREN, "Expected '(' after switch.");
    Node* condition = expression();
    consume(RIGHT_PAREN, "Expected ')' after condition.");
    consume(LEFT_BRACE, "Expected '{' after switch statement.");
    while(match({ DEFAULT, CASE })) {
        Token prev = previous();
        if(ALLOW_DEBUG) std::cout << prev.lexeme << " case\n";
        if(prev.type == DEFAULT) {
            consume(COLON, "Expected ':'");
        } else {
            primary();
            consume(COLON, "Expected ':'");
        }
        statement();
    }
    consume(RIGHT_BRACE, "Expected '}' after switch statement.");
    return condition;
}

Node* Parser::breakStatement() {
    consume(SEMICOLON, "Expected ';' after 'break'.");
    return nullptr;
}

Node* Parser::blockStatement() {
    Node* statement;
    while(!check(RIGHT_BRACE) && !isAtEnd()) {
        statement = declaration();
    } 
    consume(RIGHT_BRACE, "Expected '}' after switch statement.");
    return statement;
}

Node* Parser::whileStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'if'.");   
    Node* condition = expression();
    consume(RIGHT_PAREN, "Expect '(' after if condition.");   

    Node* body = statement();
    condition->left = body;
    return condition;
}

Node* Parser::ifStmt() {
    consume(LEFT_PAREN, "Expect '(' after 'if'.");   
    Node* condition = expression();
    consume(RIGHT_PAREN, "Expect '(' after if condition.");   

    Node* thenBranch = statement();
    condition->left = thenBranch;;
    Node* elseBranch = nullptr;
    if (match(vector({ELSE}))) {
        elseBranch = statement();
        condition->right = elseBranch;
    }
    return condition;
}

Node* Parser::printStatement() {
    Node* expr = expression(); 
    consume(SEMICOLON, "Expect ';' after value");
    return expr;
}

Node* Parser::expressionStatement() {
    Node* expr = expression(); 
    consume(SEMICOLON, "Expect ';' after value");
    return expr;
}

Node* Parser::assignment() {
    Node* expr = equality();

    if(match(vector({EQUAL}))) {
        Token equals = previous(); 
        Node* value = expression();
        expr->right = value;
    }

    return expr;
}

Node* Parser::expression() {
    return assignment();
}

Node* Parser::equality() {
    if(ALLOW_DEBUG) std::cout << "equality called\n";
    Node* expr = comparision();
    while(match(std::vector<TokenType>( BANG_EQUAL, EQUAL_EQUAL ))) {
        Token token = previous();
        Node* right = comparision();
        expr = new Node {token, right, expr}; 
    }
    return expr;
}


Node* Parser::comparision() {
    if(ALLOW_DEBUG) std::cout << "equality called\n";
    Node* expr = term();
    while(match(vector({ LESS_EQUAL, GREATER_EQUAL, GREATER, LESS }))) {
        Token token = previous();
        Node* right = term();
        expr = new Node {token, right, expr}; 
    }
    return expr;
}

Node* Parser::term() {
    if(ALLOW_DEBUG) std::cout << "term called\n";
    Node* expr = factor();
    while(match(vector({ MINUS, PLUS}))) {
        Token token = previous();
        Node* right = factor();
        expr = new Node {token, right, expr}; 
    }
    return expr;
}

Node* Parser::factor() {
    if(ALLOW_DEBUG) std::cout << "factor called\n";
    Node* expr = unary();
    while(match(vector({ SLASH, STAR}))) {
        Token token = previous(); 
        Node* right = unary();
        // Node* tmp = expr;
        expr = new Node {token, right, expr}; 
        if(ALLOW_DEBUG) std::cout << "right: " << expr->right->token.lexeme<< "\n";
        if(ALLOW_DEBUG) std::cout << "left: " << expr->left->token.lexeme << "\n";
        // expr = new Node {token, right, tmp};
    }
    return expr;
}

Node* Parser::unary() {
    if(ALLOW_DEBUG) std::cout << "unary called\n";
    if(match(vector({ BANG, MINUS }))) {
        Token token = previous();
        Node* right = primary();
        return new Node {token, right};
    }
    return primary();
}

Node* Parser::primary() {
    if(ALLOW_DEBUG) std::cout << "primary called\n";
    if(match(vector({ TokenType::FALSE }))) {
        return new Node{tokens[current-1]};
    }
    if(match(vector({ TokenType::TRUE }))) {
        return new Node{tokens[current-1]};
    }
    if(match(vector({ TokenType::NIL}))) {
        return new Node{tokens[current-1]};
    }
    if(match(vector({ TokenType::IDENTIFIER }))) {
        if(ALLOW_DEBUG) std::cout << tokens[current-1].lexeme << std::endl;
        return new Node{tokens[current-1]};
    }
    if(match(vector({ TokenType::STRING }))) {
        if(ALLOW_DEBUG) std::cout << tokens[current-1].lexeme << std::endl;
        return new Node{tokens[current-1]};
    }
    if(match(vector({ TokenType::NUMBER }))) {
        if(ALLOW_DEBUG) std::cout << tokens[current-1].lexeme << std::endl;
        return new Node{tokens[current-1]};
    }

    if(match(vector({ TokenType::LEFT_PAREN }))) {
        Node* expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression\n");
        return expr;
    }

    throw error(peek(), "Expected expression.");
}

bool Parser::match(std::vector<TokenType> types) {
    for(auto type: types) {
        if(check(type)) {
            advance();
            return true;
        }
    }
    return false;
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
    if(token.type != TOKEN_EOF)
        throw std::runtime_error(std::to_string(token.line) + " at end " + message);
    throw std::runtime_error(std::to_string(token.line) + " at " + token.lexeme);
}

