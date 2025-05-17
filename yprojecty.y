%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "yprojecty.tab.h"
    #include <string.h>
    extern int yylineno;
    extern char *yytext;
    

    void yyerror(const char *s) {
        fprintf(stderr, "Error: %s\n at line %d, near %s\n", s , yylineno, yytext);
    }
    typedef struct Symbol{
        char *name;
        int line;
        struct Symbol *next;
    }Symbol;

    typedef struct SymbolTable{
        Symbol* symbols_list;
        struct SymbolTable* outer;
    }SymbolTable;

    SymbolTable* current_table = NULL;

    SymbolTable* enter_new_table() {
        SymbolTable* new_table = (SymbolTable*)malloc(sizeof(SymbolTable));
        new_table->symbols_list = NULL;
        new_table->outer = current_table;
        current_table = new_table;
        return new_table;
    }

    void dump_current_table() {
        printf("Current Symbol Table:\n");
        SymbolTable* table = current_table;
        
        Symbol* symbols = table->symbols_list;
        if(symbols == NULL) {
            printf("No symbols in the current table.\n");
            return;
        }
        while (symbols != NULL) {
            printf("Symbol: %s, Line: %d\n", symbols->name, symbols->line);
            symbols = symbols->next;
        }
        
        
    }
    void leave_table() {
        SymbolTable* outer = current_table->outer;
        Symbol* symbol = current_table->symbols_list;
        while (symbol != NULL) {
            Symbol* temp = symbol;
            symbol = symbol->next;
            free(temp->name);
            free(temp);
        }
        free(current_table);
        current_table = outer;
    }

    Symbol* lookup_symbol(char* name){
        SymbolTable* table = current_table;
        while (table != NULL) {
            Symbol* symbol = table->symbols_list;
            while (symbol != NULL) {
                if (strcmp(symbol->name, name) == 0) {
                    return symbol;
                }
                symbol = symbol->next;
            }
            table = table->outer;
        }
        return NULL;
    }

    Symbol* current_table_last_symbol() {
        SymbolTable* table = current_table;
        if (table->symbols_list == NULL) {
            return NULL;
        }
        Symbol* symbol = table->symbols_list;
        while (symbol->next != NULL) {
            symbol = symbol->next;
        }
        return symbol;
    }

    void insert_symbol(char* name) {
        
        if (lookup_symbol(name)!= NULL) {
            printf("Error: Variable %s already declared.\n", name);
            return;
        }
        Symbol* new_symbol = (Symbol*)malloc(sizeof(Symbol));
        new_symbol->name = strdup(name);
        new_symbol->line = yylineno;
        new_symbol->next = NULL;

        if (current_table_last_symbol() == NULL) {
            current_table->symbols_list = new_symbol;
        } else {
            current_table_last_symbol()->next = new_symbol;
        }
        printf("Insert symbol: %s\n", name);
    }
    
%}

%token BOOL BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE EXTERN FALSE_TOKEN FLOAT FOR FOREACH IF INT PRINT PRINTLN READ RETURN STRING SWITCH TRUE_TOKEN VOID WHILE
%token ID INT_LITERAL REAL_LITERAL STRING_LITERAL MAIN
%token PLUS_PLUS MINUS_MINUS LESS_EQUAL GREATER_EQUAL EQUAL NOT_EQUAL AND_AND OR_OR DOT_DOT
%left OR_OR
%left AND_AND
%left '!'
%left '<' LESS_EQUAL '>' GREATER_EQUAL EQUAL NOT_EQUAL
%left '+' '-'
%left '*' '/' '%'
%right UMINUS
%union{
    int ivalue;
    float fvalue;
    char* svalue;
}

%type <ivalue> INT_LITERAL
%type <fvalue> REAL_LITERAL
%type <svalue> ID STRING_LITERAL
%type <svalue> MAIN

%define parse.error verbose
%define parse.trace

%%

program:
    pre_main_declaration main_function_declaration
    {
        printf("Program parsed successfully.\n");
    }
    |
    main_function_declaration
    {
        printf("Program parsed successfully without pre main.\n");
    }
    ;


pre_main_declaration:
    pre_main_declaration_list pre_main_declaration|pre_main_declaration_list
    ;

pre_main_declaration_list:
    function_declaration|
    const_declaration|
    variable_declaration
    ;
    

