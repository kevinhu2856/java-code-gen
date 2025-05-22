%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "yprojecty.tab.h"
    #include <string.h>
    extern int yylineno;
    extern char *yytext;

    typedef enum{
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_BOOL,
        TYPE_STRING,
        TYPE_VOID,
        TYPE_ARRAY,
    }DataType;

    typedef struct {
        DataType basetype;
        int dimensions;
    }Typeinfo;

    typedef struct ExpressionNode{
        DataType type;
        union{
            int ivalue;
            float fvalue;
            char* svalue;
            int bvalue;
        }value;
        Typeinfo array_info;
    }ExpressionNode;

    ExpressionNode* create_expr_node(DataType type) {
        ExpressionNode* node = (ExpressionNode*)malloc(sizeof(ExpressionNode));
        if (!node) {
            fprintf(stderr, "Memory allocation failed for expression node\n");
            exit(EXIT_FAILURE);
        }
        node->type = type;
        return node;
    }

    /* Free an expression node */
    void free_expr_node(ExpressionNode* node) {
        if (node) {
            if (node->type == TYPE_STRING && node->value.svalue)
                free(node->value.svalue);
            free(node);
        }
    }

    void yyerror(const char *s) {
        fprintf(stderr, "Error: %s\n at line %d, near %s\n", s , yylineno, yytext);
    }
    typedef struct Symbol{
        char *name;
        union {
            int ivalue;
            float fvalue;
            char* svalue;
            int bvalue;
        }value;
        int line;
        DataType type;
        Typeinfo typeinfo;
        int is_const;
        int is_function;
        struct Symbol *next;
    }Symbol;

    typedef struct SymbolTable{
        Symbol* symbols_list;
        struct SymbolTable* outer;
        int is_function;
    }SymbolTable;

    SymbolTable* current_table = NULL;
    DataType current_declaration_type;
    DataType current_function_return_type;
    char* current_function_name = NULL;
    int inside_loop = 0;

    const char* type_to_string(DataType type) {
        switch(type) {
            case TYPE_INT: return "INT";
            case TYPE_FLOAT: return "FLOAT";
            case TYPE_BOOL: return "BOOL";
            case TYPE_STRING: return "STRING";
            case TYPE_VOID: return "VOID";
            case TYPE_ARRAY: return "ARRAY";
            default: return "UNKNOWN";
        }
    }

    SymbolTable* enter_new_table(int is_function_scope) {
        SymbolTable* new_table = (SymbolTable*)malloc(sizeof(SymbolTable));
        new_table->symbols_list = NULL;
        new_table->outer = current_table;
        new_table->is_function = is_function_scope;
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
            printf("Symbol: %s, Type: %s, Line: %d, ", 
                  symbols->name, 
                  type_to_string(symbols->type), 
                  symbols->line);
            if(symbols->type == TYPE_INT) {
                printf("Value: %d", symbols->value.ivalue);
            } else if(symbols->type == TYPE_FLOAT) {
                printf("Value: %f", symbols->value.fvalue);
            } else if(symbols->type == TYPE_BOOL) {
                if(symbols->value.bvalue) {
                    printf("Value: true");
                } else {
                    printf("Value: false");
                }
            } else if(symbols->type == TYPE_STRING) {
                printf("Value: %s", symbols->value.svalue);
            }
            if (symbols->is_const) printf(", Constant");
            if (symbols->is_function) printf(", Function");
            if (symbols->type == TYPE_ARRAY) {
                printf(", Array of %s with %d dimensions", 
                      type_to_string(symbols->typeinfo.basetype),
                      symbols->typeinfo.dimensions);
            }
            printf("\n");
            symbols = symbols->next;
        }
    }

    
    void leave_table() {
        if (current_table == NULL) {
            fprintf(stderr, "Error: Attempting to leave non-existent table\n");
            return;
        }
        
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

    Symbol* lookup_current_scope(char* name) {
        if (current_table == NULL) return NULL;
        
        Symbol* symbol = current_table->symbols_list;
        while (symbol != NULL) {
            if (strcmp(symbol->name, name) == 0) {
                return symbol;
            }
            symbol = symbol->next;
        }
        return NULL;
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

    void insert_symbol(char* name, DataType type, int is_const, int is_function) {
        
         if (lookup_symbol(name) != NULL) {
            fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", 
                   name, yylineno);
            return;
        }
        
        Symbol* new_symbol = (Symbol*)malloc(sizeof(Symbol));
        if (!new_symbol) {
            fprintf(stderr, "Memory allocation failed for symbol\n");
            exit(EXIT_FAILURE);
        }
        
        new_symbol->name = strdup(name);
        new_symbol->line = yylineno;
        new_symbol->type = type;
        new_symbol->is_const = is_const;
        new_symbol->is_function = is_function;
        new_symbol->next = NULL;
        
        // Set array info if applicable
        if (type == TYPE_ARRAY) {
            new_symbol->typeinfo.basetype = current_declaration_type;
            new_symbol->typeinfo.dimensions = 0; // Will be updated during array declaration
        }

        if (current_table_last_symbol() == NULL) {
            current_table->symbols_list = new_symbol;
        } else {
            current_table_last_symbol()->next = new_symbol;
        }
        printf("Inserted symbol: %s, Type: %s at line %d\n", 
              name, type_to_string(type), yylineno);
    }
    typedef enum{
        op_plus,
        op_minus,
        op_multiply,
        op_divide,
        op_modulus,
        op_less,
        op_greater,
        op_less_equal,
        op_greater_equal,
        op_equal,
        op_not_equal,
        op_and,
        op_or
    }operators;

    operators char_to_operator(char op) {
        switch(op) {
            case '+': return op_plus;
            case '-': return op_minus;
            case '*': return op_multiply;
            case '/': return op_divide;
            case '%': return op_modulus;
            case '<': return op_less;
            case '>': return op_greater;
            default: return -1; // Invalid operator
        }
    }

    operators token_to_operator(int token) {
        switch(token) {
            case LESS_EQUAL: return op_less_equal;
            case GREATER_EQUAL: return op_greater_equal;
            case EQUAL: return op_equal;
            case NOT_EQUAL: return op_not_equal;
            case AND_AND: return op_and;
            case OR_OR: return op_or;
            default: return -1; // Invalid operator
        }
    }


    DataType check_expression_type(DataType left, DataType right, operators op) {
        // Type compatibility rules
        switch(op) {
            case op_plus:
                if (left == TYPE_STRING || right == TYPE_STRING) 
                    return TYPE_STRING; // String concatenation
                else if (left == TYPE_FLOAT || right == TYPE_FLOAT)
                    return TYPE_FLOAT;
                else 
                    return TYPE_INT;
            case op_minus:
            case op_multiply:
            case op_divide:
                if (left == TYPE_STRING || right == TYPE_STRING) {
                    yyerror("Type error: Cannot perform arithmetic on strings");
                    return TYPE_INT; // Default to avoid cascading errors
                }
                else if (left == TYPE_FLOAT || right == TYPE_FLOAT)
                    return TYPE_FLOAT;
                else 
                    return TYPE_INT;
            case op_modulus:
                if (left != TYPE_INT || right != TYPE_INT) {
                    yyerror("Type error: Modulo operation requires integer operands");
                    return TYPE_INT;
                }
                return TYPE_INT;
            // Comparison operators
            case op_greater:
            case op_less:
            case op_less_equal:
            case op_greater_equal:
            case op_equal:
            case op_not_equal:
                return TYPE_BOOL;
            // Logical operators
            case op_and:
            case op_or:
                if (left != TYPE_BOOL || right != TYPE_BOOL) {
                    yyerror("Type error: Logical operations require boolean operands");
                }
                return TYPE_BOOL;
            default:
                return left; // Default to left operand type
        }
    }

    int is_assignment_compatible(DataType var_type, DataType expr_type) {
        if (var_type == expr_type) return 1;
        
        // Allow int to float conversion
        if (var_type == TYPE_FLOAT && expr_type == TYPE_INT) 
            return 1;
            
        return 0;
    }

    void add_array_dimension(char* name) {
        Symbol* sym = lookup_current_scope(name);
        if (sym && sym->type == TYPE_ARRAY) {
            sym->typeinfo.dimensions++;
        }
    }

    void set_current_type(int token) {
        switch(token) {
            case INT: current_declaration_type = TYPE_INT; break;
            case FLOAT: current_declaration_type = TYPE_FLOAT; break;
            case BOOL: current_declaration_type = TYPE_BOOL; break;
            case STRING: current_declaration_type = TYPE_STRING; break;
            case VOID: current_declaration_type = TYPE_VOID; break;
            default: current_declaration_type = TYPE_INT; // Default
        }
    }
    
%}

