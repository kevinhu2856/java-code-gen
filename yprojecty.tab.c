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
#line 1 "yprojecty.y"

    #include <stdio.h>
    #include <stdlib.h>
    //#include "yprojecty.tab.h"
    #include <string.h>
    #include "parser_header.h"
    #define IS_FUNCTION 1
    #define NOT_FUNCTION 0
    #define IS_GLOBAL 1
    #define NOT_GLOBAL 0
    #define IS_CONST 1
    #define NOT_CONST 0
    int yylex();


    

#line 89 "yprojecty.tab.c"

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
  YYSYMBOL_ID = 33,                        /* ID  */
  YYSYMBOL_PLUS_PLUS = 34,                 /* PLUS_PLUS  */
  YYSYMBOL_MINUS_MINUS = 35,               /* MINUS_MINUS  */
  YYSYMBOL_LESS_EQUAL = 36,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 37,             /* GREATER_EQUAL  */
  YYSYMBOL_EQUAL = 38,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 39,                 /* NOT_EQUAL  */
  YYSYMBOL_AND_AND = 40,                   /* AND_AND  */
  YYSYMBOL_OR_OR = 41,                     /* OR_OR  */
  YYSYMBOL_DOT_DOT = 42,                   /* DOT_DOT  */
  YYSYMBOL_43_ = 43,                       /* '!'  */
  YYSYMBOL_44_ = 44,                       /* '<'  */
  YYSYMBOL_45_ = 45,                       /* '>'  */
  YYSYMBOL_46_ = 46,                       /* '+'  */
  YYSYMBOL_47_ = 47,                       /* '-'  */
  YYSYMBOL_48_ = 48,                       /* '*'  */
  YYSYMBOL_49_ = 49,                       /* '/'  */
  YYSYMBOL_50_ = 50,                       /* '%'  */
  YYSYMBOL_UMINUS = 51,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 52,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_53_ = 53,                       /* '='  */
  YYSYMBOL_54_ = 54,                       /* ';'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* '('  */
  YYSYMBOL_57_ = 57,                       /* ')'  */
  YYSYMBOL_58_ = 58,                       /* '['  */
  YYSYMBOL_59_ = 59,                       /* ']'  */
  YYSYMBOL_60_ = 60,                       /* '{'  */
  YYSYMBOL_61_ = 61,                       /* '}'  */
  YYSYMBOL_62_ = 62,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_program = 64,                   /* program  */
  YYSYMBOL_pre_main_declaration = 65,      /* pre_main_declaration  */
  YYSYMBOL_pre_main_declaration_list = 66, /* pre_main_declaration_list  */
  YYSYMBOL_pre_main_const_declaration = 67, /* pre_main_const_declaration  */
  YYSYMBOL_const_list = 68,                /* const_list  */
  YYSYMBOL_pre_main_variable_declaration = 69, /* pre_main_variable_declaration  */
  YYSYMBOL_premain_identifier_list = 70,   /* premain_identifier_list  */
  YYSYMBOL_premain_identifier_decl = 71,   /* premain_identifier_decl  */
  YYSYMBOL_function_declaration = 72,      /* function_declaration  */
  YYSYMBOL_73_1 = 73,                      /* $@1  */
  YYSYMBOL_74_2 = 74,                      /* $@2  */
  YYSYMBOL_75_3 = 75,                      /* $@3  */
  YYSYMBOL_76_4 = 76,                      /* $@4  */
  YYSYMBOL_parameter_list = 77,            /* parameter_list  */
  YYSYMBOL_78_5 = 78,                      /* $@5  */
  YYSYMBOL_main_function_declaration = 79, /* main_function_declaration  */
  YYSYMBOL_80_6 = 80,                      /* $@6  */
  YYSYMBOL_81_7 = 81,                      /* $@7  */
  YYSYMBOL_const_declaration = 82,         /* const_declaration  */
  YYSYMBOL_variable_declaration = 83,      /* variable_declaration  */
  YYSYMBOL_identifier_list = 84,           /* identifier_list  */
  YYSYMBOL_identifier_decl = 85,           /* identifier_decl  */
  YYSYMBOL_array_declaration = 86,         /* array_declaration  */
  YYSYMBOL_87_8 = 87,                      /* $@8  */
  YYSYMBOL_array_size_or_location = 88,    /* array_size_or_location  */
  YYSYMBOL_type = 89,                      /* type  */
  YYSYMBOL_block = 90,                     /* block  */
  YYSYMBOL_91_9 = 91,                      /* $@9  */
  YYSYMBOL_92_10 = 92,                     /* $@10  */
  YYSYMBOL_statement_list = 93,            /* statement_list  */
  YYSYMBOL_statement = 94,                 /* statement  */
  YYSYMBOL_simple_statment = 95,           /* simple_statment  */
  YYSYMBOL_simple_statment_without_semicolon = 96, /* simple_statment_without_semicolon  */
  YYSYMBOL_variable_assignment = 97,       /* variable_assignment  */
  YYSYMBOL_function_invocation = 98,       /* function_invocation  */
  YYSYMBOL_99_11 = 99,                     /* $@11  */
  YYSYMBOL_argument_list = 100,            /* argument_list  */
  YYSYMBOL_conditional_statement = 101,    /* conditional_statement  */
  YYSYMBOL_102_12 = 102,                   /* $@12  */
  YYSYMBOL_103_13 = 103,                   /* $@13  */
  YYSYMBOL_if_statement = 104,             /* if_statement  */
  YYSYMBOL_105_14 = 105,                   /* $@14  */
  YYSYMBOL_loop_statement = 106,           /* loop_statement  */
  YYSYMBOL_107_15 = 107,                   /* $@15  */
  YYSYMBOL_108_16 = 108,                   /* $@16  */
  YYSYMBOL_109_17 = 109,                   /* $@17  */
  YYSYMBOL_110_18 = 110,                   /* $@18  */
  YYSYMBOL_111_19 = 111,                   /* $@19  */
  YYSYMBOL_112_20 = 112,                   /* $@20  */
  YYSYMBOL_print_statement = 113,          /* print_statement  */
  YYSYMBOL_114_21 = 114,                   /* $@21  */
  YYSYMBOL_115_22 = 115,                   /* $@22  */
  YYSYMBOL_read_statement = 116,           /* read_statement  */
  YYSYMBOL_increment_decrement_statement = 117, /* increment_decrement_statement  */
  YYSYMBOL_return_statement = 118,         /* return_statement  */
  YYSYMBOL_expression = 119                /* expression  */
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
#define YYLAST   316

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  224

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


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
       2,     2,     2,    43,     2,     2,     2,    50,     2,     2,
      56,    57,    48,    46,    55,    47,     2,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    54,
      44,    53,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,    61,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    54,    54,    58,    65,    66,    70,    71,    72,    76,
     102,   106,   110,   114,   118,   125,   134,   135,   139,   153,
     184,   191,   181,   239,   246,   236,   269,   278,   277,   291,
     302,   290,   314,   340,   345,   345,   349,   354,   384,   382,
     393,   401,   412,   414,   416,   418,   420,   427,   424,   443,
     442,   458,   459,   463,   464,   465,   466,   467,   468,   469,
     470,   474,   475,   476,   477,   480,   481,   482,   483,   486,
     536,   555,   593,   593,   613,   614,   621,   625,   620,   639,
     649,   649,   652,   656,   660,   655,   671,   675,   670,   687,
     691,   686,   713,   713,   730,   730,   749,   762,   778,   794,
     810,   828,   848,   866,   881,   895,   917,   931,   945,   959,
     966,   973,   979,   984,   989,   994,   999,  1004,  1012,  1053,
    1054,  1059,  1072,  1084,  1096,  1112,  1131
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
  "WHILE", "INT_LITERAL", "REAL_LITERAL", "STRING_LITERAL", "MAIN", "ID",
  "PLUS_PLUS", "MINUS_MINUS", "LESS_EQUAL", "GREATER_EQUAL", "EQUAL",
  "NOT_EQUAL", "AND_AND", "OR_OR", "DOT_DOT", "'!'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "UMINUS", "LOWER_THAN_ELSE", "'='", "';'",
  "','", "'('", "')'", "'['", "']'", "'{'", "'}'", "':'", "$accept",
  "program", "pre_main_declaration", "pre_main_declaration_list",
  "pre_main_const_declaration", "const_list",
  "pre_main_variable_declaration", "premain_identifier_list",
  "premain_identifier_decl", "function_declaration", "$@1", "$@2", "$@3",
  "$@4", "parameter_list", "$@5", "main_function_declaration", "$@6",
  "$@7", "const_declaration", "variable_declaration", "identifier_list",
  "identifier_decl", "array_declaration", "$@8", "array_size_or_location",
  "type", "block", "$@9", "$@10", "statement_list", "statement",
  "simple_statment", "simple_statment_without_semicolon",
  "variable_assignment", "function_invocation", "$@11", "argument_list",
  "conditional_statement", "$@12", "$@13", "if_statement", "$@14",
  "loop_statement", "$@15", "$@16", "$@17", "$@18", "$@19", "$@20",
  "print_statement", "$@21", "$@22", "read_statement",
  "increment_decrement_statement", "return_statement", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-125)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-39)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,  -125,    76,  -125,  -125,  -125,    18,    30,     1,  -125,
    -125,  -125,  -125,  -125,    19,  -125,    20,  -125,  -125,  -125,
    -125,   -34,     5,     0,     8,     6,    40,    17,  -125,    43,
     129,  -125,  -125,  -125,  -125,  -125,  -125,    -9,    40,    40,
      40,  -125,   233,    76,    27,    39,  -125,  -125,  -125,  -125,
    -125,  -125,    45,    48,    40,    40,  -125,   263,  -125,   149,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    49,    64,  -125,  -125,    42,    50,    53,
     179,   125,  -125,   130,   130,   130,   130,   263,   248,   130,
     130,   -39,   -39,  -125,  -125,  -125,  -125,    56,    42,   111,
    -125,  -125,  -125,    40,    54,    42,    58,  -125,    76,  -125,
    -125,    52,  -125,  -125,    86,    34,  -125,    22,  -125,  -125,
    -125,    87,    60,  -125,   111,  -125,    68,    71,  -125,  -125,
      82,    83,    88,  -125,  -125,  -125,  -125,    76,   107,    90,
      91,    40,    40,    40,  -125,  -125,   199,    92,  -125,  -125,
      40,    -2,   -32,    97,    98,  -125,    93,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,   103,   -15,   134,   164,   233,   233,
    -125,    40,   233,  -125,  -125,    40,    40,    54,  -125,   148,
    -125,   129,    51,    40,   121,    42,   233,   233,   233,   137,
     139,  -125,   153,   233,    40,  -125,    42,  -125,   111,   165,
    -125,  -125,   176,   218,   219,  -125,    42,   -15,    40,  -125,
    -125,   175,  -125,  -125,  -125,  -125,   233,    42,    42,   184,
    -125,  -125,    42,  -125
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    44,     0,    43,    42,    45,    46,     0,     0,     4,
       7,     8,     6,     3,     0,    46,     0,    29,     1,     5,
       2,    18,     0,    16,     0,     0,     0,    20,    15,     0,
       0,    30,   116,   115,   112,   113,   114,   118,     0,     0,
       0,   117,    19,     0,     0,    18,    17,    14,    13,    10,
      11,    12,     0,     0,    72,     0,   119,   111,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,     9,     0,     0,     0,
      74,     0,   120,   107,   108,   103,   104,   109,   110,   105,
     106,   121,   122,   123,   124,   125,    21,    26,     0,    49,
      31,    73,    71,     0,    40,     0,     0,    25,     0,    86,
      89,     0,    92,    94,     0,     0,    83,     0,    55,    54,
      56,     0,     0,    47,    51,    53,     0,     0,    58,    59,
       0,     0,     0,    60,    75,    41,    22,     0,     0,     0,
       0,     0,     0,     0,    96,   102,     0,     0,    97,    98,
       0,     0,    36,     0,    34,    50,     0,    52,    61,    57,
      62,    63,    64,    28,     0,     0,     0,     0,    93,    95,
     101,     0,    69,    99,   100,     0,     0,     0,    33,     0,
      48,     0,     0,     0,     0,    76,    84,    70,    37,     0,
      36,    35,     0,    87,     0,    82,    80,    79,     0,     0,
      39,    32,     0,     0,     0,    81,    80,     0,     0,    77,
      85,     0,    65,    66,    67,    68,    90,    80,    80,     0,
      78,    88,    80,    91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,  -125,   225,  -125,    61,  -125,   221,  -125,  -125,
    -125,  -125,  -125,  -125,   114,  -125,   244,  -125,  -125,  -125,
    -125,    96,  -125,  -125,  -125,   -36,    15,   -74,  -125,  -125,
     152,    63,   124,  -125,    84,   -97,  -125,   187,  -125,  -125,
    -125,  -124,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
      99,  -125,  -125,   108,   109,  -125,   -26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    52,    11,    22,    23,    12,
      43,   105,    44,    98,    73,   106,    13,    25,    53,   118,
     119,   153,   154,   120,   177,   151,   121,   195,   156,   122,
     123,   124,   125,   211,   126,    41,    78,    79,   128,   196,
     217,   197,   198,   129,   147,   199,   139,   202,   140,   219,
     130,   142,   143,   131,   132,   133,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    56,   127,   100,     1,   112,   113,   114,     2,    70,
      71,    72,    57,    58,    59,    14,     3,    16,   182,    26,
       4,   176,    27,    14,   107,     5,   -38,   127,     6,    81,
      18,   136,   173,   174,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    54,    32,    55,
      17,   175,    21,    24,    32,    29,   148,   149,    74,    28,
      33,    30,    31,    34,    35,    36,    33,    37,   135,    34,
      35,    36,   204,    37,   -23,   150,    45,    38,    54,     1,
      55,    39,   210,    38,    75,   148,   149,    39,   145,   146,
      40,     3,    26,   220,   221,     4,    40,    97,   223,    76,
       5,   127,    99,    15,   150,    77,    96,   101,   141,    55,
     102,   -27,    55,   137,     1,   167,   168,   169,   108,   144,
     152,   155,   158,   138,   172,   159,     3,   109,   110,   111,
       4,   112,   113,   114,   115,     5,   160,   161,    15,   116,
     164,   189,   162,    47,   117,   186,   165,   166,   171,   187,
     188,   178,    74,   179,   180,    48,   181,   193,    49,    50,
      51,    60,    61,    62,    63,    64,    65,   184,   203,    66,
      67,    68,    69,    70,    71,    72,    68,    69,    70,    71,
      72,   190,   216,   194,   104,    60,    61,    62,    63,    64,
      65,   200,   176,    66,    67,    68,    69,    70,    71,    72,
      60,    61,    62,    63,    64,    65,    82,   201,    66,    67,
      68,    69,    70,    71,    72,    60,    61,    62,    63,    64,
      65,   185,   206,    66,    67,    68,    69,    70,    71,    72,
     207,   209,   218,    19,   103,    60,    61,    62,    63,    64,
      65,   222,   192,    66,    67,    68,    69,    70,    71,    72,
      46,   163,    20,   170,    60,    61,    62,    63,    64,    65,
     208,   205,    66,    67,    68,    69,    70,    71,    72,    60,
      61,    62,    63,    64,    65,   191,   157,    66,    67,    68,
      69,    70,    71,    72,    60,    61,    62,    63,    64,   183,
     134,   212,    66,    67,    68,    69,    70,    71,    72,    60,
      61,    62,    63,     0,     0,     0,   213,    66,    67,    68,
      69,    70,    71,    72,     0,   214,   215
};

