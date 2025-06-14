%{
    #include "parser_header.h"
%}

%token BOOL BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE EXTERN FALSE_TOKEN FLOAT FOR FOREACH IF INT PRINT PRINTLN READ RETURN STRING SWITCH TRUE_TOKEN VOID WHILE NOP
%token INT_LITERAL REAL_LITERAL STRING_LITERAL MAIN ID 
%token PLUS_PLUS MINUS_MINUS LESS_EQUAL GREATER_EQUAL EQUAL NOT_EQUAL AND_AND OR_OR DOT_DOT PLUS_EQUAL MINUS_EQUAL STAR_EQUAL SLASH_EQUAL PERCENT_EQUAL
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
    struct FunctionSignature* func_sign;
}

%type <ivalue> INT_LITERAL
%type <fvalue> REAL_LITERAL
%type <svalue> STRING_LITERAL
%type <svalue> MAIN ID
%type <dtype> type
%type <expr_node> expression function_invocation const_list 
%type <func_sign> argument_list

%type <ivalue> loop_boolean_point loop_statement_point loop_exe_point loop_exit_point if_exit_label if_false_label
%type <ivalue> else_statement array_size_or_location
%define parse.error verbose
%define parse.trace

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program:
    pre_main_declaration main_function_declaration
    | main_function_declaration
    ;

pre_main_declaration:
    pre_main_declaration_list
    | pre_main_declaration pre_main_declaration_list
    ;

pre_main_declaration_list:
    function_declaration
    | pre_main_const_declaration
    | pre_main_variable_declaration
    ;
    
pre_main_const_declaration:
    CONST type ID '=' const_list ';'
    {
        current_declaration_type = $2;
        insert_symbol($3, $2, IS_CONST, NOT_FUNCTION, -1, IS_GLOBAL); // Add constant to global scope
        Symbol* sym = lookup_symbol($3);
        switch (sym->type) {
            case TYPE_INT:
                sym->value.ivalue = $5->value.ivalue;
                break;
            case TYPE_FLOAT:
                sym->value.fvalue = $5->value.fvalue;
                break;
            case TYPE_BOOL:
                sym->value.bvalue = $5->value.bvalue;
                break;
            case TYPE_STRING:
                sym->value.svalue = strdup($5->value.svalue);
                break;
            default:
                fprintf(stderr, "Error: Unsupported constant type at line %d\n", yylineno);
                YYERROR;
        }
    }
    ;

const_list:
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
        $$->value.svalue = $1;
    }|
    TRUE_TOKEN{
        $$ = create_expr_node(TYPE_BOOL);
        $$->value.bvalue = 1;
    }|
    FALSE_TOKEN{
        $$ = create_expr_node(TYPE_BOOL);
        $$->value.bvalue = 0;
    };


pre_main_variable_declaration:
    type
    premain_identifier_list ';'
    {
        current_declaration_type = $1;
    }
    ;


premain_identifier_list:
    premain_identifier_decl
    | premain_identifier_decl ',' premain_identifier_list
    ;

premain_identifier_decl:
    ID
    {
        insert_symbol($1, current_declaration_type, NOT_CONST, NOT_FUNCTION, -1,IS_GLOBAL); // Add variable to global scope
        // Generate appropriate field type
        const char* java_type;
        switch(current_declaration_type) {
            case TYPE_INT: java_type = "int"; break;
            case TYPE_FLOAT: java_type = "float"; break;
            case TYPE_BOOL: java_type = "int"; break;
            //case TYPE_STRING: java_type = "Ljava/lang/String;"; break;
            default: java_type = "I"; break;
        }
        fprintf(output_file, "field static %s %s\n", java_type, $1);
    }|
    ID '=' expression
    {
        insert_symbol($1, current_declaration_type, NOT_CONST, NOT_FUNCTION,-1,IS_GLOBAL); // Add variable to function scope
        if($3!=NULL&&!is_assignment_compatible(current_declaration_type, $3->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($3->type),type_to_string(current_declaration_type), yylineno);
            YYERROR;
        }else{
            Symbol* sym = lookup_symbol($1);
            if (sym->type == TYPE_INT) {
                sym->value.ivalue = $3->value.ivalue;
                fprintf(output_file, "field static int %s = %d\n",sym->name, $3->value.ivalue);
            } else if (sym->type == TYPE_FLOAT) {
                sym->value.fvalue = $3->value.fvalue;
                fprintf(output_file, "field static float %s = %f\n",sym->name, $3->value.fvalue);
            } else if (sym->type == TYPE_BOOL) {
                sym->value.bvalue = $3->value.bvalue;
                fprintf(output_file, "field static int %s = %d\n",sym->name, $3->value.ivalue);
            } else if (sym->type == TYPE_STRING) {
                sym->value.svalue = strdup($3->value.svalue);
                fprintf(output_file, "field static java.lang.String %s = \"%s\"\n",sym->name, $3->value.svalue);
            }
        }
        free_expr_node($3);
    }
    ;


