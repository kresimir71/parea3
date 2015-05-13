/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 5 "x_rm1.y"

     #include "math.h"
     #include "stdio.h"
     #include "rm1.h"
     #include "x_io1.h"
     #include "rbt.h"
     #include "rbt_shortcuts.h"
     #include "main.h"
     #include "debug.h"
     #include "misc.h"
     #include "goals.h"
     #include "debug2.h"
#ifndef NDEBUG
     #define stderr fp_error
       /*file pointer for error output*/
#endif
       FILE *fp_error;
     /*int flex_used = 0;*/
     
/* Line 371 of yacc.c  */
#line 88 "x_rm1.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "x_rm1.tab.h".  */
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 279 "x_rm1.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  98
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNRULES -- Number of states.  */
#define YYNSTATES  101

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   381

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    14,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    51,    53,    55,    57,    59,
      61,    63,    65,    67,    69,    71,    73,    75,    77,    79,
      81,    83,    85,    87,    89,    91,    93,    95,    97,    99,
     101,   103,   105,   107,   109,   111,   113,   115,   117,   119,
     121,   123,   125,   127,   129,   131,   133,   135,   137,   139,
     141,   143,   145,   147,   149,   151,   153,   155,   157,   159,
     161,   163,   165,   167,   169,   171,   173,   175,   177,   179,
     181,   183,   185,   187,   189,   191,   193,   195,   197
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     128,     0,    -1,   130,    -1,   129,    -1,     1,    -1,   131,
       3,    -1,   132,    -1,   131,   132,    -1,    12,    -1,     9,
      -1,     8,    -1,    10,    -1,    11,    -1,    91,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,    16,    -1,    15,
      -1,    14,    -1,    13,    -1,    90,    -1,    89,    -1,    88,
      -1,    87,    -1,    86,    -1,    85,    -1,    84,    -1,    83,
      -1,    82,    -1,    81,    -1,    24,    -1,    21,    -1,    80,
      -1,    79,    -1,    78,    -1,    77,    -1,    76,    -1,    75,
      -1,    74,    -1,    73,    -1,    72,    -1,    71,    -1,    70,
      -1,    69,    -1,    68,    -1,    67,    -1,    66,    -1,    65,
      -1,    64,    -1,    63,    -1,    62,    -1,    61,    -1,    60,
      -1,    59,    -1,    58,    -1,    57,    -1,    56,    -1,    55,
      -1,    54,    -1,    53,    -1,    52,    -1,    51,    -1,    50,
      -1,    49,    -1,    48,    -1,    47,    -1,    46,    -1,    45,
      -1,    44,    -1,    43,    -1,    42,    -1,    41,    -1,    40,
      -1,    39,    -1,    38,    -1,    37,    -1,    36,    -1,    35,
      -1,    34,    -1,    33,    -1,    32,    -1,    31,    -1,    30,
      -1,    29,    -1,    28,    -1,    27,    -1,    26,    -1,    25,
      -1,    23,    -1,    22,    -1,    20,    -1,    19,    -1,    18,
      -1,    17,    -1,    92,    -1,    93,    -1,    94,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   233,   233,   234,   236,   434,   436,   437,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_EXIT",
  "TOK_LONGSTRINGLITERALSINGLEQUOTE", "TOK_LONGSTRINGLITERALDOUBLEQUOTE",
  "TOK_SHORTSTRINGLITERALSINGLEQUOTE", "TOK_SHORTSTRINGLITERALDOUBLEQUOTE",
  "TOK_COMMENT", "TOK_INTEGER", "TOK_LONGINTEGER", "TOK_FLOATNUMBER",
  "TOK_IMAGNUMBER", "TOK_SPACE", "TOK_NEWLINE", "TOK_OP", "TOK_CP",
  "TOK_COMMA", "TOK_OB", "TOK_CB", "TOK_FOR", "TOK_IF", "TOK_AO", "TOK_AC",
  "TOK_CO", "TOK_BQ", "TOK_FS", "TOK_FSFSFS", "TOK_ST", "TOK_STST",
  "TOK_EQ", "TOK_MN", "TOK_PL", "TOK_TL", "TOK_DIDI", "TOK_DI", "TOK_PC",
  "TOK_LTLT", "TOK_GTGT", "TOK_AS", "TOK_EX", "TOK_OR", "TOK_LT", "TOK_GT",
  "TOK_EQEQ", "TOK_GTEQ", "TOK_LTEQ", "TOK_LTGT", "TOK_ETEQ", "TOK_IS",
  "TOK_NOT", "TOK_IN", "TOK_WRITTEN_OR", "TOK_AND", "TOK_LAMBDA",
  "TOK_ASSERT", "TOK_PLEQ", "TOK_MNEQ", "TOK_STEQ", "TOK_DIEQ", "TOK_PCEQ",
  "TOK_STSTEQ", "TOK_GTGTEQ", "TOK_LTLTEQ", "TOK_ASEQ", "TOK_EXEQ",
  "TOK_OREQ", "TOK_PASS", "TOK_DEL", "TOK_PRINT", "TOK_RETURN",
  "TOK_YIELD", "TOK_RAISE", "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT",
  "TOK_WRITTEN_AS", "TOK_FROM", "TOK_GLOBAL", "TOK_EXEC", "TOK_SC",
  "TOK_ELIF", "TOK_ELSE", "TOK_WHILE", "TOK_TRY", "TOK_EXCEPT",
  "TOK_FINALLY", "TOK_WITH", "TOK_DEF", "TOK_STRUDL", "TOK_CLASS",
  "TOK_IDENTIFIER", "TOK_ANYCHAR", "TOK_INDENT", "TOK_DEDENT",
  "TOK_SPACE_INDENT", "TOK_SPACE_EMPTY_LINE", "TOK_SPACE_NO_INDENT",
  "TOK_NEW_LINE_IGNORED", "TOK_SPACE_AT_END_OF_LINE", "TOK_SPACE_OTHER",
  "TERMINAL_MAX_MIN_NONTERMINAL", "PYTHON_ROOT_SYMBOL_USED_ONLY_IN_PYTHON",
  "NT_ERROR", "UNUSED_TOK_EXIT", "UNUSED_TOK_LONGSTRINGLITERALSINGLEQUOTE",
  "UNUSED_TOK_LONGSTRINGLITERALDOUBLEQUOTE",
  "UNUSED_TOK_SHORTSTRINGLITERALSINGLEQUOTE",
  "UNUSED_TOK_SHORTSTRINGLITERALDOUBLEQUOTE", "UNUSED_TOK_COMMENT",
  "UNUSED_TOK_INTEGER", "UNUSED_TOK_LONGINTEGER", "UNUSED_TOK_FLOATNUMBER",
  "UNUSED_TOK_IMAGNUMBER", "UNUSED_TOK_SPACE", "UNUSED_TOK_NEWLINE",
  "UNUSED_TOKEN_OP", "UNUSED_TOKEN_CP", "UNUSED_TOKEN_COMMA",
  "UNUSED_TOKEN_", "UNUSED_TOK_IDENTIFIER", "UNUSED_TOK_ANYCHAR",
  "UNUSED_TOK_INDENT", "UNUSED_TOK_DEDENT", "MAIN_FILE", "MAIN_FILE_SEQ_1",
  "MAIN_FILE_SEQ_1_ELM", "$accept",
  "python_root_symbol_used_only_in_python", "nt_error", "main_file",
  "main_file_seq_1", "main_file_seq_1_elm", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   127,   128,   128,   129,   130,   131,   131,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,    14,    15,    16,    17,    10,     9,    11,    12,
       8,    21,    20,    19,    18,    95,    94,    93,    92,    33,
      91,    90,    32,    89,    88,    87,    86,    85,    84,    83,
      82,    81,    80,    79,    78,    77,    76,    75,    74,    73,
      72,    71,    70,    69,    68,    67,    66,    65,    64,    63,
      62,    61,    60,    59,    58,    57,    56,    55,    54,    53,
      52,    51,    50,    49,    48,    47,    46,    45,    44,    43,
      42,    41,    40,    39,    38,    37,    36,    35,    34,    31,
      30,    29,    28,    27,    26,    25,    24,    23,    22,    13,
      96,    97,    98,     0,     3,     2,     0,     6,     1,     5,
       7
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    93,    94,    95,    96,    97
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -95
static const yytype_int8 yypact[] =
{
      -1,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,     1,   -95,   -95,    91,   -95,   -95,   -95,
     -95
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -95,   -95,   -95,   -95,   -95,   -94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       1,    98,   100,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    99,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-95)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
       1,     0,    96,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,   128,   129,   130,   131,   132,     0,     3,
     132
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 233 "x_rm1.y"
    {BISON_NT((MISC_MASTER,PYTHON_ROOT_SYMBOL_USED_ONLY_IN_PYTHON,&(yyval),2,(yyvsp[(1) - (1)])));/*+*/show_rec_except_conn((yyval));list_n((yyval));(MISC_MASTER)->top=(yyval);dump_tree(MISC_MASTER);EXIT_(0);}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 234 "x_rm1.y"
    {BISON_NT((MISC_MASTER,PYTHON_ROOT_SYMBOL_USED_ONLY_IN_PYTHON,&(yyval),2,(yyvsp[(1) - (1)])));/*+*/  error_text(last_symbol_from_an_input_file(MISC_MASTER),"parse error");EXIT_(1);}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 236 "x_rm1.y"
    {BISON_NT((MISC_MASTER,NT_ERROR,&(yyval),1));/*+*/show((yyval));(yyval)->sub = NULL; (yyval)->next = NULL;/*DG_ERROR_HANDLING;*/}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 434 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE,&(yyval),3,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])));}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 436 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 437 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1,&(yyval),3,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])));}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 439 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 440 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 441 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 442 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 443 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 444 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 445 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 446 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 447 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 448 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 449 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 450 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 451 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 452 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 453 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 454 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 455 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 456 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 457 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 458 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 459 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 460 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 461 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 462 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 463 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 464 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 465 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 466 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 467 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 468 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 469 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 470 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 471 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 472 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 473 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 474 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 475 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 476 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 477 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 478 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 479 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 480 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 481 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 482 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 483 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 484 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 485 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 486 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 487 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 488 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 489 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 490 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 491 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 492 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 493 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 494 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 495 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 496 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 497 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 498 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 499 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 500 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 501 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 502 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 503 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 504 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 505 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 506 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 507 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 508 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 509 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 510 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 511 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 512 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 513 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 514 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 515 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 516 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 517 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 518 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 519 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 520 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 521 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 522 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 523 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 524 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 525 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 526 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 527 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 528 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 529 "x_rm1.y"
    {BISON_NT((MISC_MASTER,MAIN_FILE_SEQ_1_ELM,&(yyval),2,(yyvsp[(1) - (1)])));}
    break;


