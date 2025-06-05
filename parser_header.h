
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yprojecty.tab.h"

extern int yylineno;
extern char* yytext;

int globel_symbol_label = 0;


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
    typedef struct FunctionSignature {
        DataType return_type;
        int param_count;
        DataType param_types[16]; // Array of parameter types
    }FunctionSignature;

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
        int variable_label;
        int is_const;
        int is_function;
        int is_global;
        FunctionSignature function_signature; // For function symbols
        struct Symbol *next;
    }Symbol;

    

    typedef struct SymbolTable{
        Symbol* symbols_list;
        struct SymbolTable* outer;
        int is_function;
        int is_global;
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

    SymbolTable* enter_new_table(int is_function_scope,int is_global_scope) {
        SymbolTable* new_table = (SymbolTable*)malloc(sizeof(SymbolTable));
        new_table->symbols_list = NULL;
        new_table->outer = current_table;
        new_table->is_function = is_function_scope;
        new_table->is_global = is_global_scope;
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
            int symbols_label = symbols->variable_label;
            
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
            printf(", label: %d", symbols_label);
            printf(", Global: %s", symbols->is_global ? "Yes" : "No");
            if (symbols->is_function) {
                printf(", param_count: %d", symbols->function_signature.param_count);
                for (int i = 0; i < symbols->function_signature.param_count; i++) {
                    printf(", param_type[%d]: %s", i, type_to_string(symbols->function_signature.param_types[i]));
                }
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
        
        // Free string values properly
        if (temp->type == TYPE_STRING && temp->value.svalue) {
            free(temp->value.svalue);
        }
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

    void insert_symbol(char* name, DataType type, int is_const, int is_function, int label,int is_global) {
        
         if (lookup_current_scope(name) != NULL) {
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
        new_symbol->variable_label = label;
        new_symbol->is_global = is_global;
        new_symbol->next = NULL;
        new_symbol->function_signature.param_count = 0; 
        
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
        op_or,
        op_not,
        error_op
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
            case '!': return op_not;
            default: return error_op; // Invalid operator
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
            default: return error_op; // Invalid operator
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
            case op_not:
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

    FILE* output_file;
    void open_output_file(char* filename) {
        char* output_filename = (char*)malloc(strlen(filename) + 7);
        snprintf(output_filename, strlen(filename) + 6, "%s.jasm", filename);
        output_file = fopen(output_filename, "w");
        if (output_file == NULL) {
            fprintf(stderr, "Error opening output file\n");
        exit(EXIT_FAILURE);
        }
    }

    char classname[256];
    int assembly_label = 0;
    int has_return = 0;