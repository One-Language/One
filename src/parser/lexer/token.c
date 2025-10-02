/**
 The One Programming Language

 File: parser/lexer/token.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "token.h"
#include "lexer.h"
#include "../../builtins/array.h"
#include "../../builtins/error.h"

#ifdef _ONE_TEST_
#define debug_token(format, args...)     \
	printf(YELLOW "Token Debug: " format \
				  "\n" RESET,            \
		 ##args);
// printf(YELLOW "Token Debug: " format " at %d on %s in %s" \
// 			  "\n" RESET,                                 \
// 	 ##args,                                              \
// 	 __LINE__,                                            \
// 	 "file",                                              \
// 	 __FUNCTION__);
// #define debug_token(format, args...)
#else
#define debug_token(format, args...)
#endif
// Global variable(s)
extern Lexer lexer;

/*
 * @function: token_is_alpha
 * @description: check a char is a-z or A-Z or _
 * @arguments: char c is a character input
 * @return: bool, true or false
 */
bool token_is_alpha(char c)
{
	debug_token("token_is_alpha");

	return (c >= 'a' && c <= 'z') ||
		 (c >= 'A' && c <= 'Z') ||
		 c == '_';
}

/*
 * @function: token_is_ident
 * @description: check a char is a-z or A-Z or _ or 0-9
 * @arguments: char c is a character input
 * @return: bool, true or false
 */
bool token_is_ident(char c)
{
	debug_token("token_is_ident");

	return (c >= 'a' && c <= 'z') ||
		 (c >= 'A' && c <= 'Z') ||
		 c == '_' ||
		 (c >= '0' && c <= '9');
}

/*
 * @function: token_is_digit
 * @description: check a char is 0-9 (Not - +)
 * @arguments: char c is a character input
 * @return: bool, true or false
 */
bool token_is_digit(char c)
{
	debug_token("token_is_digit");

	return c >= '0' && c <= '9';
}

/*
 * @function: token_is_end
 * @description: check a char is \0 EOF
 * @arguments: char c is a character input
 * @return: bool, true or false
 */
bool token_is_end()
{
	debug_token("token_is_end");

	return *lexer.current == '\0';
}

/*
 * @function: token_recede
 * @description: go to back char and return -1th character of current source code
 * @arguments: nothing
 * @return: char, if not exists will be ... (TODO)
 */
char token_recede()
{
	debug_token("token_recede");

	lexer.current--;
	// if (lexer.current[0] == '\n' || lexer.current[0] == '\r')
	// {
	// 	lexer.pos_end.line--;
	// 	// TODO: column
	// }
	// else {
	// 	lexer.pos_end.column--;
	// }
	lexer.pos_end.index--;
	return lexer.current[-1];
}

/*
 * @function: token_recede_next
 * @description: go to back character of current source code and return it
 * @arguments: nothing
 * @return: char, if not exists will be ... (TODO)
 */
char token_recede_next()
{
	debug_token("token_recede_next");

	token_recede();

	return lexer.current[0];
}

/*
 * @function: token_recede_next_next
 * @description: return current character of current source code and go to back
 * @arguments: nothing
 * @return: char, if not exists will be ... (TODO)
 */
char token_recede_next_next()
{
	debug_token("token_recede_next_next");

	token_recede();

	return lexer.current[1];
}

/*
 * @function: token_advance
 * @description: return current character and go to next position of the source code
 * @arguments: nothing
 * @return: char
 */
char token_advance()
{
	debug_token("token_advance");

	lexer.current++;
	// if (lexer.current[0] == '\n' || lexer.current[0] == '\r')
	// {
	// 	lexer.temp_column = lexer.pos_end.column;
	// 	lexer.pos_end.column = 0;
	// 	lexer.pos_end.line++;
	// }
	// else
	// {
	// 	lexer.pos_end.column++;
	// }
	lexer.pos_end.index++;
	return lexer.current[-1];
}

/*
 * @function: token_advance_next
 * @description: go to next position of the source code and return it
 * @arguments: nothing
 * @return: char
 */
char token_advance_next()
{
	debug_token("token_advance_next");

	token_advance();

	return lexer.current[0];
}

