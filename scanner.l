%{
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include "yprojecty.tab.h"

    #define LIST     strcat(buf,yytext)
    #define token(t) {LIST; printf("<%s>\n",t);return t;}
    #define tokenInteger(t,i) {LIST; printf("<%s:%d>\n",t,i);return t;}
    #define tokenString(t,s) {LIST; printf("<%s:%s>\n",t,s);return t;}
    #define MAX_LINE_LENG 256
    char buf[MAX_LINE_LENG];
    int line_count = 1;



    

    
%}

%option noyywrap
%option yylineno

%%


"."        { printf("<.>") ;return '.'; }
","        { printf("<,>");return ','; }
":"        { printf("<:>");return ':'; }
";"        { line_count++;printf("<;>\n%d:\n",line_count);return ';'; }
"("        { printf("<(>");return '('; }
")"        { printf("<)>");return ')'; }
"["        { printf("<[>");return '['; }
"]"        { printf("<]>");return ']'; }
"{"        { line_count++;printf("<{>\n%d:\n",line_count);return '{'; }
"}"        { printf("<}>\n");return '}'; }
"+"        { printf("<+>");return '+'; }
"++"       { printf("<++>");return PLUS_PLUS; }
"-"        { printf("<->");return '-'; }
"--"       { printf("<-->");return MINUS_MINUS; }
"*"        { printf("<*>");return '*'; }
"/"        { printf("</>");return '/'; }
"%"        { printf("<&>");return '%'; }
"="        { printf("<=>");return '='; }
"<"        { printf("<<>");return '<'; }
"<="       { printf("<<=>");return LESS_EQUAL; }
">"        { printf("<>>");return '>'; }
">="       { printf("<>=>");return GREATER_EQUAL; }
"=="       { printf("<==>");return EQUAL; }
"!="       { printf("<!=>");return NOT_EQUAL; }
"&&"       { printf("<&&>");return AND_AND; }
"||"       { printf("<||>");return OR_OR; }
"!"        { printf("<!>");return '!'; }
".."      { printf("<..>");return DOT_DOT; }

"bool"      { printf("<'bool'>"); return BOOL; }
"break"     { printf("<'break'>"); return BREAK; }
"case"      { printf("<'case'>"); return CASE; }
"char"      { printf("<'char'>"); return CHAR; }
"const"     { printf("<'const'>"); return CONST; }
"continue"  { printf("<'continue'>"); return CONTINUE; }
"default"   { printf("<'default'>"); return DEFAULT; }
"do"        { printf("<'do'>"); return DO; }
"double"    { printf("<'double'>"); return DOUBLE; }
"else"      { printf("<'else'>"); return ELSE; }
"extern"    { printf("<'extern'>"); return EXTERN; }
"false"     { printf("<'false'>"); return FALSE_TOKEN; }
"float"     { printf("<'float'>"); return FLOAT; }
"for"       { printf("<'for'>"); return FOR; }
"foreach"   { printf("<'foreach'>"); return FOREACH; }
"if"        { printf("<'if'>"); return IF; }
"int"       { printf("<'int'>"); return INT; }
"print"     { printf("<'print'>"); return PRINT; }
"println"   { printf("<'println'>"); return PRINTLN; }
"read"      { printf("<'read'>"); return READ; }
"return"    { printf("<'return'>"); return RETURN; }
"string"    { printf("<'string'>"); return STRING; }
"switch"    { printf("<'switch'>"); return SWITCH; }
"true"      { printf("<'true'>"); return TRUE_TOKEN; }
"void"      { printf("<'void'>"); return VOID; }
"while"     { printf("<'while'>"); return WHILE; }
"main"      { printf("<'main'>"); return MAIN; }

[a-zA-Z_][a-zA-Z0-9_]*   { 
    yylval.svalue = strdup(yytext);
    printf("<ID: %s>", yytext);
    return ID;
}


[0-9]+   { 
    yylval.ivalue=atoi(yytext); 
    printf("<int: %s>", yytext); return INT_LITERAL;}

[0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?   {
    yylval.fvalue=atof(yytext);
     printf("<real: %s>", yytext); return REAL_LITERAL;}


\"([^\"\n]|\"\")*["]  { 
    int len = strlen(yytext);
    char *processed = malloc(len);
    int i = 1,j = 0;
    while (i < len - 1) {
        if (yytext[i] == '"' && yytext[i + 1] == '"') {
            processed[j++] = '"';
            i += 2;
        } else {
            processed[j++] = yytext[i++];
        }
    }
    processed[j] = '\0';

    printf("<string: %s>", processed);
    yylval.svalue = strdup(processed);
    free(processed);    
    return STRING_LITERAL;
}

"//".*[\n]  {  }
"/*"([^*]|\*+[^*/])*\*+"/"  {  }

[\n]       {  }
[ \t\r]+    {  }

. {printf("unexpected character");}

%%
