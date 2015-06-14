#ifndef _RM1_H
#define _RM1_H
//#include "debug2.h"
//#include "goals.h"

       extern int yy_lex (void**);
     #define YYPRINT(file, type, value)   yyprint (file, type, value)
     #define YYDEBUG 1
     #define YYERROR_VERBOSE 1

#undef YYSTYPE
#define YYSTYPE pleaf_t

#define YY_DECL int yy_lex (void**p123)
#endif
