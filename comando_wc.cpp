%{
#include <stdio.h>

int num_lines = 0;
int num_words = 0;
int num_bytes = 0;
int in_word = 0;
%}

%%

\n {
    num_lines++;
}

" " {
    if (in_word) {
        num_words++;
        in_word = 0;
    }
}

. { // si encontramos cualquier otro caracter, se considera una palabra
    in_word = 1;
}

%%

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    yyin = file; //archivo de entrada

    yylex();

    // Se imprimen resultados
    printf("%d %d %d %s\n", num_lines, num_words, num_bytes, argv[1]);

    fclose(file);
    return 0;
}