function_declaration:
    type ID 
    
    '(' 
    {
        current_function_name = strdup($2);
        insert_symbol($2, $1, IS_CONST, IS_FUNCTION, -1,IS_GLOBAL);
        enter_new_table(1,0,0);
        fprintf(output_file,"method public static %s %s(", type_to_string($1), $2);
    }
    parameter_list ')' 
    {
        has_return = 0; // Reset return flag for this function
        Symbol* sym = lookup_symbol($2);
        for(int i=0;i<sym->function_signature.param_count;i++) {
            if(i > 0) fprintf(output_file, ", ");
            switch(sym->function_signature.param_types[i]) {
                case TYPE_INT:
                    fprintf(output_file, "int");
                    break;
                case TYPE_FLOAT:
                    fprintf(output_file, "float");
                    break;
                case TYPE_BOOL:
                    fprintf(output_file, "int");
                    break;
                case TYPE_STRING:
                    fprintf(output_file, "java.lang.String");
                    break;
                default:
                    fprintf(stderr, "Error: Unsupported parameter type at line %d\n", yylineno);
                    YYERROR;
            }
        }
        current_function_return_type = $1;
        fprintf(output_file,")\n");
        fprintf(output_file,"max_stack 15\n");
        fprintf(output_file,"max_locals 15\n");
        fprintf(output_file,"{\n");

        currently_in_method=1;
    }block 
    
    {
        if(current_function_return_type != TYPE_VOID&&has_return==0) {
            fprintf(stderr, "Error: Function '%s' should return a value at line %d\n", current_function_name, yylineno);
            YYERROR;
        }
        if(current_function_return_type == TYPE_VOID&&has_return==0){
            fprintf(output_file,"return\n");
        }
        fprintf(output_file,"iconst_0\n");
        fprintf(output_file,"ireturn\n");
        fprintf(output_file,"}\n");

        free(current_function_name);
        current_function_name = NULL;
        currently_in_method=0;
        current_function_return_type = VOID; // Reset return type for next function

        has_return = 0; // Reset for next function
    }
    |
    type ID 
    
    '(' 
    {
        current_function_name = strdup($2);
        insert_symbol($2, $1, IS_CONST, IS_FUNCTION,-1,IS_GLOBAL);
        enter_new_table(1,0,0);
        fprintf(output_file,"method public static %s %s(", type_to_string($1), $2);
    } 
    ')' 
    {
        current_function_return_type = $1;
        has_return = 0; // Reset return flag for this function
        fprintf(output_file,")\n");
        fprintf(output_file,"max_stack 15\n");
        fprintf(output_file,"max_locals 15\n");
        fprintf(output_file,"{\n");
        currently_in_method=1;
    }
    block
    {
        fprintf(stderr,"has_return: %d\n", has_return);
        if(current_function_return_type == TYPE_VOID&&has_return==0){
            fprintf(output_file,"return\n");
        }
        if(current_function_return_type != TYPE_VOID&&has_return==0) {
            fprintf(stderr, "Error: Function '%s' should return a value at line %d\n", current_function_name, yylineno);
            YYERROR;
        }
        fprintf(output_file,"iconst_0\n");
        fprintf(output_file,"ireturn\n");
        fprintf(output_file,"}\n");

        free(current_function_name);
        current_function_name = NULL;
        currently_in_method=0;
        has_return = 0; // Reset for next function
        current_function_return_type = VOID; // Reset return type for next function
    }
    ;

parameter_list:
    type ID
    {
        insert_symbol($2, $1, NOT_CONST, NOT_FUNCTION,current_table->local_label,NOT_GLOBAL); // Add parameter to function scope
        current_table->local_label++;
        Symbol* func=lookup_symbol(current_function_name);
        func->function_signature.param_types[func->function_signature.param_count] = $1; // Store parameter type 
        func->function_signature.param_count ++;
    }|
    type ID 
    {
        insert_symbol($2, $1, NOT_CONST, NOT_FUNCTION,current_table->local_label,NOT_GLOBAL); 
        current_table->local_label++;
        Symbol* func=lookup_symbol(current_function_name);
        func->function_signature.param_types[func->function_signature.param_count] = $1; // Store parameter type 
        func->function_signature.param_count ++;
        
    }
    ',' parameter_list
    ;


main_function_declaration:
    VOID MAIN 
    {
        current_function_return_type = TYPE_VOID;
        current_function_name = strdup("main");
        currently_in_method=1;
        insert_symbol("main", TYPE_VOID, IS_CONST, IS_FUNCTION,-1,IS_GLOBAL);
        fprintf(output_file,"method public static void main(java.lang.String[])\n");
        fprintf(output_file,"max_stack 15\n");
        fprintf(output_file,"max_locals 15\n");
        fprintf(output_file,"{\n");
    }
    '('
    {
        enter_new_table(1,0,0); // Enter function scope
    }
    ')' block
    {
        fprintf(output_file,"return\n");
        free(current_function_name);
        current_function_name = NULL;
        fprintf(output_file,"}\n");
        currently_in_method=0;
    }
    ;

