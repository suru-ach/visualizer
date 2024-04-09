#include<string>
#include<vector>
#include<unordered_map>
#include "tokens.h"

using std::string;
using std::vector;
using std::unordered_map;


class Scanner {
	private:
		string source;
		vector<Token> tokens; 
		int start = 0;
		int current = 0;
		int line = 1;

	public:
		Scanner(string sourceFile) {
			source = sourceFile;
		}
		vector<Token> scanTokens();

		// scanToken method to scan each character and add it to respective list  
		void scanToken();
		void identifier();
		bool isAlpha(char c);
		bool isAlphaNumeric(char c);
		bool isDigit(char c);
		void number();
		char peekNext();
		char peek();
		bool match(char expected);
		// Helper: to check if at end
		bool isAtEnd();
		char advance();
		void addToken(TokenType type);
		void String();
};