static const yytype_int16 yycheck[] =
{
      26,    37,    99,    77,     3,    20,    21,    22,     7,    48,
      49,    50,    38,    39,    40,     0,    15,     2,    33,    53,
      19,    53,    56,     8,    98,    24,    58,   124,    27,    55,
       0,   105,    34,    35,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    56,    14,    58,
      32,    53,    33,    33,    14,    55,    34,    35,    43,    54,
      26,    53,    56,    29,    30,    31,    26,    33,   104,    29,
      30,    31,   196,    33,    57,    53,    33,    43,    56,     3,
      58,    47,   206,    43,    57,    34,    35,    47,    54,   115,
      56,    15,    53,   217,   218,    19,    56,    33,   222,    54,
      24,   198,    60,    27,    53,    57,    57,    57,    56,    58,
      57,    55,    58,    55,     3,   141,   142,   143,     7,    33,
      33,    61,    54,   108,   150,    54,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    54,    54,    27,    28,
      33,   177,    54,    14,    33,   171,    56,    56,    56,   175,
     176,    54,   137,    55,    61,    26,    53,   183,    29,    30,
      31,    36,    37,    38,    39,    40,    41,    33,   194,    44,
      45,    46,    47,    48,    49,    50,    46,    47,    48,    49,
      50,    33,   208,    62,    59,    36,    37,    38,    39,    40,
      41,    54,    53,    44,    45,    46,    47,    48,    49,    50,
      36,    37,    38,    39,    40,    41,    57,    54,    44,    45,
      46,    47,    48,    49,    50,    36,    37,    38,    39,    40,
      41,    57,    57,    44,    45,    46,    47,    48,    49,    50,
      54,    12,    57,     8,    55,    36,    37,    38,    39,    40,
      41,    57,   181,    44,    45,    46,    47,    48,    49,    50,
      29,   137,     8,    54,    36,    37,    38,    39,    40,    41,
      42,   198,    44,    45,    46,    47,    48,    49,    50,    36,
      37,    38,    39,    40,    41,   179,   124,    44,    45,    46,
      47,    48,    49,    50,    36,    37,    38,    39,    40,   165,
     103,   207,    44,    45,    46,    47,    48,    49,    50,    36,
      37,    38,    39,    -1,    -1,    -1,   207,    44,    45,    46,
      47,    48,    49,    50,    -1,   207,   207
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,    15,    19,    24,    27,    64,    65,    66,
      67,    69,    72,    79,    89,    27,    89,    32,     0,    66,
      79,    33,    70,    71,    33,    80,    53,    56,    54,    55,
      53,    56,    14,    26,    29,    30,    31,    33,    43,    47,
      56,    98,   119,    73,    75,    33,    70,    14,    26,    29,
      30,    31,    68,    81,    56,    58,    88,   119,   119,   119,
      36,    37,    38,    39,    40,    41,    44,    45,    46,    47,
      48,    49,    50,    77,    89,    57,    54,    57,    99,   100,
     119,   119,    57,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,    57,    33,    76,    60,
      90,    57,    57,    55,    59,    74,    78,    90,     7,    16,
      17,    18,    20,    21,    22,    23,    28,    33,    82,    83,
      86,    89,    92,    93,    94,    95,    97,    98,   101,   106,
     113,   116,   117,   118,   100,    88,    90,    55,    89,   109,
     111,    56,   114,   115,    33,    54,   119,   107,    34,    35,
      53,    88,    33,    84,    85,    61,    91,    93,    54,    54,
      54,    54,    54,    77,    33,    56,    56,   119,   119,   119,
      54,    56,   119,    34,    35,    53,    53,    87,    54,    55,
      61,    53,    33,    95,    33,    57,   119,   119,   119,    88,
      33,    84,    68,   119,    62,    90,   102,   104,   105,   108,
      54,    54,   110,   119,   104,    94,    57,    54,    42,    12,
     104,    96,    97,   113,   116,   117,   119,   103,    57,   112,
     104,   104,    57,   104
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    66,    66,    66,    67,
      68,    68,    68,    68,    68,    69,    70,    70,    71,    71,
      73,    74,    72,    75,    76,    72,    77,    78,    77,    80,
      81,    79,    82,    83,    84,    84,    85,    85,    87,    86,
      88,    88,    89,    89,    89,    89,    89,    91,    90,    92,
      90,    93,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    95,    95,    95,    96,    96,    96,    96,    97,
      97,    98,    99,    98,   100,   100,   102,   103,   101,   101,
     105,   104,   104,   107,   108,   106,   109,   110,   106,   111,
     112,   106,   114,   113,   115,   113,   116,   117,   117,   117,
     117,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     1,     1,     1,     6,
       1,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       0,     0,     8,     0,     0,     7,     2,     0,     5,     0,
       0,     7,     6,     3,     1,     3,     1,     3,     0,     5,
       3,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       3,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     3,
       4,     4,     0,     4,     1,     3,     0,     0,     9,     5,
       0,     2,     1,     0,     0,     7,     0,     0,    10,     0,
       0,    11,     0,     3,     0,     3,     2,     2,     2,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     3,     3,     3,     3,     2
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
#line 55 "yprojecty.y"
    {
        printf("Program parsed successfully.\n");
    }
#line 1652 "yprojecty.tab.c"
    break;

  case 3: /* program: main_function_declaration  */
#line 59 "yprojecty.y"
    {
        printf("Program parsed successfully without pre main.\n");
    }
#line 1660 "yprojecty.tab.c"
    break;

  case 9: /* pre_main_const_declaration: CONST type ID '=' const_list ';'  */
#line 77 "yprojecty.y"
    {
        current_declaration_type = (yyvsp[-4].dtype);
        insert_symbol((yyvsp[-3].svalue), (yyvsp[-4].dtype), IS_CONST, NOT_FUNCTION, -1, IS_GLOBAL); // Add constant to global scope
        Symbol* sym = lookup_symbol((yyvsp[-3].svalue));
        switch (sym->type) {
            case TYPE_INT:
                sym->value.ivalue = (yyvsp[-1].expr_node)->value.ivalue;
                break;
            case TYPE_FLOAT:
                sym->value.fvalue = (yyvsp[-1].expr_node)->value.fvalue;
                break;
            case TYPE_BOOL:
                sym->value.bvalue = (yyvsp[-1].expr_node)->value.bvalue;
                break;
            case TYPE_STRING:
                sym->value.svalue = strdup((yyvsp[-1].expr_node)->value.svalue);
                break;
            default:
                fprintf(stderr, "Error: Unsupported constant type at line %d\n", yylineno);
                YYERROR;
        }
    }
#line 1687 "yprojecty.tab.c"
    break;

  case 10: /* const_list: INT_LITERAL  */
#line 102 "yprojecty.y"
               {
        (yyval.expr_node) = create_expr_node(TYPE_INT);
        (yyval.expr_node)->value.ivalue = (yyvsp[0].ivalue);
    }
#line 1696 "yprojecty.tab.c"
    break;

  case 11: /* const_list: REAL_LITERAL  */
#line 106 "yprojecty.y"
                {
        (yyval.expr_node) = create_expr_node(TYPE_FLOAT);
        (yyval.expr_node)->value.fvalue = (yyvsp[0].fvalue);
    }
#line 1705 "yprojecty.tab.c"
    break;

  case 12: /* const_list: STRING_LITERAL  */
#line 110 "yprojecty.y"
                  {
        (yyval.expr_node) = create_expr_node(TYPE_STRING);
        (yyval.expr_node)->value.svalue = (yyvsp[0].svalue);
    }
#line 1714 "yprojecty.tab.c"
    break;

  case 13: /* const_list: TRUE_TOKEN  */
#line 114 "yprojecty.y"
              {
        (yyval.expr_node) = create_expr_node(TYPE_BOOL);
        (yyval.expr_node)->value.bvalue = 1;
    }
#line 1723 "yprojecty.tab.c"
    break;

  case 14: /* const_list: FALSE_TOKEN  */
#line 118 "yprojecty.y"
               {
        (yyval.expr_node) = create_expr_node(TYPE_BOOL);
        (yyval.expr_node)->value.bvalue = 0;
    }
#line 1732 "yprojecty.tab.c"
    break;

  case 15: /* pre_main_variable_declaration: type premain_identifier_list ';'  */
#line 127 "yprojecty.y"
    {
        current_declaration_type = (yyvsp[-2].dtype);
    }
#line 1740 "yprojecty.tab.c"
    break;

  case 18: /* premain_identifier_decl: ID  */
#line 140 "yprojecty.y"
    {
        insert_symbol((yyvsp[0].svalue), current_declaration_type, NOT_CONST, NOT_FUNCTION, -1,IS_GLOBAL); // Add variable to global scope
        // Generate appropriate field type
        const char* java_type;
        switch(current_declaration_type) {
            case TYPE_INT: java_type = "integer"; break;
            case TYPE_FLOAT: java_type = "float"; break;
            case TYPE_BOOL: java_type = "integer"; break;
            //case TYPE_STRING: java_type = "Ljava/lang/String;"; break;
            default: java_type = "I"; break;
        }
        fprintf(output_file, "field static %s %s\n", java_type, (yyvsp[0].svalue));
    }
#line 1758 "yprojecty.tab.c"
    break;

  case 19: /* premain_identifier_decl: ID '=' expression  */
#line 154 "yprojecty.y"
    {
        insert_symbol((yyvsp[-2].svalue), current_declaration_type, NOT_CONST, NOT_FUNCTION,-1,IS_GLOBAL); // Add variable to function scope
        if((yyvsp[0].expr_node)!=NULL&&!is_assignment_compatible(current_declaration_type, (yyvsp[0].expr_node)->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string((yyvsp[0].expr_node)->type),type_to_string(current_declaration_type), yylineno);
            YYERROR;
        }else{
            Symbol* sym = lookup_symbol((yyvsp[-2].svalue));
            if (sym->type == TYPE_INT) {
                sym->value.ivalue = (yyvsp[0].expr_node)->value.ivalue;
                fprintf(output_file, "field static int %s = %d\n",sym->name, (yyvsp[0].expr_node)->value.ivalue);
            } else if (sym->type == TYPE_FLOAT) {
                sym->value.fvalue = (yyvsp[0].expr_node)->value.fvalue;
                fprintf(output_file, "field static int %s = %f\n",sym->name, (yyvsp[0].expr_node)->value.ivalue);
            } else if (sym->type == TYPE_BOOL) {
                sym->value.bvalue = (yyvsp[0].expr_node)->value.bvalue;
                fprintf(output_file, "field static int %s = %d\n",sym->name, (yyvsp[0].expr_node)->value.ivalue);
            } else if (sym->type == TYPE_STRING) {
                sym->value.svalue = strdup((yyvsp[0].expr_node)->value.svalue);
                fprintf(output_file, "error string assignment\n");
            }
        }
        free_expr_node((yyvsp[0].expr_node));
    }
#line 1786 "yprojecty.tab.c"
    break;

  case 20: /* $@1: %empty  */
#line 184 "yprojecty.y"
    {
        current_function_name = strdup((yyvsp[-1].svalue));
        insert_symbol((yyvsp[-1].svalue), (yyvsp[-2].dtype), IS_CONST, IS_FUNCTION, -1,IS_GLOBAL);
        enter_new_table(1,0);
        fprintf(output_file,"method public static %s %s(", type_to_string((yyvsp[-2].dtype)), (yyvsp[-1].svalue));
    }
#line 1797 "yprojecty.tab.c"
    break;

  case 21: /* $@2: %empty  */
#line 191 "yprojecty.y"
    {
        has_return = 0; // Reset return flag for this function
        Symbol* sym = lookup_symbol((yyvsp[-4].svalue));
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
        current_function_return_type = (yyvsp[-5].dtype);
        fprintf(output_file,")\n");
        fprintf(output_file,"max_stack 15\n");
        fprintf(output_file,"max_locals 15\n");
        fprintf(output_file,"{\n");
    }
#line 1831 "yprojecty.tab.c"
    break;

  case 22: /* function_declaration: type ID '(' $@1 parameter_list ')' $@2 block  */
#line 221 "yprojecty.y"
    {
        free(current_function_name);
        current_function_name = NULL;
        fprintf(output_file,"}\n");
        if(current_function_return_type == TYPE_VOID&&has_return) {
            fprintf(stderr, "Error: Void function '%s' should not have a return statement at line %d\n", current_function_name, yylineno);
            YYERROR;
        }
        else if(current_function_return_type != TYPE_VOID&&!has_return) {
            fprintf(stderr, "Error: Function '%s' should return a value at line %d\n", current_function_name, yylineno);
            YYERROR;
        }
        has_return = 0; // Reset for next function
    }
#line 1850 "yprojecty.tab.c"
    break;

  case 23: /* $@3: %empty  */
#line 239 "yprojecty.y"
    {
        current_function_name = strdup((yyvsp[-1].svalue));
        insert_symbol((yyvsp[-1].svalue), (yyvsp[-2].dtype), IS_CONST, IS_FUNCTION,-1,IS_GLOBAL);
        enter_new_table(1,0);
        fprintf(output_file,"method public static %s %s(", type_to_string((yyvsp[-2].dtype)), (yyvsp[-1].svalue));
    }
#line 1861 "yprojecty.tab.c"
    break;

  case 24: /* $@4: %empty  */
#line 246 "yprojecty.y"
    {
        current_function_return_type = (yyvsp[-4].dtype);
        has_return = 0; // Reset return flag for this function
        fprintf(output_file,"){\n");
    }
#line 1871 "yprojecty.tab.c"
    break;

  case 25: /* function_declaration: type ID '(' $@3 ')' $@4 block  */
#line 252 "yprojecty.y"
    {
        free(current_function_name);
        current_function_name = NULL;
        fprintf(output_file,"}\n");
        if(current_function_return_type == TYPE_VOID&&has_return) {
            fprintf(stderr, "Error: Void function '%s' should not have a return statement at line %d\n", current_function_name, yylineno);
            YYERROR;
        }
        else if(current_function_return_type != TYPE_VOID&&!has_return) {
            fprintf(stderr, "Error: Function '%s' should return a value at line %d\n", current_function_name, yylineno);
            YYERROR;
        }
        has_return = 0; // Reset for next function
    }
#line 1890 "yprojecty.tab.c"
    break;

  case 26: /* parameter_list: type ID  */
#line 270 "yprojecty.y"
    {
        insert_symbol((yyvsp[0].svalue), (yyvsp[-1].dtype), NOT_CONST, NOT_FUNCTION,globel_symbol_label,NOT_GLOBAL); // Add parameter to function scope
        globel_symbol_label++;
        Symbol* func=lookup_symbol(current_function_name);
        func->function_signature.param_types[func->function_signature.param_count] = (yyvsp[-1].dtype); // Store parameter type 
        func->function_signature.param_count ++;
    }
#line 1902 "yprojecty.tab.c"
    break;

  case 27: /* $@5: %empty  */
#line 278 "yprojecty.y"
    {
        insert_symbol((yyvsp[0].svalue), (yyvsp[-1].dtype), NOT_CONST, NOT_FUNCTION,globel_symbol_label,NOT_GLOBAL); 
        Symbol* func=lookup_symbol(current_function_name);
        func->function_signature.param_types[func->function_signature.param_count] = (yyvsp[-1].dtype); // Store parameter type 
        func->function_signature.param_count ++;
        
    }
#line 1914 "yprojecty.tab.c"
    break;

  case 29: /* $@6: %empty  */
#line 291 "yprojecty.y"
    {
        current_function_return_type = TYPE_VOID;
        current_function_name = strdup("main");
        insert_symbol("main", TYPE_VOID, IS_CONST, IS_FUNCTION,-1,IS_GLOBAL);
        globel_symbol_label = 0; // Reset global symbol label for main function
        fprintf(output_file,"method public static void main(java.lang.String[])\n");
        fprintf(output_file,"max_stack 15\n");
        fprintf(output_file,"max_locals 15\n");
        fprintf(output_file,"{\n");
    }
#line 1929 "yprojecty.tab.c"
    break;

  case 30: /* $@7: %empty  */
#line 302 "yprojecty.y"
    {
        enter_new_table(1,0); // Enter function scope
    }
#line 1937 "yprojecty.tab.c"
    break;

  case 31: /* main_function_declaration: VOID MAIN $@6 '(' $@7 ')' block  */
#line 306 "yprojecty.y"
    {
        free(current_function_name);
        current_function_name = NULL;
        fprintf(output_file,"}\n");
    }
#line 1947 "yprojecty.tab.c"
    break;

  case 32: /* const_declaration: CONST type ID '=' const_list ';'  */
#line 315 "yprojecty.y"
    {
        current_declaration_type = (yyvsp[-4].dtype);
        insert_symbol((yyvsp[-3].svalue), (yyvsp[-4].dtype), IS_CONST, NOT_FUNCTION, -1, NOT_GLOBAL); // Add constant to global scope
        Symbol* sym = lookup_symbol((yyvsp[-3].svalue));
        switch (sym->type) {
            case TYPE_INT:
                sym->value.ivalue = (yyvsp[-1].expr_node)->value.ivalue;
                break;
            case TYPE_FLOAT:
                sym->value.fvalue = (yyvsp[-1].expr_node)->value.fvalue;
                break;
            case TYPE_BOOL:
                sym->value.bvalue = (yyvsp[-1].expr_node)->value.bvalue;
                break;
            case TYPE_STRING:
                sym->value.svalue = strdup((yyvsp[-1].expr_node)->value.svalue);
                break;
            default:
                fprintf(stderr, "Error: Unsupported constant type at line %d\n", yylineno);
                YYERROR;
        }
    }
#line 1974 "yprojecty.tab.c"
    break;

  case 36: /* identifier_decl: ID  */
#line 350 "yprojecty.y"
    {
        insert_symbol((yyvsp[0].svalue), current_declaration_type, NOT_CONST, NOT_FUNCTION, globel_symbol_label,NOT_GLOBAL);
        globel_symbol_label++;
    }
#line 1983 "yprojecty.tab.c"
    break;

  case 37: /* identifier_decl: ID '=' expression  */
#line 355 "yprojecty.y"
    {
        insert_symbol((yyvsp[-2].svalue), current_declaration_type, NOT_CONST, NOT_FUNCTION, globel_symbol_label,NOT_GLOBAL);
        globel_symbol_label++;
        if((yyvsp[0].expr_node) != NULL && !is_assignment_compatible(current_declaration_type, (yyvsp[0].expr_node)->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", 
                   type_to_string((yyvsp[0].expr_node)->type), type_to_string(current_declaration_type), yylineno);
            YYERROR;
        } else {
            Symbol* sym = lookup_symbol((yyvsp[-2].svalue));
            if (sym->type == TYPE_INT) {
                sym->value.ivalue = (yyvsp[0].expr_node)->value.ivalue;
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_FLOAT) {
                sym->value.fvalue = (yyvsp[0].expr_node)->value.fvalue;
                fprintf(output_file, "fstore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_BOOL) {
                sym->value.bvalue = (yyvsp[0].expr_node)->value.bvalue;
                fprintf(output_file, "istore %d\n", sym->variable_label);
            } else if (sym->type == TYPE_STRING) {
                sym->value.svalue = strdup((yyvsp[0].expr_node)->value.svalue);
                fprintf(output_file, "astore %d\n", sym->variable_label);
            }
        }
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2013 "yprojecty.tab.c"
    break;

  case 38: /* $@8: %empty  */
#line 384 "yprojecty.y"
    {
        current_declaration_type = (yyvsp[-1].dtype);
        insert_symbol((yyvsp[0].svalue), TYPE_ARRAY, NOT_CONST, NOT_FUNCTION,globel_symbol_label,NOT_GLOBAL); // Record as array type
        globel_symbol_label++;
    }
#line 2023 "yprojecty.tab.c"
    break;

  case 40: /* array_size_or_location: '[' expression ']'  */
#line 394 "yprojecty.y"
    {
        if((yyvsp[-1].expr_node)->type != TYPE_INT) {
            fprintf(stderr, "Error: Array size must be an integer at line %d\n", yylineno);
            YYERROR;
        }
        free_expr_node((yyvsp[-1].expr_node));
    }
#line 2035 "yprojecty.tab.c"
    break;

  case 41: /* array_size_or_location: '[' expression ']' array_size_or_location  */
#line 402 "yprojecty.y"
    {
        if((yyvsp[-2].expr_node)->type != TYPE_INT) {
            fprintf(stderr, "Error: Array size must be an integer at line %d\n", yylineno);
            YYERROR;
        }
        free_expr_node((yyvsp[-2].expr_node));
    }
#line 2047 "yprojecty.tab.c"
    break;

  case 42: /* type: INT  */
#line 412 "yprojecty.y"
        { (yyval.dtype) = TYPE_INT; current_declaration_type = TYPE_INT; }
#line 2053 "yprojecty.tab.c"
    break;

  case 43: /* type: FLOAT  */
#line 414 "yprojecty.y"
          { (yyval.dtype) = TYPE_FLOAT; current_declaration_type = TYPE_FLOAT;}
#line 2059 "yprojecty.tab.c"
    break;

  case 44: /* type: BOOL  */
#line 416 "yprojecty.y"
         { (yyval.dtype) = TYPE_BOOL; current_declaration_type = TYPE_BOOL;}
#line 2065 "yprojecty.tab.c"
    break;

  case 45: /* type: STRING  */
#line 418 "yprojecty.y"
           { (yyval.dtype) = TYPE_STRING; current_declaration_type = TYPE_STRING;}
#line 2071 "yprojecty.tab.c"
    break;

  case 46: /* type: VOID  */
#line 420 "yprojecty.y"
         { (yyval.dtype) = TYPE_VOID; current_declaration_type = TYPE_VOID;}
#line 2077 "yprojecty.tab.c"
    break;

  case 47: /* $@9: %empty  */
#line 427 "yprojecty.y"
    {
        if(current_declaration_type==VOID&&!has_return) {
            fprintf(output_file, "return\n");
            has_return = 1; // Mark that this block has a return statement
        }
    }
#line 2088 "yprojecty.tab.c"
    break;

  case 48: /* block: '{' statement_list $@9 '}'  */
#line 435 "yprojecty.y"
    {
        dump_current_table();
        leave_table();
        
        
    }
#line 2099 "yprojecty.tab.c"
    break;

  case 49: /* $@10: %empty  */
#line 443 "yprojecty.y"
    {
        if(current_declaration_type==VOID&&!has_return) {
            fprintf(output_file, "return\n");
            has_return = 1; // Mark that this block has a return statement
        }
    }
#line 2110 "yprojecty.tab.c"
    break;

  case 50: /* block: '{' $@10 '}'  */
#line 450 "yprojecty.y"
    {
        dump_current_table();
        leave_table();
        
        
    }
#line 2121 "yprojecty.tab.c"
    break;

  case 69: /* variable_assignment: ID '=' expression  */
#line 487 "yprojecty.y"
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
        if((yyvsp[0].expr_node)!=NULL&&!is_assignment_compatible(sym->type, (yyvsp[0].expr_node)->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", 
                   type_to_string((yyvsp[0].expr_node)->type), type_to_string(sym->type), yylineno);
            YYERROR;
        } else {
            if (sym->type == TYPE_INT) {
                sym->value.ivalue = (yyvsp[0].expr_node)->value.ivalue;
                if(sym->is_global == 1) {
                    fprintf(output_file, "putstatic int %s.%s\n",classname, sym->name);
                } else {
                    fprintf(output_file, "istore %d\n", sym->variable_label);
                }
            } else if (sym->type == TYPE_FLOAT) {
                sym->value.fvalue = (yyvsp[0].expr_node)->value.fvalue;
                if(sym->is_global == 1) {
                    fprintf(output_file, "putstatic float %s.%s\n",classname, sym->name);
                } else {
                    fprintf(output_file, "fstore %d\n", sym->variable_label);  // Use fstore for float
                }
            } else if (sym->type == TYPE_BOOL) {
                sym->value.bvalue = (yyvsp[0].expr_node)->value.bvalue;
                if(sym->is_global == 1) {
                    fprintf(output_file, "putstatic int %s.%s\n",classname, sym->name);
                } else {
                    fprintf(output_file, "istore %d\n", sym->variable_label);
                }
            } else if (sym->type == TYPE_STRING) {
                if (sym->value.svalue) free(sym->value.svalue);  // Free old string
                sym->value.svalue = strdup((yyvsp[0].expr_node)->value.svalue);
                if(sym->is_global == 1) {
                    fprintf(output_file, "putstatic java/lang/String %s.%s\n",classname, sym->name);
                } else {
                    fprintf(output_file, "astore %d\n", sym->variable_label);
                }
            }
        }
        //fprintf(output_file, "istore %d\n", sym->variable_label);
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2175 "yprojecty.tab.c"
    break;

  case 70: /* variable_assignment: ID array_size_or_location '=' expression  */
#line 537 "yprojecty.y"
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
        if((yyvsp[0].expr_node)!=NULL&&!is_assignment_compatible(sym->typeinfo.basetype, (yyvsp[0].expr_node)->type)) {
            fprintf(stderr, "Error: cannot assign %s to %s at line %d\n", type_to_string((yyvsp[0].expr_node)->type),type_to_string(sym->typeinfo.basetype), yylineno);
            YYERROR;
        }
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2196 "yprojecty.tab.c"
    break;

  case 71: /* function_invocation: ID '(' argument_list ')'  */
#line 556 "yprojecty.y"
    {
        dump_current_table();
        Symbol* sym = lookup_symbol((yyvsp[-3].svalue));
        
        if(sym == NULL) {
            fprintf(stderr, "Error: Function '%s' not declared at line %d\n", (yyvsp[-3].svalue), yylineno);
            YYERROR;
        }
        if (!sym->is_function) {
            fprintf(stderr, "Error: '%s' is not a function at line %d\n", (yyvsp[-3].svalue), yylineno);
            YYERROR;
        }
        (yyval.expr_node)= create_expr_node(sym->type);
        fprintf(output_file, "invoke static %s %s.%s(",type_to_string(sym->type),classname, sym->name);
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
        // Here we would check argument types and count
    }
#line 2238 "yprojecty.tab.c"
    break;

  case 72: /* $@11: %empty  */
#line 593 "yprojecty.y"
          {
        Symbol* sym = lookup_symbol((yyvsp[-1].svalue));
        fprintf(output_file, "invoke static %s %s.%s(",type_to_string(sym->type),classname, sym->name);
    }
#line 2247 "yprojecty.tab.c"
    break;

  case 73: /* function_invocation: ID '(' $@11 ')'  */
#line 597 "yprojecty.y"
    {
        fprintf(output_file, ")\n");
        Symbol* sym = lookup_symbol((yyvsp[-3].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Function '%s' not declared at line %d\n", (yyvsp[-3].svalue), yylineno);
            YYERROR;
        }
        if (!sym->is_function) {
            fprintf(stderr, "Error: '%s' is not a function at line %d\n", (yyvsp[-3].svalue), yylineno);
            YYERROR;
        }
        (yyval.expr_node)= create_expr_node(sym->type);
        // Check that function doesn't require arguments
    }
#line 2266 "yprojecty.tab.c"
    break;

  case 75: /* argument_list: expression ',' argument_list  */
#line 614 "yprojecty.y"
                                {
    }
#line 2273 "yprojecty.tab.c"
    break;

  case 76: /* $@12: %empty  */
#line 621 "yprojecty.y"
    {
        fprintf(output_file, "ifeq L%d\n", assembly_label);
    }
#line 2281 "yprojecty.tab.c"
    break;

  case 77: /* $@13: %empty  */
#line 625 "yprojecty.y"
    {
        fprintf(output_file, "goto L%d\n", assembly_label+1);
        fprintf(output_file, "L%d:\n", assembly_label);
        assembly_label++;
    }
#line 2291 "yprojecty.tab.c"
    break;

  case 78: /* conditional_statement: IF '(' expression ')' $@12 if_statement ELSE $@13 if_statement  */
#line 631 "yprojecty.y"
    {
        if ((yyvsp[-6].expr_node)->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in if statement must be boolean at line %d\n", yylineno);
            YYERROR;
        }
        fprintf(output_file, "L%d:\n", assembly_label);
        assembly_label++;
    }
#line 2304 "yprojecty.tab.c"
    break;

  case 79: /* conditional_statement: IF '(' expression ')' if_statement  */
#line 640 "yprojecty.y"
    {
        if ((yyvsp[-2].expr_node)->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in if statement must be boolean at line %d\n", yylineno);
            YYERROR;
        }
    }
#line 2315 "yprojecty.tab.c"
    break;

  case 80: /* $@14: %empty  */
#line 649 "yprojecty.y"
    {enter_new_table(0,0);}
#line 2321 "yprojecty.tab.c"
    break;

  case 81: /* if_statement: $@14 statement  */
#line 651 "yprojecty.y"
    {dump_current_table();leave_table();}
#line 2327 "yprojecty.tab.c"
    break;

  case 83: /* $@15: %empty  */
#line 656 "yprojecty.y"
    {
        inside_loop++;
    }
#line 2335 "yprojecty.tab.c"
    break;

  case 84: /* $@16: %empty  */
#line 660 "yprojecty.y"
    {
        if ((yyvsp[0].expr_node)->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in while loop must be boolean at line %d\n", yylineno);
            YYERROR;
        }
    }
#line 2346 "yprojecty.tab.c"
    break;

  case 85: /* loop_statement: WHILE $@15 '(' expression $@16 ')' if_statement  */
#line 667 "yprojecty.y"
    {
        inside_loop--;
    }
#line 2354 "yprojecty.tab.c"
    break;

  case 86: /* $@17: %empty  */
#line 671 "yprojecty.y"
    {
        inside_loop++;
    }
#line 2362 "yprojecty.tab.c"
    break;

  case 87: /* $@18: %empty  */
#line 675 "yprojecty.y"
    {
        if ((yyvsp[0].expr_node)->type != TYPE_BOOL) {
            fprintf(stderr, "Error: Condition in while loop must be boolean at line %d\n", yylineno);
            YYERROR;
        }
    }
#line 2373 "yprojecty.tab.c"
    break;

  case 88: /* loop_statement: FOR $@17 '(' simple_statment expression $@18 ';' simple_statment_without_semicolon ')' if_statement  */
#line 682 "yprojecty.y"
    {
        
        inside_loop--;
    }
#line 2382 "yprojecty.tab.c"
    break;

  case 89: /* $@19: %empty  */
#line 687 "yprojecty.y"
    {
        inside_loop++;
    }
#line 2390 "yprojecty.tab.c"
    break;

  case 90: /* $@20: %empty  */
#line 691 "yprojecty.y"
    {
        if ((yyvsp[-2].expr_node)->type != TYPE_INT||(yyvsp[0].expr_node)->type != TYPE_INT) {
            fprintf(stderr, "Error: Condition in foreach loop must be integer at line %d\n", yylineno);
            YYERROR;
        }
    }
#line 2401 "yprojecty.tab.c"
    break;

  case 91: /* loop_statement: FOREACH $@19 '(' ID ':' expression DOT_DOT expression $@20 ')' if_statement  */
#line 698 "yprojecty.y"
    {
        inside_loop--;
        dump_current_table();
        leave_table();
        // Verify ID is declared and of compatible type with expressions
        Symbol* sym = lookup_symbol((yyvsp[-7].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[-7].svalue), yylineno);
            YYERROR;
        }
    }
#line 2417 "yprojecty.tab.c"
    break;

  case 92: /* $@21: %empty  */
#line 713 "yprojecty.y"
         {
        fprintf(output_file, "getstatic java.io.PrintStream java.lang.System.out\n");
    }
#line 2425 "yprojecty.tab.c"
    break;

  case 93: /* print_statement: PRINT $@21 expression  */
#line 715 "yprojecty.y"
                 {
        if ((yyvsp[0].expr_node)->type == TYPE_INT) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(int)\n");
        } else if ((yyvsp[0].expr_node)->type == TYPE_FLOAT) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(float)\n");
        } else if ((yyvsp[0].expr_node)->type == TYPE_BOOL) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(int)\n");
        } else if ((yyvsp[0].expr_node)->type == TYPE_STRING) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(java.lang.String)\n");
        } else {
            fprintf(stderr, "Error: Cannot print type '%s' at line %d\n", type_to_string((yyvsp[0].expr_node)->type), yylineno);
            YYERROR;
        }
    }