/*
 * @function: token_peek
 * @description: return current character of current source code
 * @arguments: nothing
 * @return: char
 */
char token_peek()
{
	debug_token("token_peek");

	return *lexer.current;
}

/*
 * @function: token_peek_next
 * @description: return next character of current source code
 * @arguments: nothing
 * @return: char
 */
char token_peek_next()
{
	debug_token("token_peek_next");

	if (token_is_end()) return '\0';
	return lexer.current[1];
}

/*
 * @function: token_peek_prev
 * @description: return prev character of current source code
 * @arguments: nothing
 * @return: char
 */
char token_peek_prev()
{
	debug_token("token_peek_prev");

	return lexer.current[-1]; // TODO: Review
}

/*
 * @function: token_match
 * @description: check current character of lexer is equal to `expected`, it's yes or no
 * @arguments: char expected
 * @return: bool, true or false
 */
bool token_match(char expected)
{
	debug_token("token_match");

	if (token_is_end()) return false;
	if (*lexer.current != expected) return false;
	lexer.current++;
	return true;
}

/*
 * @function: token_make
 * @description: create a pointer to Token struct without value
 * @arguments: TokenType
 * @return: A pointer to Token struct
 */
Token* token_make(TokenType type)
{
	debug_token("token_make");

	return token_make_value(type, NULL);
}

/*
 * @function: token_make_value
 * @description: create a pointer to Token struct with a value
 * @arguments: TokenType and a char* value
 * @return: A pointer to Token struct
 */
Token* token_make_value(TokenType type, char* value)
{
	debug_token("token_make_string");

	Token* t = malloc(sizeof(Token));
	t->value = value;
	t->type = type;
	t->length = (int)(lexer.current - lexer.start);

	t->pos = lexer.pos;
	t->pos.tokens = lexer.pos.tokens++;
	t->pos.column = lexer.pos.column > 0 ? lexer.pos.column - 1 : lexer.pos.column;

	t->pos_end.tokens = lexer.pos_end.tokens++;
	t->pos_end.index = lexer.pos_end.index;

	return t;
}

/*
 * @function: token_make_error
 * @description: create a pointer to a Error Token struct with a error message
 * @arguments: char* error message
 * @return: A pointer to Token struct
 */
Token* token_make_error(char* message)
{
	debug_token("token_make_error");

	return token_make_value(TOKEN_ERROR, message);
}

/*
 * @function: token_name
 * @description: convert TokenType to token name as char*
 * @arguments: TokenType type
 * @return: char*: token name
 */