/* Line 1787 of yacc.c  */
#line 2227 "x_rm1.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 534 "x_rm1.y"

          

/*BEGIN token_table DELIMITER*/
	token_table_t token_table[]  = {{ TOK_EXIT ,"TOK_EXIT"},
{ TOK_LONGSTRINGLITERALSINGLEQUOTE ,"TOK_LONGSTRINGLITERALSINGLEQUOTE"},
{ TOK_LONGSTRINGLITERALDOUBLEQUOTE ,"TOK_LONGSTRINGLITERALDOUBLEQUOTE"},
{ TOK_SHORTSTRINGLITERALSINGLEQUOTE ,"TOK_SHORTSTRINGLITERALSINGLEQUOTE"},
{ TOK_SHORTSTRINGLITERALDOUBLEQUOTE ,"TOK_SHORTSTRINGLITERALDOUBLEQUOTE"},
{ TOK_COMMENT ,"TOK_COMMENT"},
{ TOK_INTEGER ,"TOK_INTEGER"},
{ TOK_LONGINTEGER ,"TOK_LONGINTEGER"},
{ TOK_FLOATNUMBER ,"TOK_FLOATNUMBER"},
{ TOK_IMAGNUMBER ,"TOK_IMAGNUMBER"},
{ TOK_SPACE ,"TOK_SPACE"},
{ TOK_NEWLINE ,"TOK_NEWLINE"},
{ TOK_OP ,"TOK_OP"},
{ TOK_CP ,"TOK_CP"},
{ TOK_COMMA ,"TOK_COMMA"},
{ TOK_OB ,"TOK_OB"},
{ TOK_CB ,"TOK_CB"},
{ TOK_FOR ,"TOK_FOR"},
{ TOK_IF ,"TOK_IF"},
{ TOK_AO ,"TOK_AO"},
{ TOK_AC ,"TOK_AC"},
{ TOK_CO ,"TOK_CO"},
{ TOK_BQ ,"TOK_BQ"},
{ TOK_FS ,"TOK_FS"},
{ TOK_FSFSFS ,"TOK_FSFSFS"},
{ TOK_ST ,"TOK_ST"},
{ TOK_STST ,"TOK_STST"},
{ TOK_EQ ,"TOK_EQ"},
{ TOK_MN ,"TOK_MN"},
{ TOK_PL ,"TOK_PL"},
{ TOK_TL ,"TOK_TL"},
{ TOK_DIDI ,"TOK_DIDI"},
{ TOK_DI ,"TOK_DI"},
{ TOK_PC ,"TOK_PC"},
{ TOK_LTLT ,"TOK_LTLT"},
{ TOK_GTGT ,"TOK_GTGT"},
{ TOK_AS ,"TOK_AS"},
{ TOK_EX ,"TOK_EX"},
{ TOK_OR ,"TOK_OR"},
{ TOK_LT ,"TOK_LT"},
{ TOK_GT ,"TOK_GT"},
{ TOK_EQEQ ,"TOK_EQEQ"},
{ TOK_GTEQ ,"TOK_GTEQ"},
{ TOK_LTEQ ,"TOK_LTEQ"},
{ TOK_LTGT ,"TOK_LTGT"},
{ TOK_ETEQ ,"TOK_ETEQ"},
{ TOK_IS ,"TOK_IS"},
{ TOK_NOT ,"TOK_NOT"},
{ TOK_IN ,"TOK_IN"},
{ TOK_WRITTEN_OR ,"TOK_WRITTEN_OR"},
{ TOK_AND ,"TOK_AND"},
{ TOK_LAMBDA ,"TOK_LAMBDA"},
{ TOK_ASSERT ,"TOK_ASSERT"},
{ TOK_PLEQ ,"TOK_PLEQ"},
{ TOK_MNEQ ,"TOK_MNEQ"},
{ TOK_STEQ ,"TOK_STEQ"},
{ TOK_DIEQ ,"TOK_DIEQ"},
{ TOK_PCEQ ,"TOK_PCEQ"},
{ TOK_STSTEQ ,"TOK_STSTEQ"},
{ TOK_GTGTEQ ,"TOK_GTGTEQ"},
{ TOK_LTLTEQ ,"TOK_LTLTEQ"},
{ TOK_ASEQ ,"TOK_ASEQ"},
{ TOK_EXEQ ,"TOK_EXEQ"},
{ TOK_OREQ ,"TOK_OREQ"},
{ TOK_PASS ,"TOK_PASS"},
{ TOK_DEL ,"TOK_DEL"},
{ TOK_PRINT ,"TOK_PRINT"},
{ TOK_RETURN ,"TOK_RETURN"},
{ TOK_YIELD ,"TOK_YIELD"},
{ TOK_RAISE ,"TOK_RAISE"},
{ TOK_BREAK ,"TOK_BREAK"},
{ TOK_CONTINUE ,"TOK_CONTINUE"},
{ TOK_IMPORT ,"TOK_IMPORT"},
{ TOK_WRITTEN_AS ,"TOK_WRITTEN_AS"},
{ TOK_FROM ,"TOK_FROM"},
{ TOK_GLOBAL ,"TOK_GLOBAL"},
{ TOK_EXEC ,"TOK_EXEC"},
{ TOK_SC ,"TOK_SC"},
{ TOK_ELIF ,"TOK_ELIF"},
{ TOK_ELSE ,"TOK_ELSE"},
{ TOK_WHILE ,"TOK_WHILE"},
{ TOK_TRY ,"TOK_TRY"},
{ TOK_EXCEPT ,"TOK_EXCEPT"},
{ TOK_FINALLY ,"TOK_FINALLY"},
{ TOK_WITH ,"TOK_WITH"},
{ TOK_DEF ,"TOK_DEF"},
{ TOK_STRUDL ,"TOK_STRUDL"},
{ TOK_CLASS ,"TOK_CLASS"},
{ TOK_IDENTIFIER ,"TOK_IDENTIFIER"},
{ TOK_ANYCHAR ,"TOK_ANYCHAR"},
{ TOK_INDENT ,"TOK_INDENT"},
{ TOK_DEDENT ,"TOK_DEDENT"},
{ TOK_SPACE_INDENT ,"TOK_SPACE_INDENT"},
{ TOK_SPACE_EMPTY_LINE ,"TOK_SPACE_EMPTY_LINE"},
{ TOK_SPACE_NO_INDENT ,"TOK_SPACE_NO_INDENT"},
{ TOK_NEW_LINE_IGNORED ,"TOK_NEW_LINE_IGNORED"},
{ TOK_SPACE_AT_END_OF_LINE ,"TOK_SPACE_AT_END_OF_LINE"},
{ TOK_SPACE_OTHER ,"TOK_SPACE_OTHER"},
{ PYTHON_ROOT_SYMBOL_USED_ONLY_IN_PYTHON ,"PYTHON_ROOT_SYMBOL_USED_ONLY_IN_PYTHON"},
{ NT_ERROR ,"NT_ERROR"},
{ UNUSED_TOK_EXIT ,"UNUSED_TOK_EXIT"},
{ UNUSED_TOK_LONGSTRINGLITERALSINGLEQUOTE ,"UNUSED_TOK_LONGSTRINGLITERALSINGLEQUOTE"},
{ UNUSED_TOK_LONGSTRINGLITERALDOUBLEQUOTE ,"UNUSED_TOK_LONGSTRINGLITERALDOUBLEQUOTE"},
{ UNUSED_TOK_SHORTSTRINGLITERALSINGLEQUOTE ,"UNUSED_TOK_SHORTSTRINGLITERALSINGLEQUOTE"},
{ UNUSED_TOK_SHORTSTRINGLITERALDOUBLEQUOTE ,"UNUSED_TOK_SHORTSTRINGLITERALDOUBLEQUOTE"},
{ UNUSED_TOK_COMMENT ,"UNUSED_TOK_COMMENT"},
{ UNUSED_TOK_INTEGER ,"UNUSED_TOK_INTEGER"},
{ UNUSED_TOK_LONGINTEGER ,"UNUSED_TOK_LONGINTEGER"},
{ UNUSED_TOK_FLOATNUMBER ,"UNUSED_TOK_FLOATNUMBER"},
{ UNUSED_TOK_IMAGNUMBER ,"UNUSED_TOK_IMAGNUMBER"},
{ UNUSED_TOK_SPACE ,"UNUSED_TOK_SPACE"},
{ UNUSED_TOK_NEWLINE ,"UNUSED_TOK_NEWLINE"},
{ UNUSED_TOKEN_OP ,"UNUSED_TOKEN_OP"},
{ UNUSED_TOKEN_CP ,"UNUSED_TOKEN_CP"},
{ UNUSED_TOKEN_COMMA ,"UNUSED_TOKEN_COMMA"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOKEN_ ,"UNUSED_TOKEN_"},
{ UNUSED_TOK_IDENTIFIER ,"UNUSED_TOK_IDENTIFIER"},
{ UNUSED_TOK_ANYCHAR ,"UNUSED_TOK_ANYCHAR"},
{ UNUSED_TOK_INDENT ,"UNUSED_TOK_INDENT"},
{ UNUSED_TOK_DEDENT ,"UNUSED_TOK_DEDENT"},
{ UNUSED_TOK_DEDENT ,"UNUSED_TOK_DEDENT"},
{ UNUSED_TOK_DEDENT ,"UNUSED_TOK_DEDENT"},
{ UNUSED_TOK_DEDENT ,"UNUSED_TOK_DEDENT"},
{ UNUSED_TOK_DEDENT ,"UNUSED_TOK_DEDENT"},
{ UNUSED_TOK_DEDENT ,"UNUSED_TOK_DEDENT"},
{ UNUSED_TOK_DEDENT ,"UNUSED_TOK_DEDENT"},
{ MAIN_FILE ,"MAIN_FILE"},
{ MAIN_FILE_SEQ_1 ,"MAIN_FILE_SEQ_1"},
{ MAIN_FILE_SEQ_1_ELM ,"MAIN_FILE_SEQ_1_ELM"},
{0,NULL}};

/*END token_table DELIMITER*/     


