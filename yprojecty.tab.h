/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YPROJECTY_TAB_H_INCLUDED
# define YY_YY_YPROJECTY_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BOOL = 258,                    /* BOOL  */
    BREAK = 259,                   /* BREAK  */
    CASE = 260,                    /* CASE  */
    CHAR = 261,                    /* CHAR  */
    CONST = 262,                   /* CONST  */
    CONTINUE = 263,                /* CONTINUE  */
    DEFAULT = 264,                 /* DEFAULT  */
    DO = 265,                      /* DO  */
    DOUBLE = 266,                  /* DOUBLE  */
    ELSE = 267,                    /* ELSE  */
    EXTERN = 268,                  /* EXTERN  */
    FALSE_TOKEN = 269,             /* FALSE_TOKEN  */
    FLOAT = 270,                   /* FLOAT  */
    FOR = 271,                     /* FOR  */
    FOREACH = 272,                 /* FOREACH  */
    IF = 273,                      /* IF  */
    INT = 274,                     /* INT  */
    PRINT = 275,                   /* PRINT  */
    PRINTLN = 276,                 /* PRINTLN  */
    READ = 277,                    /* READ  */
    RETURN = 278,                  /* RETURN  */
    STRING = 279,                  /* STRING  */
    SWITCH = 280,                  /* SWITCH  */
    TRUE_TOKEN = 281,              /* TRUE_TOKEN  */
    VOID = 282,                    /* VOID  */
    WHILE = 283,                   /* WHILE  */
    INT_LITERAL = 284,             /* INT_LITERAL  */
    REAL_LITERAL = 285,            /* REAL_LITERAL  */
    STRING_LITERAL = 286,          /* STRING_LITERAL  */
    MAIN = 287,                    /* MAIN  */
    ID = 288,                      /* ID  */
    PLUS_PLUS = 289,               /* PLUS_PLUS  */
    MINUS_MINUS = 290,             /* MINUS_MINUS  */
    LESS_EQUAL = 291,              /* LESS_EQUAL  */
    GREATER_EQUAL = 292,           /* GREATER_EQUAL  */
    EQUAL = 293,                   /* EQUAL  */
    NOT_EQUAL = 294,               /* NOT_EQUAL  */
    AND_AND = 295,                 /* AND_AND  */
    OR_OR = 296,                   /* OR_OR  */
    DOT_DOT = 297,                 /* DOT_DOT  */
    UMINUS = 298,                  /* UMINUS  */
    LOWER_THAN_ELSE = 299          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 387 "yprojecty.y"

    int ivalue;
    float fvalue;
    char* svalue;
    int dtype;
    struct ExpressionNode* expr_node;

#line 116 "yprojecty.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_YPROJECTY_TAB_H_INCLUDED  */
