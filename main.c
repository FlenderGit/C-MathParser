#include <stdio.h>
#include <time.h>

#include "include/print.h"
#include "include/parser.h"
#include "include/error.h"
#include "include/eval.h"

int main(int argc, char *argv[])
{

	if ( argc < 2 ) {
		error_custom_exit("Usage: cal 'expr'\nExemple -> cal '.1 + .2'");
	}

	printf("En cours...\n");

	Parser* parser = parser_init(argv[1]);
	Token* token = parse_expr(parser, 0);
	clock_t begin, end;

	begin = clock();
	double value = eval_token(token);
	end = clock();

    unsigned long millis = (end -  begin) * 1000 / CLOCKS_PER_SEC;
	// printf("TOTAL :  %g en %lu ms ", eval(argv[1]), millis);
	printf("TOTAL :  %g en %lu ms\n", value, millis);

	char buffer[40] = "";
	print_token3(token, 0, 0, buffer);

	print_expr(token);

	free_token(token);
	free_parser(parser);

	return 0;
}










void printEquality(double value1, double value2)
{
	printf("[%c] : %f = %f\n", value1 == value2 ? 'Y' : 'N' , value1, value2);
}




