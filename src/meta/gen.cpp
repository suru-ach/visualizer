#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using std::string;
using std::ofstream;
using std::vector;
using std::cin, std::cerr;

class MetaPrinter {
    public:
        MetaPrinter(string baseName, vector<string> methods): baseName{baseName}, methods{methods}
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
        static string sub_define(string params);
        static vector<string> split_by_delimit(string method, char delim = ',');

        string filename;
        string baseName;
        vector<string> methods;
        ofstream ost;

        /*
        vector<string> methods {
            "Binary:Expr<T>* left,Token operator_,Expr<T>* right",
            "Grouping:Expr<T>* expression",
            "Literal:Token value",
            "Unary:Token operator_,Expr<T>* right"
        };
        */
};

// split using delimit ','

vector<string> MetaPrinter::split_by_delimit(string method, char delim){
    vector<string> strings_split;

    // split using delimit ',' or ' '
    int it = 0;
    while(it!=-1) {
        it = method.find(delim);
        if(it == -1 || it >= method.size()) {
            strings_split.push_back(method);
            break;
        }
        strings_split.push_back(method.substr(0, it));
        method = method.substr(it+1, method.size()-it-1);
    }
    return strings_split;
};

string MetaPrinter::sub_define(string str) {
    vector<string> strings_split = split_by_delimit(str, ',');

    string res = "";
    for(string dec: strings_split) {
        res += "\t\t" + dec + ";\n";
    }
    return res;
}

string MetaPrinter::sub_constructor(string str) {
    vector<string> strings_split = split_by_delimit(str, ',');

    string res = "";
    for(int i=0;i<strings_split.size();i++) {
        string dec = strings_split[i];
        const string method = split_by_delimit(dec, ' ')[1];
        res += method + "(" + method + ")";
        if(i != strings_split.size() - 1) res+=",";
    }
    return res;
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
            << "\t\t}\n\n"
            // define node values.
            << sub_define(params) << "\n\n"
            << "};\n";
    }
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

    string baseName, param;
    int n;
    try {
        vector<string> params;
        cin >> baseName;
        while(std::getline(cin, param)) {
            if(param.size()) params.push_back(param);
        }

        MetaPrinter mt {baseName, params};
        mt.print();

    } catch(...) {
        cerr << "Input format wrong";
    }
}

