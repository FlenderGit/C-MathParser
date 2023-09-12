#include <stdio.h>

#include "include/print.h"
#include "include/tokeniser.h"
#include "include/parser.h"

double eval_token(Token *token)
{
	switch(token->type){

	// Just a number
	case T_NUMBER: return token->value;
	
	// A variable (Eg. x,y...)
	// case T_VARIABLE: return token->value;

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
		case 1: return token->function.prot->function1(eval_token(token->function.args[0]));
		case 2: return token->function.prot->function2(eval_token(token->function.args[0]),eval_token(token->function.args[1]));
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





double eval_var(Token* token, double variable) {
	switch(token->type){
		case T_NUMBER: return token->value;
		case T_VARIABLE: return variable;
		case T_OPERATOR:

			switch(token->operator) {
				case OPE_ADD: return eval_var(token->left,variable) + eval_var(token->right,variable);
				case OPE_MINUS: return eval_var(token->left,variable) - eval_var(token->right,variable);
				case OPE_MULTI: return eval_var(token->left,variable) * eval_var(token->right,variable);
				case OPE_DIV: return eval_var(token->left,variable) / eval_var(token->right,variable);
			}
		case T_CALL:
			switch(token->function.prot->numberArgs) {
				case 1: return token->function.prot->function1(eval_var(token->function.args[0], variable));
				case 2: return token->function.prot->function2(eval_var(token->function.args[0], variable), eval_var(token->function.args[1], variable));
			}

		default:
			printf("TOKEN not recon");
			return -5;

	};
}

void eval_range(char* expr, double min, double max, double step, PRINT_TYPE type) {

	Parser* parser = parser_init(expr);
	Token* token = parse_expr(parser, 0);

	print_token(token, 0);

	switch(type) {
		case P_GRAPH:
			print_graph(token, min, max, step, 0, 10);
			break;
		case P_TABLE: print_table(token, min, max, step); break;
	}

	free_token(token);
	free_parser(parser);
}
