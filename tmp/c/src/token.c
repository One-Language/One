/**
 File: token.c
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "lexer.h"
#include "one.h"

typedef struct lexer Lexer;

void token_init(Lexer *lex)
{
#ifdef DEBUG
	printf("[token_init]\n");
#endif
}

bool token_is_space(char c)
{
	if (c == ' ')
		return true;
	else if (c == '\t')
		return true;
	else if (c == '\n')
		return true;
	else if (c == '\r')
		return true;
	return false;
}

bool token_is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	else if (c >= 'A' && c <= 'Z')
		return true;
	else if (c == '_')
		return true;
	return false;
}

bool token_is_number(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

bool token_is_digit(char c)
{
	if (token_is_number(c) == true)
		return true;
	else if (c == '.')
		return true;
	return false;
}

bool token_is_ident(char c)
{
	if (token_is_alpha(c) == true)
	{
		return true;
	}
	else if (token_is_number(c) == true)
	{
		return true;
	}
	return false;
}

// Token* tk = NULL;

// Token* token_get(Lexer* lex)
// {
//   if(tk == NULL) return NULL;
//   return tk;
// }

// Token* token_getnext(Lexer* lex)
// {
//   tk = token_next(lex);
//   return tk;
// }

Token *token_next(Lexer *lex)
{
	// #ifdef DEBUG
	//   printf("[token_next] %c\n", *lex->s);
	// #endif

	Token *t = malloc(sizeof(Token));

	if (*lex->s == '\0')
	{
		t->type = tok_eof;
		return t;
	}

	while (token_is_space(*lex->s) == true)
	{
		token_nextchar(lex);
	}

	// Get identifier
	if (token_is_alpha(*lex->s) == true)
	{
		t->vstring = sdsnew((char[]){*lex->s});
		token_nextchar(lex); // eat first char

		while (token_is_ident(*lex->s) == true)
		{
			t->vstring = sdscat(t->vstring, (char[]){*lex->s});
			token_nextchar(lex);
		}

		t->vstring = sdscat(t->vstring,
			 (char[]){'\0'}); // put EOF for string!

#ifdef DEBUG
		// printf("[string] %s\n", t->vstring);
#endif

		// sdsfree(t->vstring);
		// printf("==>%s\n", t->vstring);

		if (strcmp(t->vstring, "def") == 0)
		{
			t->type = tok_def;
			return t;
		}
		else if (strcmp(t->vstring, "extern") == 0)
		{
			t->type = tok_extern;
			return t;
		}
		else if (strcmp(t->vstring, "ret") == 0)
		{
			t->type = tok_ret;
			return t;
		}

		else if (strcmp(t->vstring, "i8") == 0)
		{
			t->type = tok_type_i32;
			return t;
		}
		else if (strcmp(t->vstring, "i16") == 0)
		{
			t->type = tok_type_i32;
			return t;
		}
		else if (strcmp(t->vstring, "i32") == 0)
		{
			t->type = tok_type_i32;
			return t;
		}

		else if (strcmp(t->vstring, "u8") == 0)
		{
			t->type = tok_type_i32;
			return t;
		}
		else if (strcmp(t->vstring, "u16") == 0)
		{
			t->type = tok_type_i32;
			return t;
		}
		else if (strcmp(t->vstring, "u32") == 0)
		{
			t->type = tok_type_i32;
			return t;
		}

		else if (strcmp(t->vstring, "f32") == 0)
		{
			t->type = tok_type_f32;
			return t;
		}
		else if (strcmp(t->vstring, "f64") == 0)
		{
			t->type = tok_type_f32;
			return t;
		}

		else if (strcmp(t->vstring, "bool") == 0)
		{
			t->type = tok_type_bool;
			return t;
		}
		else if (strcmp(t->vstring, "char") == 0)
		{
			t->type = tok_type_char;
			return t;
		}
		else if (strcmp(t->vstring, "string") == 0)
		{
			t->type = tok_type_string;
			return t;
		}

		t->type = tok_identifier;
		return t;
	}

	// Get number
	if (token_is_digit(*lex->s) == true)
	{
		sds NumStr = sdsnew((char[]){*lex->s});
		token_nextchar(lex); // eat first digit

		while (token_is_digit(*lex->s) == true)
		{
			NumStr = sdscat(NumStr, (char[]){*lex->s});
			token_nextchar(lex); // eat next digits...
		}

		t->type = tok_number;
		t->vint = strtod(NumStr, 0);

		sdsfree(NumStr);
		return t;
	}

	// operators
	if (*lex->s == '{')
	{
		token_nextchar(lex);
		t->type = '{';
		return t;
	}
	else if (*lex->s == '}')
	{
		token_nextchar(lex);
		t->type = '}';
		return t;
	}
	else if (*lex->s == '(')
	{
		token_nextchar(lex);
		t->type = '(';
		return t;
	}
	else if (*lex->s == ')')
	{
		token_nextchar(lex);
		t->type = ')';
		return t;
	}
	else if (*lex->s == '=')
	{
		token_nextchar(lex);
		t->type = '=';
		return t;
	}

	// Skip less than a single-line comments
	if (*lex->s == '#')
	{
		do {
			token_nextchar(lex); // eat '#' at first and other chars at next...
		} while (*lex->s != EOF && *lex->s != '\0' && *lex->s != '\n' &&
			 *lex->s != '\r' && *lex->s != '#');

		if (*lex->s != EOF && *lex->s != '\0')
		{
			return token_next(lex);
		}
		else
		{
			t->type = tok_eof;
			return t;
		}
	}

	// '/' operator
	if (*lex->s == '/')
	{
		token_nextchar(lex); // eat '/'

		// Skip single-line comments
		if (*lex->s == '/')
		{
			do {
				token_nextchar(lex); // eat '/' at first and other chars at next...
			} while (*lex->s != EOF && *lex->s != '\0' && *lex->s != '\n' &&
				 *lex->s != '\r');

			if (*lex->s != EOF && *lex->s != '\0')
			{
				return token_next(lex);
			}
			else
			{
				t->type = tok_eof;
				return t;
			}
		}

		// Skip multi-line comments
		else if (*lex->s == '*')
		{
			token_nextchar(lex); // eat '*'

			while (true)
			{
				char c1 = *lex->s;
				if (c1 == '\0')
					break;
				token_nextchar(lex); // eat first-part

				char c2 = *lex->s;
				if (c2 == '\0')
					break;
				token_nextchar(lex); // eat second-part

				if (c1 == '*' && c2 == '/')
				{
					break;
				}
				// else repeat
			}

			if (*lex->s != EOF && *lex->s != '\0')
			{
				return token_next(lex);
			}
			else
			{
				t->type = tok_eof;
				return t;
			}
		}
		else if (*lex->s == '/')
		{
			t->type = 500;
			return t;
		}
		else
		{
			t->type = '/';
			return t;
		}
	}
}

Token *token_prev(Lexer *lex)
{
	// TODO
	Token *t;
	return t;
}

char token_nextchar(Lexer *lex)
{
	lex->location.i++;
	if (*lex->s == '\n')
	{
		lex->location.l++;
		lex->location.c = 1;
	}
	else
	{
		lex->location.c++;
	}
	*lex->s++;
	// if (*lex->s == '\0') return '\0';//return 0;//exit(1);//return '\0';
	// else
	return *lex->s;
}

char token_prevchar(Lexer *lex)
{
	lex->location.i--;
	lex->location.c--;
	if (lex->location.c <= 0)
	{
		if (lex->location.c < 0)
			lex->location.c = 0;
		lex->location.l--;
	}
	*lex->s--;
}

bool token_is_end(Lexer *lex)
{
#ifdef DEBUG
	if (*lex->s == '\0')
		printf("[token_end] %s\n", (*lex->s == '\0') ? "True" : "False");
#endif

	if (*lex->s == '\0' || *lex->s == EOF)
		return true;
	else
		return false;
}

void token_free(Token *t)
{
	sdsfree(t->vstring);
}

char *token_name(Token *t)
{
	if (t == NULL)
		return "EOF";

	switch (t->type)
	{
		case tok_eof:
			return "EOF";
			break;

		case '/':
			return "OPERATOR_DIV";
			break;

		case tok_div_int: // '//'
			return "OPERATOR_DIV_int";
			break;

		case '+':
			return "OPERATOR_ADD";
			break;

		case '-':
			return "OPERATOR_MIN";
			break;

		case '*':
			return "OPERATOR_MUL";
			break;

		case '=':
			return "OPERATOR_DEFINE";
			break;

		case tok_define: // '=='
			return "OPERATOR_EQUAL";
			break;

		case '{':
			return "SECTION_OPEN";
			break;

		case '}':
			return "SECTION_CLOSE";
			break;

		case '(':
			return "BRACKET_OPEN";
			break;

		case ')':
			return "BRACKET_CLOSE";
			break;

		case tok_identifier:
			return "IDENTIFIER";
			break;

		case tok_string:
			return "STRING";
			break;

		case tok_number:
			return "NUMBER";
			break;

		case tok_def:
			return "DEF";
			break;

		case tok_extern:
			return "EXTERN";
			break;

		case tok_ret:
			return "RETURN";
			break;

		case tok_type_i8:
			return "TYPE_I8";
			break;
		case tok_type_i16:
			return "TYPE_I16";
			break;
		case tok_type_i32:
			return "TYPE_I32";
			break;
		case tok_type_i64:
			return "TYPE_I64";
			break;

		case tok_type_u8:
			return "TYPE_U8";
			break;
		case tok_type_u16:
			return "TYPE_U16";
			break;
		case tok_type_u32:
			return "TYPE_U32";
			break;
		case tok_type_u64:
			return "TYPE_U64";
			break;

		case tok_type_f32:
			return "TYPE_F64";
			break;
		case tok_type_f64:
			return "TYPE_F64";
			break;

		case tok_type_bool:
			return "TYPE_BOOL";
			break;
		case tok_type_char:
			return "TYPE_CHAR";
			break;
		case tok_type_string:
			return "TYPE_STRING";
			break;

		default:
			return "UNKNOWN";
			break;
	}
}

void token_log(Token *t)
{
	printf("[token] %s", token_name(t));

	if (t == NULL)
		return; // Fix crash bug when we have a blank line at end of the file!

	if (t->type == tok_string || t->type == tok_identifier)
		printf(" = %s", t->vstring);
	else if (t->type == tok_number)
		printf(" = %d", t->vint);

	printf("\n");
}

bool token_is_operator(Token *t)
{
	switch (t->type)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '>':
		case '<':
			return true;
			break;

		default:
			return false;
	}
}
