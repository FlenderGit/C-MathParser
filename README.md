# Recreate eval function

## Usage
Build the exemple -> `gcc main.c -o cal -Iinclude error.c eval.c parser.c tokeniser.c print.c chart.c`
The the exemple -> `cal "1+2*(3-4)/5+2"`

Use the lib:
* #include "include/eval.h"
* eval(".2+4");

## TO DO:
[Y] Make the usage of function work 100%
* Optimize the code
* Hashtable function
* Handle flag/option in command
* Redo eval/var -> test if X else msg
* next_token redo
*  