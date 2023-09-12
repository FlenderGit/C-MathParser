#ifndef EVAL_H
#define EVAL_H

#include "tokeniser.h"
#include "print.h"

/*
 * eval.h
 * Used to get result of
 * a expression from a string
 */

/*
 * Function: eval_token
 * --------------------
 * get the result of the node Token by calculating
 * result of child node
 * 
 * *token 		: the node token
 * 
 * returns		: result of node and node's child
 * 
 */ 
double eval_token(Token *token);


/*
 * Function: eval
 * -------------------- 
 * get the result from a string
 *
 * *expr		: the expression to calculate
 *
 * returns		: result of the string 
 *
 */
double eval(char* expr);

double eval_var(Token* token, double variable);
void eval_range(char* expr, double min, double max, double step, PRINT_TYPE type);


#endif