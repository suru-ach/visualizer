#ifndef STMT_H_
#define STMT_H_
#include "Expr.h"
#include "token.h"
#include <memory>

template<typename T>
class Stmt;

template<typename T>
class Expression;

template<typename T>
class Print;

template<typename T>
class VisitorStmt {
	public:
		virtual T visitExpressionStmt(shared_ptr<Expression<T>> Stmt) = 0;
		virtual T visitPrintStmt(shared_ptr<Print<T>> Stmt) = 0;
};
template<typename T>
class Stmt {
	public:
		virtual T accept(shared_ptr<VisitorStmt<T>> visitor) = 0;
};

template<typename T>
class Expression :
    public Stmt<T>,
    public std::enable_shared_from_this<Expression<T>>
{

	public:
		Expression(shared_ptr<Expr<T>> expression)
		:expression(expression) { }

		T accept(shared_ptr<VisitorStmt<T> >visitor) {
			return visitor->visitExpressionStmt(this->shared_from_this());
		}
		shared_ptr<Expr<T>> expression;
};

template<typename T>
class Print :
    public Stmt<T>,
    public std::enable_shared_from_this<Print<T>>
{
	public:
		Print(shared_ptr<Expr<T>> expression)
		:expression(expression) { }

		T accept(shared_ptr<VisitorStmt<T> >visitor) {
			return visitor->visitPrintStmt(this->shared_from_this());
		}
		shared_ptr<Expr<T>> expression;
};

#endif //Stmt_H
