#include "lox.h" 
#include "scanner.h"
#include "parser.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

#define ALLOW_DEBUG 1

using std::string;
using std::cin;
using std::cout;
using std::endl;

bool Lox::hadError = false;

std::vector<std::string> Lox::tokenStrings {
    "LEFT_PAREN","RIGHT_PAREN","LEFT_BRACE","RIGHT_BRACE",
        "COMMA","DOT","MINUS","PLUS","SEMICOLON","SLASH","STAR",
        "BANG","BANG_EQUAL",
        "EQUAL","EQUAL_EQUAL",
        "GREATER","GREATER_EQUAL",
        "LESS","LESS_EQUAL",
        "IDENTIFIER","STRING","NUMBER",
        "AND","CLASS","ELSE","FALSE","FUN","FOR","IF","NIL","OR",
        "PRINT","RETURN","SUPER","THIS","TRUE","VAR","WHILE",
        "TOKEN_EOF","SWITCH","CASE"
};

int Lox::runScript (int argc, char *argv[])
{
    if(argc > 2) {
        std::cerr << "Usage: ./jlox [script]\n";
        return 1;
    } else if(argc == 2) {
        runFile(argv[1]); 
    } else {
        runPrompt();
    }
    return 0;
}

void Lox::runFile(const char* filename) {
    std::ifstream input{filename};
    std::stringstream ss;
    while(input >> ss.rdbuf()) { }
    run(ss.str());

}

void Lox::runPrompt() {
    string input;
    while(1) {
        cout << "> ";
        std::getline(cin, input);
        run(input);
        hadError = false;
    }
}

void Lox::run(string source) {
    Scanner* scanner = new Scanner(source);    
    vector<Token> tokens = scanner->scanTokens();

    for(auto token: tokens) {
        if(ALLOW_DEBUG) cout << std::setw(20) << token.lexeme << std::setw(20)<< tokenStrings[token.type] << endl;
    }

    Parser* parser = new Parser(tokens);
    Node* tree_root = parser->parse();
    cout << parser->traverser(tree_root) << endl;

    // AstTraverser ast;
    // cout << astTree.size()<<endl;
    // cout << astTree.size() << endl;
    // Expr<Object>* astTree = parser->parse();
    // astTree->accept(&ast);

    /*
    Parser* parser = new Parser(tokens);
    Expr<Object>* final = parser->parse();
    */

    // final->accept();

    /*
    cout << endl;
    for(auto token: tokens) {
        cout << token.toString() << endl;
    }
    */
}

void Lox::error(int line, std::string message) {
    report(line, "", message);
}

void Lox::report(int line, std::string where, std::string message) {
    cout << "[line " << line << "] Error" << where << ": " << message << endl;
    hadError = true;
}
