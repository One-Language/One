/**
 The One Programming Language

 File: tokenizer/tokenizer.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

/*
 * @function: tokenizer_file
 * @description: Create a array of tokens from a filepath
 * @inputs: char* of a one' pathfile
 * @return: Array of Token
 */
Token* tokenizer_file(char* filepath)
{
	char* data = fileReads(filepath);
	return tokenizer_string(data);
}

/*
 * @function: tokenizer_string
 * @description: Create a array of tokens from a one program source-code char*
 * @inputs: char* of a One program source-code
 * @return: Array of Token
 */
Token* tokenizer_string(char* data)
{
}