const_declaration:
    CONST type ID '=' const_list ';'
    {
        current_declaration_type = $2;
        insert_symbol($3, $2, IS_CONST, NOT_FUNCTION, -1, NOT_GLOBAL); // Add constant to global scope
        Symbol* sym = lookup_symbol($3);
        switch (sym->type) {
            case TYPE_INT:
                sym->value.ivalue = $5->value.ivalue;
                break;
            case TYPE_FLOAT:
                sym->value.fvalue = $5->value.fvalue;
                break;
            case TYPE_BOOL:
                sym->value.bvalue = $5->value.bvalue;
                break;
            case TYPE_STRING:
                sym->value.svalue = strdup($5->value.svalue);
                break;
            default:
                fprintf(stderr, "Error: Unsupported constant type at line %d\n", yylineno);
                YYERROR;
        }
    }   
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
        insert_symbol($1, current_declaration_type, NOT_CONST, NOT_FUNCTION, current_table->local_label,NOT_GLOBAL);
        current_table->local_label++;
    }|
    ID '=' expression
    {
        insert_symbol($1, current_declaration_type, NOT_CONST, NOT_FUNCTION, current_table->local_label,NOT_GLOBAL);
        current_table->local_label++;
        if($3 != NULL && !is_assignment_compatible(current_declaration_type, $3->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", 
                   type_to_string($3->type), type_to_string(current_declaration_type), yylineno);
            YYERROR;
        } else {
            Symbol* sym = lookup_symbol($1);
            if (sym->type == TYPE_INT) {
                sym->value.ivalue = $3->value.ivalue;
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_FLOAT) {
                sym->value.fvalue = $3->value.fvalue;
                fprintf(output_file, "fstore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_BOOL) {
                sym->value.bvalue = $3->value.bvalue;
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_STRING) {
                sym->value.svalue = strdup($3->value.svalue);
                fprintf(output_file, "astore %d\n", sym->variable_label);
            }
        }
        free_expr_node($3);
    };

array_declaration:
    type 
    ID 
    {
        current_declaration_type = $1;
    }
    array_size_or_location 
    {
        for(int i=0;i<$4;i++) {
            char buffer[256];
            sprintf(buffer, "%s[%d]", $2, i);
            insert_symbol(buffer, TYPE_ARRAY, NOT_CONST, NOT_FUNCTION,current_table->local_label,NOT_GLOBAL);
            Symbol* sym = lookup_symbol($2);
            sym->typeinfo.location = i; // Set array size
            sym->typeinfo.basetype = $1;
            current_table->local_label++;
        }
    }';'
    ;

array_size_or_location:
    '[' expression ']'
    {
        if($2->type != TYPE_INT) {
            fprintf(stderr, "Error: Array size/location must be an integer at line %d\n", yylineno);
            YYERROR;
        }
        if($2->value.ivalue <= 0) {
            fprintf(stderr, "Error: Array size/location must be greater than 0 at line %d\n", yylineno);
            YYERROR;
        }
        $$ = $2->value.ivalue; // Store the size/location expression
        free_expr_node($2);
    }|
    '[' expression ']' array_size_or_location
    {
        if($2->type != TYPE_INT) {
            fprintf(stderr, "Error: Array size/location must be an integer at line %d\n", yylineno);
            YYERROR;
        }
        if($2->value.ivalue <= 0) {
            fprintf(stderr, "Error: Array size/location must be greater than 0 at line %d\n", yylineno);
            YYERROR;
        }
        $$ = $2->value.ivalue*$4; // Multiply sizes if nested
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
    '{' statement_list '}'
    {
        dump_current_table();
        leave_table();
    }
    |
    '{' '}'
    {
        dump_current_table();
        leave_table();
    };

statement_list:
    statement|
    statement_list statement 
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
    increment_decrement_statement ';'|
     ';'|
    arithmetic_statement ';';

simple_statment_without_semicolon:
    variable_assignment|
    print_statement|
    read_statement|
    increment_decrement_statement|
    arithmetic_statement;

arithmetic_statement:
    ID PLUS_EQUAL
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
            fprintf(stderr, "Error: Cannot perform arithmetic on non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        fprintf(output_file, "iload %d\n", sym->variable_label);
    } expression
    {
        Symbol* sym = lookup_symbol($1);
        if($4!=NULL&&!is_assignment_compatible(sym->type, $4->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($4->type), type_to_string(sym->type), yylineno);
            YYERROR;
        } else {
            if (sym->type == TYPE_INT) {
                fprintf(output_file, "iadd\n");
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_FLOAT) {
                fprintf(output_file, "fadd\n");
                fprintf(output_file, "fstore %d\n", sym->variable_label);  // Use fstore for float
            }
        }
        free_expr_node($4);
    }|
    ID MINUS_EQUAL 
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
            fprintf(stderr, "Error: Cannot perform arithmetic on non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        fprintf(output_file, "iload %d\n", sym->variable_label);
    }
    expression
    {
        Symbol* sym = lookup_symbol($1);
        if($4!=NULL&&!is_assignment_compatible(sym->type, $4->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($4->type), type_to_string(sym->type), yylineno);
            YYERROR;
        } else {
            if (sym->type == TYPE_INT) {
                fprintf(output_file, "isub\n");
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_FLOAT) {
                fprintf(output_file, "fsub\n");
                fprintf(output_file, "fstore %d\n", sym->variable_label);  // Use fstore for float
            }
        }
        free_expr_node($4);
    }|
    ID STAR_EQUAL 
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
            fprintf(stderr, "Error: Cannot perform arithmetic on non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        fprintf(output_file, "iload %d\n", sym->variable_label);
    }
    expression
    {
        Symbol* sym = lookup_symbol($1);
        if($4!=NULL&&!is_assignment_compatible(sym->type, $4->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($4->type), type_to_string(sym->type), yylineno);
            YYERROR;
        } else {
            if (sym->type == TYPE_INT) {
                fprintf(output_file, "imul\n");
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_FLOAT) {
                fprintf(output_file, "fmul\n");
                fprintf(output_file, "fstore %d\n", sym->variable_label);  // Use fstore for float
            }
        }
        free_expr_node($4);
    }|
    ID SLASH_EQUAL 
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
            fprintf(stderr, "Error: Cannot perform arithmetic on non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        fprintf(output_file, "iload %d\n", sym->variable_label);
    }
    expression
    {
        Symbol* sym = lookup_symbol($1);
        if($4!=NULL&&!is_assignment_compatible(sym->type, $4->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($4->type), type_to_string(sym->type), yylineno);
            YYERROR;
        } else {
            if (sym->type == TYPE_INT) {
                fprintf(output_file, "idiv\n");
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_FLOAT) {
                fprintf(output_file, "fdiv\n");
                fprintf(output_file, "fstore %d\n", sym->variable_label);  // Use fstore for float
            }
        }
        free_expr_node($4);
    }|
    ID PERCENT_EQUAL 
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
            fprintf(stderr, "Error: Cannot perform arithmetic on non-numeric type '%s' at line %d\n", $1, yylineno);
            YYERROR;
        }
        fprintf(output_file, "iload %d\n", sym->variable_label);
    }
    expression
    {
        Symbol* sym = lookup_symbol($1);
        if($4!=NULL&&!is_assignment_compatible(sym->type, $4->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string($4->type), type_to_string(sym->type), yylineno);
            YYERROR;
        } else {
            if (sym->type == TYPE_INT) {
                fprintf(output_file, "irem\n");
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_FLOAT) {
                fprintf(output_file, "frem\n");
                fprintf(output_file, "fstore %d\n", sym->variable_label);  // Use fstore for float
            }
        }
        free_expr_node($4);
    };
    

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
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", 
                   type_to_string($3->type), type_to_string(sym->type), yylineno);
            YYERROR;
        } else {
            if (sym->type == TYPE_INT) {
                sym->value.ivalue = $3->value.ivalue;
                if(sym->is_global == 1) {
                    fprintf(output_file, "putstatic int %s.%s\n",classname, sym->name);
                } else {
                    fprintf(output_file, "istore %d\n", sym->variable_label);
                }
            } else if (sym->type == TYPE_FLOAT) {
                sym->value.fvalue = $3->value.fvalue;
                if(sym->is_global == 1) {
                    fprintf(output_file, "putstatic float %s.%s\n",classname, sym->name);
                } else {
                    fprintf(output_file, "fstore %d\n", sym->variable_label);  // Use fstore for float
                }
            } else if (sym->type == TYPE_BOOL) {
                sym->value.bvalue = $3->value.bvalue;
                if(sym->is_global == 1) {
                    fprintf(output_file, "putstatic int %s.%s\n",classname, sym->name);
                } else {
                    fprintf(output_file, "istore %d\n", sym->variable_label);
                }
            } else if (sym->type == TYPE_STRING) {
                if (sym->value.svalue) free(sym->value.svalue);  // Free old string
                sym->value.svalue = strdup($3->value.svalue);
                if(sym->is_global == 1) {
                    fprintf(output_file, "putstatic java/lang/String %s.%s\n",classname, sym->name);
                } else {
                    fprintf(output_file, "astore %d\n", sym->variable_label);
                }
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
        if(sym->function_signature.param_count != $3->param_count) {
            fprintf(stderr, "Error: Function '%s' expects %d parameters but got %d at line %d\n", 
                   $1, sym->function_signature.param_count, $3->param_count, yylineno);
            YYERROR;
        }
        for(int i=0;i<sym->function_signature.param_count;i++) {
            if(sym->function_signature.param_types[i] != $3->param_types[i]) {
                fprintf(stderr, "Error: Function '%s' expects parameter %d to be of type %s but got %s at line %d\n", 
                       $1, i+1, type_to_string(sym->function_signature.param_types[i]), type_to_string($3->param_types[i]), yylineno);
                YYERROR;
            }
        }
        $$= create_expr_node(sym->type);
        if(currently_in_method){
            fprintf(output_file, "invokestatic %s %s.%s(",type_to_string(sym->type),classname, sym->name);
            for(int i=0;i<sym->function_signature.param_count;i++) {
                if(i > 0) fprintf(output_file, ", ");
                switch(sym->function_signature.param_types[i]) {
                    case TYPE_INT:
                        fprintf(output_file, "int");
                        break;
                    case TYPE_FLOAT:
                        fprintf(output_file, "float");
                        break;
                    case TYPE_BOOL:
                        fprintf(output_file, "int");
                        break;
                    case TYPE_STRING:
                        fprintf(output_file, "java.lang.String");
                        break;
                    default:
                        fprintf(stderr, "Error: Unsupported parameter type at line %d\n", yylineno);
                        YYERROR;
                }
            }
            fprintf(output_file, ")\n");
        }
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
        if(sym->function_signature.param_count != 0) {
            fprintf(stderr, "Error: Function '%s' expects %d parameters but got 0 at line %d\n", 
                   $1, sym->function_signature.param_count, yylineno);
            YYERROR;
        }
        if(currently_in_method){
            fprintf(output_file, "invokestatic %s %s.%s()\n",type_to_string(sym->type),classname, sym->name);
        }
        $$= create_expr_node(sym->type);
        
    };

argument_list:
    expression
    {
        $$ = create_function_signature($1->type); // Create a new function signature
        $$->param_types[0] = $1->type; // Store type of this argument
        $$->param_count = 1; // Initialize count to 1
        free_expr_node($1); // Free the expression node after storing its type
    }|
    expression ',' argument_list
    {
        $$=$3;
        $$->param_types[$$->param_count] = $1->type; // Store type of this argument
        $$->param_count++;
        free_expr_node($1); // Free the expression node after storing its type
    }
    ;

conditional_statement:
    IF if_false_label if_exit_label '(' expression ')' 
      {
          fprintf(output_file, "ifeq L%d\n", $2);
          enter_new_table(0,0,current_table->local_label);
      }
      if_statement
      {    
        fprintf(output_file, "goto L%d\n", $3);
        fprintf(output_file,"L%d:\n", $2);
        fprintf(output_file, "nop\n");
      }
      else_statement
      {
        fprintf(output_file, "L%d:\n", $3); // Jump to end if no else 
      }
;

else_statement:
    ELSE if_exit_label
    {
        enter_new_table(0,0,current_table->local_label);
    }
    if_statement
    {
        $$=1;
    }
    | /*nothing*/
    {
        $$=0;
    };

if_false_label:
     {
        $$=assembly_label;
        assembly_label++;
    }

if_exit_label:
     {
        $$=assembly_label;
        assembly_label++;
    }

if_statement:
    statement
    {dump_current_table();leave_table();}|
    
    block;

loop_statement:
    WHILE  '(' loop_boolean_point loop_exe_point loop_exit_point
    {
        enter_new_table(0,0,current_table->local_label); // Enter loop scope
        fprintf(output_file, "L%d:\n", $3); //mark loop start
    }
    expression
    {
        fprintf(output_file, "ifeq L%d\n", $5); //goto end if condition is false
        if ($7->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in while loop must be boolean at line %d\n", yylineno);
            YYERROR;
        }
    }
    ')' if_statement
    {
        fprintf(output_file, "goto L%d\n", $3); //goto boolean point
        fprintf(output_file, "L%d:\n", $5); // mark loop end
        inside_loop--;
    }|
    FOR loop_boolean_point loop_statement_point loop_exe_point loop_exit_point
    {
        inside_loop++;
        enter_new_table(0,0,current_table->local_label);
    }
    '(' simple_statment
    {
        fprintf(output_file, "L%d:\n", $2);// mark boolean point (loop start)
    }  
    expression
    {
        if ($10->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in while loop must be boolean at line %d\n", yylineno);
            YYERROR;
        }
        fprintf(output_file, "ifeq L%d\n", $5); // Jump to end if condition is false
        fprintf(output_file, "goto L%d\n", $4); //jump to loop body
    } 
    ';' 
    {
        fprintf(output_file, "L%d:\n", $3); // mark statement point
    }
     simple_statment_without_semicolon
    {
        fprintf(output_file, "goto L%d\n", $2); //jump to boolean point
        fprintf(output_file, "L%d:\n", $4); //mark exe point
    }
    ')'   if_statement
    {
        fprintf(output_file, "goto L%d\n", $3); // jump to statement point
        fprintf(output_file, "L%d:\n", $5); // Mark loop end
        inside_loop--;
    }|
    FOREACH '(' ID ':' expression loop_boolean_point loop_exit_point
    {
        Symbol* sym = lookup_symbol($3);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' doesn't exist %d\n", $3, yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot use constant '%s' in foreach loop at line %d\n", sym->name, yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT) {
            fprintf(stderr, "Error: Foreach loop variable '%s' must be int %d\n", sym->name, yylineno);
            YYERROR;
        }
        fprintf(output_file, "istore %d\n", sym->variable_label);
        sym->value.ivalue = $5->value.ivalue;
        fprintf(output_file, "L%d:\n", $6); // mark boolean point (loop start)
    }
    DOT_DOT expression  ')'
    {
        inside_loop++;
        enter_new_table(0,0,current_table->local_label); // Enter loop scope
        Symbol* sym = lookup_symbol($3);
        if ($5->type != TYPE_INT || $10->type != TYPE_INT) {
            fprintf(stderr, "Error: Foreach loop range must be integers at line %d\n", yylineno);
            YYERROR;
        }
        
        fprintf(output_file, "iload %d\n", sym->variable_label);
        fprintf(stderr, "sym: %d exp: %d", sym->value.ivalue,$10->value.ivalue); // jump to end if variable >= end value
        if(sym->value.ivalue < $10->value.ivalue) {
            fprintf(output_file, "isub\n");
            fprintf(output_file, "iflt L%d\n", $7);
        } else if (sym->value.ivalue > $10->value.ivalue) {
            fprintf(output_file, "isub\n");
            fprintf(output_file, "ifgt L%d\n", $7);
        }else if (sym->value.ivalue == $10->value.ivalue) {
            fprintf(output_file, "goto L%d\n", $7);
        }
    } 
    if_statement
    {   
        Symbol* sym = lookup_symbol($3);
        if(sym->value.ivalue < $10->value.ivalue) {
            fprintf(output_file, "iload %d\n", sym->variable_label);
            fprintf(output_file, "sipush 1\n");
            fprintf(output_file, "iadd\n");
            fprintf(output_file, "istore %d\n", sym->variable_label);
        } else if (sym->value.ivalue > $10->value.ivalue) {
            fprintf(output_file, "iload %d\n", sym->variable_label);
            fprintf(output_file, "sipush 1\n");
            fprintf(output_file, "isub\n");
            fprintf(output_file, "istore %d\n", sym->variable_label);
        }
        fprintf(output_file, "goto L%d\n", $6); // jump to boolean point
        fprintf(output_file, "L%d:\n", $7); // mark loop end
        inside_loop--;
        dump_current_table();
    };

