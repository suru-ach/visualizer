#include <string>
using namespace std;

enum TokenType {
	// Single-character tokens.
	LEFT_PAREN, 
	RIGHT_PAREN, 
	LEFT_BRACE, 
	RIGHT_BRACE,
	COMMA, 
	DOT, 
	MINUS, 
	PLUS, 
	SEMICOLON, 
	SLASH, 
	STAR,

	// One or two character tokens.
	BANG, 
	BANG_EQUAL,
	EQUAL, 
	EQUAL_EQUAL,
	GREATER, 
	GREATER_EQUAL,
	LESS, 
	LESS_EQUAL,

	// Literals.
	IDENTIFIER, 
	STRING, 
	NUMBER,

	// Keywords.
	AND, 
	CLASS, 
	ELSE, 
	FALSE, 
	FUN, 
	FOR, 
	IF, 
	NIL, 
	OR,
	PRINT, 
	RETURN, 
	SUPER, 
	THIS, 
	TRUE, 
	VAR, 
	WHILE,

	TOKEN_EOF
};

class Token {
	public:
		TokenType type;
		string lexeme;
		int line; 


		string toString();
		Token(TokenType type_val, string lexeme_val, int line_val) {
			type = type_val;
			lexeme = lexeme_val;
			line = line_val;
		}
};