function_declaration:
    type ID '(' parameter_list ')' block 
    {
        insert_symbol($2);
    }|
    type ID '(' ')' block
    {
        insert_symbol($2);
    }
    ;

parameter_list:
    type ID|
    type ID ',' parameter_list
    ;


main_function_declaration:
    VOID MAIN '(' ')' block
    ;

const_declaration:
    CONST type ID '=' const_expression ';'
    {
        insert_symbol($3);
    }
    ;

variable_declaration:
    type identifier_list ';'{
        printf("Variable declaration parsed successfully.\n");
    }
    ;

identifier_list:
    identifier_decl|identifier_decl ',' identifier_list
    ;

identifier_decl:
    ID
    {
        insert_symbol($1);
    }|
    ID '=' expression
    {
        insert_symbol($1);
    }
    ;

array_declaration:
    type ID array_size_or_location ';'
    {
        insert_symbol($2);
    }
    ;

array_size_or_location:
    '[' expression ']'|
    '[' expression ']' array_size_or_location
    ;

type:
    INT|
    FLOAT|
    BOOL|
    STRING;

left_brace:
    '{'
    {
        printf("Entering new block.\n");
        enter_new_table();
    }
    ;

right_brace:
    '}'
    {
        printf("Exiting block.\n");
        dump_current_table();
        leave_table();
    }
    ;

block:
    left_brace statement_list right_brace
    |left_brace right_brace;

statement_list:
    statement|
    statement statement_list
    ;

statement:
    simple_statment|
    variable_declaration|
    const_declaration|
    array_declaration|
    function_invocation ';'|
    conditional_statement|
    loop_statement|
    return_statement;


simple_statment:
    variable_assignment ';'|
    print_statement ';'|
    read_statement ';' |
    increment_decrement_statement ';';

simple_statment_without_semicolon:
    variable_assignment|
    print_statement|
    read_statement|
    increment_decrement_statement;

variable_assignment:
    ID '=' expression 
    {
        if(lookup_symbol($1) == NULL){
            printf("Error: Variable %s not declared.\n", $1);
            YYERROR;
        }
    }|
    ID array_size_or_location '=' expression
    {
        if(lookup_symbol($1) == NULL){
            printf("Error: Variable %s not declared.\n", $1);
            YYERROR;
        }
    } ;

function_invocation:
    ID '(' argument_list ')' ;

argument_list:
    expression|
    expression ',' argument_list
    ;


conditional_statement:
    IF '(' bool_expression ')' if_statement ELSE if_statement|
    IF '(' bool_expression ')' if_statement;

if_statement:
    statement|
    block;

loop_statement:
    WHILE '(' bool_expression ')' if_statement|
    FOR '(' simple_statment  bool_expression ';' simple_statment_without_semicolon')' if_statement|
    FOREACH '(' ID ':' expression DOT_DOT expression ')' if_statement;



print_statement:
    PRINT expression |
    PRINTLN expression ;


read_statement:
    READ ID ;

increment_decrement_statement:
    ID PLUS_PLUS |
    ID MINUS_MINUS |
    ID array_size_or_location PLUS_PLUS |
    ID array_size_or_location MINUS_MINUS ;

return_statement:
    RETURN expression ';'|
    RETURN ';';

bool_expression:
    expression EQUAL expression|
    expression NOT_EQUAL expression|
    expression '<' expression|
    expression '>' expression|
    expression LESS_EQUAL expression|
    expression GREATER_EQUAL expression|
    bool_expression AND_AND bool_expression|
    bool_expression OR_OR bool_expression|
    '!' bool_expression|
    '(' bool_expression ')';

const_expression:
    INT_LITERAL|
    REAL_LITERAL|
    STRING_LITERAL|
    TRUE_TOKEN|
    FALSE_TOKEN;


expression:
    INT_LITERAL|
    REAL_LITERAL|
    STRING_LITERAL|
    TRUE_TOKEN|
    FALSE_TOKEN|
    function_invocation|
    ID|
    ID array_size_or_location|
    '(' expression ')'|
    expression '+' expression|
    expression '-' expression|
    expression '*' expression|
    expression '/' expression|
    expression '%' expression|
    '-' expression %prec UMINUS;
%%
int main() {
    extern int yydebug;
    yydebug = 0;
    current_table = enter_new_table();
    printf("Starting parser...\n");
    yyparse();
    dump_current_table();
    leave_table();
    printf("Parser finished.\n");
    return 0;
}
