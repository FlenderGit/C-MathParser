#ifndef TOKENISER_H
#define TOKENISER_H

/*
 * Enum: TOKEN_TYPE 
 * Type used to define a Token type
 * 
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

typedef double (*ptrFunction)(double);


typedef struct FunctPrototype
{
	ptrFunction function;
	unsigned short numberArgs;
	char *name; 
} FunctPrototype;


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