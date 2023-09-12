#include <stdio.h>
#include <string.h>

#include "include/tokeniser.h"
#include "include/eval.h"

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
		printf("NAME :%s\n", token->function.prot->name);
		printTab(tab_number);
		printf("ARGS :\n");
		
		for(short i=0; i<token->function.prot->numberArgs;++i){
			print_token(token->function.args[i],tab_number+1);
		}
		
		break;
	case T_VARIABLE:
		printTab(tab_number);
		printf("TYPE: VARIABLE\n");
		break;

	case T_EOF:
		printf("TYPE : EOF");
		break;
	}
}


void print_token2(Token *token, short tab_number, int is_right)
{

	static _Bool lsRight[10] = {0};

	lsRight[tab_number] = is_right;
	if (token==NULL)
		return;

    int i;


	for(i=1; i<tab_number; ++i){
		printf("%s", lsRight[i] ? "    " : "|   ");
	}

	if(i <= tab_number){
		printf("%s", lsRight[i] ? "`-- " : "|-- ");
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

            print_token2(token->left,tab_number+1, 0);
            print_token2(token->right,tab_number+1, 1);
            
            break;
    }
}

void print_token3(Token *token, int is_tail, int tab_indent, char* buffer)
{

	printf("%s", buffer);

	if(tab_indent)
		printf	("%s", is_tail ? "`-- " : "|-- ");

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

			char new_buffer[40];
			strcpy(new_buffer, buffer);
			
			if(tab_indent)
				strcat(new_buffer, is_tail ? "    " : "|   ");

            print_token3(token->left, 0, tab_indent+1, new_buffer);
            print_token3(token->right, 1, tab_indent+1,new_buffer);
            
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

void print_table(Token* token, double min, double max, double step) {
	for(double i=min; i<max; i+=step) {
		double var = eval_var(token, i);
		printf("| %g\t| %g\t|\n", i, var);
	}
}

void print_graph(Token* token, double min, double max, double step, int yMin, int ymax)
{
	printf("%s", "TEST : \u280A\n");
}