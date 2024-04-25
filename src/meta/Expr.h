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
		Binary(Expr<T>* left, Token operator_, Expr<T>* right)
		:Expr<T>* left, Token operator_, Expr<T>* right { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitBinaryExpr(this);
		}
// split by ,	}

template<typename T>
class Grouping : public Expr<T> {
	public:
		Grouping(Expr<T>* expression)
		:Expr<T>* expression { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitGroupingExpr(this);
		}
// split by ,	}

template<typename T>
class Literal : public Expr<T> {
	public:
		Literal(Token value)
		:Token value { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitLiteralExpr(this);
		}
// split by ,	}

template<typename T>
class Unary : public Expr<T> {
	public:
		Unary(Token operator_, Expr<T>* right)
		:Token operator_, Expr<T>* right { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitUnaryExpr(this);
		}
// split by ,	}
};

#endif //Expr_H