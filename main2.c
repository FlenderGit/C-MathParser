#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

void error_custom_exit(char* message);
void error_system_exit(char* message);

typedef enum {
	T_EOF,
	T_NUMBER,
	T_VARIABLE,

	T_OPERATOR,
	T_CALL,

	T_OPEN,
	T_CLOSE
} TOKEN_TYPE;

typedef enum  {
	OPE_ADD		= 1,
	OPE_MINUS,
	OPE_MULTI,
	OPE_DIV
} TOKEN_OPERATOR;


typedef double (*ptrFunction)(double);


typedef struct FunctPrototype
{
	ptrFunction function;
	unsigned short numberArgs;
	char *name; 
} FunctPrototype;


typedef struct Token
{
	TOKEN_TYPE type;
	union {
		double value;
		struct {
			TOKEN_OPERATOR operator;
			struct Token *left;
			struct Token *right;
		};
		struct {
			FunctPrototype *prot;
			struct Token **args;
		} function;
	};
} Token;

typedef struct Tokeniser
{
	int cursor;
	char* expr;
} Tokeniser;

typedef struct {
	Tokeniser* tokeniser;
	Token* current;
} Parser;

Token* next_token(Tokeniser *tokeniser);
Token* create_token();
void free_token(Token* token);
void free_parser(Parser* token);
void printToken(Token *token,short tab_number);


Parser* parser_init(char* expr);
Token* parser_advance(Parser *parser);
Token* parse_expr(Parser *parser, TOKEN_OPERATOR operator );
Token* parser_prefix_expr(Parser *parser);
Token* parser_infix_expr(Parser *parser, TOKEN_OPERATOR operator, Token *left);

double eval_token(Token *token);
double eval(char* expr);

int main(int argc, char *argv[])
{

	if ( argc < 2 ) {
		error_custom_exit("Usage: cal 'expr'\nExemple -> cal '.1 + .2'");
	}

	printf("En cours...\n");

	//char expr[50];
	//printf("Enter expression : ");
	//scanf("%[^\n]s", expr);

	/*
	Parser* parser = parser_init(argv[1]);
	for(short i=0; i<4; ++i) {
		printToken(parser->current,0);
		parser_advance(parser);
	}
	*/

	//printToken(parse_expr(parser,0),0);	

	
	clock_t begin, end;
	begin = clock();
	double result = eval(argv[1]);
	end = clock();

    unsigned long millis = (end -  begin) * 1000 / CLOCKS_PER_SEC;

	printf("TOTAL :  %g en %lu ms ", eval(argv[1]), millis);

	return 0;
}

void error_custom_exit(char* message)
{
	fprintf(stderr, message);
	exit(EXIT_FAILURE);
}

