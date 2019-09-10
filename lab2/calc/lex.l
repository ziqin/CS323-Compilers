%{
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
%}

%option yylineno
digits      [0-9]+
number      {digits}(\.{digits})?
add         "+"
sub         "-"
mul         "*"
div         "/"
whitespace  " "|\t
newline     \n|\r|\r\n

%%
{number}        { printf("%s", yytext); }
{add}           { printf(" ADD "); }
{sub}           { printf(" SUB "); }
{mul}           { printf(" MUL "); }
{div}           { printf(" DIV "); }
{whitespace}+   {}
{newline}       { putchar('\n'); }
.               { puts("\nUnexpected value!"); }
%%

int main(int argc, char **argv){
    int i;
    char *file_path;
    if(argc < 2){
        fprintf(stderr, "Usage: %s <file_path>...\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        for(i = 1; i < argc; i++){
            file_path = argv[i];
            FILE *fd = fopen(file_path, "r");
            if(!fd){
                perror(file_path);
                return EXIT_FAILURE;
            }
            yyrestart(fd);
            yylex();
            fclose(fd);
        }
        return EXIT_SUCCESS;
    }
}
