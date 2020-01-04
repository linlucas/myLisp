#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>
#include "mpc.h"

long getOperationType(long x, char *op, long y);
long evaluate(mpc_ast_t *t);


int main(int argc, char *argv[]) {
    // create parsers
    mpc_parser_t *Number = mpc_new("number");
    mpc_parser_t *Operator = mpc_new("operator");
    mpc_parser_t *Expr = mpc_new("expr");
    mpc_parser_t *MyLisp = mpc_new("myLisp");

    // define parsers
    mpca_lang(MPCA_LANG_DEFAULT, 
    "                                                     \
      number   : /-?[0-9]+/ ;                             \
      operator : '+' | '-' | '*' | '/' ;                  \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      myLisp    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, MyLisp);

    puts("myLisp version 0.0.4");
    puts("Press ctrl + c to exit\n");

    while (1) {
        char *input = readline("myLisp > ");
        add_history(input);
        
        // parse user input
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, MyLisp, &r)) {
            long result = evaluate(r.output);
            printf("li\n", result);
            mpc_ast_delete(r.output);
        } else {
            // on failure print and delete the error
            mpc_ast_print(r.error);
            mpc_ast_delete(r.error);
        }
        free(input);
    }
    mpc_cleanup(4, Number, Operator, Expr, MyLisp);
    return 0;
}

long getOperationType(long x, char *op, long y) {
    if (strcmp(op, "+") == 0) {
        return x + y;
    } else if (strcmp(op, "-") == 0) {
        return x - y;
    } else if (strcmp(op, "*") == 0) {
        return x * y;
    } else if (strcmp(op, "/") == 0) {
        return x / y;
    }
    return 0;
}

long evaluate(mpc_ast_t *t) {
    char *end;
    int i = 3;

    if (strstr(t->tag, "number")) {
        return strtol(t->contents, &end, 10);
    }
    char *op = t->children[1]->contents;
    long x = evaluate(t->children[2]);

    while (strstr(t->children[i]->tag, "expr")) {
        x = getOperationType(x, op, evaluate(t->children[i]));
        ++i;
    }
    return x;
}