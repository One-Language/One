
enum one_token {
	TOK_START = 255
	#define DEF(id, str) ,id
	#include "tokens.h"
	#undef DEF
};
