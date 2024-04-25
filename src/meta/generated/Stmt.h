#ifndef STMT_H_
#define STMT_H_
#include "token.h"

template<typename T>
class Stmt;

template<typename T>
class Expression;

template<typename T>
class Print;

template<typename T>
class Visitor {
	public:
		virtual T visitExpressionStmt(Expression<T>* Stmt) = 0;
		virtual T visitPrintStmt(Print<T>* Stmt) = 0;
};
template<typename T>
class Stmt {
	public:
		virtual T accept(Visitor<T> *visitor) = 0;
};

template<typename T>
class Expression : public Stmt<T> {
	public:
		Expression(Expr expression)
		:expression(expression) { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitExpressionStmt(this);
		}

		Expr expression;


};

template<typename T>
class Print : public Stmt<T> {
	public:
		Print(Expr expression)
		:expression(expression) { }

		T accept(Visitor<T> *visitor) {
			return visitor->visitPrintStmt(this);
		}

		Expr expression;


};

#endif //Stmt_H