#ifndef ERROR_H
#define ERROR_H

/*
 * error.h
 * Used to handle error in program
 */

/*
 * Function error_system
 * --------------------
 * Print the error message and
 * the error stock in errno to
 * stder
 * 
 * Used to system error like
 * memory allocation
 */
void error_system(char* message);

/*
 * Function error_system_exit
 * --------------------
 * Like error_system but stop
 * the program
 */
void error_system_exit(char* message);

/*
 * Function error_custom
 * --------------------
 * Print  a custom error
 * message
 * 
 * Used for other error
 */
void error_custom(char* message);

/*
 * Function error_custom_exit
 * --------------------
 * Like error_custom but stop
 * the program
 */
void error_custom_exit(char* message);

#endif