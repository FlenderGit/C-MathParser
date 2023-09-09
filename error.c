
#include <stdio.h>
#include <stdlib.h>

void error_system(char* message)
{
	perror(message);
}

void error_system_exit(char* message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void error_custom(char* message)
{
	fprintf(stderr, message);
}

void error_custom_exit(char* message)
{
	fprintf(stderr, message);
	exit(EXIT_FAILURE);
}