#line 2444 "yprojecty.tab.c"
    break;

  case 94: /* $@22: %empty  */
#line 730 "yprojecty.y"
           {
        fprintf(output_file, "getstatic java.io.PrintStream java.lang.System.out\n");
    }
#line 2452 "yprojecty.tab.c"
    break;

  case 95: /* print_statement: PRINTLN $@22 expression  */
#line 732 "yprojecty.y"
                {
        if ((yyvsp[0].expr_node)->type == TYPE_INT) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(int)\n");
        } else if ((yyvsp[0].expr_node)->type == TYPE_FLOAT) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(float)\n");
        } else if ((yyvsp[0].expr_node)->type == TYPE_BOOL) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(int)\n");
        } else if ((yyvsp[0].expr_node)->type == TYPE_STRING) {
            fprintf(output_file, "invokevirtual void java.io.PrintStream.println(java.lang.String)\n");
        } else {
            fprintf(stderr, "Error: Cannot print type '%s' at line %d\n", type_to_string((yyvsp[0].expr_node)->type), yylineno);
            YYERROR;
        }
    }
#line 2471 "yprojecty.tab.c"
    break;

  case 96: /* read_statement: READ ID  */
#line 749 "yprojecty.y"
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
#line 2487 "yprojecty.tab.c"
    break;

  case 97: /* increment_decrement_statement: ID PLUS_PLUS  */
