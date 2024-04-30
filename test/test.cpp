#include <iostream>
#include <string>
#include <memory>
#include "../src/lox.h"

int main(int argc, char* argv[]) {
    Lox lox;    
    lox.runScript(argc, argv);
}

/*
int main(int argc, char* argv[]) {

    AstVisitor visitor;
    AstTraverser visitor2;
    
    Object test0  = Object::make_num_obj(1);
    Object test1  = Object::make_num_obj(2);
    Object test2  = Object::make_num_obj(3);

    Literal<Object> *literal = new Literal<Object> {test0};
    Literal<Object> *literal2 = new Literal<Object> {test1};;
    Literal<Object> *literal3 = new Literal<Object> {test2};;

    Expr<Object>* l1 = literal;
    Expr<Object>* l2 = literal2;
    Expr<Object>* l3 = literal3;

    Token tt2(TokenType::MINUS, "-", Object::make_str_obj(""), 1);
    Expr<Object> *expr2 = new Unary {tt2, l3};
    Expr<Object> *expr3 = new Grouping {expr2};

    Token tt3(TokenType::STAR, "*", Object::make_str_obj(""), 1);
    Expr<Object> *expr4 = new Binary {expr3, tt3, l1};

    Token tt(TokenType::PLUS, "+", Object::make_str_obj(""), 1);
    Expr<Object> *expr = new Binary(expr4, tt, l2);

    expr->accept(&visitor2);

    // expr->accept(&astVisitor);

}
*/

/*
int main(int argc, char* argv[]) {
    AstVisitor astVisitor;

    Literal<std::string> literal {"1"};
    Literal<std::string> literal2 {"2"};
    Literal<std::string> literal3 {"3"};

    Expr<std::string> *l1 = &literal;
    Expr<std::string> *l2 = &literal2;
    Expr<std::string> *l3 = &literal3;

    Token tt2(TokenType::MINUS, "-", Object::make_str_obj(""), 1);
    Expr<std::string> *expr2 = new Unary {tt2, l3};
    Expr<std::string> *expr3 = new Grouping {expr2};

    Token tt3(TokenType::STAR, "*", Object::make_str_obj(""), 1);
    Expr<std::string> *expr4 = new Binary {expr3, tt3, l1};

    Token tt(TokenType::PLUS, "+", Object::make_str_obj(""), 1);
    Expr<std::string> *expr = new Binary(expr4, tt, l2);

    std::cout << expr->accept(&astVisitor);

}
*/

/*
#include "../src/lox.h"
#include <gtest/gtest.h>


TEST(MyTestSuite, TestDefault) {
    EXPECT_EQ(1,1);
    EXPECT_EQ(1,1);
}

TEST(MySuite2, TestTwo) {
    EXPECT_FALSE(0);
    EXPECT_TRUE(1);
}
*/
