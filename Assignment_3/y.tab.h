/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OPEN_BRACKET = 258,
    CLOSE_BRACKET = 259,
    ASSIGN = 260,
    PRINT = 261,
    num = 262,
    VARIABLE = 263,
    ADD = 264,
    SUB = 265,
    MUL = 266,
    DIV = 267,
    POW = 268,
    EXP = 269,
    SQRT = 270,
    MOD = 271,
    PI = 272,
    E = 273,
    COS = 274,
    SIN = 275,
    TAN = 276,
    ASIN = 277,
    ACOS = 278,
    ATAN = 279,
    COT = 280,
    SEC = 281,
    COSEC = 282,
    LOG = 283,
    LN = 284
  };
#endif
/* Tokens.  */
#define OPEN_BRACKET 258
#define CLOSE_BRACKET 259
#define ASSIGN 260
#define PRINT 261
#define num 262
#define VARIABLE 263
#define ADD 264
#define SUB 265
#define MUL 266
#define DIV 267
#define POW 268
#define EXP 269
#define SQRT 270
#define MOD 271
#define PI 272
#define E 273
#define COS 274
#define SIN 275
#define TAN 276
#define ASIN 277
#define ACOS 278
#define ATAN 279
#define COT 280
#define SEC 281
#define COSEC 282
#define LOG 283
#define LN 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "calc.y"

double p;
char id;

#line 120 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