#line 763 "yprojecty.y"
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
#line 2507 "yprojecty.tab.c"
    break;

  case 98: /* increment_decrement_statement: ID MINUS_MINUS  */
#line 779 "yprojecty.y"
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
#line 2527 "yprojecty.tab.c"
    break;

  case 99: /* increment_decrement_statement: ID array_size_or_location PLUS_PLUS  */
#line 795 "yprojecty.y"
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
#line 2547 "yprojecty.tab.c"
    break;

  case 100: /* increment_decrement_statement: ID array_size_or_location MINUS_MINUS  */
#line 811 "yprojecty.y"
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
#line 2567 "yprojecty.tab.c"
    break;

  case 101: /* return_statement: RETURN expression ';'  */
#line 829 "yprojecty.y"
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
        if (!is_assignment_compatible(current_function_return_type, (yyvsp[-1].expr_node)->type)) {
            fprintf(stderr, "Error: Cannot return %s from function returning %s at line %d\n",
                   type_to_string((yyvsp[-1].expr_node)->type), type_to_string(current_function_return_type), yylineno);
            YYERROR;
        }
        has_return = 1; // Mark that this function has a return statement
        fprintf(output_file, "ireturn\n");

    }
#line 2591 "yprojecty.tab.c"
    break;

  case 102: /* return_statement: RETURN ';'  */
