%{
#include <stdio.h>
%}

DIGITO_BINARIO  [01]
LITERAL_BINARIA  0b{DIGITO_BINARIO}+

%%

{LITERAL_BINARIA}  {
                     int value = 0;
                     char *p = yytext + 2; // Se salta los caracteres 0b
                     while (*p) {
                        value = value * 2 + (*p - '0');
                        p++;
                     }
                     printf("Literal binaria: %s (Valor en de base 10: %d)\n", yytext, value);
                     return value;
                    }

.   ;

%%

int main(int argc, char** argv) {
   yylex();
   return 0;
}
