#include <stdlib.h>
#include <stdio.h>

#include "include/tokeniser.h"
#include "include/parser.h"
#include "include/print.h"


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

void free_parser(Parser* parser)
{
	free(parser->tokeniser);
	free(parser);
}

Token* parse_expr(Parser *parser, TOKEN_OPERATOR operator )
{
	Token *left = parser_prefix_expr(parser);
	Token *next = parser->current;
	TOKEN_OPERATOR next_ope = next->operator;

	while(next->type != T_EOF ) {

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
	case T_NUMBER: case T_VARIABLE:
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
		tok = parser->current;
		parser_advance(parser);
		
		if(parser->current->type==T_OPEN){
			parser_advance(parser);
		}

		for(short i=0; i<tok->function.prot->numberArgs; ++i){
			tok->function.args[i] = parse_expr(parser,0);
			
			if(parser->current->type = T_COMMA)
				parser_advance(parser);
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