#line 849 "yprojecty.y"
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
    }
#line 2608 "yprojecty.tab.c"
    break;

  case 103: /* expression: expression EQUAL expression  */
#line 867 "yprojecty.y"
    {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_equal));
        (yyval.expr_node)->value.bvalue = (yyvsp[-2].expr_node)->value.bvalue == (yyvsp[0].expr_node)->value.bvalue;
        fprintf(output_file, "isub\n", assembly_label);
        fprintf(output_file, "ifeq L%d\n", assembly_label);
        fprintf(output_file, "iconst_0\n");
        fprintf(output_file, "goto L%d\n", assembly_label+1);
        fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
        assembly_label++;
        fprintf(output_file, "L%d:\n", assembly_label);
        assembly_label++;
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2627 "yprojecty.tab.c"
    break;

  case 104: /* expression: expression NOT_EQUAL expression  */
#line 881 "yprojecty.y"
                                   {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_not_equal));
        (yyval.expr_node)->value.bvalue = (yyvsp[-2].expr_node)->value.bvalue != (yyvsp[0].expr_node)->value.bvalue;
        fprintf(output_file, "isub\n", assembly_label);
        fprintf(output_file, "ifne L%d\n", assembly_label);
        fprintf(output_file, "iconst_0\n");
        fprintf(output_file, "goto L%d\n", assembly_label+1);
        fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
        assembly_label++;
        fprintf(output_file, "L%d:\n", assembly_label);
        assembly_label++;
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2646 "yprojecty.tab.c"
    break;

  case 105: /* expression: expression '<' expression  */
