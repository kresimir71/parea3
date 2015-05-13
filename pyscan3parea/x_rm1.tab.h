/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_X_RM1_TAB_H_INCLUDED
# define YY_YY_X_RM1_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_EXIT = 258,
     TOK_LONGSTRINGLITERALSINGLEQUOTE = 259,
     TOK_LONGSTRINGLITERALDOUBLEQUOTE = 260,
     TOK_SHORTSTRINGLITERALSINGLEQUOTE = 261,
     TOK_SHORTSTRINGLITERALDOUBLEQUOTE = 262,
     TOK_COMMENT = 263,
     TOK_INTEGER = 264,
     TOK_LONGINTEGER = 265,
     TOK_FLOATNUMBER = 266,
     TOK_IMAGNUMBER = 267,
     TOK_SPACE = 268,
     TOK_NEWLINE = 269,
     TOK_OP = 270,
     TOK_CP = 271,
     TOK_COMMA = 272,
     TOK_OB = 273,
     TOK_CB = 274,
     TOK_FOR = 275,
     TOK_IF = 276,
     TOK_AO = 277,
     TOK_AC = 278,
     TOK_CO = 279,
     TOK_BQ = 280,
     TOK_FS = 281,
     TOK_FSFSFS = 282,
     TOK_ST = 283,
     TOK_STST = 284,
     TOK_EQ = 285,
     TOK_MN = 286,
     TOK_PL = 287,
     TOK_TL = 288,
     TOK_DIDI = 289,
     TOK_DI = 290,
     TOK_PC = 291,
     TOK_LTLT = 292,
     TOK_GTGT = 293,
     TOK_AS = 294,
     TOK_EX = 295,
     TOK_OR = 296,
     TOK_LT = 297,
     TOK_GT = 298,
     TOK_EQEQ = 299,
     TOK_GTEQ = 300,
     TOK_LTEQ = 301,
     TOK_LTGT = 302,
     TOK_ETEQ = 303,
     TOK_IS = 304,
     TOK_NOT = 305,
     TOK_IN = 306,
     TOK_WRITTEN_OR = 307,
     TOK_AND = 308,
     TOK_LAMBDA = 309,
     TOK_ASSERT = 310,
     TOK_PLEQ = 311,
     TOK_MNEQ = 312,
     TOK_STEQ = 313,
     TOK_DIEQ = 314,
     TOK_PCEQ = 315,
     TOK_STSTEQ = 316,
     TOK_GTGTEQ = 317,
     TOK_LTLTEQ = 318,
     TOK_ASEQ = 319,
     TOK_EXEQ = 320,
     TOK_OREQ = 321,
     TOK_PASS = 322,
     TOK_DEL = 323,
     TOK_PRINT = 324,
     TOK_RETURN = 325,
     TOK_YIELD = 326,
     TOK_RAISE = 327,
     TOK_BREAK = 328,
     TOK_CONTINUE = 329,
     TOK_IMPORT = 330,
     TOK_WRITTEN_AS = 331,
     TOK_FROM = 332,
     TOK_GLOBAL = 333,
     TOK_EXEC = 334,
     TOK_SC = 335,
     TOK_ELIF = 336,
     TOK_ELSE = 337,
     TOK_WHILE = 338,
     TOK_TRY = 339,
     TOK_EXCEPT = 340,
     TOK_FINALLY = 341,
     TOK_WITH = 342,
     TOK_DEF = 343,
     TOK_STRUDL = 344,
     TOK_CLASS = 345,
     TOK_IDENTIFIER = 346,
     TOK_ANYCHAR = 347,
     TOK_INDENT = 348,
     TOK_DEDENT = 349,
     TOK_SPACE_INDENT = 350,
     TOK_SPACE_EMPTY_LINE = 351,
     TOK_SPACE_NO_INDENT = 352,
     TOK_NEW_LINE_IGNORED = 353,
     TOK_SPACE_AT_END_OF_LINE = 354,
     TOK_SPACE_OTHER = 355,
     TERMINAL_MAX_MIN_NONTERMINAL = 356,
     PYTHON_ROOT_SYMBOL_USED_ONLY_IN_PYTHON = 357,
     NT_ERROR = 358,
     UNUSED_TOK_EXIT = 359,
     UNUSED_TOK_LONGSTRINGLITERALSINGLEQUOTE = 360,
     UNUSED_TOK_LONGSTRINGLITERALDOUBLEQUOTE = 361,
     UNUSED_TOK_SHORTSTRINGLITERALSINGLEQUOTE = 362,
     UNUSED_TOK_SHORTSTRINGLITERALDOUBLEQUOTE = 363,
     UNUSED_TOK_COMMENT = 364,
     UNUSED_TOK_INTEGER = 365,
     UNUSED_TOK_LONGINTEGER = 366,
     UNUSED_TOK_FLOATNUMBER = 367,
     UNUSED_TOK_IMAGNUMBER = 368,
     UNUSED_TOK_SPACE = 369,
     UNUSED_TOK_NEWLINE = 370,
     UNUSED_TOKEN_OP = 371,
     UNUSED_TOKEN_CP = 372,
     UNUSED_TOKEN_COMMA = 373,
     UNUSED_TOKEN_ = 374,
     UNUSED_TOK_IDENTIFIER = 375,
     UNUSED_TOK_ANYCHAR = 376,
     UNUSED_TOK_INDENT = 377,
     UNUSED_TOK_DEDENT = 378,
     MAIN_FILE = 379,
     MAIN_FILE_SEQ_1 = 380,
     MAIN_FILE_SEQ_1_ELM = 381
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_X_RM1_TAB_H_INCLUDED  */