%token BOOL BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE EXTERN FALSE_TOKEN FLOAT FOR FOREACH IF INT PRINT PRINTLN READ RETURN STRING SWITCH TRUE_TOKEN VOID WHILE
%token  INT_LITERAL REAL_LITERAL STRING_LITERAL MAIN ID
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
    int dtype;
    struct ExpressionNode* expr_node;
}

%type <ivalue> INT_LITERAL
%type <fvalue> REAL_LITERAL
%type <svalue> STRING_LITERAL
%type <svalue> MAIN ID
%type <dtype> type
%type <expr_node> expression

%define parse.error verbose
%define parse.trace

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program:
    pre_main_declaration main_function_declaration
    {
        printf("Program parsed successfully.\n");
    }
    | main_function_declaration
    {
        printf("Program parsed successfully without pre main.\n");
    }
    ;

pre_main_declaration:
    pre_main_declaration_list
    | pre_main_declaration pre_main_declaration_list
    ;

pre_main_declaration_list:
    function_declaration
    | const_declaration
    | variable_declaration
    ;
    



function_declaration:
    type ID 
    
    '(' 
    {
        enter_new_table(1);
    }
    parameter_list ')' 
    {
        current_function_return_type = $1;
        current_function_name = strdup($2);
        insert_symbol($2, $1, 0, 1);
    }block 
    
    {
        free(current_function_name);
        current_function_name = NULL;
    }
    |
    type ID 
    
    '(' 
    {
        enter_new_table(1);
    } 
    ')' 
    {
        current_function_return_type = $1;
        current_function_name = strdup($2);
        insert_symbol($2, $1, 0, 1);
    }
    block
    {
        free(current_function_name);
        current_function_name = NULL;
    }
    ;