#line 895 "yprojecty.y"
                             {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_less));
        if ((yyvsp[-2].expr_node)->type == TYPE_INT && (yyvsp[0].expr_node)->type == TYPE_INT) {
            (yyval.expr_node)->value.bvalue = (yyvsp[-2].expr_node)->value.ivalue < (yyvsp[0].expr_node)->value.ivalue;
        } else if ((yyvsp[-2].expr_node)->type == TYPE_FLOAT || (yyvsp[0].expr_node)->type == TYPE_FLOAT) {
            float left = ((yyvsp[-2].expr_node)->type == TYPE_FLOAT) ? (yyvsp[-2].expr_node)->value.fvalue : (float)(yyvsp[-2].expr_node)->value.ivalue;
            float right = ((yyvsp[0].expr_node)->type == TYPE_FLOAT) ? (yyvsp[0].expr_node)->value.fvalue : (float)(yyvsp[0].expr_node)->value.ivalue;
            (yyval.expr_node)->value.bvalue = left < right;
        } else {
            (yyval.expr_node)->value.bvalue = 0;  // Default for other types
        }
        fprintf(output_file, "isub\n", assembly_label);
        fprintf(output_file, "iflt L%d\n", assembly_label);
        fprintf(output_file, "iconst_0\n");
        fprintf(output_file, "goto L%d\n", assembly_label+1);
        fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
        assembly_label++;
        fprintf(output_file, "L%d:\n", assembly_label);
        assembly_label++;
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2673 "yprojecty.tab.c"
    break;

  case 106: /* expression: expression '>' expression  */
