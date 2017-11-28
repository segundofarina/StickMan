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
     OPEN_ANGLE_BRACKET = 267,
     CLOSE_ANGLE_BRACKET = 268,
     ADD = 269,
     SUBSTRACT = 270,
     INTEGER = 271,
     DOUBLE = 272,
     VARIABLE = 273,
     STRING = 274,
     INTEGER_TYPE = 275,
     DOUBLE_TYPE = 276,
     STRING_TYPE = 277
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
#define OPEN_ANGLE_BRACKET 267
#define CLOSE_ANGLE_BRACKET 268
#define ADD 269
#define SUBSTRACT 270
#define INTEGER 271
#define DOUBLE 272
#define VARIABLE 273
#define STRING 274
#define INTEGER_TYPE 275
#define DOUBLE_TYPE 276
#define STRING_TYPE 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 10 "yacc.y"
{char * string ; int integer;}
/* Line 1529 of yacc.c.  */
#line 95 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