parameter_list:
    type ID
    {
        insert_symbol($2, $1, 0, 0); // Add parameter to function scope
    }|
    type ID 
    {
        insert_symbol($2, $1, 0, 0); // Add parameter to function scope
    }
    ',' parameter_list
    ;


main_function_declaration:
    VOID MAIN 
    {
        current_function_return_type = TYPE_VOID;
        current_function_name = strdup("main");
        insert_symbol("main", TYPE_VOID, 0, 1);
    }
    '('
    {
        enter_new_table(1); // Enter function scope
    }
     ')' block
     {
        free(current_function_name);
        current_function_name = NULL;
    }
    ;

const_declaration:
    CONST type 
    {
        current_declaration_type = $2;
    }
    identifier_list ';'
    ;

variable_declaration:
    type 
    identifier_list ';'
    ;

identifier_list:
    identifier_decl|identifier_decl ',' identifier_list
    ;

identifier_decl:
    ID
    {
        insert_symbol($1, current_declaration_type, 0, 0);
    }|
    ID '=' expression
    {
        insert_symbol($1, current_declaration_type, 0, 0);
        if($3!=NULL&&!is_assignment_compatible(current_declaration_type, $3->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($3->type),type_to_string(current_declaration_type), yylineno);
            YYERROR;
        }else{
            Symbol* sym = lookup_symbol($1);
            if (sym->type == TYPE_INT) {
                sym->value.ivalue = $3->value.ivalue;
            } else if (sym->type == TYPE_FLOAT) {
                sym->value.fvalue = $3->value.fvalue;
            } else if (sym->type == TYPE_BOOL) {
                sym->value.bvalue = $3->value.bvalue;
            } else if (sym->type == TYPE_STRING) {
                sym->value.svalue = strdup($3->value.svalue);
            }
        }
        free_expr_node($3);
    }
    ;

