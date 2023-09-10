#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "include/error.h"
#include "include/tokeniser.h"


FunctPrototype lsFunction[] = {
	{ .function1=sin, 1, "sin"},
	{ .function2=pow, 2, "pow"}
};

Token* next_token(Tokeniser *tokeniser)
{

	Token* tok = create_token();
	char current = tokeniser->expr[tokeniser->cursor];

	// Advance to net token skipping black space
	while(current==' ') {
		tokeniser->cursor++;
		current = tokeniser->expr[tokeniser->cursor];
	}

	if (current=='\0'){
		tok->type=T_EOF;
		tokeniser->cursor++;
		return tok;
	} else if(isalpha(current)) {
		

		// Test variable

		int i = 0;
		char buffer[10];
		char* parenthese;

		parenthese = strchr(tokeniser->expr+tokeniser->cursor,'(');

		if( parenthese != NULL ) {

			size_t length = parenthese - (tokeniser->expr+tokeniser->cursor);
			strncpy(buffer, tokeniser->expr+tokeniser->cursor, length);
			buffer[length] = '\0';

			while ( i < 1 ) {

				if ( !strcmp(buffer, lsFunction[i].name) )
					break;

				++i;
			}

			tok->type = T_CALL;
			tok->function.prot = &lsFunction[i];
			tok->function.args = malloc(sizeof(Token)*lsFunction[i].numberArgs);

			tokeniser->cursor += strlen(buffer);
			return tok;

		} else {
			printf("NOPE\n");
		}

		

	} else if (isdigit(current)||current=='.'){
		tok->type=T_NUMBER;
		short n;

		char* expr = tokeniser->expr + tokeniser->cursor;

		sscanf(expr,"%lf%n",&tok->value,&n);
		tokeniser->cursor += n;

		return tok;

	} else if (current=='(') {
		tok->type=T_OPEN;
		tokeniser->cursor++;


	} else if (current==')') {
		tok->type=T_CLOSE;
		tok->operator = 0;
		tokeniser->cursor++;

	} else {
		tok->type=T_OPERATOR;
		tok->left=(void*)0;
		tok->right=(void*)0;
		switch(current){
		case '+': tok->operator=OPE_ADD;break;
		case '-': tok->operator=OPE_MINUS;break;
		case '*': tok->operator=OPE_MULTI;break;
		case '/': tok->operator=OPE_DIV;break;
		default: tok->value=current;
		}
		tokeniser->cursor++;
	}
	return tok;
}

Token* create_token()
{
	Token* token = malloc(sizeof(Token));

	if ( token == NULL )
		error_system_exit("Error with memory allocation for Token");

	return token;
}

void free_token(Token* token)
{
	if( token->type == T_OPERATOR )
	{
		free_token(token->left);
		free_token(token->right);
	} 
	else if ( token->type == T_CALL ) {
		for (short i=0; i<token->function.prot->numberArgs; ++i){
			free(&token->function.args[i]);
		}
	}

	free(token);
}

