#include <stdio.h>
#include <time.h>
#include <string.h>

#include "include/print.h"
#include "include/parser.h"
#include "include/error.h"
#include "include/eval.h"

#include "include/chart.h"

#define clrscr() printf("\e[1;1H\e[2J")

typedef enum {
	X_SIMPLE,
	X_LIST,
	X_RANGE
} X_TYPE;

typedef struct {
	X_TYPE type;
	union main
	{
		double value;
		double* list;
	};	
} X;

void exec_eval(Token* token, double variable);
void handle_range(Token* token, double list_number[3]);

int main(int argc, char *argv[])
{

	// Exit if not expr
	if ( argc < 2 ) {
		error_custom_exit("Usage: cal 'expr'\nExemple -> cal '.1 + .2'");
	}

	PRINT_TYPE print_type = -1;
	unsigned short index_expr = 1;

	X_TYPE x_type = -2;
	short index_x = -1;

	// printf("Test : |\u2801|\u2808|\n");
	printf("\nEn cours...\n\n");

	// Analyse command options
	for(unsigned short i=1; i<argc; ++i) {
		if(argv[i][0]=='-'){
			switch(argv[i][1+(argv[i][1] == '-')])
			{
				case 'x': case 'X':
					//printf("x DETECTED\n");
					index_x=i;
					break;
				case 'f': case 'F':
					//printf("Show graph\n");
					print_type = P_GRAPH;
					break;
				case 't': case 'T':
					//printf("Show binary tree\n");
					print_type = P_TREE;
					break;
				case 'g': case 'G':
					//printf("Show table\n");
					print_type = P_TABLE;
					break;
				case 'r': case 'R':
					//printf("Show line\n");
					print_type = P_ROW;
					break;
				default:
					printf("option %s not detected", argv[i]);
			}

		} else {
			index_expr=i;
		}

	}

	// Set parser's variables
	Parser* parser = parser_init(argv[index_expr]);
	Token* token = parse_expr(parser, 0);
	
	// If tree, print the tree
	

	// Analyse x values
	// If option -x exists
	if(index_x!=-1){

		// X_SIMPLE set value
		// else analyse and execute
		char* ptr_equal = strchr(argv[index_x], '=');

		if(ptr_equal==NULL)
			error_custom_exit("-x option need  equal sign. E.g. : '-x=3'");

		++ptr_equal;
		
		// IDEA : Create X_CONFIG -> X_TYPE, (value || start, end, value || ls ) 

		// if x have one value -> use function start_eval
		// else
		
		//char delimiter[] = ",";
		//char* to = strtok(ptr_equal, delimiter);
    
		if(*ptr_equal=='['){
			// Handle list

		} else {

			double values[3];
			unsigned short count_comma = 0;
			char delimiter[] = ",";
			char* to = strtok(ptr_equal, delimiter);

			
			while (to != NULL) {
        		double value;
        		if (sscanf(to, "%lf", &values[count_comma++]) != 1) {
            		break;
        		}
        		to = strtok(NULL, delimiter);
    		}

			
			
			//++count_comma;
			//sscanf(to, "%lf", &value) ;
			// printf("VAL : %g\n", value);

			switch (count_comma)
			{
			case 1:
				exec_eval(token, values[0]);
				break;

			case 3:
				handle_range(token, values);
				break;
			
			default:
				error_custom("Unespected number of values for -x argument.");
			}

		}
	

		/*
    	while (to != NULL) {
        double value;
        if (sscanf(to, "%lf", &value) == 1) {
            printf("Valeur : %.2lf\n", value);
        }
        to = strtok(NULL, delimiter);
    	}
		*/
	
	}

	if(print_type==P_TREE) {
		
	} else if (print_type==P_ROW) {
		printf("Display decoded expression of : %s\n\n", argv[index_expr]);
		print_expr(token);
		printf("\n\n");
	}
	
	if(index_x==-1) {
		double variable = 0;
		if(strchr(argv[index_expr], 'x')!=NULL){
			printf("var x detected : remplaced by 0\n");
		}

		switch (print_type)
		{
		case -1:
			break;
		case P_TREE:
			printf("Display binary tree of : %s\n\n", argv[index_expr]);
			print_tree(token);
			break;
		case P_ROW:
			printf("Display decoded expression of : %s\n\n", argv[index_expr]);
			print_expr(token);
			printf("\n\n");
			break;
		default:
			printf("This print option is not compatible without the x");
			break;
		}

		exec_eval(token, variable);
	}

		
	
	
	//eval_range(argv[1], 0, 2, .1, TABLE);
	

	/*
	clrscr();

	Chart chart = {
		9, 0, 0, token
	};

	draw_chart(&chart);
	handle_input(&chart);
	*/

	// Free data
	free_token(token);
	free_parser(parser);
	

	return 0;
}



void printEquality(double value1, double value2)
{
	printf("[%c] : %f = %f\n", value1 == value2 ? 'Y' : 'N' , value1, value2);
}

void exec_eval(Token* token, double variable) {
	clock_t begin, end;
	double value;
		
	begin = clock();
	value = eval_var(token, variable);
	end = clock();
	printf("TOTAL : %g en %lu ms", value, (end-begin) * 1000 / CLOCKS_PER_SEC);
}

void handle_range(Token* token, double list_number[3])
{
	if(list_number[0]>list_number[1])
		error_custom("Min must be under max");

	if(list_number[2]<0)
		error_custom("Step must be superior than 0");

	print_table(token, list_number[0], list_number[1], list_number[2]);
}