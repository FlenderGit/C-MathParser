#ifndef TOKENISER_H
#define TOKENISER_H

/*
 * Enum: TOKEN_TYPE 
 * -------------------- 
 * Type used to define a Token type
 */
typedef enum {
	T_EOF,
	T_NUMBER,
	T_VARIABLE,

	T_OPERATOR,
	T_CALL,

	T_OPEN,
	T_CLOSE
} TOKEN_TYPE;


/*
 * Enum: TOKEN_OPERATOR 
 * -------------------- 
 * Value used to defined a Token operator if
 * the Token is type T_OPERATOR
 * 
 */
typedef enum  {
	OPE_ADD		= 1,
	OPE_MINUS,
	OPE_MULTI,
	OPE_DIV
} TOKEN_OPERATOR;

/*
 * typedef for function pointers
 */
typedef double (*ptrFunction1)(double);
typedef double (*ptrFunction2)(double, double);

/*
 * Struct: FuncPrototype
 * -------------------- 
 * A function prototype used the create
 * a list with all allowed functions and
 * only give the pointer
 */
typedef struct FunctPrototype
{
	union
	{
	ptrFunction1 function1;
	ptrFunction2 function2;
	};
	
	unsigned short numberArgs;
	char *name; 
} FunctPrototype;

/*
 * Struct: Token
 * -------------------- 
 * The representation off a token
 * 
 * type			: type of token, see TOKEN_TYPE
 * value		: value if NUMBER
 * struct		: operator, left and right node if OPERATOR
 * function		: funtion prototype and list of args as Token if CALL
 */
typedef struct Token
{
	TOKEN_TYPE type;
	union {
		double value;
		struct {
			TOKEN_OPERATOR operator;
			struct Token *left;
			struct Token *right;
		};
		struct {
			FunctPrototype *prot;
			struct Token **args;
		} function;
	};
} Token;


/*
 * Struct: Tokeniser
 * -------------------- 
 * Used to analyse the string and create token
 * 
 * int			: the cursor inside the expr
 * char*		: the expr
 */
typedef struct Tokeniser
{
	int cursor;
	char* expr;
} Tokeniser;



// ------------- Functions definitions -------------

/*
 * Function: next_token 
 * --------------------
 * get the next token from the tokeniser
 * 
 * tokeniser 	: the tokeniser
 *
 * returns		: pointer of the next token
 * 
 */
Token* next_token(Tokeniser *tokeniser);


/*
 * Function: create_token
 * --------------------
 * create a new empty token
 * 
 * returns		: new empty token 
 *
 */
Token* create_token();


/*
 * Function: free_token
 * -------------------- 
 * free the token and their children
 * 
 * *token 		: the token to free 
 * 
 */
void free_token(Token* token);

#endif