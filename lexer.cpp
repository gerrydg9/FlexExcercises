%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int line_number = 1;
void error(char c) {
    printf("Error en la linea %d: caracter no reconocido '%c'\n", line_number, c);
    exit(1);
}
%}

%option noyywrap
%option outfile="lex_tokens.tokens"

%%
[0-9]+ {
    printf("<INT,%s>\n", yytext);
}
[0-9]+"."[0-9]* {
    printf("<FLOAT,%s>\n", yytext);
}
[a-zA-Z_][a-zA-Z0-9_]* {
    if (strcmp(yytext, "if") == 0) {
        printf("<IF>\n");
    } else if (strcmp(yytext, "then") == 0) {
        printf("<THEN>\n");
    } else if (strcmp(yytext, "else") == 0) {
        printf("<ELSE>\n");
    } else if (strcmp(yytext, "while") == 0) {
        printf("<WHILE>\n");
    } else if (strcmp(yytext, "do") == 0) {
        printf("<DO>\n");
    } else if (strcmp(yytext, "case") == 0) {
        printf("<CASE>\n");
    } else if (strcmp(yytext, "is") == 0) {
        printf("<IS>\n");
    } else if (strcmp(yytext, "void") == 0) {
        printf("<VOID>\n");
    } else if (strcmp(yytext, "true") == 0) {
        printf("<TRUE>\n");
    } else if (strcmp(yytext, "false") == 0) {
        printf("<FALSE>\n");
    } else if (strcmp(yytext, "begin") == 0) {
        printf("<BEGIN>\n");
    } else if (strcmp(yytext, "end") == 0) {
        printf("<END>\n");
    } else if (strcmp(yytext, "not") == 0) {
        printf("<NOT>\n");
    } else {
        printf("<ID,%s>\n", yytext);
    }
}
"--".* {
    // Se omite el comentario
}
"/*" {
    int depth = 1;
    char c;
    while (depth > 0) {
        c = yyinput();
        if (c == '\n') {
            line_number++;
        } else if (c == EOF) {
            error(c);
        } else if (c == '/' && yyinput() == '*') {
            depth++;
        } else if (c == '*' && yyinput() == '/') {
            depth--;
        }
    }
}
[><]=?|<> {
    printf("<OP_REL,%s>\n", yytext);
}
":=" {
    printf("<ASIGN>\n");
}

[ \t\n]+ {
    if (*yytext == '\n') {
        line_number++;
    }
}
[+\-/%*] {
    printf("<OP_ARIT,%c>\n", *yytext);
}

. {
    error(*yytext);
}

%%

int main(int argc, char* argv[]) {
    if (argc != 2 || strcmp(strrchr(argv[1], '.'), ".art") != 0) {
        printf("%s archivo.art ", argv[0]);
        return
