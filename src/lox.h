/*
 *      main lox interface
 */

#ifndef LOX_H_
#define LOX_H_

#include <string>

class Lox {
    public:
        static int runScript(int argc, char* argv[]);
        static void error(int line, std::string message);
    private:
        static void runFile(const char* filename); 
        static void runPrompt();
        static void run(std::string source);
        static void report(int line, std::string where, std::string message);
        static bool hadError;

};

#endif // !LOX_H_
