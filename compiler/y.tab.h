/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     QUOTE = 258,
     INIT = 259,
     PRINT = 260,
     SEMICOLON = 261,
     OPEN_CURLY_BRACKET = 262,
     CLOSE_CURLY_BRACKET = 263,
     HASHTAG = 264,
     OPEN_PARENTHESES = 265,
     CLOSE_PARENTHESES = 266,
     ADD = 267,
     SUBSTRACT = 268,
     INTEGER = 269,
     DOUBLE = 270,
     VARIABLE = 271,
     STRING = 272,
     INTEGER_TYPE = 273,
     DOUBLE_TYPE = 274,
     STRING_TYPE = 275,
     ACTION_TYPE = 276,
     INCLUDE = 277,
     COLON = 278,
     FOR = 279,
     WHILE = 280,
     IF = 281,
     ELSE = 282,
     ELSEIF = 283,
     ON = 284,
     RUN = 285,
     EQUAL = 286,
     NOT_EQUAL = 287,
     GREATER_THAN = 288,
     EQUAL_GREATER_THAN = 289,
     EQUAL_LESS_THAN = 290,
     LESS_THAN = 291,
     MULTIPLY = 292,
     DIVIDE = 293,
     RETURN = 294
   };
#endif
/* Tokens.  */
#define QUOTE 258
#define INIT 259
#define PRINT 260
#define SEMICOLON 261
#define OPEN_CURLY_BRACKET 262
#define CLOSE_CURLY_BRACKET 263
#define HASHTAG 264
#define OPEN_PARENTHESES 265
#define CLOSE_PARENTHESES 266
#define ADD 267
#define SUBSTRACT 268
#define INTEGER 269
#define DOUBLE 270
#define VARIABLE 271
#define STRING 272
#define INTEGER_TYPE 273
#define DOUBLE_TYPE 274
#define STRING_TYPE 275
#define ACTION_TYPE 276
#define INCLUDE 277
#define COLON 278
#define FOR 279
#define WHILE 280
#define IF 281
#define ELSE 282
#define ELSEIF 283
#define ON 284
#define RUN 285
#define EQUAL 286
#define NOT_EQUAL 287
#define GREATER_THAN 288
#define EQUAL_GREATER_THAN 289
#define EQUAL_LESS_THAN 290
#define LESS_THAN 291
#define MULTIPLY 292
#define DIVIDE 293
#define RETURN 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 10 "grammar.y"
{char * string ; int integer;}
/* Line 1529 of yacc.c.  */
#line 129 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

