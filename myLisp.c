#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>

int main(int argc, char** argv) {
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