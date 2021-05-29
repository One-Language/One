/**
 The One Programming Language

 File: token.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"

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
