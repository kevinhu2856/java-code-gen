/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 ".\\yprojecty.y"

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

    void yyerror(const char *s) {
        fprintf(stderr, "Error: %s\n at line %d, near %s\n", s , yylineno, yytext);
    }
    typedef struct Symbol{
        char *name;
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
    char* current_function_name;
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
            printf("Symbol: %s, Type: %s, Line: %d", 
                  symbols->name, 
                  type_to_string(symbols->type), 
                  symbols->line);
            
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
    

#line 380 "yprojecty.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yprojecty.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BOOL = 3,                       /* BOOL  */
  YYSYMBOL_BREAK = 4,                      /* BREAK  */
  YYSYMBOL_CASE = 5,                       /* CASE  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_CONST = 7,                      /* CONST  */
  YYSYMBOL_CONTINUE = 8,                   /* CONTINUE  */
  YYSYMBOL_DEFAULT = 9,                    /* DEFAULT  */
  YYSYMBOL_DO = 10,                        /* DO  */
  YYSYMBOL_DOUBLE = 11,                    /* DOUBLE  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_EXTERN = 13,                    /* EXTERN  */
  YYSYMBOL_FALSE_TOKEN = 14,               /* FALSE_TOKEN  */
  YYSYMBOL_FLOAT = 15,                     /* FLOAT  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_FOREACH = 17,                   /* FOREACH  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_INT = 19,                       /* INT  */
  YYSYMBOL_PRINT = 20,                     /* PRINT  */
  YYSYMBOL_PRINTLN = 21,                   /* PRINTLN  */
  YYSYMBOL_READ = 22,                      /* READ  */
  YYSYMBOL_RETURN = 23,                    /* RETURN  */
  YYSYMBOL_STRING = 24,                    /* STRING  */
  YYSYMBOL_SWITCH = 25,                    /* SWITCH  */
  YYSYMBOL_TRUE_TOKEN = 26,                /* TRUE_TOKEN  */
  YYSYMBOL_VOID = 27,                      /* VOID  */
  YYSYMBOL_WHILE = 28,                     /* WHILE  */
  YYSYMBOL_INT_LITERAL = 29,               /* INT_LITERAL  */
  YYSYMBOL_REAL_LITERAL = 30,              /* REAL_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 31,            /* STRING_LITERAL  */
  YYSYMBOL_MAIN = 32,                      /* MAIN  */
  YYSYMBOL_PLUS_PLUS = 33,                 /* PLUS_PLUS  */
  YYSYMBOL_MINUS_MINUS = 34,               /* MINUS_MINUS  */
  YYSYMBOL_LESS_EQUAL = 35,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 36,             /* GREATER_EQUAL  */
  YYSYMBOL_EQUAL = 37,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 38,                 /* NOT_EQUAL  */
  YYSYMBOL_AND_AND = 39,                   /* AND_AND  */
  YYSYMBOL_OR_OR = 40,                     /* OR_OR  */
  YYSYMBOL_DOT_DOT = 41,                   /* DOT_DOT  */
  YYSYMBOL_42_ = 42,                       /* '!'  */
  YYSYMBOL_43_ = 43,                       /* '<'  */
  YYSYMBOL_44_ = 44,                       /* '>'  */
  YYSYMBOL_45_ = 45,                       /* '+'  */
  YYSYMBOL_46_ = 46,                       /* '-'  */
  YYSYMBOL_47_ = 47,                       /* '*'  */
  YYSYMBOL_48_ = 48,                       /* '/'  */
  YYSYMBOL_49_ = 49,                       /* '%'  */
  YYSYMBOL_UMINUS = 50,                    /* UMINUS  */
  YYSYMBOL_ID = 51,                        /* ID  */
  YYSYMBOL_52_ = 52,                       /* '('  */
  YYSYMBOL_53_ = 53,                       /* ')'  */
  YYSYMBOL_54_ = 54,                       /* ','  */
  YYSYMBOL_55_ = 55,                       /* ';'  */
  YYSYMBOL_56_ = 56,                       /* '='  */
  YYSYMBOL_57_ = 57,                       /* '['  */
  YYSYMBOL_58_ = 58,                       /* ']'  */
  YYSYMBOL_59_ = 59,                       /* '{'  */
  YYSYMBOL_60_ = 60,                       /* '}'  */
  YYSYMBOL_61_ = 61,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_program = 63,                   /* program  */
  YYSYMBOL_pre_main_declaration = 64,      /* pre_main_declaration  */
  YYSYMBOL_pre_main_declaration_list = 65, /* pre_main_declaration_list  */
  YYSYMBOL_function_declaration = 66,      /* function_declaration  */
  YYSYMBOL_67_1 = 67,                      /* $@1  */
  YYSYMBOL_68_2 = 68,                      /* $@2  */
  YYSYMBOL_69_3 = 69,                      /* $@3  */
  YYSYMBOL_70_4 = 70,                      /* $@4  */
  YYSYMBOL_parameter_list = 71,            /* parameter_list  */
  YYSYMBOL_72_5 = 72,                      /* $@5  */
  YYSYMBOL_main_function_declaration = 73, /* main_function_declaration  */
  YYSYMBOL_74_6 = 74,                      /* $@6  */
  YYSYMBOL_75_7 = 75,                      /* $@7  */
  YYSYMBOL_const_declaration = 76,         /* const_declaration  */
  YYSYMBOL_77_8 = 77,                      /* $@8  */
  YYSYMBOL_variable_declaration = 78,      /* variable_declaration  */
  YYSYMBOL_identifier_list = 79,           /* identifier_list  */
  YYSYMBOL_identifier_decl = 80,           /* identifier_decl  */
  YYSYMBOL_array_declaration = 81,         /* array_declaration  */
  YYSYMBOL_82_9 = 82,                      /* $@9  */
  YYSYMBOL_array_size_or_location = 83,    /* array_size_or_location  */
  YYSYMBOL_type = 84,                      /* type  */
  YYSYMBOL_block = 85,                     /* block  */
  YYSYMBOL_86_10 = 86,                     /* $@10  */
  YYSYMBOL_87_11 = 87,                     /* $@11  */
  YYSYMBOL_statement_list = 88,            /* statement_list  */
  YYSYMBOL_statement = 89,                 /* statement  */
  YYSYMBOL_simple_statment = 90,           /* simple_statment  */
  YYSYMBOL_simple_statment_without_semicolon = 91, /* simple_statment_without_semicolon  */
  YYSYMBOL_variable_assignment = 92,       /* variable_assignment  */
  YYSYMBOL_function_invocation = 93,       /* function_invocation  */
  YYSYMBOL_argument_list = 94,             /* argument_list  */
  YYSYMBOL_conditional_statement = 95,     /* conditional_statement  */
  YYSYMBOL_if_statement = 96,              /* if_statement  */
  YYSYMBOL_97_12 = 97,                     /* $@12  */
  YYSYMBOL_loop_statement = 98,            /* loop_statement  */
  YYSYMBOL_99_13 = 99,                     /* $@13  */
  YYSYMBOL_100_14 = 100,                   /* $@14  */
  YYSYMBOL_101_15 = 101,                   /* $@15  */
  YYSYMBOL_print_statement = 102,          /* print_statement  */
  YYSYMBOL_read_statement = 103,           /* read_statement  */
  YYSYMBOL_increment_decrement_statement = 104, /* increment_decrement_statement  */
  YYSYMBOL_return_statement = 105,         /* return_statement  */
  YYSYMBOL_bool_expression = 106,          /* bool_expression  */
  YYSYMBOL_expression = 107                /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   268

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  200

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,     2,     2,    49,     2,     2,
      52,    53,    47,    45,    54,    46,     2,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    55,
      43,    56,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,    60,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   343,   343,   347,   354,   355,   359,   360,   361,   371,
     375,   368,   389,   393,   386,   406,   411,   410,   420,   426,
     419,   438,   437,   445,   450,   450,   454,   458,   467,   465,
     475,   476,   480,   482,   484,   486,   488,   493,   492,   503,
     502,   512,   513,   517,   518,   519,   520,   521,   522,   523,
     524,   528,   529,   530,   531,   534,   535,   536,   537,   540,
     552,   566,   579,   594,   595,   600,   601,   604,   604,   607,
     611,   610,   619,   618,   627,   626,   646,   647,   651,   664,
     680,   696,   712,   730,   743,   756,   757,   758,   759,   760,
     761,   762,   763,   764,   765,   769,   770,   771,   772,   773,
     774,   775,   776,   777,   778,   779,   780,   781,   782,   783
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BOOL", "BREAK",
  "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE",
  "EXTERN", "FALSE_TOKEN", "FLOAT", "FOR", "FOREACH", "IF", "INT", "PRINT",
  "PRINTLN", "READ", "RETURN", "STRING", "SWITCH", "TRUE_TOKEN", "VOID",
  "WHILE", "INT_LITERAL", "REAL_LITERAL", "STRING_LITERAL", "MAIN",
  "PLUS_PLUS", "MINUS_MINUS", "LESS_EQUAL", "GREATER_EQUAL", "EQUAL",
  "NOT_EQUAL", "AND_AND", "OR_OR", "DOT_DOT", "'!'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "UMINUS", "ID", "'('", "')'", "','", "';'",
  "'='", "'['", "']'", "'{'", "'}'", "':'", "$accept", "program",
  "pre_main_declaration", "pre_main_declaration_list",
  "function_declaration", "$@1", "$@2", "$@3", "$@4", "parameter_list",
  "$@5", "main_function_declaration", "$@6", "$@7", "const_declaration",
  "$@8", "variable_declaration", "identifier_list", "identifier_decl",
  "array_declaration", "$@9", "array_size_or_location", "type", "block",
  "$@10", "$@11", "statement_list", "statement", "simple_statment",
  "simple_statment_without_semicolon", "variable_assignment",
  "function_invocation", "argument_list", "conditional_statement",
  "if_statement", "$@12", "loop_statement", "$@13", "$@14", "$@15",
  "print_statement", "read_statement", "increment_decrement_statement",
  "return_statement", "bool_expression", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-99)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-40)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      31,   -99,    24,   -99,   -99,   -99,   -18,    21,    31,   -99,
     -99,   -99,   -99,   -99,   -23,   -99,   -99,   -99,   -99,   -99,
     -99,    -3,     1,    -2,     9,    28,    39,   123,   -99,     9,
      48,    52,   -99,    24,    66,   -99,   -99,   -99,   -99,   -99,
     123,    65,   123,   -99,   203,   -99,   -99,    68,    73,    59,
     -99,   -99,    72,   123,   -99,   180,   123,   123,   123,   123,
     123,    69,   -99,    84,    69,   -99,    77,   170,   165,   -99,
      47,    47,   -99,   -99,   -99,    80,   -99,    69,    97,   -99,
     -99,   123,    99,    54,    98,   -99,    24,   -99,   -99,   -99,
     -99,   124,   123,   123,   109,    33,   -99,    57,   -99,   -99,
     -99,   126,   127,    54,   -99,   130,   144,   -99,   -99,   146,
     166,   167,   -99,   -99,   -99,   168,   179,   113,   203,   203,
     -99,   -99,   145,   192,   -99,   -99,   123,    11,   111,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,   -14,   181,   113,   113,
     -30,   160,   -99,   113,   203,   -99,   -99,   123,    99,   -16,
     113,   184,   -99,    76,   135,   113,   113,    69,   123,   123,
     123,   123,   123,   123,   108,   203,   191,   -20,   123,   -99,
     -99,   214,   -99,   242,    54,   203,   203,   203,   203,   203,
     203,    69,   -99,   -14,   189,    69,   -99,   -99,   202,   -99,
     -99,   -99,   -99,   123,   -99,    69,   194,   -99,    69,   -99
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    34,     0,    33,    32,    35,    36,     0,     0,     4,
       6,     3,     7,     8,     0,    36,    21,    18,     1,     5,
       2,    26,     0,    24,     0,     0,     9,     0,    23,     0,
      26,     0,    19,     0,     0,    99,    98,    95,    96,    97,
       0,   101,     0,   100,    27,    25,    22,     0,     0,     0,
      13,   109,     0,     0,   102,     0,     0,     0,     0,     0,
       0,     0,    10,    15,     0,    62,     0,    63,     0,   103,
     104,   105,   106,   107,   108,    37,    20,     0,     0,    14,
      61,     0,    30,     0,     0,    11,     0,    64,    31,    72,
      74,     0,     0,     0,     0,     0,    70,     0,    45,    44,
      46,     0,     0,    41,    43,     0,     0,    48,    49,     0,
       0,     0,    50,    40,    17,     0,     0,     0,    76,    77,
      78,    84,     0,     0,    79,    80,     0,     0,    26,    38,
      42,    51,    47,    52,    53,    54,     0,     0,     0,     0,
       0,     0,    83,     0,    59,    81,    82,     0,     0,     0,
       0,     0,    93,     0,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,    60,     0,     0,     0,    94,
      91,    92,    69,    66,     0,    89,    90,    85,    86,    87,
      88,    67,    29,     0,     0,    67,    68,    71,     0,    55,
      56,    57,    58,     0,    65,    67,     0,    73,    67,    75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -99,   -99,   -99,   248,   -99,   -99,   -99,   -99,   -99,   171,
     -99,   250,   -99,   -99,     4,   -99,    16,    82,   -99,   -99,
     -99,   -40,     3,   125,   -99,   -99,   156,    86,   128,   -99,
      78,   -81,   182,   -99,   -98,   -99,   -99,   -99,   -99,   -99,
      79,    83,    85,   -99,     7,   -27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    33,    77,    34,    64,    48,
      78,    11,    25,    47,    98,    24,    99,    22,    23,   100,
     148,   127,   101,   172,    83,    84,   102,   103,   104,   188,
     105,    43,    66,   107,   173,   174,   108,   123,   115,   116,
     109,   110,   111,   112,   140,   141
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,    54,   106,    14,    12,    16,    92,    93,    94,   155,
     156,    14,    12,    51,    17,    55,    13,   124,   125,   155,
     156,    18,   106,   157,    13,    67,    68,     1,    21,    70,
      71,    72,    73,    74,     1,   183,    49,   149,     2,     3,
     126,    53,    88,     4,   145,   146,     3,    35,     5,    26,
       4,    15,    29,    27,    67,     5,    28,     1,     6,    36,
      30,     2,    37,    38,    39,   118,   119,   147,   122,     3,
      89,    90,    91,     4,    92,    93,    94,    95,     5,    40,
      32,    15,    96,   187,    41,    42,    35,   194,   121,    49,
     124,   125,   -12,   106,    58,    59,    60,   197,    36,   144,
     199,    37,    38,    39,    27,    97,    31,    46,   166,    52,
      63,    45,   154,   126,    53,   155,   156,    52,    40,    50,
     165,    61,    53,    41,    42,    65,    62,    35,    75,   169,
      80,   175,   176,   177,   178,   179,   180,    35,   -16,    36,
     -39,   184,    37,    38,    39,   152,   153,   155,   156,    36,
     164,    86,    37,    38,    39,   138,    53,   167,   113,    40,
     120,   181,   170,   171,    41,   139,   196,    27,   -28,    40,
     158,   159,   160,   161,    41,    42,   117,   128,   162,   163,
      56,    57,    58,    59,    60,   131,    76,   129,    69,    79,
      56,    57,    58,    59,    60,   158,   159,   160,   161,   132,
     142,   133,    85,   162,   163,    56,    57,    58,    59,    60,
      56,    57,    58,    59,    60,    56,    57,    58,    59,    60,
     136,   134,   135,    82,    81,    56,    57,    58,    59,    60,
     193,   137,   151,    69,    56,    57,    58,    59,    60,    56,
      57,    58,    59,    60,   143,   168,   182,   198,    56,    57,
      58,    59,    60,   155,   185,   195,    19,   114,    20,   130,
     186,   189,   190,    87,   150,     0,   191,     0,   192
};