loop_boolean_point:
     {
       $$=assembly_label;
        assembly_label++;
    };

loop_statement_point:
     {
       $$=assembly_label;
        assembly_label++;
    };

loop_exe_point:
{
       $$=assembly_label;
        assembly_label++;
};

loop_exit_point:
    {
        $$ = assembly_label;
        assembly_label++;
    }
;

print_statement:
    PRINT{
        fprintf(output_file, "getstatic java.io.PrintStream java.lang.System.out\n");
    } expression {
        if ($3->type == TYPE_INT) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.print(int)\n");
        } else if ($3->type == TYPE_FLOAT) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.print(float)\n");
        } else if ($3->type == TYPE_BOOL) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.print(int)\n");
        } else if ($3->type == TYPE_STRING) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.print(java.lang.String)\n");
        } else {
            fprintf(stderr, "Error: Cannot print type '%s' at line %d\n", type_to_string($3->type), yylineno);
            YYERROR;
        }
    }
    |
    PRINTLN{
        fprintf(output_file, "getstatic java.io.PrintStream java.lang.System.out\n");
    } expression{
        if ($3->type == TYPE_INT) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(int)\n");
        } else if ($3->type == TYPE_FLOAT) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(float)\n");
        } else if ($3->type == TYPE_BOOL) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(int)\n");
        } else if ($3->type == TYPE_STRING) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(java.lang.String)\n");
        } else {
            fprintf(stderr, "Error: Cannot print type '%s' at line %d\n", type_to_string($3->type), yylineno);
            YYERROR;
        }
    } ;

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
        if(sym->is_global == 1) {
            fprintf(output_file, "getstatic %s.%s\n", classname, $1);
        } else {
            fprintf(output_file, "iload %d\n", sym->variable_label);
        }
        if (sym->type == TYPE_INT) {
            fprintf(output_file, "sipush 1\n");
            fprintf(output_file, "iadd\n");
        } else if (sym->type == TYPE_FLOAT) {
            fprintf(output_file, "fconst_1\n");
            fprintf(output_file, "fadd\n");
        } 
        fprintf(output_file, "istore %d\n",sym->variable_label);
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
        if(sym->is_global == 1) {
            fprintf(output_file, "getstatic %s.%s\n", classname, $1);
        } else {
            fprintf(output_file, "iload %d\n", sym->variable_label);
        }
        if (sym->type == TYPE_INT) {
            fprintf(output_file, "sipush 1\n");
            fprintf(output_file, "isub\n");
        } else if (sym->type == TYPE_FLOAT) {
            fprintf(output_file, "fconst_1\n");
            fprintf(output_file, "fsub\n");
        } 
        fprintf(output_file, "istore %d\n",sym->variable_label);
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
        if ($2->type != current_function_return_type) {
            // If types don't match, report an error
            fprintf(stderr, "Error: Cannot return %s from function returning %s at line %d\n",
                   type_to_string($2->type), type_to_string(current_function_return_type), yylineno);
            YYERROR;
        }
        has_return = 1; // Mark that this function has a return statement
        fprintf(output_file, "ireturn\n");

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
        has_return = 1; // Mark that this function has a return statement
        fprintf(output_file, "return\n");
    };

    


