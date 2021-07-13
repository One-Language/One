/**
 The One Programming Language

 File: tokenizer/tokenizer.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

/*
 @function: tokenizerString
 @inputs: string of a one' pathfile
 @return: Array of Token
 */
Token* tokenizerFile(char *filepath)
{
	char* data = fileReads(filepath);
	return tokenizerString(data);
}

/*
 @function: tokenizerString
 @inputs: string of a One program source-code
 @return: Array of Token
 */
Token* tokenizerString(char *data)
{
	
}