array_declaration:
    type 
    ID 
    {
        current_declaration_type = $1;
        insert_symbol($2, TYPE_ARRAY, 0, 0); // Record as array type
    }
    array_size_or_location ';'
    ;

array_size_or_location:
    '[' expression ']'
    {
        if($2->type != TYPE_INT) {
            fprintf(stderr, "Error: Array size must be an integer at line %d\n", yylineno);
            YYERROR;
        }
        free_expr_node($2);
    }|
    '[' expression ']' array_size_or_location
    {
        if($2->type != TYPE_INT) {
            fprintf(stderr, "Error: Array size must be an integer at line %d\n", yylineno);
            YYERROR;
        }
        free_expr_node($2);
    }
    ;

type:
    INT { $$ = TYPE_INT; current_declaration_type = TYPE_INT; }
    |
    FLOAT { $$ = TYPE_FLOAT; current_declaration_type = TYPE_FLOAT;}
    |
    BOOL { $$ = TYPE_BOOL; current_declaration_type = TYPE_BOOL;}
    |
    STRING { $$ = TYPE_STRING; current_declaration_type = TYPE_STRING;}
    |
    VOID { $$ = TYPE_VOID; current_declaration_type = TYPE_VOID;}
    ;

block:
    '{'
    {
        enter_new_table(0);
    } 
    statement_list '}'
    {
        dump_current_table();
        leave_table();
    }
    |
    '{'
    {
        enter_new_table(0);
    } '}'
    {
        dump_current_table();
        leave_table();
    };

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
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot assign to constant '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        if($3!=NULL&&!is_assignment_compatible(sym->type, $3->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($3->type),type_to_string(sym->type), yylineno);
            YYERROR;
        }else{
            Symbol* sym = lookup_symbol($1);
            if (sym->type == TYPE_INT) {
                sym->value.ivalue = $3->value.ivalue;
            } else if (sym->type == TYPE_FLOAT) {
                sym->value.fvalue = $3->value.fvalue;
            } else if (sym->type == TYPE_BOOL) {
                sym->value.bvalue = $3->value.bvalue;
            } else if (sym->type == TYPE_STRING) {
                sym->value.svalue = strdup($3->value.svalue);
            }
        }
        free_expr_node($3);
    }|
    ID array_size_or_location '=' expression
    {
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_ARRAY) {
            fprintf(stderr, "Error: Variable '%s' is not an array at line %d\n", $1, yylineno);
            YYERROR;
        }
        if($4!=NULL&&!is_assignment_compatible(sym->typeinfo.basetype, $4->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($4->type),type_to_string(sym->typeinfo.basetype), yylineno);
            YYERROR;
        }
        free_expr_node($4);
    } ;

function_invocation:
    ID '(' argument_list ')'
    {
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Function '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (!sym->is_function) {
            fprintf(stderr, "Error: '%s' is not a function at line %d\n", $1, yylineno);
            YYERROR;
        }
        // Here we would check argument types and count
    }|
    ID '(' ')'
    {
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Function '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (!sym->is_function) {
            fprintf(stderr, "Error: '%s' is not a function at line %d\n", $1, yylineno);
            YYERROR;
        }
        // Check that function doesn't require arguments
    };

argument_list:
    expression|
    expression ',' argument_list
    ;


conditional_statement:
    IF '(' expression ')' if_statement ELSE if_statement
    {
        if ($3->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in if statement must be boolean at line %d\n", yylineno);
            YYERROR;
        }
    }|
    IF '(' expression')' if_statement 
    {
        if ($3->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in if statement must be boolean at line %d\n", yylineno);
            YYERROR;
        }
    }
    %prec LOWER_THAN_ELSE
    ;

