#ifndef PRINT_H
#define PRINT_H

#include "tokeniser.h"

/*
 * Function: print_token
 * --------------------
 * print the token on the shell
 *
 * *token 		: the token to print
 * tab_number	: the number of tab 
 *
 */
void print_token(Token *token, short tab_number);
void print_token2(Token *token, short tab_number, int isTail);

void print_expr(Token* token);
void printTab(short lvlInt);

#endif