char* token_name(TokenType type)
{
	//	debug_token("token_name");

	switch (type)
	{
		case TOKEN_EOF:
			return "EOF";
		case TOKEN_ERROR:
			return "Error";

		case TOKEN_VALUE_IDENTIFIER:
			return "value_identifier";

		case TOKEN_TYPE_I8:
			return "type_i8";
		case TOKEN_TYPE_I16:
			return "type_i16";
		case TOKEN_TYPE_I32:
			return "type_i32";
		case TOKEN_TYPE_I64:
			return "type_i64";
		case TOKEN_TYPE_I128:
			return "type_i128";

		case TOKEN_TYPE_U8:
			return "type_u8";
		case TOKEN_TYPE_U16:
			return "type_u16";
		case TOKEN_TYPE_U32:
			return "type_u32";
		case TOKEN_TYPE_U64:
			return "type_u64";
		case TOKEN_TYPE_U128:
			return "type_u128";

		case TOKEN_TYPE_F32:
			return "type_f32";
		case TOKEN_TYPE_F64:
			return "type_f64";

		case TOKEN_TYPE_BOOL:
			return "type_bool";
		case TOKEN_TYPE_STRING:
			return "type_string";
		case TOKEN_TYPE_CHAR:
			return "type_char";

		case TOKEN_VALUE_NUMBER:
			return "value_number";
		case TOKEN_VALUE_STRING:
			return "value_string";
		case TOKEN_VALUE_CHAR:
			return "value_char";

		case TOKEN_VALUE_BOOL_TRUE:
			return "value_true";
		case TOKEN_VALUE_BOOL_FALSE:
			return "value_false";

		case TOKEN_OPERATOR_NONE:
			return "NonOp";

		case TOKEN_OPERATOR_EQUAL_EQUAL:
			return "==";
		case TOKEN_OPERATOR_EQUAL:
			return "=";

		case TOKEN_OPERATOR_GREATER:
			return ">";
		case TOKEN_OPERATOR_GREATER_EQUAL:
			return "<=";
		case TOKEN_OPERATOR_LESS:
			return "<";
		case TOKEN_OPERATOR_LESS_EQUAL:
			return "<=";

		case TOKEN_OPERATOR_PLUS:
			return "+";
		case TOKEN_OPERATOR_PLUSPLUS:
			return "++";
		case TOKEN_OPERATOR_MINUS:
			return "-";
		case TOKEN_OPERATOR_MINUSMINUS:
			return "--";
		case TOKEN_OPERATOR_STAR:
			return "*";
		case TOKEN_OPERATOR_POWER:
			return "**";
		case TOKEN_OPERATOR_SLASH:
			return "/";
		case TOKEN_OPERATOR_SLASH_INT:
			return "//";

		case TOKEN_OPERATOR_REMAINDER:
			return "%";

		case TOKEN_OPERATOR_SHIFT_LEFT:
			return "<<";
		case TOKEN_OPERATOR_SHIFT_RIGHT:
			return ">>";

		case TOKEN_OPERATOR_AND:
			return "&&";
		case TOKEN_OPERATOR_BITWISE_AND:
			return "&";

		case TOKEN_OPERATOR_OR:
			return "||";
		case TOKEN_OPERATOR_BITWISE_OR:
			return "|";

		case TOKEN_OPERATOR_BITWISE_XOR:
			return "^";

		case TOKEN_OPERATOR_EQUAL_PLUS:
			return "+=";
		case TOKEN_OPERATOR_EQUAL_MINUS:
			return "-=";
		case TOKEN_OPERATOR_EQUAL_STAR:
			return "*=";
		case TOKEN_OPERATOR_EQUAL_POWER:
			return "**=";
		case TOKEN_OPERATOR_EQUAL_SLASH:
			return "/=";
		case TOKEN_OPERATOR_EQUAL_SLASH_INT:
			return "//=";
		case TOKEN_OPERATOR_EQUAL_SHIFT_LEFT:
			return "<<=";
		case TOKEN_OPERATOR_EQUAL_SHIFT_RIGHT:
			return ">>=";

		case TOKEN_OPERATOR_BRACKET_ROUND_LEFT:
			return "(";
		case TOKEN_OPERATOR_BRACKET_ROUND_RIGHT:
			return ")";

		case TOKEN_OPERATOR_BRACKET_SQUARE_LEFT:
			return "[";
		case TOKEN_OPERATOR_BRACKET_SQUARE_RIGHT:
			return "]";

		case TOKEN_OPERATOR_BRACKET_CURLY_LEFT:
			return "{";
		case TOKEN_OPERATOR_BRACKET_CURLY_RIGHT:
			return "}";

		case TOKEN_OPERATOR_COMMA:
			return ",";
		case TOKEN_OPERATOR_COLON:
			return ":";
		case TOKEN_OPERATOR_COLONCOLON:
			return "::";
		case TOKEN_OPERATOR_QUESTION:
			return "?";
		case TOKEN_OPERATOR_DOT:
			return ".";
		case TOKEN_OPERATOR_DOTDOT:
			return "..";
		case TOKEN_OPERATOR_DOTDOTDOT:
			return "...";

		case TOKEN_IF:
			return "IF";
		case TOKEN_ELSE:
			return "ELSE";

		//		case TOKEN_WHILE:
		//			return "WHILE";
		case TOKEN_MATCH:
			return "MATCH";
		case TOKEN_FOR:
			return "FOR";
			//		case TOKEN_DO:
			//			return "do";

		case TOKEN_RET:
			return "RET";
		case TOKEN_FN:
			return "FN";

			//	case TOKEN_CLASS:
			//	case TOKEN_THIS:
			//	case TOKEN_SUPER:

		case TOKEN_IS:
			return "is";
		case TOKEN_IN:
			return "in";
		case TOKEN_AS:
			return "as";
		case TOKEN_SWITCH:
			return "switch";
		case TOKEN_CASE:
			return "case";
		case TOKEN_BREAK:
			return "break";
		case TOKEN_CONTINUE:
			return "continue";
		case TOKEN_GO:
			return "go";

		case TOKEN_PRINT:
			return "_";
		case TOKEN_PRINTNL:
			return "__";
		case TOKEN_OPERATOR_BANG:
			return "!";
		case TOKEN_OPERATOR_EQUAL_BANG:
			return "!=";
		case TOKEN_PRINTDB:
			return "!_";
		case TOKEN_PRINTDBNL:
			return "!__";

		case TOKEN_PACKAGE:
			return "package";
		case TOKEN_IMPORT:
			return "import";

		case TOKEN_CONST:
			return "CONST";
		case TOKEN_FINAL:
			return "FINAL";
		case TOKEN_STATIC:
			return "static";

		case TOKEN_OPERATOR_EQUAL_REMAINDER:
			return "%=";
		case TOKEN_OPERATOR_EQUAL_AND:
			return "&&=";
		case TOKEN_OPERATOR_EQUAL_BITWISE_AND:
			return "&=";
		case TOKEN_OPERATOR_EQUAL_OR:
			return "||=";
		case TOKEN_OPERATOR_EQUAL_BITWISE_OR:
			return "|=";

		case TOKEN_OPERATOR_EQUAL_THREE:
			return "<=>";

		case TOKEN_ASSERT:
			return "assert";
		case TOKEN_STRUCT:
			return "struct";
		case TOKEN_TYPE:
			return "type";
		case TOKEN_INTERFACE:
			return "interface";

		case TOKEN_SKIP_WHITESPACE:
			return "skip_whitespace";
		case TOKEN_SKIP_WHITESPACE_LINE:
			return "skip_whitespace_line";
		case TOKEN_SKIP_COMMENT_SINGLE:
			return "skip_comment_inline";
		case TOKEN_SKIP_COMMENT_MULTI:
			return "skip_comment_multi";

		case TOKEN_SEMICOLON:
			return "SEMICOLON";
		default:
			return "UNKNOWN";
	}
}