if_statement:
    {enter_new_table(0);}
    statement
    {dump_current_table();leave_table();}|
    block;

loop_statement:
    WHILE
    {
        inside_loop++;
    }
     '(' expression
     {
        if ($4->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in while loop must be boolean at line %d\n", yylineno);
            YYERROR;
        }
     } ')' if_statement
     {
        inside_loop--;
    }|
    FOR 
    {
        inside_loop++;
    }
    '(' simple_statment  expression{
        if ($5->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in while loop must be boolean at line %d\n", yylineno);
            YYERROR;
        }
    } ';' simple_statment_without_semicolon')' if_statement
    {
        
        inside_loop--;
    }|
    FOREACH 
    {
        inside_loop++;
    }
    '(' ID ':' expression DOT_DOT expression{
        if ($6->type != TYPE_INT||$8->type != TYPE_INT) {
            fprintf(stderr, "Error: Condition in foreach loop must be integer at line %d\n", yylineno);
            YYERROR;
        }
    } ')' if_statement
    {
        inside_loop--;
        dump_current_table();
        leave_table();
        // Verify ID is declared and of compatible type with expressions
        Symbol* sym = lookup_symbol($4);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $4, yylineno);
            YYERROR;
        }
    };



print_statement:
    PRINT expression |
    PRINTLN expression ;


read_statement:
    READ ID {
        Symbol* sym = lookup_symbol($2);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $2, yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot read into constant '%s' at line %d\n", $2, yylineno);
            YYERROR;
        }
    };

