#ifndef SCANNER_H_
#define SCANNER_H_

#include "token.h"
#include <string>
#include <unordered_map>
#include <vector>
using std::string;
using std::vector;
using std::unordered_map;

class Scanner {
 private:
    string source;
    vector<Token> tokens;
    static unordered_map <string, TokenType> keywords;
    int start = 0;
    int current = 0;
    int line = 1;

    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, Object literal);
    bool match(char expected);
    char peek();
    void generateString();
    void generateNumber();
    bool isDigit(char c);
    char peekNext();
    void identifier();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);

 public:
    explicit Scanner(string source);
    vector<Token> scanTokens();
    bool isAtEnd();
};

#endif // !SCANNER_H_
