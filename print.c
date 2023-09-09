#include "include/tokeniser.h"
#include <stdio.h>

void printTab(short lvlInt)
{
	for(short i=0;i<lvlInt;++i) {
		printf("\t");
	}
}

void print_token(Token *token, short tab_number)
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
			print_token(token->left,tab_number+1);
		}
			
		printTab(tab_number);
		printf("RIGHT :\n");
		if(token->right!=NULL)
			print_token(token->right,tab_number+1);
		break;
	case T_CALL:
		printTab(tab_number);
		printf("TYPE : CALL\n");
		printTab(tab_number);
		printf("ARGS :\n");
		/*
		for(short i=0; i<token->function.prot->numberArgs;++i){
			print_token(&token->function.args[i],lvlInt+1);
		}
		*/
		break;
	case T_EOF:
		printf("TYPE : EOF");
		break;
	}
}


void print_token2(Token *token, short tab_number, int isTail)
{

    if(tab_number != 0) {
        for(short i=0; i<tab_number-1; ++i){
            printf("|   ");
        }
        if(isTail == 0){
            printf("|-- ");
        } else {
            printf("=-- "); 
        }
    }

	switch(token->type) {
        case T_NUMBER:
            printf("%g\n", token->value);
            break;
        case T_OPERATOR:
            switch(token->operator) {
                case OPE_ADD: printf("+"); break;
                case OPE_MINUS: printf("-"); break;
                case OPE_DIV: printf("/"); break;
                case OPE_MULTI: printf("*"); break;
            }
            printf("\n");

            if(token->left!=(void*)0)
                print_token2(token->left,tab_number+1, 0);
            if(token->right!=NULL)
                print_token2(token->right,tab_number+1, 1);
            
            break;
    }
}

void print_expr(Token* token)
{
    if(token->type == T_OPERATOR) {
        char operator;

        switch(token->operator) {
            case OPE_ADD: operator='+'; break;
            case OPE_MINUS: operator='-'; break;
            case OPE_MULTI: operator='*'; break;
            case OPE_DIV: operator='/'; break;
        }

        printf("(");
        print_expr(token->left);
        printf("%c", operator);
        print_expr(token->right);
        printf(")");
    } else if (token->type == T_NUMBER){
        printf("%g", token->value);
    }
}