/*
 * @function: token_utf8_string_length
 * @description: strlen while counting the character in utf8 mode not asci mode
 * @arguments: char* s
 * @return: size_t: number it will be >= 0
 */
size_t token_utf8_string_length(char* s)
{
	size_t len = 0;
	for (; *s; ++s)
		if ((*s & 0xC0) != 0x80) ++len;
	return len;
}

/*
 * @function: token_is_skip
 * @description: check this tokentype is whitespace, comment-inline and multiline comment etc.
 * @arguments: TokenType
 * @return: bool: 0 or 1, true or false
 */
bool token_is_skip(TokenType type)
{
	return (
		 type == TOKEN_SKIP_WHITESPACE ||
		 type == TOKEN_SKIP_WHITESPACE_LINE ||
		 type == TOKEN_SKIP_COMMENT_SINGLE ||
		 type == TOKEN_SKIP_COMMENT_MULTI);
}

/*
 * @function: tokenizer_string
 * @description: Create a array of tokens from a one program source-code char*
 * @inputs: char* of a One program source-code
 * @return: Array of Token
 */
Token** tokenizer_string(char* data)
{
	debug_token("tokenizer_string");
	debug_token("tokenizer_string: %s", data);

	lexer_init(data);

	Array tokens;
	array_init(&tokens);

	size_t i;
	Token* t;
	for (;;)
	{
		t = lexer_scan();
		// printf("==>%s\n", token_name(t->type));
		array_push(&tokens, t);
		// debug_lexer("parser_scan: print_token %s", token_name(t->type));
		if (t->type == TOKEN_ERROR)
		{
			printf("Error: %s\n", t->value);
			break;
		}
		else if (t->type == TOKEN_EOF)
			break;
	}

	debug_token("tokenizer_string: count of tokens is %d", tokens.count);
	debug_token("tokenizer_string: size of tokens is %d", tokens.size);

	// while (*data != '\0')
	// {
	// 	Token* t = token_make_value(TOKEN_VALUE_IDENTIFIER, (char*){data});
	// 	array_push(&tokens, t);
	// 	data++;
	// }

	return (Token**)tokens.data;
}
