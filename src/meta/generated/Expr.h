#ifndef EXPR_H_
#define EXPR_H_
#include "token.h"

template<typename T>
class Expr;

template<typename T>
class Binary;

template<typename T>
class Grouping;

template<typename T>
class Literal;

template<typename T>
class Unary;

template<typename T>
class Visitor {
	public:
		virtual T visitBinaryExpr(Binary<T>* Expr) = 0;
		virtual T visitGroupingExpr(Grouping<T>* Expr) = 0;
		virtual T visitLiteralExpr(Literal<T>* Expr) = 0;
		virtual T visitUnaryExpr(Unary<T>* Expr) = 0;
};
template<typename T>
class Expr {
	public:
		virtual T accept(Visitor<T> *visitor) = 0;
};

template<typename T>
class Binary : public Expr<T> {
	public:
		Binary(Expr<T>* left,Token operator_,Expr<T>* right)
		:left(left),operator_(operator_),right(right) { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitBinaryExpr(this);
		}

		Expr<T>* left;
		Token operator_;
		Expr<T>* right;


};

template<typename T>
class Grouping : public Expr<T> {
	public:
		Grouping(Expr<T>* expression)
		:expression(expression) { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitGroupingExpr(this);
		}

		Expr<T>* expression;


};

template<typename T>
class Literal : public Expr<T> {
	public:
		Literal(Token value)
		:value(value) { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitLiteralExpr(this);
		}

		Token value;


};

template<typename T>
class Unary : public Expr<T> {
	public:
		Unary(Token operator_,Expr<T>* right)
		:operator_(operator_),right(right) { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitUnaryExpr(this);
		}

		Token operator_;
		Expr<T>* right;


};

#endif //Expr_H