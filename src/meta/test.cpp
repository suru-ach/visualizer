#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::ofstream;
using std::vector;
using std::endl;

class MetaPrinter {
    public:
        MetaPrinter(string baseName): baseName{baseName}
            {
                filename = baseName+".h"; 
                ost.open(filename, std::ios::out);
            }
        
        void print();
    private:
        void header();
        void declareTypes();
        void visitorDeclare();
        void baseDefine();
        void defineMethods();
        void footer();

        // helper
        string sub_constructor(string params);

        string filename;
        string baseName;
        ofstream ost;

        vector<string> methods {
            "Binary:Expr<T>* left, Token operator_, Expr<T>* right",
            "Grouping:Expr<T>* expression",
            "Literal:Token value",
            "Unary:Token operator_, Expr<T>* right"
        };
};

string MetaPrinter::sub_constructor(string str) {
    cout << str;
    return str;
}

void MetaPrinter::header() {
    string baseNameUpper = baseName;
    for(auto &ch: baseNameUpper) ch = toupper(ch);
    ost << "#ifndef "+baseNameUpper+"_H_\n#define "+baseNameUpper+"_H_\n#include \"token.h\"\n";
}

void MetaPrinter::declareTypes() {
    ost << "\ntemplate<typename T>\n"
        << "class " << baseName << ";\n";
    
    for(string method_base: methods) {
        int colon_at = method_base.find(':');
        string method = method_base.substr(0, colon_at);
        ost << "\ntemplate<typename T>\n"
            << "class " << method << ";\n";
    }
}

void MetaPrinter::visitorDeclare() {
    ost << "\ntemplate<typename T>\n"
        << "class Visitor {" << "\n\tpublic:\n";
    
    for(string method_base: methods) {
        int colon_at = method_base.find(':');
        string method = method_base.substr(0, colon_at);
        ost << "\t\tvirtual T visit" << method << baseName << "(" << method << "<T>* " << baseName << ") = 0;\n";
    }

    ost << "};\n";
}

void MetaPrinter::baseDefine() {
    ost << "template<typename T>\n" 
        << "class " << baseName << " {\n"
        << "\tpublic:\n"
        << "\t\tvirtual T accept(Visitor<T> *visitor) = 0;\n"
        << "};\n";
}

void MetaPrinter::defineMethods() {

    for(string method_base: methods) {

        int colon_at = method_base.find(':');
        string method = method_base.substr(0, colon_at);
        string params = method_base.substr(colon_at+1, method_base.size()-colon_at);

        ost << "\ntemplate<typename T>\n"
            << "class " << method << " : public " << baseName << "<T> {" << "\n\tpublic:\n"
            << "\t\t" << method << "(" << params << ")\n"
            << "\t\t:" << sub_constructor(params) << " { }\n\n"
            << "\t\tT accept(Visitor<T> *visitor) {\n"
            << "\t\t\treturn visitor->visit" << method << baseName << "(this);\n"
            << "\t\t}\n";

            // << "// split by ,\n";

        ost << "\t}\n";
    }
    
    ost << "};\n";
}

void MetaPrinter::footer() {
    ost << "\n#endif //" << baseName << "_H";
}

void MetaPrinter::print() {
    header();
    declareTypes();
    visitorDeclare();
    baseDefine();
    defineMethods();
    footer();
}

int main() {
    MetaPrinter mt {"Expr"};
    mt.print();
}

/*

template <typename T>
class Literal : public Expr<T> {
    public:
        Literal(T value_): value(value_) {}
        T accept(Visitor<T> *visitor) {
            return visitor->visitLiteralExpr(this);
        }

        T value;
};

template <typename T>
class Grouping : public Expr<T> {
    public:
        Grouping(Expr<T>* expression_)
            :expression(expression_) { }

        T accept(Visitor<T> *visitor) {
            return visitor->visitGroupingExpr(this);
        }

        Expr<T>* expression;
};

template <typename T>
class Binary : public Expr<T> {
    public:
        Binary(Expr<T>* right_, Token operation_, Expr<T>* left_)
            :left(left_), right(right_), operation(operation_) { }

        T accept(Visitor<T> *visitor) {
            return visitor->visitBinaryExpr(this);
        }

        Expr<T>* left;
        Token operation;
        Expr<T>* right;
};

template <typename T>
class Unary : public Expr<T> {
    public:
        Unary(Token operation_, Expr<T>* right_)
            :operation(operation_), right(right_) { }

        T accept(Visitor<T> *visitor) {
            return visitor->visitUnaryExpr(this);
        }
        Token operation;
        Expr<T>* right;
};

#endif // !EXPR_H_

----------------------------------------

#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#define path ../                // executable run from current directory

using std::string;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::pair;

class MetaPrinter {
    public:
        MetaPrinter() {}
        MetaPrinter(string baseName, vector<string> types, string ost_)
            :baseName(baseName), string_types(types), ost(ost_) {}

        //printer methods
        void appendHeaders(vector<string> &libs);
        void declareType( string baseName);
        void declareVirtualType(string baseName, string string);
        void declareVisitorClass(string baseName, string string);
        void defineType(string baseName, string string);
        static vector<pair<string, string>> generateParamPairs(string params);

    private:
        ofstream ost;
        string baseName;
        vector<string> string_types;
        vector<pair<string, string>> types;
};

// append headers
// declaring type
// declare Virtual type
// declare Visitor class
// defining type

int main() {
    string file_to_write{"Expr.cpp"};

    vector<string> methods = {
        "Binary : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal : Object value",
        "Unary : Token operator, Expr right"
    };

    // should I use string streams or just string manipulations 
    // going with string streams for now

    stringstream ss;
    MetaPrinter meta_printer("Expr", methods, file_to_write);
    meta_printer.appendHeaders(methods);
}

vector<pair<string ,string>> MetaPrinter::generateParamPairs(string params) {
    std::cout << params; 
    return {};
}

void MetaPrinter::appendHeaders(vector<string> &libs) {
    string baseNameUpper = baseName;
    for(auto &ch: baseNameUpper) ch = toupper(ch);
    ost << "#ifndef "+baseNameUpper+"_H_\n#define "+baseNameUpper+"_H_\n#include \"token.h\"\n";
}

// declaring type
void MetaPrinter::declareType(string baseName) {
    ost << "template <typename T>\nclass " + baseName + ";\n\n";
}

void declareVirtualType(ofstream &ost, string baseName, string type) {
    string writer_to_stream;

    int colon_pos = type.find(':');
    string className = type.substr(0, colon_pos);
    string methods = type.substr(colon_pos+1, type.size() - colon_pos - 1);
    vector<pair<string ,string>> generated_type = MetaPrinter::generateParamPairs(methods);

    for(auto &[type, params]: generated_type) {
        ost << "template <typename T>\nclass " + type + ";\n\n";
    }
}

*/
