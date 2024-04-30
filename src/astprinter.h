#ifndef AST_PRINTER_
#define AST_PRINTER_
#include "Expr.h"
#include <memory>

/*
class AstVisitor: public Visitor<std::string> {
    std::string visitLiteralExpr(Literal<std::string> *expr);
    std::string visitGroupingExpr(Grouping<std::string> *expr);
    std::string visitUnaryExpr(Unary<std::string> *expr);
    std::string visitBinaryExpr(Binary<std::string> *expr);
};

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
    */
class AstTraverser:
    public Visitor<Object>,
    std::enable_shared_from_this<AstTraverser>
{
    Object visitLiteralExpr(shared_ptr<Literal<Object>> expr);
    Object visitGroupingExpr(shared_ptr<Grouping<Object>> expr);
    Object visitUnaryExpr(shared_ptr<Unary<Object>> expr);
    Object visitBinaryExpr(shared_ptr<Binary<Object>> expr);
};

#endif // !AST_PRINTER_
