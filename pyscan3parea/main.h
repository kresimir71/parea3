#ifndef _MAIN_H
#define _MAIN_H
//#include "goals.h"
#include "debug2.h"
#include "inc.h"
#include "col.h"

int main(  int argc,  char **argv);
void main_prepare_rule(void* p, long token, pleaf_t* res, long count, ...);

#ifndef MISC_MACRO_AFTER_PRODUCTION
#define MISC_MACRO_AFTER_PRODUCTION 
#endif

/*macro called after a grammar production is recognised*/
//DOC_DEFINE(BISON_NT DG_BISON_COMMON)
#define BISON_NT(params) \
  main_prepare_rule params ;if(!MISC_MASTER->misc_yychar){MISC_MASTER->misc_yychar=&yychar;MISC_MASTER->misc_yyempty=YYEMPTY;}
char * concat_unbound(char *str1,long length1, char *str2, long length2);
long mm2_sum_used(void);
#if !defined NDEBUG
extern FILE * answ_tree;
#endif

#if !defined APPL_MAIN_APPLICATION_IDENTIFIER_CPP2 || !defined NDEBUG
extern void load_string_token_prop(void);
extern void * string_token_prop;
extern void load_token_string_prop(void);
extern void * token_string_prop;
#endif

#if !defined NDEBUG
extern void dump_tree_mem(parser_master_t*p);
void dt_mem_dump_to_stderr(lisp_cons_cell_t* t);
extern void dt_mem_dump(lisp_cons_cell_t* t);
void dt_mem_dump2(lisp_cons_cell_t* t);
extern lisp_cons_cell_t* dt_mem(pleaf_t t);
#endif

#if !defined NDEBUG
char* dt_mem_dump_to_string(lisp_cons_cell_t* t, char* str,char*(*print_attributes)(pleaf_t p));
lisp_cons_cell_t* dt_mem(pleaf_t t);
#endif

#if !defined APPL_MAIN_APPLICATION_IDENTIFIER_CPP2 || !defined NDEBUG
void dt(pleaf_t t, FILE* answ_tree);
#endif

#if !defined NDEBUG
extern void dump_tree(parser_master_t*p);
#endif

#if !defined NDEBUG
void db_init();
#endif

lisp_cons_cell_t* dt_mem2(pleaf_t t);
void misc_store_last_symbol(parser_master_t*p, pleaf_t l);
col_t* symbol_text_rec(pleaf_t b,col_t*r,col_t*(*st)(pleaf_t));
col_t * symbol_text6(pleaf_t sym,col_t*(*st)(pleaf_t));
void new_terminal_dummy(parser_master_t*p,long id, long pos0 ,long pos1);
#endif


