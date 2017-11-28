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
     SEMICOLON = 259,
     OPEN_CURLY_BRACKET = 260,
     CLOSE_CURLY_BRACKET = 261,
     HASHTAG = 262,
     EQUAL = 263,
     OPEN_PARENTHESES = 264,
     CLOSE_PARENTHESES = 265,
     LESS_THAN = 266,
     GREATER_THAN = 267,
     ADD = 268,
     SUBSTRACT = 269,
     INTEGER = 270,
     DOUBLE = 271,
     VARIABLE = 272,
     STRING = 273,
     INTEGER_TYPE = 274,
     DOUBLE_TYPE = 275,
     STRING_TYPE = 276,
     RETURN = 277
   };
#endif
/* Tokens.  */
#define QUOTE 258
#define SEMICOLON 259
#define OPEN_CURLY_BRACKET 260
#define CLOSE_CURLY_BRACKET 261
#define HASHTAG 262
#define EQUAL 263
#define OPEN_PARENTHESES 264
#define CLOSE_PARENTHESES 265
#define LESS_THAN 266
#define GREATER_THAN 267
#define ADD 268
#define SUBSTRACT 269
#define INTEGER 270
#define DOUBLE 271
#define VARIABLE 272
#define STRING 273
#define INTEGER_TYPE 274
#define DOUBLE_TYPE 275
#define STRING_TYPE 276
#define RETURN 277




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

