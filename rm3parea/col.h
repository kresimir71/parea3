#ifndef __COL_H
#define __COL_H
#include "stdlib.h"
#include "stdio.h"
#include "rm1.h"
//#include "goals.h"
//#include "debug2.h"

    /*function type*/
//DOC_TYPEDEF(col_data_function_t DG_COL)
typedef void (*col_data_function_t)(void*);

typedef enum
  {
    /*lisp list*/
    LISTP = 1,
    /*cons cell*/
    CONSP,
    /*bison symbol*/
    PLEAFP,
    /*lisp integer*/
    INTP,
    /*lisp string*/
    STRINGP,
    /*associative array*/
    AAP,
    /*c stack*/
    STACKP,
    /*c list*/
    CLISTP,
    /*general storage*/
    VOIDP,
    /*xstring storage*/
    XSTRINGP,
    /*c string*/
    SSTRINGP,
    /*c integer*/
    SINTP,
    /*set from xstring*/
    SETP,
    /*file*/
    FILEP,
    /*parser*/
    PARSERP,
    /*next free type slot*/
    COL_NEXT_FREE_TYPE_SLOT,
    /*collection type*/
    //DOC_TYPEDEF(lisp_type_t DG_COL)
  } lisp_type_t;

typedef struct
{
  /*type of variable*/
  lisp_type_t type;
  /*value of variable*/
  void * val;
  /*mm handle of variable*/
  void* mm_handle;
  /*collection of types*/
  //DOC_TYPEDEF(col_t DG_COL)
} col_t;

typedef enum
{
  /*begin of list*/
  LIST = 1,
  /*terminal*/
  TERM = 2,
  /*nonterminal*/
  NONTERM = 4,
  /*hide symbol*/
  HIDE = 8,
  /*begin of list without subtree*/
  LIST_NEXT = 16,
  /*show symbol*/
  SHOW = 32,
  /*text heap is bounded*/
  COL_TEXT_HEAP_BOUNDED = 64,
  /*some semantic attributes of a symbol*/
  //DOC_TYPEDEF(tags_t DG_BISON_SYMBOL_ATTRIBUTES)
} tags_t;

typedef struct 
{
  /*type of variable*/
  lisp_type_t type;
  /*XSTRING to read from */
  col_t*xstring;
  /*mm handle of variable*/
  void* mm_handle;

  /*heap id */
  long id;
  /*last character read by flex*/
  long flex_num_chars;
  /*AAP array of new line characters*/
  col_t* cnt_nl;
  /*number of new line characters encountered*/
  long cnt_nl_length;
  /*last read character*/
  long array_pos;
  /*file name XSTRING*/
  col_t* file_name;
  /*file pointer*/
  FILE* file_ptr;
  /*pushed chars to input*/
  col_t*misc_ahead_xstring;
  /*number of read chars from misc_ahead_xstring*/
  long misc_ahead_read;
  /*additional information*/
  col_t* add_info;
  /*parser for this buffer*/
  struct parser_master_tag* ps01_parser;
  /*at end of input?*/
  long eof_flag;
  /*text heap to represent buffer or file*/
  //DOC_TYPEDEF(text_heap_heap_t DG_FLEX_BUFFERS)
} text_heap_heap_t;

typedef struct leaf
{
  /*type of variable*/
  lisp_type_t type;
  /* first element*/
  void * val;
  /* mm handle of cell*/
  void* mm_handle;
  /*symbol id*/
  long id;
  /*next symbol in tree:may be changed*/
  struct leaf *next;
  /*sub symbol in tree:may be changed*/
  struct leaf *sub;
  /*next symbol in tree:internal*/
  struct leaf *next_all;
  /*sub symbol in tree:internal*/
  struct leaf *sub_all;
  /*tag of symbol*/
  tags_t tag;
  /*begin and end position of the first symbol in list*/
  long pos[2];
  /*begin and end position of the last symbol in list*/
  long pos_end[2];
  /*file of symbol*/
  text_heap_heap_t * text_heap_heap;
  /*user attributes*/
  col_t*user_attributes;
  /*bison symbol*/
  //DOC_TYPEDEF(leaf_t DG_BISON_SYMBOL_ATTRIBUTES)
} leaf_t;

/*pointer to bison symbol*/
//DOC_TYPEDEF(pleaf_t DG_BISON_SYMBOL_ATTRIBUTES)
typedef leaf_t* pleaf_t;

