#ifndef EXPR_H_
#define EXPR_H_
#include "token.h"
#include <memory>

using std::shared_ptr;

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
		virtual T visitBinaryExpr(shared_ptr<Binary<T>> Expr) = 0;
		virtual T visitGroupingExpr(shared_ptr<Grouping<T>> Expr) = 0;
		virtual T visitLiteralExpr(shared_ptr<Literal<T>> Expr) = 0;
		virtual T visitUnaryExpr(shared_ptr<Unary<T>> Expr) = 0;
};
template<typename T>
class Expr {
	public:
		virtual T accept(shared_ptr<Visitor<T>> visitor) = 0;
};

template<typename T>
class Binary :
    public Expr<T>,
    public std::enable_shared_from_this<Binary<T>>
{
	public:
		Binary(shared_ptr<Expr<T>> left,Token operator_,shared_ptr<Expr<T>> right)
		:left(left),operator_(operator_),right(right) { }

		T accept(shared_ptr<Visitor<T>> visitor) {
			return visitor->visitBinaryExpr(this->shared_from_this());
		}

		shared_ptr<Expr<T>> left;
		Token operator_;
		shared_ptr<Expr<T>> right;
};

template<typename T>
class Grouping : 
    public Expr<T>,
    public std::enable_shared_from_this<Grouping<T>>
{
	public:
		Grouping(shared_ptr<Expr<T>> expression)
		:expression(expression) { }

		T accept(shared_ptr<Visitor<T>> visitor) {
			return visitor->visitGroupingExpr(this->shared_from_this());
		}

		shared_ptr<Expr<T>> expression;


};

template<typename T>
class Literal :
    public Expr<T>,
    std::enable_shared_from_this<Literal<T>>
{
	public:
		Literal(Object value)
		:value(value) { }

		T accept(shared_ptr<Visitor<T>> visitor) {
			return visitor->visitLiteralExpr(this->shared_from_this());
		}

		Object value;


};

template<typename T>
class Unary :
    public Expr<T>,
    std::enable_shared_from_this<Unary<T>>
{
	public:
		Unary(Token operator_,shared_ptr<Expr<T>> right)
		:operator_(operator_),right(right) { }

		T accept(shared_ptr<Visitor<T>> visitor) {
			return visitor->visitUnaryExpr(this->shared_from_this());
		}

		Token operator_;
		shared_ptr<Expr<T>> right;
};

#endif //Expr_H
