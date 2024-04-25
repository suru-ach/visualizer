#include "lox.h" 
#include "scanner.h"
#include "astprinter.h"
#include "parser.h"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cin;
using std::cout;
using std::endl;

bool Lox::hadError = false;

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

    Parser* parser = new Parser(tokens);
    
    AstTraverser ast;
    Expr<Object>* astTree = parser->parse();
    astTree->accept(&ast);

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


