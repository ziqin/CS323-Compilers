%{
    #include "string.h"
    #include"lex.yy.c"
    char * cat(const char *, const char *, const char *);
    void yyerror(char*s){}

    /*
     * We make assumpti ons on the input:
     * there are no syntax errors, and
     * only consist two operators, plus
     * and minus, and all numbers contain
     * exactly one digit, no spaces.
     */

    // where reverse Polish notation goes
    char *result;
%}
%define api.value.type { char* }
%token TERM ADD SUB

%%
Eval: Expr { result = $1; }
Expr: TERM              { $$ = $1; }
    | Expr ADD TERM     { $$ = cat($1, $3, $2); }
    | Expr SUB TERM     { $$ = cat($1, $3, $2); }
%%

char *convert(char *expr){
    YY_BUFFER_STATE buf;
    buf = yy_scan_string(expr);
    yyparse();
    yy_delete_buffer(buf);
    return result;
}

char * cat(const char *a, const char *b, const char *c) {
    char * concatenated = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + 1);
    return strcat(strcat(strcpy(concatenated, a), b), c);
}
