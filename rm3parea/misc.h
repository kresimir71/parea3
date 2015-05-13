#ifndef _MISC_H
#define _MISC_H
#include <pcre.h>
#include "col.h"
//#include "goals.h"
#include "stdio.h"
#include "string.h"
//#include "rm1.h"
//#include "x_io1.h"
#include "rbt.h"
#include "rbt_shortcuts.h"
/* #include "x_rm1.tab.h" */
#include "aa.h"
//#include "inc.h"
//#include "debug.h"
#include "list.h"
#include "stack.h"
//#include "goals.h"
//#include "debug2.h"

#define YYPARSE_PARAM misc_master
#define YYLEX_PARAM misc_master

/*pointer to parser record known in parser rules*/
//DOC_DEFINE(MISC_MASTER DG_BISON_COMMON)
#define MISC_MASTER ((parser_master_t*)misc_master)

#define MIN(a,b)\
(a<b?a:b)

/*to be done at every new begin of yy lex function. The state_name is the default state which begins whenever flex_token_pos==1. The user should, for simplicity, not use the default but always force BEGIN(state) via mp->change_state . mp->change_state and mp->change_pos can be used to change the position and state at the beginning of flex function.*/
//DOC_DEFINE(FLEX_BEGIN DG_FLEX_STATE_AND_POSITION)
#define FLEX_BEGIN(state_name) \
FLEX_BEGIN_NEXT_TOKEN \
if (flex_token_pos <= 1) BEGIN( state_name);\
if (mp->change_state != -1) {long flex_num_chars=mp->change_pos;BEGIN(mp->change_state);mp->change_state=-1;if(-1!=mp->change_pos){flex_token_pos=flex_num_chars+1;yy_restart(NULL);}}

/*to be done when a terminal is recognised by flex*/
//DOC_DEFINE(FLEX_NEW_TERMINAL DG_FLEX_COMMON)
#define FLEX_NEW_TERMINAL(ter) \
mp->yylval=new_terminal(mp,ter,flex_token_pos,flex_token_pos+yy_leng)

/*to be done when a terminal is recognised by flex:adjust pointers*/
//DOC_DEFINE(FLEX_INCREASE_POSITION DG_FLEX_STATE_AND_POSITION)
#define FLEX_INCREASE_POSITION \
flex_token_pos+=yy_leng

/*to be done when an unwanted terminal is recognised by flex*/
//DOC_DEFINE(FLEX_NEW_TERMINAL_DUMMY DG_FLEX_COMMON)
#define FLEX_NEW_TERMINAL_DUMMY(ter) \
new_terminal_dummy(mp,ter,flex_token_pos,flex_token_pos+yy_leng)

/*Macro called in flex yy lex function to get characters. When at the end of input then flex gets YY_NULL==0 count. This is the sign for emitting the end of line token. Why &&i ?*/
//DOC_DEFINE(YY_INPUT DG_FLEX_COMMON)
#define YY_INPUT(buf,result,max_size) \
{ \
   long i;\
   for(i=0;i<max_size&&i<number_of_chars_to_read_for_flex;i++){long c = DER(mp->col01_flex_getchar)(mp) ;buf[i]=c;/* if(mp->current_text_heap->eof_flag==EOF&&!i){ mp->current_text_heap->flex_num_chars--; } */if(mp->current_text_heap->eof_flag==EOF)break;} \
   result = (!i ? YY_NULL : i); \
}

/* yy lex function locals. flex_token_pos is a variable used ONLY in scanner (there is nowhere 'extern'), beginning at 1, increasing by yy_leng, and adjusted when changing position*/
//DOC_DEFINE(FLEX_DECLARATIONS DG_FLEX_COMMON)
#define FLEX_DECLARATIONS \
long flex_token_pos = 1;

typedef struct 
{
  long id;
  char* str;
  /*array of all (symbol number, symbol name) pairs*/
  //DOC_TYPEDEF(token_table_t DG_BISON_COMMON)
} token_table_t;

/*to be done every time yy lex is called: only first time is important - to initialize the parser pointer (for advanced architectures twice is possible)*/
//DOC_DEFINE(FLEX_BEGIN_NEXT_TOKEN DG_BISON_COMMON)
#define FLEX_BEGIN_NEXT_TOKEN {static long step=0;if (!mp&&!step) {step=1;return (long)&mp;} if (!mp&&step==1) {step=0;return (long)(((unsigned long)&mp)>>32);}  /*not needed:*/step=0;}



extern void misc_macro_after_symbol(parser_master_t*);
extern void main_after_symbol_macro(long *result);
extern int yydebug;			/*  nonzero means print parse trace	*/
int yyparse(void*misc_parser);
int yyerror (char *s);
int yyprint (FILE *file,int type,YYSTYPE value);
long yylex_(parser_master_t*p);
#ifdef yylex
/*we are in flex compile unit: the macro should never be equal to itself otherwise double symbols*/
int yylex (void);
#else
int yylex (YYSTYPE * v,void*current_misc_master_record);
#endif
int yylex_close(void);