typedef struct parser_master_tag
{
  col_t dummy;
  /*Array of issued (non)terminals which have not been connected in tree yet, i.e. no symbol has them as sub or next. They are the roots of unconnected branches*/
  //DOC_STRUCTVAR(misc_parse_error_list DG_BISON_COMMON)
  col_t* misc_parse_error_list;
  /*stack of parser_master_t (future extension)*/
  //DOC_STRUCTVAR(misc_stack DG_BISON_COMMON)
  col_t* misc_stack;
  /*indicator can only be set during yylex function and its calls: next symbol required! (no effect if set elsewhere because set to 0 at the begin of yylex)*/
  //DOC_STRUCTVAR(misc_flex_try_again DG_FLEX_READCHAR)
  long misc_flex_try_again;
  /*new required buffer position on rewind request*/
  //DOC_STRUCTVAR(change_pos DG_FLEX_REWIND_OR_CHANGE_STATE)
  long change_pos;
  /*new required flex state on rewind request*/
  //DOC_STRUCTVAR(change_state DG_FLEX_REWIND_OR_CHANGE_STATE)
  long change_state;
  /*array of connecting nonterminals in grammar*/
  //DOC_STRUCTVAR(connecting_nonterminal DG_BISON_LIST_FROM_BRANCH)
  col_t*connecting_nonterminal;
  /*last symbol from an input file, not a buffer*/
  //DOC_STRUCTVAR(recorded_last_symbol_from_an_input_file DG_BISON_COMMON)
  pleaf_t recorded_last_symbol_from_an_input_file;
  /*last symbol given to bison parser by the lexer, used currently to hang preceeding and/or following space tokens on it. Only the first such token has the preceeding list non-empty! The space tokens themself are not forwarded to the bison parser.  */
  //DOC_STRUCTVAR(recorded_last_symbol DG_BISON_COMMON)
  pleaf_t recorded_last_symbol;
  /*full file name when found, short name when not found*/
  //DOC_STRUCTVAR(full_name_of_last_open_file DG_FLEX_BUFFERS)
  char full_name_of_last_open_file[512];
  /*current buffer*/
  //DOC_STRUCTVAR(current_text_heap DG_FLEX_BUFFERS)
  text_heap_heap_t *current_text_heap;
  /*last assigned terminal*/
  //DOC_STRUCTVAR(current_terminal DG_BISON_COMMON)
  pleaf_t current_terminal;
  /*last assigned nonterminal*/
  //DOC_STRUCTVAR(current_nonterminal DG_BISON_COMMON)
  pleaf_t current_nonterminal;
  /*top of parse tree*/
  pleaf_t top;
  /*symbol worked on*/
  pleaf_t yylval;
  /*the pointer to lookahead token yychar of the parser */
  //DOC_STRUCTVAR(misc_yychar DG_BISON_COMMON)
  int *misc_yychar;
  /*the constant YYEMPTY of the parser that indicates no lookahead token in parser's yychar*/
  //DOC_STRUCTVAR(misc_yyempty DG_BISON_COMMON)
  int misc_yyempty;
  /*list of terminals to be pushed to parser input before asking a new token from flex*/
  //DOC_STRUCTVAR(additional_token_list DG_BISON_PUSHSYMBOL)
  col_t* additional_token_list;
  /*Ponter to parser_master_t pointer in scanner. The very first call to flex has to deliver the pointer to the pointer of parser in flex. */
  //DOC_STRUCTVAR(misc_parser_for_flex DG_BISON_COMMON)
  struct parser_master_tag** misc_parser_for_flex;
  /*function for flex to get char */
  //DOC_STRUCTVAR(col01_flex_getchar DG_BISON_COMMON)
  long (*col01_flex_getchar)(struct parser_master_tag*p);
  /*function for bison to get symbol */
  //DOC_STRUCTVAR(col01_yylex DG_BISON_COMMON)
  long (*col01_yylex)(YYSTYPE *t, void*current_misc_master_record);
  /*flex function pointer */
  //DOC_STRUCTVAR(col01_flex_call DG_BISON_COMMON)
  long (*col01_flex_call)(void**p);
  /* user data: currently a list of SPACE terminals to ba hanged on a non-SPACE terminal in some applications*/
  //DOC_STRUCTVAR(parser_user_data DG_BISON_COMMON)
  col_t* parser_user_data;
  /*the parser type*/
  //DOC_TYPEDEF(parser_master_t DG_BISON_COMMON)
} parser_master_t;

