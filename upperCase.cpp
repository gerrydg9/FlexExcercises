%{
#include <stdio.h>
#include <ctype.h>
%}

%%
[a-z]+ { 
    int i;
    for (i = 0; yytext[i] != '\0'; i++) {
        putchar(toupper(yytext[i]));
    }
    putchar(' ');
}

%%

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(" %s ", argv[0]);
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    FILE *salida = fopen(argv[2], "w");

    yyin = entrada;
    yyout = salida;

    yylex();

    fclose(entrada);
    fclose(salida);

    return 0;
}