expression:
    expression EQUAL expression
    {
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_equal));
        $$->value.bvalue = $1->value.bvalue == $3->value.bvalue;
        if(currently_in_method){
            fprintf(output_file, "isub\n");
            fprintf(output_file, "ifeq L%d\n", assembly_label);
            fprintf(output_file, "iconst_0\n");
            fprintf(output_file, "goto L%d\n", assembly_label+1);
            fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
            assembly_label++;
            fprintf(output_file, "L%d:\n", assembly_label);
            assembly_label++;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression NOT_EQUAL expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_not_equal));
        $$->value.bvalue = $1->value.bvalue != $3->value.bvalue;
        if(currently_in_method){
            fprintf(output_file, "isub\n");
            fprintf(output_file, "ifne L%d\n", assembly_label);
            fprintf(output_file, "iconst_0\n");
            fprintf(output_file, "goto L%d\n", assembly_label+1);
            fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
            assembly_label++;
            fprintf(output_file, "L%d:\n", assembly_label);
            assembly_label++;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression '<' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_less));
        if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
            $$->value.bvalue = $1->value.ivalue < $3->value.ivalue;
        } else if ($1->type == TYPE_FLOAT || $3->type == TYPE_FLOAT) {
            float left = ($1->type == TYPE_FLOAT) ? $1->value.fvalue : (float)$1->value.ivalue;
            float right = ($3->type == TYPE_FLOAT) ? $3->value.fvalue : (float)$3->value.ivalue;
            $$->value.bvalue = left < right;
        } else {
            $$->value.bvalue = 0;  // Default for other types
        }
        if(currently_in_method){
            fprintf(output_file, "isub\n");
            fprintf(output_file, "iflt L%d\n", assembly_label);
            fprintf(output_file, "iconst_0\n");
            fprintf(output_file, "goto L%d\n", assembly_label+1);
            fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
            assembly_label++;
            fprintf(output_file, "L%d:\n", assembly_label);
            assembly_label++;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression '>' expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_greater));
        $$->value.bvalue = $1->value.bvalue > $3->value.bvalue;
        if(currently_in_method){
            fprintf(output_file, "isub\n");
            fprintf(output_file, "ifgt L%d\n", assembly_label);
            fprintf(output_file, "iconst_0\n");
            fprintf(output_file, "goto L%d\n", assembly_label+1);
            fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
            assembly_label++;
            fprintf(output_file, "L%d:\n", assembly_label);
            assembly_label++;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression LESS_EQUAL expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_less_equal));
        $$->value.bvalue = $1->value.bvalue <= $3->value.bvalue;
        if(currently_in_method){
            fprintf(output_file, "isub\n");
            fprintf(output_file, "ifle L%d\n", assembly_label);
            fprintf(output_file, "iconst_0\n");
            fprintf(output_file, "goto L%d\n", assembly_label+1);
            fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
            assembly_label++;
            fprintf(output_file, "L%d:\n", assembly_label);
            assembly_label++;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression GREATER_EQUAL expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_greater_equal));
        $$->value.bvalue = $1->value.bvalue >= $3->value.bvalue;
        if(currently_in_method){
            fprintf(output_file, "isub\n");
            fprintf(output_file, "ifge L%d\n", assembly_label);
            fprintf(output_file, "iconst_0\n");
            fprintf(output_file, "goto L%d\n", assembly_label+1);
            fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
            assembly_label++;
            fprintf(output_file, "L%d:\n", assembly_label);
            assembly_label++;
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression AND_AND expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_and));
        $$->value.bvalue = $1->value.bvalue && $3->value.bvalue;
        if(currently_in_method){
            fprintf(output_file, "iand\n");
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    expression OR_OR expression{
        $$ = create_expr_node(check_expression_type($1->type, $3->type, op_or));
        $$->value.bvalue = $1->value.bvalue || $3->value.bvalue;
        if(currently_in_method){
            fprintf(output_file, "ior\n");
        }
        free_expr_node($1);
        free_expr_node($3);
    }|
    '!' expression{
        $$ = create_expr_node(check_expression_type($2->type, TYPE_BOOL, op_not));
        $$->value.bvalue = !$2->value.bvalue;
        if(currently_in_method){
            fprintf(output_file, "ixor\n");
        }
        free_expr_node($2);
    }|
    INT_LITERAL{
        $$ = create_expr_node(TYPE_INT);
        $$->value.ivalue = $1;
        if(currently_in_method){
            fprintf(output_file, "sipush %d\n", $1);
        } 
    }|
    REAL_LITERAL{
        $$ = create_expr_node(TYPE_FLOAT);
        $$->value.fvalue = $1;
        if(currently_in_method){
            fprintf(output_file, "ldc %f\n", $1);
        }
    }|
    STRING_LITERAL{
        $$ = create_expr_node(TYPE_STRING);
        $$->value.svalue = strdup($1);
        if(currently_in_method){
            fprintf(output_file, "ldc \"%s\"\n", $1);
        }
    }|
    TRUE_TOKEN{
        $$ = create_expr_node(TYPE_BOOL);
        $$->value.bvalue = 1;
        if(currently_in_method){
            fprintf(output_file, "sipush 1\n");
        }
    }|
    FALSE_TOKEN{
        $$ = create_expr_node(TYPE_BOOL);
        $$->value.bvalue = 0;
        if(currently_in_method){
            fprintf(output_file, "sipush 0\n");
        }
    }|
    function_invocation{
        if ($1->type == TYPE_VOID) {
            fprintf(stderr, "Error: Function returns void at line %d\n", yylineno);
            YYERROR;
        }
        $$ = create_expr_node($1->type);
    }|
    ID{
        Symbol* sym = lookup_symbol($1);
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1, yylineno);
            YYERROR;
        }
        if(sym->is_function) {
            fprintf(stderr, "Error: '%s' is a function, not a variable at line %d\n", $1, yylineno);
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
        if(currently_in_method){
            if (sym->is_const) {
                switch (sym->type) {
                    case TYPE_INT:
                        fprintf(output_file, "sipush %d\n", sym->value.ivalue);
                        break;
                    case TYPE_FLOAT:
                        fprintf(output_file, "ldc %f\n", sym->value.fvalue);
                        break;
                    case TYPE_BOOL:
                        fprintf(output_file, "sipush %d\n", sym->value.bvalue);
                        break;
                    case TYPE_STRING:
                        fprintf(output_file, "ldc \"%s\"\n", sym->value.svalue);
                        break;
                    default:
                        yyerror("Unsupported constant type");
                        YYERROR;
                }
            }
            else if (sym->is_global == 1) {
                switch (sym->type) {
                    case TYPE_INT:
                        fprintf(output_file, "getstatic int %s.%s\n",classname, sym->name);
                        break;
                    case TYPE_FLOAT:
                        fprintf(output_file, "getstatic float %s.%s\n",classname, sym->name);
                        break;
                    case TYPE_BOOL:
                        fprintf(output_file, "getstatic int %s.%s\n",classname, sym->name);
                        break;
                    case TYPE_STRING:
                        fprintf(output_file, "getstatic java.lang.String %s.%s\n",classname, sym->name);
                        break;
                    default:
                        yyerror("Unsupported constant type");
                        YYERROR;
                }
                
            } else {
                switch (sym->type) {
                    case TYPE_INT:
                        fprintf(output_file, "iload %d\n", sym->variable_label);
                        break;
                    case TYPE_FLOAT:
                        fprintf(output_file, "fload %d\n", sym->variable_label);
                        break;
                    case TYPE_BOOL:
                        fprintf(output_file, "iload %d\n", sym->variable_label);
                        break;
                    case TYPE_STRING:
                        fprintf(output_file, "ldc \"%s\"\n", sym->value.svalue);
                        break;
                    default:
                        yyerror("Unsupported constant type");
                        YYERROR;
                }
            }
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
        if(currently_in_method){
            fprintf(output_file, "iadd\n");
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
        if(currently_in_method){
            fprintf(output_file, "isub\n");
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
        if(currently_in_method){
            fprintf(output_file, "imul\n");
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
        if ($3->value.ivalue == 0) {
            yyerror("Error: Division by zero");
            YYERROR;
        }
        if(currently_in_method){
            fprintf(output_file, "idiv\n");
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
        if ($3->value.ivalue == 0) {
            yyerror("Error: Division by zero");
            YYERROR;
        }
        if(currently_in_method){
            fprintf(output_file, "irem\n");
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
        if(currently_in_method){
            fprintf(output_file, "ineg\n");
        }
        free_expr_node($2);
    };
%%
int main(int argc, char** argv)  {
    printf("Starting parser...\n");

    extern int yydebug;
    extern FILE *yyin;
    yydebug = 0;
    
    char *input_file_name = argv[1];

    if (input_file_name[0] == '.' && (input_file_name[1] == '/' || input_file_name[1] == '\\')) {
        input_file_name += 2;
    }
    
    strncpy(classname, input_file_name, strlen(input_file_name) - 3);
    classname[strlen(input_file_name) - 3] = '\0'; // Remove .y extension

    char* dot = strrchr(classname, '.');
    if(dot && strcmp(dot, ".sd") == 0) {
        *dot = '\0'; 
    }

    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", input_file_name);
        return EXIT_FAILURE;
    }
    yyin = input_file;
    if (open_output_file(classname)==1){
        fclose(output_file);
        char jsm_filename[300];
        snprintf(jsm_filename, sizeof(jsm_filename), "%s.jasm", classname);
        remove(jsm_filename);
        return EXIT_FAILURE;
    }

    fprintf(output_file,"class %s \n{\n", classname);
    printf("%d: ", yylineno);
    current_table = enter_new_table(0,1,0);
    if(yyparse()==1) {
        fprintf(stderr, "Parsing failed.\n");
        fclose(input_file);
        fclose(output_file);
        char jsm_filename[300];
        snprintf(jsm_filename, sizeof(jsm_filename), "%s.jasm", classname);
        remove(jsm_filename);
        return EXIT_FAILURE;
    }
    dump_current_table();
    leave_table();
    printf("Parser finished.\n");
    fprintf(output_file,"}\n");
    fclose(output_file);
    return 0;
}