static const yytype_int16 yycheck[] =
{
      27,    41,    83,     0,     0,     2,    20,    21,    22,    39,
      40,     8,     8,    40,    32,    42,     0,    33,    34,    39,
      40,     0,   103,    53,     8,    52,    53,     3,    51,    56,
      57,    58,    59,    60,     3,    55,    33,    51,     7,    15,
      56,    57,    82,    19,    33,    34,    15,    14,    24,    52,
      19,    27,    54,    56,    81,    24,    55,     3,    27,    26,
      51,     7,    29,    30,    31,    92,    93,    56,    95,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    46,
      52,    27,    28,   181,    51,    52,    14,   185,    55,    86,
      33,    34,    53,   174,    47,    48,    49,   195,    26,   126,
     198,    29,    30,    31,    56,    51,    24,    55,   148,    52,
      51,    29,   139,    56,    57,    39,    40,    52,    46,    53,
     147,    53,    57,    51,    52,    53,    53,    14,    59,    53,
      53,   158,   159,   160,   161,   162,   163,    14,    54,    26,
      60,   168,    29,    30,    31,   138,   139,    39,    40,    26,
     143,    54,    29,    30,    31,    42,    57,   150,    60,    46,
      51,    53,   155,   156,    51,    52,   193,    56,    57,    46,
      35,    36,    37,    38,    51,    52,    52,    51,    43,    44,
      45,    46,    47,    48,    49,    55,    61,    60,    53,    64,
      45,    46,    47,    48,    49,    35,    36,    37,    38,    55,
      55,    55,    77,    43,    44,    45,    46,    47,    48,    49,
      45,    46,    47,    48,    49,    45,    46,    47,    48,    49,
      52,    55,    55,    58,    54,    45,    46,    47,    48,    49,
      41,    52,    51,    53,    45,    46,    47,    48,    49,    45,
      46,    47,    48,    49,    52,    61,    55,    53,    45,    46,
      47,    48,    49,    39,    12,    53,     8,    86,     8,   103,
     174,   183,   183,    81,   136,    -1,   183,    -1,   183
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,    15,    19,    24,    27,    63,    64,    65,
      66,    73,    76,    78,    84,    27,    84,    32,     0,    65,
      73,    51,    79,    80,    77,    74,    52,    56,    55,    54,
      51,    79,    52,    67,    69,    14,    26,    29,    30,    31,
      46,    51,    52,    93,   107,    79,    55,    75,    71,    84,
      53,   107,    52,    57,    83,   107,    45,    46,    47,    48,
      49,    53,    53,    51,    70,    53,    94,   107,   107,    53,
     107,   107,   107,   107,   107,    59,    85,    68,    72,    85,
      53,    54,    58,    86,    87,    85,    54,    94,    83,    16,
      17,    18,    20,    21,    22,    23,    28,    51,    76,    78,
      81,    84,    88,    89,    90,    92,    93,    95,    98,   102,
     103,   104,   105,    60,    71,   100,   101,    52,   107,   107,
      51,    55,   107,    99,    33,    34,    56,    83,    51,    60,
      88,    55,    55,    55,    55,    55,    52,    52,    42,    52,
     106,   107,    55,    52,   107,    33,    34,    56,    82,    51,
      90,    51,   106,   106,   107,    39,    40,    53,    35,    36,
      37,    38,    43,    44,   106,   107,    83,   106,    61,    53,
     106,   106,    85,    96,    97,   107,   107,   107,   107,   107,
     107,    53,    55,    55,   107,    12,    89,    96,    91,    92,
     102,   103,   104,    41,    96,    53,   107,    96,    53,    96
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    63,    64,    64,    65,    65,    65,    67,
      68,    66,    69,    70,    66,    71,    72,    71,    74,    75,
      73,    77,    76,    78,    79,    79,    80,    80,    82,    81,
      83,    83,    84,    84,    84,    84,    84,    86,    85,    87,
      85,    88,    88,    89,    89,    89,    89,    89,    89,    89,
      89,    90,    90,    90,    90,    91,    91,    91,    91,    92,
      92,    93,    93,    94,    94,    95,    95,    97,    96,    96,
      99,    98,   100,    98,   101,    98,   102,   102,   103,   104,
     104,   104,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     1,     1,     1,     0,
       0,     8,     0,     0,     7,     2,     0,     5,     0,     0,
       7,     0,     5,     3,     1,     3,     1,     3,     0,     5,
       3,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       3,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     3,
       4,     4,     3,     1,     3,     7,     5,     0,     2,     1,
       0,     6,     0,     9,     0,    10,     2,     2,     2,     2,
       2,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     3,     3,     3,     3,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: pre_main_declaration main_function_declaration  */
#line 344 ".\\yprojecty.y"
    {
        printf("Program parsed successfully.\n");
    }
#line 1901 "yprojecty.tab.c"
    break;

  case 3: /* program: main_function_declaration  */
#line 348 ".\\yprojecty.y"
    {
        printf("Program parsed successfully without pre main.\n");
    }
#line 1909 "yprojecty.tab.c"
    break;

  case 9: /* $@1: %empty  */
#line 371 ".\\yprojecty.y"
    {
        enter_new_table(1);
    }
#line 1917 "yprojecty.tab.c"
    break;

  case 10: /* $@2: %empty  */
#line 375 ".\\yprojecty.y"
    {
        current_function_return_type = (yyvsp[-5].dtype);
        current_function_name = strdup((yyvsp[-4].svalue));
        insert_symbol((yyvsp[-4].svalue), (yyvsp[-5].dtype), 0, 1);
    }
#line 1927 "yprojecty.tab.c"
    break;

  case 11: /* function_declaration: type ID '(' $@1 parameter_list ')' $@2 block  */
#line 381 ".\\yprojecty.y"
    {
        free(current_function_name);
        current_function_name = NULL;
    }
#line 1936 "yprojecty.tab.c"
    break;

  case 12: /* $@3: %empty  */
#line 389 ".\\yprojecty.y"
    {
        enter_new_table(1);
    }
#line 1944 "yprojecty.tab.c"
    break;

  case 13: /* $@4: %empty  */
#line 393 ".\\yprojecty.y"
    {
        current_function_return_type = (yyvsp[-4].dtype);
        current_function_name = strdup((yyvsp[-3].svalue));
        insert_symbol((yyvsp[-3].svalue), (yyvsp[-4].dtype), 0, 1);
    }
#line 1954 "yprojecty.tab.c"
    break;

  case 14: /* function_declaration: type ID '(' $@3 ')' $@4 block  */
#line 399 ".\\yprojecty.y"
    {
        free(current_function_name);
        current_function_name = NULL;
    }
#line 1963 "yprojecty.tab.c"
    break;

  case 15: /* parameter_list: type ID  */
#line 407 ".\\yprojecty.y"
    {
        insert_symbol((yyvsp[0].svalue), (yyvsp[-1].dtype), 0, 0); // Add parameter to function scope
    }
#line 1971 "yprojecty.tab.c"
    break;

  case 16: /* $@5: %empty  */
#line 411 ".\\yprojecty.y"
    {
        insert_symbol((yyvsp[0].svalue), (yyvsp[-1].dtype), 0, 0); // Add parameter to function scope
    }
#line 1979 "yprojecty.tab.c"
    break;

  case 18: /* $@6: %empty  */
#line 420 ".\\yprojecty.y"
    {
        current_function_return_type = TYPE_VOID;
        current_function_name = strdup("main");
        insert_symbol("main", TYPE_VOID, 0, 1);
    }
#line 1989 "yprojecty.tab.c"
    break;

  case 19: /* $@7: %empty  */
#line 426 ".\\yprojecty.y"
    {
        enter_new_table(1); // Enter function scope
    }
#line 1997 "yprojecty.tab.c"
    break;

  case 20: /* main_function_declaration: VOID MAIN $@6 '(' $@7 ')' block  */
#line 430 ".\\yprojecty.y"
     {
        free(current_function_name);
        current_function_name = NULL;
    }
#line 2006 "yprojecty.tab.c"
    break;

  case 21: /* $@8: %empty  */
#line 438 ".\\yprojecty.y"
    {
        current_declaration_type = (yyvsp[0].dtype);
    }
#line 2014 "yprojecty.tab.c"
    break;

  case 26: /* identifier_decl: ID  */
#line 455 ".\\yprojecty.y"
    {
        insert_symbol((yyvsp[0].svalue), current_declaration_type, 0, 0);
    }
#line 2022 "yprojecty.tab.c"
    break;

  case 27: /* identifier_decl: ID '=' expression  */
#line 459 ".\\yprojecty.y"
    {
        insert_symbol((yyvsp[-2].svalue), current_declaration_type, 0, 0);
    }
#line 2030 "yprojecty.tab.c"
    break;

  case 28: /* $@9: %empty  */
#line 467 ".\\yprojecty.y"
    {
        current_declaration_type = (yyvsp[-1].dtype);
        insert_symbol((yyvsp[0].svalue), TYPE_ARRAY, 0, 0); // Record as array type
    }
#line 2039 "yprojecty.tab.c"
    break;

  case 32: /* type: INT  */
#line 480 ".\\yprojecty.y"
        { (yyval.dtype) = TYPE_INT; current_declaration_type = TYPE_INT; }
#line 2045 "yprojecty.tab.c"
    break;

  case 33: /* type: FLOAT  */
#line 482 ".\\yprojecty.y"
          { (yyval.dtype) = TYPE_FLOAT; current_declaration_type = TYPE_FLOAT;}
#line 2051 "yprojecty.tab.c"
    break;

  case 34: /* type: BOOL  */
#line 484 ".\\yprojecty.y"
         { (yyval.dtype) = TYPE_BOOL; current_declaration_type = TYPE_BOOL;}
#line 2057 "yprojecty.tab.c"
    break;

  case 35: /* type: STRING  */
#line 486 ".\\yprojecty.y"
           { (yyval.dtype) = TYPE_STRING; current_declaration_type = TYPE_STRING;}
#line 2063 "yprojecty.tab.c"
    break;

  case 36: /* type: VOID  */
#line 488 ".\\yprojecty.y"
         { (yyval.dtype) = TYPE_VOID; current_declaration_type = TYPE_VOID;}
#line 2069 "yprojecty.tab.c"
    break;

  case 37: /* $@10: %empty  */
#line 493 ".\\yprojecty.y"
    {
        enter_new_table(0);
    }
#line 2077 "yprojecty.tab.c"
    break;

  case 38: /* block: '{' $@10 statement_list '}'  */
#line 497 ".\\yprojecty.y"
    {
        dump_current_table();
        leave_table();
    }
#line 2086 "yprojecty.tab.c"
    break;

  case 39: /* $@11: %empty  */
#line 503 ".\\yprojecty.y"
    {
        enter_new_table(0);
    }
#line 2094 "yprojecty.tab.c"
    break;

  case 40: /* block: '{' $@11 '}'  */
#line 506 ".\\yprojecty.y"
    {
        dump_current_table();
        leave_table();
    }
#line 2103 "yprojecty.tab.c"
    break;

  case 59: /* variable_assignment: ID '=' expression  */
#line 541 ".\\yprojecty.y"
    {
        Symbol* sym = lookup_symbol((yyvsp[-2].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot assign to constant '%s' at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
    }
#line 2119 "yprojecty.tab.c"
    break;

  case 60: /* variable_assignment: ID array_size_or_location '=' expression  */
#line 553 ".\\yprojecty.y"
    {
        Symbol* sym = lookup_symbol((yyvsp[-3].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[-3].svalue), yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_ARRAY) {
            fprintf(stderr, "Error: Variable '%s' is not an array at line %d\n", (yyvsp[-3].svalue), yylineno);
            YYERROR;
        }
    }
#line 2135 "yprojecty.tab.c"
    break;

  case 61: /* function_invocation: ID '(' argument_list ')'  */
#line 567 ".\\yprojecty.y"
    {
        Symbol* sym = lookup_symbol((yyvsp[-3].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Function '%s' not declared at line %d\n", (yyvsp[-3].svalue), yylineno);
            YYERROR;
        }
        if (!sym->is_function) {
            fprintf(stderr, "Error: '%s' is not a function at line %d\n", (yyvsp[-3].svalue), yylineno);
            YYERROR;
        }
        // Here we would check argument types and count
    }
#line 2152 "yprojecty.tab.c"
    break;

  case 62: /* function_invocation: ID '(' ')'  */
#line 580 ".\\yprojecty.y"
    {
        Symbol* sym = lookup_symbol((yyvsp[-2].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Function '%s' not declared at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
        if (!sym->is_function) {
            fprintf(stderr, "Error: '%s' is not a function at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
        // Check that function doesn't require arguments
    }
#line 2169 "yprojecty.tab.c"
    break;

  case 67: /* $@12: %empty  */
#line 604 ".\\yprojecty.y"
    {enter_new_table(0);}
#line 2175 "yprojecty.tab.c"
    break;

  case 68: /* if_statement: $@12 statement  */
#line 606 ".\\yprojecty.y"
    {dump_current_table();leave_table();}
#line 2181 "yprojecty.tab.c"
    break;

  case 70: /* $@13: %empty  */
#line 611 ".\\yprojecty.y"
    {
        inside_loop++;
    }
#line 2189 "yprojecty.tab.c"
    break;

  case 71: /* loop_statement: WHILE $@13 '(' bool_expression ')' if_statement  */
#line 615 ".\\yprojecty.y"
     {
        inside_loop--;
    }
#line 2197 "yprojecty.tab.c"
    break;

  case 72: /* $@14: %empty  */
#line 619 ".\\yprojecty.y"
    {
        inside_loop++;
    }
#line 2205 "yprojecty.tab.c"
    break;

  case 73: /* loop_statement: FOR $@14 '(' simple_statment bool_expression ';' simple_statment_without_semicolon ')' if_statement  */
#line 623 ".\\yprojecty.y"
    {
        inside_loop--;
    }
#line 2213 "yprojecty.tab.c"
    break;

  case 74: /* $@15: %empty  */
#line 627 ".\\yprojecty.y"
    {
        inside_loop++;
    }
#line 2221 "yprojecty.tab.c"
    break;

  case 75: /* loop_statement: FOREACH $@15 '(' ID ':' expression DOT_DOT expression ')' if_statement  */
#line 631 ".\\yprojecty.y"
    {
        inside_loop--;
        dump_current_table();
        leave_table();
        // Verify ID is declared and of compatible type with expressions
        Symbol* sym = lookup_symbol((yyvsp[-6].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[-6].svalue), yylineno);
            YYERROR;
        }
    }
#line 2237 "yprojecty.tab.c"
    break;

  case 78: /* read_statement: READ ID  */
#line 651 ".\\yprojecty.y"
            {
        Symbol* sym = lookup_symbol((yyvsp[0].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[0].svalue), yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot read into constant '%s' at line %d\n", (yyvsp[0].svalue), yylineno);
            YYERROR;
        }
    }
#line 2253 "yprojecty.tab.c"
    break;

  case 79: /* increment_decrement_statement: ID PLUS_PLUS  */
#line 665 ".\\yprojecty.y"
    {
        Symbol* sym = lookup_symbol((yyvsp[-1].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[-1].svalue), yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot modify constant '%s' at line %d\n", (yyvsp[-1].svalue), yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT && sym->type != TYPE_FLOAT) {
            fprintf(stderr, "Error: Cannot increment non-numeric type '%s' at line %d\n", (yyvsp[-1].svalue), yylineno);
            YYERROR;
        }
    }
#line 2273 "yprojecty.tab.c"
    break;

  case 80: /* increment_decrement_statement: ID MINUS_MINUS  */
#line 681 ".\\yprojecty.y"
    {
        Symbol* sym = lookup_symbol((yyvsp[-1].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[-1].svalue), yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot modify constant '%s' at line %d\n", (yyvsp[-1].svalue), yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT && sym->type != TYPE_FLOAT) {
            fprintf(stderr, "Error: Cannot increment non-numeric type '%s' at line %d\n", (yyvsp[-1].svalue), yylineno);
            YYERROR;
        }
    }
#line 2293 "yprojecty.tab.c"
    break;

  case 81: /* increment_decrement_statement: ID array_size_or_location PLUS_PLUS  */
#line 697 ".\\yprojecty.y"
    {
        Symbol* sym = lookup_symbol((yyvsp[-2].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot modify constant '%s' at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT && sym->type != TYPE_FLOAT) {
            fprintf(stderr, "Error: Cannot increment non-numeric type '%s' at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
    }
#line 2313 "yprojecty.tab.c"
    break;

  case 82: /* increment_decrement_statement: ID array_size_or_location MINUS_MINUS  */
#line 713 ".\\yprojecty.y"
    {
        Symbol* sym = lookup_symbol((yyvsp[-2].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
        if (sym->is_const) {
            fprintf(stderr, "Error: Cannot modify constant '%s' at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
        if (sym->type != TYPE_INT && sym->type != TYPE_FLOAT) {
            fprintf(stderr, "Error: Cannot increment non-numeric type '%s' at line %d\n", (yyvsp[-2].svalue), yylineno);
            YYERROR;
        }
    }
#line 2333 "yprojecty.tab.c"
    break;

  case 83: /* return_statement: RETURN expression ';'  */
#line 731 ".\\yprojecty.y"
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
    }
#line 2350 "yprojecty.tab.c"
    break;

  case 84: /* return_statement: RETURN ';'  */
#line 744 ".\\yprojecty.y"
    {
        if (current_function_name == NULL) {
            yyerror("Return statement outside of function");
            YYERROR;
        }
        if (current_function_return_type != TYPE_VOID) {
            yyerror("Non-void function must return a value");
            YYERROR;
        }
    }
#line 2365 "yprojecty.tab.c"
    break;

  case 85: /* bool_expression: expression EQUAL expression  */
#line 756 ".\\yprojecty.y"
                               {}
#line 2371 "yprojecty.tab.c"
    break;

  case 86: /* bool_expression: expression NOT_EQUAL expression  */
#line 757 ".\\yprojecty.y"
                                   {}
#line 2377 "yprojecty.tab.c"
    break;

  case 87: /* bool_expression: expression '<' expression  */
#line 758 ".\\yprojecty.y"
                             {}
#line 2383 "yprojecty.tab.c"
    break;

  case 88: /* bool_expression: expression '>' expression  */
#line 759 ".\\yprojecty.y"
                             {}
#line 2389 "yprojecty.tab.c"
    break;

  case 89: /* bool_expression: expression LESS_EQUAL expression  */
#line 760 ".\\yprojecty.y"
                                    {}
#line 2395 "yprojecty.tab.c"
    break;

  case 90: /* bool_expression: expression GREATER_EQUAL expression  */
#line 761 ".\\yprojecty.y"
                                       {}
#line 2401 "yprojecty.tab.c"
    break;

  case 91: /* bool_expression: bool_expression AND_AND bool_expression  */
#line 762 ".\\yprojecty.y"
                                           {}
#line 2407 "yprojecty.tab.c"
    break;

  case 92: /* bool_expression: bool_expression OR_OR bool_expression  */
#line 763 ".\\yprojecty.y"
                                         {}
#line 2413 "yprojecty.tab.c"
    break;

  case 93: /* bool_expression: '!' bool_expression  */
#line 764 ".\\yprojecty.y"
                       {}
#line 2419 "yprojecty.tab.c"
    break;

  case 94: /* bool_expression: '(' bool_expression ')'  */
#line 765 ".\\yprojecty.y"
                           {}
#line 2425 "yprojecty.tab.c"
    break;

  case 95: /* expression: INT_LITERAL  */
#line 769 ".\\yprojecty.y"
               {}
#line 2431 "yprojecty.tab.c"
    break;

  case 96: /* expression: REAL_LITERAL  */
#line 770 ".\\yprojecty.y"
                {}
#line 2437 "yprojecty.tab.c"
    break;

  case 97: /* expression: STRING_LITERAL  */
#line 771 ".\\yprojecty.y"
                  {}
#line 2443 "yprojecty.tab.c"
    break;

  case 98: /* expression: TRUE_TOKEN  */
#line 772 ".\\yprojecty.y"
              {}
#line 2449 "yprojecty.tab.c"
    break;

  case 99: /* expression: FALSE_TOKEN  */
#line 773 ".\\yprojecty.y"
               {}
#line 2455 "yprojecty.tab.c"
    break;

  case 100: /* expression: function_invocation  */
#line 774 ".\\yprojecty.y"
                       {}
#line 2461 "yprojecty.tab.c"
    break;

  case 101: /* expression: ID  */
#line 775 ".\\yprojecty.y"
      {}
#line 2467 "yprojecty.tab.c"
    break;

  case 102: /* expression: ID array_size_or_location  */
#line 776 ".\\yprojecty.y"
                             {}
#line 2473 "yprojecty.tab.c"
    break;

  case 103: /* expression: '(' expression ')'  */
#line 777 ".\\yprojecty.y"
                      {}
#line 2479 "yprojecty.tab.c"
    break;

  case 104: /* expression: expression '+' expression  */
#line 778 ".\\yprojecty.y"
                             {}
#line 2485 "yprojecty.tab.c"
    break;

  case 105: /* expression: expression '-' expression  */
#line 779 ".\\yprojecty.y"
                             {}
#line 2491 "yprojecty.tab.c"
    break;

  case 106: /* expression: expression '*' expression  */
#line 780 ".\\yprojecty.y"
                             {}
#line 2497 "yprojecty.tab.c"
    break;

  case 107: /* expression: expression '/' expression  */
#line 781 ".\\yprojecty.y"
                             {}
#line 2503 "yprojecty.tab.c"
    break;

  case 108: /* expression: expression '%' expression  */
#line 782 ".\\yprojecty.y"
                             {}
#line 2509 "yprojecty.tab.c"
    break;

  case 109: /* expression: '-' expression  */
#line 783 ".\\yprojecty.y"
                               {}
#line 2515 "yprojecty.tab.c"
    break;


#line 2519 "yprojecty.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 784 ".\\yprojecty.y"

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
