/*
 *      main lox interface
 */

#ifndef LOX_H_
#define LOX_H_

#include <string>
#include <vector>

class Lox {
    public:
        static int runScript(int argc, char* argv[]);
        static void error(int line, std::string message);
        static std::vector<std::string> tokenStrings;
    private:
        static void runFile(const char* filename); 
        static void runPrompt();
        static void run(std::string source);
        static void report(int line, std::string where, std::string message);
        static bool hadError;

};

#endif // !LOX_H_
