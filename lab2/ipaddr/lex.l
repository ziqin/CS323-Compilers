%{
    int indicator = 0;
    char *addr_type = NULL;
%}

%option     noyywrap
v4section   (0|[1-9][0-9]?|1[0-9]{2}|2([0-4][0-9]|5[0-5]))
hexdigit    [0-9A-Fa-f]
v6section   ({hexdigit}{1,4})
v4          ({v4section}\.){3}{v4section}
v6          ({v6section}:){7}{v6section}

%%
{v4} { indicator = 4; }
{v6} { indicator = 6; }
<<EOF>> {
    if(indicator == 4)
        addr_type = "IPv4";
    else if(indicator == 6)
        addr_type = "IPv6";
    else
        addr_type = "Neither";
    indicator = 0;
    return 0;
}
\n {}
. {}
%%
char *validIPAddress(char *IP){
    YY_BUFFER_STATE buf;
    buf = yy_scan_string(IP);
    yylex();
    yy_delete_buffer(buf);
    return addr_type;
}
