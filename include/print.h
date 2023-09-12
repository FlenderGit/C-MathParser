#ifndef PRINT_H
#define PRINT_H

#include "tokeniser.h"

typedef enum {
    GRAPH,
    TABLE
} PRINT_TYPE;

/*
 * Function: print_token
 * --------------------
 * print the token on the shell
 *
 * *token 		: the token to print
 * tab_number	: the number of tab = default 0
 */
void print_token(Token *token, short tab_number);


/*
 * Function: print_token2
 * --------------------
 * Print the tree of the expr
 * 
 * E.g with (2+.5)*4
 *
 * *
 * |-- +
 * |   |-- 2
 * |   `-- 0.5
 * `-- 4
 * 
 * To read this, each operator have two branch below
 * Each branch have a number or another operator.
 * 
 * +
 * |-- 2
 * `-- 0.5
 * Mean "2+0.5"
 * 
 * /!\ Function use static var so one usage
 * for multiple usage, see print_token3
 * 
 * Token*       : The token to show
 * short        : The distance of parent node to the root node
 * int          : If the node is the last node of a expr
 * 
 * TD : Handle function
 */
void print_token2(Token *token, short tab_number, int isTail);


/*
 * Function: print_token3
 * --------------------
 * Usage: Like print_token3 but can be use
 * multiple time because of string buffer
 * 
 * TD : Optimize the buffer to not use space_black
 */
void print_token3(Token *token, int is_tail, int tab_indent, char* buffer);


/*
 * Function: print_expr
 * --------------------
 * The a expr from the root node
 * using recursivity to print node
 * with multiple children (OPERATOR or CALL)
 * 
 * Token*       : the root token
 */
void print_expr(Token* token);


/*
 * Function: printTab
 * -------------------- 
 * print multiple tab equivalent to the arg
 * 
 * short        : the number of tab
 */
void printTab(short lvlInt);

void print_table(Token* token, double min, double max, double step);
void print_graph(Token* token, double min, double max, double step, int yMin, int ymax);

#endif