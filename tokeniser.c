#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "include/error.h"
#include "include/tokeniser.h"

// Test
double minTest(double a, double b){
	return a < b ? a : b;
}

FunctPrototype lsFunction[] = {
	{ .function1=sin, 1, "sin"},
	{ .function2=pow, 2, "pow"},
	{ .function2=minTest, 2, "min"}
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
	} else if (current=='x') {
		tok->type=T_VARIABLE;
		tokeniser->cursor++;
		return tok;
	} else if (current==',') {
		tok->type=T_COMMA;
		tok->operator=0;
		tokeniser->cursor++;
		return tok;
	} else if(isalpha(current)) {
		

		// Test variable

		int i = 0;
		char* parenthese;

		//tok->type = T_VARIABLE;
		//tokeniser->cursor++;
		char cu;

		do {
			cu = tokeniser->expr[tokeniser->cursor+(i++)];
		} while(cu != ' ' && cu != '(' && cu != '\0');

		char* name = malloc(sizeof(char)*i);
		
		if( name != NULL ) {

			strncpy(name, tokeniser->expr+tokeniser->cursor, i);
			name[i-1] = '\0';
			tokeniser->cursor += i-1;

			i = 0;
			while ( i < 2 ) {
				if ( !strcmp(name, lsFunction[i].name) )
					break;
				++i;
			}


			tok->type = T_CALL;
			tok->function.prot = &lsFunction[i];
			tok->function.args = malloc(sizeof(Token)*lsFunction[i].numberArgs);

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

