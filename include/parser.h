#ifndef PARSER_H
#define PARSER_H

#include "tokeniser.h"

/*
 * parser.h
 * Used to analyse tokens
 * from the tokeniser and
 * build the AST of the
 * expression
 */

/* Struct Parser
 * --------------------
 * tokeninser is used to get the next token
 * current is the current token
 */
typedef struct {
	Tokeniser* tokeniser;
	Token* current;
} Parser;


// ------------- Functions definitions -------------

/*
 * Function: parser_init
 * -------------------- 
 * Init the parser and attributs
 * 
 * char* expr 	: The string of the expression
 * 
 * return		: The parser	 
 */
Parser* parser_init(char* expr);

/*
 * Function: parser_advance
 * -------------------- 
 * Advance the tokeniser and
 * set the current token
 * 
 * Parser*		: The parser ( C is no POO :sad: )
 * 
 * return		: The current token 
 */
Token* parser_advance(Parser *parser);


/*
 * Function: parse_expr
 * -------------------- 
 * Analyse the first token and test
 * if the second is not EOF (end of expr)
 * 
 * IF second operator order superior of the
 * current return the current node.
 * ELSE build node with left part as the
 * current node. With this, the child node
 * will be evaluate first. 
 * 
 * Parser*		: The parser
 * TOKEN_OPE...	: The operator
 * 
 * return		: The AST node
 */
Token* parse_expr(Parser *parser, TOKEN_OPERATOR operator );


/*
 * Function: parser_prefix_expr
 * -------------------- 
 * Build "one" node
 * IF token a number	-> return
 * IF ( 				-> return the expr inside ()
 * IF OPERATOR (like -) -> return next number * -1
 * IF CALL				-> return CALL and set the value of arguments
 * 
 * Parser*		: The parser
 * 
 * return		: The AST node 
 */
Token* parser_prefix_expr(Parser *parser);


/*
 * Function: parser_infix_expr
 * -------------------- 
 * Build a node with left node as child
 * Used to build the AST using operator order
 * 
 * Parser*		: The parser
 * TOKEN_OPE...	: The operator
 * Token*		: The left token of the expr
 * 
 * return		: The AST node 
 */
Token* parser_infix_expr(Parser *parser, TOKEN_OPERATOR operator, Token *left);


/*
 * Function: free_parser
 * -------------------- 
 * Free the memory of the parser
 * 
 * Parser*		: The parser to delete
 */
void free_parser(Parser* parser);

#endif