#line 917 "yprojecty.y"
                             {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_greater));
        (yyval.expr_node)->value.bvalue = (yyvsp[-2].expr_node)->value.bvalue > (yyvsp[0].expr_node)->value.bvalue;
        fprintf(output_file, "isub\n", assembly_label);
        fprintf(output_file, "ifgt L%d\n", assembly_label);
        fprintf(output_file, "iconst_0\n");
        fprintf(output_file, "goto L%d\n", assembly_label+1);
        fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
        assembly_label++;
        fprintf(output_file, "L%d:\n", assembly_label);
        assembly_label++;
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2692 "yprojecty.tab.c"
    break;

  case 107: /* expression: expression LESS_EQUAL expression  */
#line 931 "yprojecty.y"
                                    {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_less_equal));
        (yyval.expr_node)->value.bvalue = (yyvsp[-2].expr_node)->value.bvalue <= (yyvsp[0].expr_node)->value.bvalue;
        fprintf(output_file, "isub\n", assembly_label);
        fprintf(output_file, "ifle L%d\n", assembly_label);
        fprintf(output_file, "iconst_0\n");
        fprintf(output_file, "goto L%d\n", assembly_label+1);
        fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
        assembly_label++;
        fprintf(output_file, "L%d:\n", assembly_label);
        assembly_label++;
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2711 "yprojecty.tab.c"
    break;

  case 108: /* expression: expression GREATER_EQUAL expression  */
#line 945 "yprojecty.y"
                                       {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_greater_equal));
        (yyval.expr_node)->value.bvalue = (yyvsp[-2].expr_node)->value.bvalue >= (yyvsp[0].expr_node)->value.bvalue;
        fprintf(output_file, "isub\n", assembly_label);
        fprintf(output_file, "ifge L%d\n", assembly_label);
        fprintf(output_file, "iconst_0\n");
        fprintf(output_file, "goto L%d\n", assembly_label+1);
        fprintf(output_file, "L%d:\niconst_1\n", assembly_label);
        assembly_label++;
        fprintf(output_file, "L%d:\n", assembly_label);
        assembly_label++;
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2730 "yprojecty.tab.c"
    break;

  case 109: /* expression: expression AND_AND expression  */
#line 959 "yprojecty.y"
                                 {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_and));
        (yyval.expr_node)->value.bvalue = (yyvsp[-2].expr_node)->value.bvalue && (yyvsp[0].expr_node)->value.bvalue;
        fprintf(output_file, "iand\n", assembly_label);
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2742 "yprojecty.tab.c"
    break;

  case 110: /* expression: expression OR_OR expression  */
#line 966 "yprojecty.y"
                               {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_or));
        (yyval.expr_node)->value.bvalue = (yyvsp[-2].expr_node)->value.bvalue || (yyvsp[0].expr_node)->value.bvalue;
        fprintf(output_file, "ior\n", assembly_label);
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2754 "yprojecty.tab.c"
    break;

  case 111: /* expression: '!' expression  */
#line 973 "yprojecty.y"
                  {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[0].expr_node)->type, TYPE_BOOL, op_not));
        (yyval.expr_node)->value.bvalue = !(yyvsp[0].expr_node)->value.bvalue;
        fprintf(output_file, "ixor\n");
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2765 "yprojecty.tab.c"
    break;

  case 112: /* expression: INT_LITERAL  */
#line 979 "yprojecty.y"
               {
        (yyval.expr_node) = create_expr_node(TYPE_INT);
        (yyval.expr_node)->value.ivalue = (yyvsp[0].ivalue);
        fprintf(output_file, "sipush %d\n", (yyvsp[0].ivalue));
    }
#line 2775 "yprojecty.tab.c"
    break;

  case 113: /* expression: REAL_LITERAL  */
#line 984 "yprojecty.y"
                {
        (yyval.expr_node) = create_expr_node(TYPE_FLOAT);
        (yyval.expr_node)->value.fvalue = (yyvsp[0].fvalue);
        fprintf(output_file, "ldc %f\n", (yyvsp[0].fvalue));
    }
#line 2785 "yprojecty.tab.c"
    break;

  case 114: /* expression: STRING_LITERAL  */
#line 989 "yprojecty.y"
                  {
        (yyval.expr_node) = create_expr_node(TYPE_STRING);
        (yyval.expr_node)->value.svalue = strdup((yyvsp[0].svalue));
        fprintf(output_file, "ldc \"%s\"\n", (yyvsp[0].svalue));
    }
#line 2795 "yprojecty.tab.c"
    break;

  case 115: /* expression: TRUE_TOKEN  */
