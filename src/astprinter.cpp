#include "astprinter.h"
#include "iostream"

/*
std::string AstVisitor::visitLiteralExpr(Literal<std::string> *expr) {
    return expr->value;
}
std::string AstVisitor::visitGroupingExpr(Grouping<std::string> *expr) {
    return "(group " + expr->expression->accept(this) + ")";
}
std::string AstVisitor::visitUnaryExpr(Unary<std::string> *expr) {
    return "( " + expr->operation.lexeme + expr->right->accept(this) + " )";
}
std::string AstVisitor::visitBinaryExpr(Binary<std::string> *expr) {
    return "( " + expr->operation.lexeme
        + " "
        + expr->left->accept(this)
        + " "
        + expr->right->accept(this)
        + " )";
}
*/

std::string AstVisitor::visitLiteralExpr(Literal<std::string> *expr) {
    std::cout << ' ' << expr->value << ' ';
    // return std::string{std::string::make_nil_obj()};
    return "";
}

std::string AstVisitor::visitGroupingExpr(Grouping<std::string> *expr) {
    std::cout << " g( ";
    expr->expression->accept(this);
    std::cout << " ) ";
    // return std::string{std::string::make_nil_obj()};
    return "";
}

std::string AstVisitor::visitUnaryExpr(Unary<std::string> *expr) {
    std::cout << " u( " << expr->operation.lexeme;
    expr->right->accept(this);
    std::cout << " ) ";
    // return std::string{std::string::make_nil_obj()};
    return "";
}

std::string AstVisitor::visitBinaryExpr(Binary<std::string> *expr) {
    std::cout << " b(" << expr->operation.lexeme;
    expr->right->accept(this);
    expr->left->accept(this);
    std::cout << " ) "; 
    // return std::string{std::string::make_nil_obj()};
    return "";
}

Object AstTraverser::visitLiteralExpr(Literal<Object> *expr) {
    std::cout << ' ' << expr->value.toString() << ' ';
    return Object{Object::make_nil_obj()};
}

Object AstTraverser::visitGroupingExpr(Grouping<Object> *expr) {
    std::cout << " g( ";
    expr->expression->accept(this);
    std::cout << " ) ";
    return Object{Object::make_nil_obj()};
}

Object AstTraverser::visitUnaryExpr(Unary<Object> *expr) {
    std::cout << " u( " << expr->operation.lexeme;
    expr->right->accept(this);
    std::cout << " ) ";
    return Object{Object::make_nil_obj()};
}

Object AstTraverser::visitBinaryExpr(Binary<Object> *expr) {
    std::cout << " b(" << expr->operation.lexeme;
    expr->right->accept(this);
    expr->left->accept(this);
    std::cout << " ) "; 
    return Object{Object::make_nil_obj()};
}

/*
const tree3D = {
    
};
*/
