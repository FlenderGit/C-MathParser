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
* operator.h : Hashtable, Add operator (byte && pow)
* function.h : Hashtable function & add function (sqrt, max, cos, tan, arcsin..., )
* option.h : Handle flag/option in command `cal "1+x" -x=1` & `cal "1+x" -x=1,10,1`
* Redo eval/var -> if X ->msg break eval_var with 0, eval -> deprecated 
* next_token reformat + add fonction (extract str && skip_blanck)
* add static