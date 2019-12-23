#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include "mpc.h"

int main(int argc, char** argv) {
    // create parsers
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* MyLisp = mpc_new("myLisp");

    puts("myLisp version 0.0.3");
    puts("Press ctrl + c to exit\n");

    while (1) {
        char* input = readline("myLisp > ");
        add_history(input);
        printf("%s\n", input);
        free(input);
    }
    return 0;
}