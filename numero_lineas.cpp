%option noyywrap

%{
#include <stdio.h>
int line_number = 1; // Variable global para almacenar el número de línea actual
%}

%{
// Reglas analizador léxico
%}

%%

\n               { ++line_number; } // Se incrementa el número de línea

.                { printf("%d: %s", line_number, yytext); } // Imprime el número de línea y la entrada actual

%%

int main() {
    yylex();
    return 0;
}
