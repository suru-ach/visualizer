#ifndef EXPR_H_
#define EXPR_H_

#include "token.h"
#include <string>

template <typename T>
class Expr;

template <typename T>
class Literal;

template <typename T>
class Grouping;

template <typename T>
class Unary;

template <typename T>
class Binary;

template <typename T>
class Visitor {
    public:
        virtual T visitLiteralExpr(Literal<T> *expr) = 0;
        virtual T visitGroupingExpr(Grouping<T> *expr) = 0;
        virtual T visitUnaryExpr(Unary<T> *expr) = 0;
        virtual T visitBinaryExpr(Binary<T> *expr) = 0;
};

template <typename T>
class Expr {
    public:
        virtual T accept(Visitor<T> *visitor) = 0;
};

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