increment_decrement_statement:
    ID PLUS_PLUS 
    {
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot modify constant '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT && sym->type != TYPE_FLOAT) {
            fprintf(stderr, "Error: Cannot increment non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
    }|
    ID MINUS_MINUS 
    {
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot modify constant '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT && sym->type != TYPE_FLOAT) {
            fprintf(stderr, "Error: Cannot increment non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
    }|
    ID array_size_or_location PLUS_PLUS 
    {
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot modify constant '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT && sym->type != TYPE_FLOAT) {
            fprintf(stderr, "Error: Cannot increment non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
    }|
    ID array_size_or_location MINUS_MINUS 
    {
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot modify constant '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT && sym->type != TYPE_FLOAT) {
            fprintf(stderr, "Error: Cannot increment non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
    };

return_statement:
    RETURN expression ';'
    {
        if (current_function_name == NULL) {
            yyerror("Return statement outside of function");
            YYERROR;
        }
        // Check that expression type matches function return type
        if (current_function_return_type == TYPE_VOID) {
            yyerror("Cannot return a value from a void function");
            YYERROR;
        }
        // Additional type checking would go here
    }|
    RETURN ';'
    {
        if (current_function_name == NULL) {
            yyerror("Return statement outside of function");
            YYERROR;
        }
        if (current_function_return_type != TYPE_VOID) {
            yyerror("Non-void function must return a value");
            YYERROR;
        }
    };

    


expression:
    expression EQUAL expression
    {
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_equal));
        $$->value.bvalue = $1->value.bvalue == $3->value.bvalue;
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression NOT_EQUAL expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_not_equal));
        $$->value.bvalue = $1->value.bvalue != $3->value.bvalue;
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression '<' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_less));
        $$->value.bvalue = $1->value.bvalue < $3->value.bvalue;
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression '>' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_greater));
        $$->value.bvalue = $1->value.bvalue > $3->value.bvalue;
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression LESS_EQUAL expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_less_equal));
        $$->value.bvalue = $1->value.bvalue <= $3->value.bvalue;
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression GREATER_EQUAL expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_greater_equal));
        $$->value.bvalue = $1->value.bvalue >= $3->value.bvalue;
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression AND_AND expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_and));
        $$->value.bvalue = $1->value.bvalue && $3->value.bvalue;
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression OR_OR expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_or));
        $$->value.bvalue = $1->value.bvalue || $3->value.bvalue;
        free_expr_node($1);
        free_expr_node($3);
    }|
    '!' expression{
        $$ = create_expr_node(check_expression_type($2->type, TYPE_BOOL, op_equal));
        $$->value.bvalue = !$2->value.bvalue;
        free_expr_node($2);
    }|
    INT_LITERAL{
        $$ = create_expr_node(TYPE_INT);
        $$->value.ivalue = $1;
    }|
    REAL_LITERAL{
        $$ = create_expr_node(TYPE_FLOAT);
        $$->value.fvalue = $1;
    }|
    STRING_LITERAL{
        $$ = create_expr_node(TYPE_STRING);
        $$->value.svalue = strdup($1);
    }|
    TRUE_TOKEN{
        $$ = create_expr_node(TYPE_BOOL);
        $$->value.bvalue = 1;
    }|
    FALSE_TOKEN{
        $$ = create_expr_node(TYPE_BOOL);
        $$->value.bvalue = 0;
    }|
    function_invocation{
        
    }|
    ID{
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        $$ = create_expr_node(sym->type);
        if (sym->type == TYPE_INT) {
            $$->value.ivalue = sym->value.ivalue;
        } else if (sym->type == TYPE_FLOAT) {
            $$->value.fvalue = sym->value.fvalue;
        } else if (sym->type == TYPE_BOOL) {
            $$->value.bvalue = sym->value.bvalue;
        } else if (sym->type == TYPE_STRING) {
            $$->value.svalue = strdup(sym->value.svalue);
        }

    }|
    ID array_size_or_location{}|
    '(' expression ')'{
        $$ = create_expr_node($2->type);
        $$->value = $2->value;
        free_expr_node($2);
    }|
    expression '+' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_plus));
        if($$->type == TYPE_STRING) {
            $$->value.svalue = (char*)malloc(strlen($1->value.svalue) + strlen($3->value.svalue) + 1);
            strcpy($$->value.svalue, $1->value.svalue);
            strcat($$->value.svalue, $3->value.svalue);
        } else {
            $$->value.ivalue = $1->value.ivalue + $3->value.ivalue;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression '-' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_minus));
        if($$->type == TYPE_STRING) {
            yyerror("Type error: Cannot subtract strings");
            YYERROR;
        } else {
            $$->value.ivalue = $1->value.ivalue - $3->value.ivalue;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression '*' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_multiply));
        if($$->type == TYPE_STRING) {
            yyerror("Type error: Cannot multiply strings");
            YYERROR;
        } else {
            $$->value.ivalue = $1->value.ivalue * $3->value.ivalue;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression '/' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_divide));
        if($$->type == TYPE_STRING) {
            yyerror("Type error: Cannot divide strings");
            YYERROR;
        } else {
            $$->value.ivalue = $1->value.ivalue / $3->value.ivalue;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression '%' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_modulus));
        if($$->type == TYPE_STRING) {
            yyerror("Type error: Cannot modulo strings");
            YYERROR;
        } else if ($3->value.ivalue == 0) {
            yyerror("Error: Division by zero");
            YYERROR;
        } else {
            $$->value.ivalue = $1->value.ivalue % $3->value.ivalue;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    '-' expression %prec UMINUS{
        $$ = create_expr_node($2->type);
        if($$->type == TYPE_STRING) {
            yyerror("Type error: Cannot negate strings");
            YYERROR;
        } else if ($2->type == TYPE_INT) {
            $$->value.ivalue = -$2->value.ivalue;
        } else if ($2->type == TYPE_FLOAT) {
            $$->value.fvalue = -$2->value.fvalue;
        } else if ($2->type == TYPE_BOOL) {
            if ($2->value.bvalue) {
                $$->value.bvalue = 0;
            } else {
                $$->value.bvalue = 1;
            }
        }else {
            yyerror("Type error: Cannot negate non-numeric type");
            YYERROR;
        }
        free_expr_node($2);
    };
%%
int main() {
    extern int yydebug;
    yydebug = 0;
    current_table = enter_new_table(0);
    printf("Starting parser...\n");
    yyparse();
    dump_current_table();
    leave_table();
    printf("Parser finished.\n");
    return 0;
}