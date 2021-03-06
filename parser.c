#include <stdio.h>
#include "mpc.h"

// Declare a static buffer for user input of maximum size 2048 
static char input[2048];

int main(int argc, char** argv) {

	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");

	// Define the parsers
	mpca_lang(MPC_LANG_DEFAULT,
		"                                                    \
		number   : /-?[0-9]+/ ;                              \
		operator : '+' | '-' | '*' | '/' ;                   \
		expr     : <number> | '(' <operator> <expr>+ ')' ;   \
		lispy    : /^/ <operator> <expr>+ /$/ ;              \
		",
		Number, Operator, Expr, Lispy);

	// Print Version and Exit Information
	puts("Lispy Version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");

	while (1) {

		// Output prompt
		fputs("lispy> ", stdout);

		// Read a line of user input
		fgets(input, 2048, stdin);

		// Attempt to parse user input
		mpc_result_t r;
		if (mpc_parse("<stdin>", input, Lispy, &r)) {
			// On success print the AST
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		} else {
			// Otherwise print the error
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
	}

	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	return 0;
}