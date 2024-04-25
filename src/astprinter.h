#ifndef AST_PRINTER_
#define AST_PRINTER_
#include "Expr.h"

class AstVisitor: public Visitor<std::string> {
    std::string visitLiteralExpr(Literal<std::string> *expr);
    std::string visitGroupingExpr(Grouping<std::string> *expr);
    std::string visitUnaryExpr(Unary<std::string> *expr);
    std::string visitBinaryExpr(Binary<std::string> *expr);
};

class AstTraverser: public Visitor<Object> {
    struct ObjectTree {
        ObjectTree(): res{""}, left{nullptr}, right{nullptr} {}

        ObjectTree(std::string str)
            : res{str}, left{nullptr}, right{nullptr} {}

        ObjectTree(std::string str, ObjectTree* right_)
            : res{str}, left{nullptr}, right{right_} {}

        ObjectTree(std::string str, ObjectTree* left_, ObjectTree* right_)
            : res{str}, left{left_}, right{right_} {}

        std::string res;
        ObjectTree* left;
        ObjectTree* right;
        void print(std::ofstream& ost);
    };
    Object visitLiteralExpr(Literal<Object> *expr);
    Object visitGroupingExpr(Grouping<Object> *expr);
    Object visitUnaryExpr(Unary<Object> *expr);
    Object visitBinaryExpr(Binary<Object> *expr);
};

#endif // !AST_PRINTER_
