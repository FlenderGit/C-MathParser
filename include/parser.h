#ifndef PARSER_H
#define PARSER_H

#include "tokeniser.h"

typedef double (*ptrFunction)(double);

typedef struct {
	Tokeniser* tokeniser;
	Token* current;
} Parser;






// ------------- Functions definitions -------------


Parser* parser_init(char* expr);

Token* parser_advance(Parser *parser);

Token* parse_expr(Parser *parser, TOKEN_OPERATOR operator );

Token* parser_prefix_expr(Parser *parser);

Token* parser_infix_expr(Parser *parser, TOKEN_OPERATOR operator, Token *left);

void free_parser(Parser* token);




// Token* parse(Token *token);

#endif