long misc_yylex (YYSTYPE * v,void*current_misc_master_record);
parser_master_t* misc_new_parser(long (*gc)(parser_master_t*), long (*yyl)(YYSTYPE *, void*),long (*flex_yyl)(void));
lisp_cons_cell_t* dt_mem2_from_current_list(col_t* current);
//col_t * symbol_text6(pleaf_t sym,col_t*(*st)(pleaf_t));
//col_t* symbol_text_rec(pleaf_t b,col_t*r,col_t*(*st)(pleaf_t));
//extern int misc_flex_try_again;
void misc_push_ahead(text_heap_heap_t* h,col_t*x);
col_t* misc_get_next_ahead(text_heap_heap_t* h);
long line_number_middle(pleaf_t sym);
void misc_unbound_parse_error_list(parser_master_t*p);
void misc_unbound_parse_error_list_step(aa_data_t*c);
void misc_unbound_rec_from_misc_parse_error_list(pleaf_t b);
//extern col_t* misc_parse_error_list;
void misc_adopt_symbol(pleaf_t l);
//void misc_store_last_symbol(parser_master_t*p, pleaf_t l);
//void new_terminal_dummy(parser_master_t*p,long id, long pos0 ,long pos1);
void misc_fatal_error_exit(parser_master_t*p,char*message);
void error_text_end(pleaf_t p, char* text);
void error_text(pleaf_t p, char* text);
void push_arguments_to_buffer_0(parser_master_t*p,long argc,char**argv,long state);
extern pleaf_t recorded_last_symbol_from_an_input_file;
pleaf_t last_symbol_from_an_input_file(parser_master_t*p);
void show_rec_except_under_id_but_well_under_di(pleaf_t b,long id,long di, long do_show);
extern char full_name_of_last_open_file[512];
void close_text_file(text_heap_heap_t*t);
#if 0
lisp_cons_cell_t* uncons(lisp_cons_cell_t* a);
lisp_cons_cell_t* cons(col_t* a, col_t* b);
#endif
void push_additional_token_list(parser_master_t*p,long id,long pos0,long pos1);
void general_main_init(void);
void deshow_rec_id(pleaf_t b,long id);
//lisp_cons_cell_t* dt_mem2(pleaf_t t);
void dt_mem_unbound(lisp_cons_cell_t* t);
extern pleaf_t current_terminal;
extern pleaf_t current_terminal;
long pointer_at_the_end(text_heap_heap_t*txt_heap);
char* symbol_file(pleaf_t sym);
long line_number_beg(pleaf_t sym);
long line_number_end(pleaf_t sym);
long line_number(text_heap_heap_t*txt_heap,long position);
FILE* probe_text_file_for_read(parser_master_t*p,col_t* dir, col_t*file_name);
FILE* text_file_for_read(parser_master_t*p,col_t* dirs, col_t*file_name);
pleaf_t find_pleaf_with_id(pleaf_t b,long id);
void rewind_before_symbol(pleaf_t sym, long state);
void flex_pushstring2(parser_master_t*p,col_t* xstr);
void flex_pushstring2null(parser_master_t*p);
void show_rec_except_conn(pleaf_t b);
col_t * symbol_text3(pleaf_t sym);
void show_rec(pleaf_t b);
void show_rec_id(pleaf_t b,long id);
#ifndef NDEBUG
#ifdef START_SIMBOL_FOR_BIFL_GRAMMAR_UNIQUE_IN_BIFL
extern void bifl_dump_rules(lisp_cons_cell_t *input);
#endif
#endif
void flex_create_new_read_xstring(parser_master_t*p,col_t*xstr,long state);
void load_connecting_nonterminal(parser_master_t*p);
void load_connecting_nonterminal2(parser_master_t*p);
extern col_t*connecting_nonterminal;
void change_flex_state(parser_master_t*p,long state);
extern FILE *fp_error;
extern token_table_t token_table[];
extern text_heap_heap_t* open_text_file_for_read(parser_master_t*p,char* file,col_t*dir_array);
extern text_heap_heap_t *current_text_heap;
extern void * text_heap_heap;
extern void * create_text_heap_heap(void);
extern void flex_pushstring(parser_master_t*p,char* str);
extern void rewind_after_symbol(pleaf_t sym, long state);
extern long pleaf_pos_end(pleaf_t t);
extern long pleaf_pos(pleaf_t t);
extern void delist_rec(pleaf_t b);
extern void deshow(pleaf_t b);
extern void deshow_rec(pleaf_t b);
#ifndef NDEBUG
extern void text_heap_1_write(void * text_heap_1_instance,char c, unsigned long pos);
extern char text_heap_1_read(void * text_heap_1_instance, unsigned long pos);
extern char *text_heap_1_read2(text_heap_heap_t * text_heap_heap, unsigned long pos1,unsigned long pos2,char*all_txt);
extern void * create_text_heap_1(void);
#endif
extern char *file_name(char* env, char* name);
//extern long change_pos;
//extern long change_state;
extern void rewind_scanner(parser_master_t*p,long state_long, long pos);
extern void misc_empty_lookahead(parser_master_t*p);
#if !defined NDEBUG
extern long search_token_table(char *token_str);
#endif
extern void id(pleaf_t a, long id);
extern void misc_connect_sub(pleaf_t a, pleaf_t b);
extern void list(pleaf_t b);
extern void hide(pleaf_t b);
extern long current_terminal_pos0(parser_master_t*p);
extern pleaf_t new_terminal(parser_master_t*p,long id, long pos0 ,long pos1);
extern pleaf_t new_nonterminal(parser_master_t*p,long id, long pos0 ,long pos1);
extern pleaf_t top;
#if !defined NDEBUG
extern char* search_table_token(long token);
#endif
extern void misc_connect_next(pleaf_t a, pleaf_t b);
/* extern void e(pleaf_t* a, pleaf_t* b); */
extern void list_n(pleaf_t b);
extern long flex_getchar(parser_master_t*p);
extern col_t* col_new_pleaf(void);
extern col_t* lisp_pleaf(pleaf_t p);
extern pleaf_t* val_lisp_pleaf(col_t*lisp_symbol);
extern void show(pleaf_t b);
void compile_pcre(pcre **re, char *pattern);
long use_pcre(pcre *re, char *subject, long subject_length, long *rc,long ovector[],long oveccount);
#endif