#line 994 "yprojecty.y"
              {
        (yyval.expr_node) = create_expr_node(TYPE_BOOL);
        (yyval.expr_node)->value.bvalue = 1;
        fprintf(output_file, "sipush 1\n");
    }
#line 2805 "yprojecty.tab.c"
    break;

  case 116: /* expression: FALSE_TOKEN  */
#line 999 "yprojecty.y"
               {
        (yyval.expr_node) = create_expr_node(TYPE_BOOL);
        (yyval.expr_node)->value.bvalue = 0;
        fprintf(output_file, "sipush 0\n");
    }
#line 2815 "yprojecty.tab.c"
    break;

  case 117: /* expression: function_invocation  */
#line 1004 "yprojecty.y"
                       {
        if ((yyvsp[0].expr_node)->type == TYPE_VOID) {
            fprintf(stderr, "Error: Function returns void at line %d\n", yylineno);
            YYERROR;
        }
        (yyval.expr_node) = create_expr_node((yyvsp[0].expr_node)->type);
        
    }
#line 2828 "yprojecty.tab.c"
    break;

  case 118: /* expression: ID  */
#line 1012 "yprojecty.y"
      {
        Symbol* sym = lookup_symbol((yyvsp[0].svalue));
        if(sym == NULL) {
            fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", (yyvsp[0].svalue), yylineno);
            YYERROR;
        }
        (yyval.expr_node) = create_expr_node(sym->type);
        if (sym->type == TYPE_INT) {
            (yyval.expr_node)->value.ivalue = sym->value.ivalue;
        } else if (sym->type == TYPE_FLOAT) {
            (yyval.expr_node)->value.fvalue = sym->value.fvalue;
        } else if (sym->type == TYPE_BOOL) {
            (yyval.expr_node)->value.bvalue = sym->value.bvalue;
        } else if (sym->type == TYPE_STRING) {
            (yyval.expr_node)->value.svalue = strdup(sym->value.svalue);
        }
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
            fprintf(output_file, "getstatic int %s.%s\n",classname, sym->name);
        } else {
            fprintf(output_file, "iload %d\n", sym->variable_label);
        }
    }
#line 2874 "yprojecty.tab.c"
    break;

  case 119: /* expression: ID array_size_or_location  */
#line 1053 "yprojecty.y"
                             {}
#line 2880 "yprojecty.tab.c"
    break;

  case 120: /* expression: '(' expression ')'  */
#line 1054 "yprojecty.y"
                      {
        (yyval.expr_node) = create_expr_node((yyvsp[-1].expr_node)->type);
        (yyval.expr_node)->value = (yyvsp[-1].expr_node)->value;
        free_expr_node((yyvsp[-1].expr_node));
    }
#line 2890 "yprojecty.tab.c"
    break;

  case 121: /* expression: expression '+' expression  */
#line 1059 "yprojecty.y"
                             {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_plus));
        if((yyval.expr_node)->type == TYPE_STRING) {
            (yyval.expr_node)->value.svalue = (char*)malloc(strlen((yyvsp[-2].expr_node)->value.svalue) + strlen((yyvsp[0].expr_node)->value.svalue) + 1);
            strcpy((yyval.expr_node)->value.svalue, (yyvsp[-2].expr_node)->value.svalue);
            strcat((yyval.expr_node)->value.svalue, (yyvsp[0].expr_node)->value.svalue);
        } else {
            (yyval.expr_node)->value.ivalue = (yyvsp[-2].expr_node)->value.ivalue + (yyvsp[0].expr_node)->value.ivalue;
        }
        fprintf(output_file, "iadd\n");
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2908 "yprojecty.tab.c"
    break;

  case 122: /* expression: expression '-' expression  */
#line 1072 "yprojecty.y"
                             {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_minus));
        if((yyval.expr_node)->type == TYPE_STRING) {
            yyerror("Type error: Cannot subtract strings");
            YYERROR;
        } else {
            (yyval.expr_node)->value.ivalue = (yyvsp[-2].expr_node)->value.ivalue - (yyvsp[0].expr_node)->value.ivalue;
        }
        fprintf(output_file, "isub\n");
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2925 "yprojecty.tab.c"
    break;

  case 123: /* expression: expression '*' expression  */
#line 1084 "yprojecty.y"
                             {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_multiply));
        if((yyval.expr_node)->type == TYPE_STRING) {
            yyerror("Type error: Cannot multiply strings");
            YYERROR;
        } else {
            (yyval.expr_node)->value.ivalue = (yyvsp[-2].expr_node)->value.ivalue * (yyvsp[0].expr_node)->value.ivalue;
        }
        fprintf(output_file, "imul\n");
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2942 "yprojecty.tab.c"
    break;

  case 124: /* expression: expression '/' expression  */
#line 1096 "yprojecty.y"
                             {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_divide));
        if((yyval.expr_node)->type == TYPE_STRING) {
            yyerror("Type error: Cannot divide strings");
            YYERROR;
        } else {
            (yyval.expr_node)->value.ivalue = (yyvsp[-2].expr_node)->value.ivalue / (yyvsp[0].expr_node)->value.ivalue;
        }
        if ((yyvsp[0].expr_node)->value.ivalue == 0) {
            yyerror("Error: Division by zero");
            YYERROR;
        }
        fprintf(output_file, "idiv\n");
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2963 "yprojecty.tab.c"
    break;

  case 125: /* expression: expression '%' expression  */
#line 1112 "yprojecty.y"
                             {
        (yyval.expr_node) = create_expr_node(check_expression_type((yyvsp[-2].expr_node)->type, (yyvsp[0].expr_node)->type, op_modulus));
        if((yyval.expr_node)->type == TYPE_STRING) {
            yyerror("Type error: Cannot modulo strings");
            YYERROR;
        } else if ((yyvsp[0].expr_node)->value.ivalue == 0) {
            yyerror("Error: Division by zero");
            YYERROR;
        } else {
            (yyval.expr_node)->value.ivalue = (yyvsp[-2].expr_node)->value.ivalue % (yyvsp[0].expr_node)->value.ivalue;
        }
        if ((yyvsp[0].expr_node)->value.ivalue == 0) {
            yyerror("Error: Division by zero");
            YYERROR;
        }
        fprintf(output_file, "irem\n");
        free_expr_node((yyvsp[-2].expr_node));
        free_expr_node((yyvsp[0].expr_node));
    }
#line 2987 "yprojecty.tab.c"
    break;

  case 126: /* expression: '-' expression  */
#line 1131 "yprojecty.y"
                               {
        (yyval.expr_node) = create_expr_node((yyvsp[0].expr_node)->type);
        if((yyval.expr_node)->type == TYPE_STRING) {
            yyerror("Type error: Cannot negate strings");
            YYERROR;
        } else if ((yyvsp[0].expr_node)->type == TYPE_INT) {
            (yyval.expr_node)->value.ivalue = -(yyvsp[0].expr_node)->value.ivalue;
        } else if ((yyvsp[0].expr_node)->type == TYPE_FLOAT) {
            (yyval.expr_node)->value.fvalue = -(yyvsp[0].expr_node)->value.fvalue;
        } else if ((yyvsp[0].expr_node)->type == TYPE_BOOL) {
            if ((yyvsp[0].expr_node)->value.bvalue) {
                (yyval.expr_node)->value.bvalue = 0;
            } else {
                (yyval.expr_node)->value.bvalue = 1;
            }
        }else {
            yyerror("Type error: Cannot negate non-numeric type");
            YYERROR;
        }
        fprintf(output_file, "ineg\n");
        free_expr_node((yyvsp[0].expr_node));
    }
#line 3014 "yprojecty.tab.c"
    break;


#line 3018 "yprojecty.tab.c"

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

#line 1153 "yprojecty.y"

int main(int argc, char** argv)  {

    extern int yydebug;
    extern FILE *yyin;
    yydebug = 0;
    current_table = enter_new_table(0,1);

    

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
    printf("Class name: %s\n", classname);
    printf("Input file: %s\n", input_file_name);

    open_output_file(classname);

    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", input_file_name);
        return EXIT_FAILURE;
    }
    yyin = input_file;

    fprintf(output_file,"class %s {\n", classname);

    printf("Starting parser...\n");
    yyparse();
    dump_current_table();
    leave_table();
    printf("Parser finished.\n");

    fprintf(output_file,"}\n");
    fclose(output_file);
    return 0;
}