void error_system_exit(char* message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

double eval_token(Token *token)
{
	switch(token->type){

	// Just a number
	case T_NUMBER: return token->value;
	
	// A variable (Eg. x,y...)
	case T_VARIABLE: return token->value;

	// A Operator (factorize if possible)
	case T_OPERATOR:

		switch(token->operator) {

		case OPE_ADD: return eval_token(token->left) + eval_token(token->right);
		case OPE_MINUS: return eval_token(token->left) - eval_token(token->right);
		case OPE_MULTI: return eval_token(token->left) * eval_token(token->right);
		case OPE_DIV: return eval_token(token->left) / eval_token(token->right);

		}


	// A function
	case T_CALL:
		switch(token->function.prot->numberArgs) {
		case 1: return token->function.prot->function(eval_token(token->function.args[0]));
		}
	
	// Error
	default: return -3;

	};
	
}

double eval(char* expr)
{
	Parser* parser = parser_init(expr);
	Token* token = parse_expr(parser, 0);
	double value = eval_token(token);
	
	free_token(token);
	free_parser(parser);
	return value;
}


Parser* parser_init(char* expr)
{
	Parser *parser = malloc(sizeof(Parser));
	Tokeniser *tokeniser = malloc(sizeof(Tokeniser));
	tokeniser->expr = expr;
	tokeniser->cursor = 0;
	parser->tokeniser = tokeniser;
	parser->current = next_token(tokeniser);
	return parser;
}

Token* parser_advance(Parser *parser)
{
	parser->current = next_token(parser->tokeniser);
	return parser->current;
}

Token* parse_expr(Parser *parser, TOKEN_OPERATOR operator )
{
	Token *left = parser_prefix_expr(parser);
	Token *next = parser->current;
	TOKEN_OPERATOR next_ope = next->operator;


	while(next_ope != T_EOF ) {

		if(operator >= next_ope)
			break;

		parser_advance(parser);		
		left = parser_infix_expr(parser,next->operator,left);
		next = parser->current;
		next_ope = parser->current->operator;
	}

	return left;
}

Token* parser_prefix_expr(Parser *parser)
{
	Token* tok = (void*)0;

	switch(parser->current->type) {
	case T_NUMBER:
		tok = parser->current;
		parser_advance(parser);
		return tok;
	case T_OPEN:
		parser_advance(parser);
		tok = parse_expr(parser,0);
		if(parser->current->type == T_CLOSE)
			parser_advance(parser);
		return tok;
	case T_OPERATOR:
		parser_advance(parser);
		if(parser->current->type==OPE_MINUS)
			parser->current->value *= -1;
		return parser->current;
	case T_CALL:
		printf("ENTER\n");
		tok = parser->current;
		printf("CALL FIND :\n" );
		parser_advance(parser);
		if(parser->current->type==T_OPEN)
			parser_advance(parser);
		for(short i=0; i<tok->function.prot->numberArgs; ++i){
			tok->function.args[i] = parse_expr(parser,0);
		}
		if(parser->current->type == T_CLOSE)
			parser_advance(parser);
		return tok;
	}

	return (void*)0;

}

Token* parser_infix_expr(Parser *parser, TOKEN_OPERATOR operator, Token *left)
{
	Token *tok = malloc(sizeof(Token));
	tok->type = T_OPERATOR;
	tok->operator = operator;
	tok->left = left;	
	tok->right = parse_expr(parser, operator);
	return tok;
}

FunctPrototype lsFunction[] = {
	{sin, 1, "sin"}
};

void printTab(short lvlInt)
{
	for(short i=0;i<lvlInt;++i) {
		printf("\t");
	}
}

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
	} else if(isalpha(current)) {
		

		// Test variable

		/*
		int i = 0;
		char buffer[10];
		char* parenthese;

		parenthese = strchr(tokeniser->expr+tokeniser->cursor,'(');

		if( parenthese != NULL ) {

			size_t length = parenthese - (tokeniser->expr+tokeniser->cursor);
			strncpy(buffer, tokeniser->expr+tokeniser->cursor, length);
			buffer[length] = '\0';

			while ( i < 1 ) {

				if ( strcmp(buffer, lsFunction[i].name) )
					break;

				++i;
			}

			tok->type = T_CALL;
			tok->function.prot = &lsFunction[i];
			tokeniser->cursor += strlen(buffer);
			return tok;

		} else {
			printf("NOPE");
		}
		*/

		

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
	else if ( token->type == T_CALL )
		free(token->function.args);

	free(token);
}

void free_parser(Parser* parser)
{
	free(parser->tokeniser);
	free(parser);
}

void printToken(Token *token, short tab_number)
{
	switch(token->type) {
	case T_NUMBER:
		printTab(tab_number);
		printf("TYPE : NUMBER\n");
		printTab(tab_number);
		printf("VALUE : %f\n", token->value);
		break;
	case T_OPERATOR:
		printTab(tab_number);
		printf("TYPE : OPERATOR\n");
		printTab(tab_number);
		printf("VALUE : ");
		switch(token->operator) {
			case OPE_ADD: printf("ADD\n"); break;
			case OPE_MINUS: printf("MINUS\n"); break;
			case OPE_DIV: printf("DIVISION\n"); break;
			case OPE_MULTI: printf("MULTIPLICATION\n"); break;
			default: printf("ERROR -> %c\n", token->value);
		}
		printTab(tab_number);
		printf("LEFT :\n");
		if(token->left!=(void*)0){
			printToken(token->left,tab_number+1);
		}
			
		printTab(tab_number);
		printf("RIGHT :\n");
		if(token->right!=NULL)
			printToken(token->right,tab_number+1);
		break;
	case T_CALL:
		printTab(tab_number);
		printf("TYPE : CALL\n");
		printTab(tab_number);
		printf("ARGS :\n");
		/*
		for(short i=0; i<token->function.prot->numberArgs;++i){
			printToken(&token->function.args[i],lvlInt+1);
		}
		*/
		break;
	case T_EOF:
		printf("TYPE : EOF\n");
		break;
	}
}	