/*allocate storage*/
//DOC_DEFINE(STORAGE DG_MM)
#define STORAGE(x,t,s)\
do\
{\
  if ((x =  t malloc (s)) == 0) {\
    fprintf (stderr,"internal error: malloc failed: %s %s\n",#t,#x);\
    exit(1);\
  }\
} while (0)
/*allocate storage*/
//DOC_DEFINE(CSTORAGE DG_MM)
#define CSTORAGE(x,t,nelements,sizeofeach)\
do\
{\
  if ((x =  t calloc (nelements,sizeofeach)) == 0) {\
    fprintf (stderr,"internal error: calloc failed: %s %s\n",#t,#x);\
    exit(1);\
  }\
} while (0)

typedef enum
  {
    /*reuse argument storage for result*/
    //DOC_ENUMCONST(XSTRING_REUSE DG_XSTRING)
    XSTRING_REUSE=1,
    /*allocate new storage for result*/
    //DOC_ENUMCONST(XSTRING_BOUNDNEW DG_XSTRING)
    XSTRING_BOUNDNEW=1<<1,
    /*unbound argument storage*/
    //DOC_ENUMCONST(XSTRING_UNBOUNDOLD DG_XSTRING)
    XSTRING_UNBOUNDOLD=1<<2,
    /*storage indicators for substring*/
    //DOC_TYPEDEF(xstring_substring_flags_t DG_XSTRING)
  } xstring_substring_flags_t;

typedef enum
  {
    /*duplicate xstring by strcpy*/
    //DOC_ENUMCONST(XSTRING_STRCPY DG_XSTRING)
    XSTRING_STRCPY=1,
    /*duplicate xstring by memcpy*/
    //DOC_ENUMCONST(XSTRING_MEMCPY DG_XSTRING)
     XSTRING_MEMCPY=1<<1,
    /*duplication indicators*/
    //DOC_TYPEDEF(col_duplicate_flags_t DG_COL)
  } col_duplicate_flags_t;

/*rename*/
//DOC_TYPEDEF(col_type_t DG_COL)
typedef lisp_type_t col_type_t;


#define COL_STRUCT_SIZEOF(s) (sizeof(s))
  /*((((sizeof(s)-1)/sizeof(int))+1)*sizeof(int))*/

typedef struct cons
{
  /*type of variable*/
  lisp_type_t type;
  /* first element*/
  col_t * car;
  /* mm handle of cell*/
  void* mm_handle;
  /*rest list*/
  struct cons * cdr;
#ifndef NDEBUG  
  pleaf_t comment;
#endif
  /*lisp cons cell*/
  //DOC_TYPEDEF(lisp_cons_cell_t DG_COL)
} lisp_cons_cell_t;
//#ifndef NDEBUG
/*allocation function*/
//DOC_DEFINE(COL_VAR DG_COL)
#define COL_VAR(col_var,col_type)\
col_t* col_var=new_col_symbol(col_type)

/*allocation function*/
//DOC_DEFINE(BOUND_MEM DG_COL)
#define BOUND_MEM(var,type,size)\
  type *var= (type*)bound_new_mem(size)

/*deallocation function*/
//DOC_DEFINE(UNBOUND_MEM DG_COL)
#define UNBOUND_MEM(var)\
unbound_mem_from_handle(var)

/*deallocation function*/
//DOC_DEFINE(UNBOUND_COL_VAR DG_COL)
#define UNBOUND_COL_VAR(col_var)\
unbound_mem_from_handle(col_var->mm_handle)

//#ifndef NDEBUG
/*allocation function*/
//DOC_DEFINE(STORAGE_LISP_VAR DG_COL)
#define STORAGE_LISP_VAR(result_var,lisp_type,result)\
STORAGE(result_var,(col_t*),sizeof(col_t));\
if (lisp_type==INTP)\
{\
  result_var->val = (void*)(result);\
}\
if (lisp_type!=INTP)\
{\
  result_var->val = (void*)(result);\
}\
result_var->type = lisp_type;
  //#endif
/*value function*/
//DOC_DEFINE(VALUE_LISP_VAR DG_COL)
#define VALUE_LISP_VAR(var)\
((var)->type != INTP ? (var)->val : (long)((var)->val))

/*value function*/
//DOC_DEFINE(VALUE_COL_VAR DG_COL)
#define VALUE_COL_VAR(var)\
((var)->type != INTP ? (var)->val : (long)((var)->val))

/*allocating function*/
//DOC_DEFINE(COL_BOUND_MEM DG_COL)
#define COL_BOUND_MEM(var,type)\
  var= (type*)bound_new_mem(sizeof(type));\
  var->mm_handle = mm_handle;
  //#endif
//#ifndef NDEBUG
/*allocating function*/
//DOC_DEFINE(COL_BOUND_MEM_NO_HANDLE DG_COL)
#define COL_BOUND_MEM_NO_HANDLE(var,type)\
  type*var= (type*)bound_new_mem(sizeof(type));

/*allocating function*/
//     DOC_DEFINE(COL_BOUND_MEM_NO_HANDLE_SIZE DG_COL)
     #define COL_BOUND_MEM_NO_HANDLE_SIZE(var,type,size)\
  type*var= (type*)bound_new_mem(size);
//#endif

     /*allocating function*/
//DOC_DEFINE(NEW_XSTRING_CONST DG_XSTRING)
#define NEW_XSTRING_CONST(text)\
new_xstring(strlen(text),text)

     /*allocating function*/
//DOC_DEFINE(COL_NEW_XSTRING_CONST DG_XSTRING)
#define COL_NEW_XSTRING_CONST(text)\
col_new_xstring(strlen(text),text,XSTRING_STRCPY)

/*dereferencing function*/
#define DER(x)\
(*(x))
     
/*copy function*/
//DOC_DEFINE(COPY_STRUCT DG_COL)
#define COPY_STRUCT(a,b,type)\
if(a&&b){memcpy(a,b,sizeof(type));}

col_t* col_cut_xstring(col_t*x,long pos1,long pos2);
col_t* col_insert(col_t*x,col_t*to_insert,long pos);
col_t* (*col_xstring_insert)(col_t*x,col_t*to_insert,long pos);
col_t* col_space(long length);
col_t* (*col_xstring_space)(long length);
col_t* col_new_xstring2(long length, char* init, long copy_length);
col_t* col_bound_new_extended(long size,long type,void* init);
long col_extended_type_unbound(col_t*s);
col_t* col_new_cons(col_t* car, void* cdr);
col_t* col_bound_col(col_t* c);
col_t* col_new_file(void);
col_t* col_new_col(lisp_type_t t,void* init);
col_t* col_xstring_substring(col_t* str,long p1, long p2_used, long p2,xstring_substring_flags_t flag);
col_t * col_concat_xstring(col_t *str1,col_t *str2);
col_t* col_print_col_to_xstring(col_t* c);
long col_unbound_col(void*s);
long col_unbound_xstring(col_t*str);
col_t* col_new_xstring(long length, char* init,col_duplicate_flags_t flag);
col_t* col_duplicate_xstring(col_t* xs, col_duplicate_flags_t flag);
col_t* col_new_col_symbol(col_type_t col_type);
col_t* col_nth2(lisp_cons_cell_t* c, long n);
col_t* col_nth(col_t* l, long n);
col_t* new_col_symbol(col_type_t col_type);
void bound_new_col_symbol(col_t** var,col_type_t col_type,void* val);
void unbound_col(col_t*s);
void del_elm_xstring(col_t*s,long elm);
void add_elm_xstring(col_t*s,long elm);
long is_elm_xstring(col_t*s,long elm);
col_t* set0_xstring(col_t*s);
long* val_int(col_t* s);
col_t* print_col_to_xstring(col_t* c);
col_t* duplicate_xstring(col_t* xs);
char* val_xstring_or_string(col_t* s);
col_t* new_int(long init);
col_t* xstring_substring(col_t* str,long p1, long p2,xstring_substring_flags_t flag);
col_t * concat_xstring(col_t *str1,col_t *str2);
void unbound_xstring(col_t*str);
col_t* new_xstring(long length, char* init);
long length_xstring(col_t* s);
long (*col_length_xstring)(col_t* s);
char* val_xstring(col_t* s);
char* (*col_val_xstring)(col_t* s);
char* val_lisp_string(col_t*lisp_symbol);
long* val_lisp_int(col_t*lisp_symbol);
#ifndef NDEBUG
char * concat_free(char *str1,long length1, char *str2, long length2);
char * concat_unbound(char *str1,long length1, char *str2, long length2);
char * concat(char*c, char*d);
#ifndef NDEBUG
char * downcase(char*c);
char * upper(char*c);
#endif
col_t* copy_lisp_symbol(col_t*lisp_symbol);
col_t* lisp_string(char *str);
char* substring(char* str,long p1, long p2);
col_t* lisp_substring(col_t* str,long p1, long p2);
col_t* lisp_list(lisp_cons_cell_t* cell);
col_t* lisp_int(long i);
#endif
#endif
