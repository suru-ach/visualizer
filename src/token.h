#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
using std::string;

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  TOKEN_EOF
};

class Object {
 public:
    typedef enum {
      Object_str,
      Object_num,
      Object_bool,
      Object_nil,
      Object_fun,
      Object_instance,
      Object_class,
    } Object_type;
    string str;
    double num;
    bool boolean;
    int* nil;
    Object_type type;
    string toString();
    static Object make_num_obj(double num);
    static Object make_str_obj(string str);
    static Object make_bool_obj(bool boolean);
    static Object make_nil_obj();
};

class Token {
    public:
        TokenType type;
        string lexeme;
        Object literal;
        int line;

        Token(TokenType type, string lexeme, Object literal, int line)
            : type(type), lexeme(lexeme), literal(literal), line(line)
        { }
        string toString();
};

#endif // !TOKEN_H_
