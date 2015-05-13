#include "col.h"
//#include "goals.h"
#include "math.h"
#include "stdio.h"
#include "rbt.h"
#include "rbt_shortcuts.h"
#include "main.h"
#include "debug.h"
#include "inc.h"
#include "mm.h"
#include "mm2.h"
#include "goals.h"
#include "debug2.h"
#include <signal.h>
#include <stdarg.h>

#if !defined NDEBUG
FILE *answ;
FILE * answ_tree = NULL;
//DOC_VARIABLE(token_string_prop DG_FLEX_READCHAR)
void * token_string_prop;
//DOC_VARIABLE(string_token_prop DG_FLEX_READCHAR)
void * string_token_prop;
#endif

static void main_signal_handler(int);

static void
main_signal_handler(int signalnumber)
{
  char * signalname;
  if (signalnumber == SIGINT){
    signalname="SIGINT";
  }
  if (signalnumber == SIGQUIT){
    signalname="SIGQUIT";
  }
  if (signalnumber == SIGTERM){
    signalname="SIGTERM";
  }
  fprintf(stderr, "terminated with signal %s\n",signalname);
#if RM2_LIBRARY_TEST==1
  {
    void *array[10];
    size_t size;
    char **strings;
    size_t i;
    
    size = backtrace (array, 10);
    strings = backtrace_symbols (array, size);
    
    printf ("Obtained %zd stack frames.\n", size);
    
    for (i = 0; i < size; i++)
      printf ("%s\n", strings[i]);
    
    free (strings);
  }
#endif
  exit(1);
}

static int main2(  int argc,  char **argv){
  if (signal(SIGINT, main_signal_handler) == SIG_ERR) {
    printf ("SIGINT handler installing problems\n");
    EXIT_(1);
  }
  if (signal(SIGQUIT, main_signal_handler) == SIG_ERR) {
    printf ("SIGQUIT handler installing problems\n");
    EXIT_(1);
  }
  if (signal(SIGTERM, main_signal_handler) == SIG_ERR) {
    printf ("SIGTERM handler installing problems\n");
    EXIT_(1);
  }

#if RM2_LIBRARY_TEST==1
  rm2_library_test(argc,argv);
  return 0;
#endif

  MAIN_INIT(argc,argv);
  return 0;

}
#ifndef RM2_BUILD_LIBRARY
/*main */
int main(  int argc,  char **argv)
{
  return main2(argc,argv);
}
#endif

/*flex get character*/
//DOC_FUNC_DEF(flex_getchar DG_FLEX_READCHAR)
long flex_getchar(parser_master_t*p)
{
  // EOF== was end, EOF-1==was end but rewinded
  BEGIN_FUNCTION(flex_getchar,2);
  long fgetc_needed =0;
  char return_char='z';
  long return_size=1;
  long * flex_num_chars_x;
  long * array_pos_x;
  long debug_false_char=0;
  col_t**xstring;
  flex_num_chars_x = &p->current_text_heap->flex_num_chars;
  array_pos_x = &p->current_text_heap->array_pos;
  xstring=(col_t**)&(p->current_text_heap->xstring);
  ASSERT(DER(xstring));
  if (*array_pos_x==*flex_num_chars_x) {
    //read from file
    char received_char[251];//={0,0};
    col_t*c;
    if(p->current_text_heap->eof_flag==EOF||p->current_text_heap->eof_flag==EOF-1){
      // EOF== was end, EOF-1==was end but rewinded
      p->current_text_heap->eof_flag=EOF;// must again be EOF to inform flex no more input
      goto end1;
    }
    fgetc_needed=1;
    c=misc_get_next_ahead(p->current_text_heap);//after push misc_ahead_xstring the scanner must be restarted because we know nothing about internal scanner buffer

    //    received_char[1] = 0;
    if(c){
      received_char[0]=DER(val_xstring(c));
      return_size=1;
    }else if(p->current_text_heap->file_ptr){
      received_char[0] = 'Z';
      return_size=fread(received_char,1,1,p->current_text_heap->file_ptr); 
      /* return_size=read(fileno(p->current_text_heap->file_ptr),received_char,250); */
    }else{
      received_char[0] = EOF;
      debug_false_char=1,return_size=0;
    }

    if(c)col_unbound_col(c);
    if(return_size){

      col_t* add_str01=col_new_xstring2(return_size+1,received_char,return_size);
      DER(xstring)=concat_xstring(DER(xstring),add_str01);
/*       if (!received_char[0]) */
/* 	{ */
/* 	  //this is the same as else, for '\0' */
/* 	  received_char[0]=65; */
/* 	  DER(xstring)=concat_xstring(DER(xstring),NEW_XSTRING_CONST(received_char)); */
/* 	  DER(val_xstring(DER(xstring))+*flex_num_chars_x)=0; */
/* 	} */
/*       else */
/* 	{ */
/* 	  DER(xstring)=concat_xstring(DER(xstring),NEW_XSTRING_CONST(received_char)); */
/* 	} */
   (*array_pos_x)+=return_size; 
    }
  }else{
    //read from the buffer
    if(p->current_text_heap->eof_flag==EOF){
      // EOF== was end, EOF-1==was end but rewinded
      //  the scanner will see EOF!=EOF-1 and accept the next char
      p->current_text_heap->eof_flag=EOF-1;
    }
  }
  if(return_size){
     return_char = DER(val_xstring(DER(xstring))+*flex_num_chars_x);
     (*flex_num_chars_x)++;
  }
    
  if (return_char=='\n' 
#if defined APPL_MAIN_APPLICATION_IDENTIFIER_CPP2 && APPL_MAIN_APPLICATION_IDENTIFIER_CPP2!=0
      && !cmd_ln_args_state && (fgetc_needed||(part_text_partial_flag&&!p->current_text_heap->file_ptr))
#endif
      )
    {
      col_t *i1,*i2;
      long result =aa_unset_col_col((col_t*)(p->current_text_heap->cnt_nl),i1=new_int((*flex_num_chars_x)-1));
      result =aa_assign((col_t*)(p->current_text_heap->cnt_nl),i1,i2=new_int(p->current_text_heap->cnt_nl_length),RETURN_NULL_IF_EXISTS);
      ASSERT(result);
      if(!result)
	{
	  col_unbound_col(i1);
	  col_unbound_col(i2);
	}
      p->current_text_heap->cnt_nl_length++;
    }
  MISC_MACRO_AFTER_FLEX_GET_CHAR();
  if (return_size==0)
    {
       //empty buffer and ( end of file or no file)
       p->current_text_heap->eof_flag=EOF;
    }
/*   else */
/*     { */
/*        p->current_text_heap->eof_flag=0; */
/*     } */
 end1:
  DEBUG_DUMP_CHAR(2,return_char);
  DEBUG_DUMP_INT(2,p->current_text_heap->eof_flag);
  DEBUG_DUMP_INT(2,debug_false_char);
  DEBUG_DUMP_INT(2,p->current_text_heap->array_pos);
  DEBUG_DUMP_INT(2,p->current_text_heap->flex_num_chars);
  //  ASSERT(!debug_false_char);
  END_FUNCTION(flex_getchar,return return_char;,2);
}

 
/*After grammar production is parsed connect the dependencies of the rule. The result symbol shares the buffer and the begin position with the first dependency. count is the number of dependencies + 1 */
//DOC_FUNC_DEF(main_prepare_rule DG_BISON_COMMON)
void main_prepare_rule(void*p, long token, pleaf_t* res, long count, ...)
{
  BEGIN_FUNCTION(main_prepare_rule,2);
  long i;
  parser_master_t*p1=p;
  pleaf_t dep[1000];
  va_list param_pt;
  va_start(param_pt,count);
  ASSERT(count>0);
  ASSERT(count<999);
  for(i=0;i<count-1;i++) dep[i]=va_arg(param_pt,pleaf_t);
  if (count==1)
    {
      long pos;
      pos=current_terminal_pos0(p1);
      *res=new_nonterminal(p1,token,pos,pos);
    }
  else if(count>1)
    {
      pleaf_t b=dep[0];
      pleaf_t a;
      *res=new_nonterminal(p1,token,0,0);
      a=*res;
      misc_connect_sub(a,b);
      misc_adopt_symbol(b);
      a->tag|=COL_TEXT_HEAP_BOUNDED;
      a->text_heap_heap = (text_heap_heap_t*)col_bound_col((col_t*)(b->text_heap_heap));
      /*be aware that pos_end can be in another file or buffer*/
      memcpy(a->pos,b->pos,2*sizeof(long));memcpy(a->pos_end,(dep[count-2])->pos_end,2*sizeof(long));
    }
  for(i=0;i<count-2;i++)
    {
      misc_connect_next(dep[i],dep[i+1]);
      misc_adopt_symbol(dep[i+1]);
    }
  va_end(param_pt);
  MISC_MACRO_AFTER_PRODUCTION;
  END_FUNCTION(main_prepare_rule,return;,2);
}

#if !defined NDEBUG
void dt(pleaf_t t, FILE* answ_tree)
{
  BEGIN_FUNCTION(dt,2);
  unsigned long hide_show;
  if (t)
    {
      hide_show = (!strcmp(IFDEFXX,"00") ? !(t->tag & HIDE) : t->tag & SHOW);
      if (t->tag & (LIST | LIST_NEXT))
	fprintf(answ_tree,"\n(list ; %s\n",search_table_token(t->id));
      if (hide_show)
	{
	  fprintf(answ_tree,"\n(list '%s %d %d)",search_table_token(t->id),pleaf_pos(t),pleaf_pos_end(t));
	}
      dt(t->sub,answ_tree);
      if (t->tag & LIST)
	fprintf(answ_tree,")");
      dt(t->next,answ_tree);
      if  (!(t->tag & LIST))
	if  (t->tag & LIST_NEXT)
	  fprintf(answ_tree,")");
    }
  END_FUNCTION(dt,return;,2);
}

void dt_mem_dump_to_stderr(lisp_cons_cell_t* t)
{
  BEGIN_FUNCTION(dt_mem_dump_to_stderr,2);
  if (t)
    {
      if (t->car && t->car->type == LISTP)
	{
	  fprintf(stderr,"\n(list ; %s\n",(t->comment?search_table_token(t->comment->id):""));
	  if (t->car->val)
	    dt_mem_dump_to_stderr((lisp_cons_cell_t*)(t->car->val));
	  fprintf(stderr,")");
	  if (t->cdr)
	    dt_mem_dump_to_stderr(t->cdr);
	}
      if (t->car && t->car->type == PLEAFP)
	{
	  fprintf(stderr,"\n(list '%s %d %d)",search_table_token(((pleaf_t)(t->car->val))->id),pleaf_pos((pleaf_t)(t->car->val)),pleaf_pos_end((pleaf_t)(t->car->val)));
	  if (t->cdr)
	    dt_mem_dump_to_stderr(t->cdr);
	}
    }
  END_FUNCTION(dt_mem_dump_to_stderr,return;,2);
}
void dt_mem_dump(lisp_cons_cell_t* t)
{
  BEGIN_FUNCTION(dt_mem_dump,2);
  if (t)
    {
      if (t->car && t->car->type == LISTP)
	{
	  fprintf(answ_tree,"\n(list ; %s\n",search_table_token(t->comment->id));
	  if (t->car->val)
	    dt_mem_dump((lisp_cons_cell_t*)(t->car->val));
	  fprintf(answ_tree,")");
	  if (t->cdr)
	    dt_mem_dump(t->cdr);
	}
      if (t->car && t->car->type == PLEAFP)
	{
	  fprintf(answ_tree,"\n(list '%s %d %d)",search_table_token(((pleaf_t)(t->car->val))->id),pleaf_pos((pleaf_t)(t->car->val)),pleaf_pos_end((pleaf_t)(t->car->val)));
	  if (t->cdr)
	    dt_mem_dump(t->cdr);
	}
    }
  END_FUNCTION(dt_mem_dump,return;,2);
}

void dt_mem_dump2(lisp_cons_cell_t* t)
{
  BEGIN_FUNCTION(dt_mem_dump2,2);
  if (t)
    {
      if (t->car && t->car->type == LISTP)
	{
	  fprintf(answ_tree,"\n[ # %s\n",search_table_token(t->comment->id));
	  if (t->car->val)
	    dt_mem_dump2((lisp_cons_cell_t*)(t->car->val));
	  fprintf(answ_tree,"]");
	  if (t->cdr){
	    fprintf(answ_tree,",");
	    dt_mem_dump2(t->cdr);
	  }
	}
      if (t->car && t->car->type == PLEAFP)
	{
	  fprintf(answ_tree,"\n[ \"%s\", %d, %d]",search_table_token(((pleaf_t)(t->car->val))->id),pleaf_pos((pleaf_t)(t->car->val)),pleaf_pos_end((pleaf_t)(t->car->val)));
	  if (t->cdr){
	    fprintf(answ_tree,",");
	    dt_mem_dump2(t->cdr);
	  }
	}
    }
  END_FUNCTION(dt_mem_dump2,return;,2);
}


char* dt_mem_dump_to_string(lisp_cons_cell_t* t, char* str,char*(*print_attributes)(pleaf_t p))
{
  BEGIN_FUNCTION(dt_mem_dump_to_string,2);
  char* txt;
  if (t)
    {
      if (t->car && t->car->type == LISTP)
	{
	  txt=(char*)bound_new_mem(200);
	  sprintf(txt,"\n(list ; %s",search_table_token(t->comment->id));
	  str = concat_unbound(str,strlen(str),txt,strlen(txt));
	  if (t->car->val)
	    {
	      str = dt_mem_dump_to_string((lisp_cons_cell_t*)(t->car->val),str,print_attributes);
	    }
	  sprintf(str+strlen(str),")"); //1 char from concat_unbound!
	  if (t->cdr)
	    str = dt_mem_dump_to_string(t->cdr,str,print_attributes);
	}
      if (t->car && t->car->type == PLEAFP)
	{
	  char *attr;
	  if (print_attributes)
	    {
	      attr=(*print_attributes)((pleaf_t)(t->car->val));
	    }
	  else
	    {
	      attr="";
	    }

	  txt=(char*)bound_new_mem(200);
	  sprintf(txt,"\n(list '%s %d %d)%s",search_table_token(((pleaf_t)(t->car->val))->id),pleaf_pos((pleaf_t)(t->car->val)),pleaf_pos_end((pleaf_t)(t->car->val)),attr);
	  str = concat_unbound(str,strlen(str),txt,strlen(txt));
	  if (t->cdr)
	    str=dt_mem_dump_to_string(t->cdr,str,print_attributes);
	}
    }
  END_FUNCTION(dt_mem_dump_to_string,return str;,2);
}

lisp_cons_cell_t* dt_mem(pleaf_t t)
{
  BEGIN_FUNCTION(dt_mem,2);
  unsigned long hide_show;
  lisp_cons_cell_t* new_list_cons=NULL;
  lisp_cons_cell_t* sym_cons=NULL;
  col_t* new_list=NULL;
  col_t* sym=NULL;
  static lisp_cons_cell_t* last_constructed=NULL;
  lisp_cons_cell_t* res_sub=NULL;
  lisp_cons_cell_t* res_next=NULL;
  lisp_cons_cell_t* last_constructed_sub=NULL;
  lisp_cons_cell_t* result=NULL;
  lisp_cons_cell_t* connected=NULL;

  if (!t) {END_FUNCTION(  dt_mem;,return NULL;,2);}
  hide_show = (!strcmp(IFDEFXX,"00") ? !(t->tag & HIDE) : t->tag & SHOW);
  if (t->tag & (LIST | LIST_NEXT))
    {
      if ((new_list_cons = (lisp_cons_cell_t*)malloc (sizeof(lisp_cons_cell_t))) == 0) {
	printf ("insufficient memory (lisp_cons_cell_t)\n");
	EXIT_(1);
      }
      if ((new_list = (col_t*)malloc (sizeof(col_t))) == 0) {
	printf ("insufficient memory (col_t)\n");
	EXIT_(1);
      }
      new_list_cons->cdr=NULL;
      new_list_cons->car=new_list;
      new_list_cons->comment=t;
      new_list->val= NULL;
      new_list->type=LISTP;
    }
  if (hide_show)
    {
      if ((sym_cons = (lisp_cons_cell_t*)malloc (sizeof(lisp_cons_cell_t))) == 0) {
	printf ("insufficient memory (lisp_cons_cell_t)\n");
	EXIT_(1);
      }
      if ((sym = (col_t*)malloc (sizeof(col_t))) == 0) {
	printf ("insufficient memory (col_t)\n");
	EXIT_(1);
      }
      sym->val= t;
      sym->type=PLEAFP;
      sym_cons->cdr=NULL;
      sym_cons->car=sym;
      last_constructed = sym_cons;
    }
  res_sub = dt_mem(t->sub);
  last_constructed_sub = last_constructed;
  res_next = dt_mem(t->next);
  if (t->tag & LIST)
    {
      if(sym)
	{
	  sym_cons->cdr = res_sub;
	  new_list->val = sym_cons;
	}
      else
	if(!sym)
	  {
	    new_list->val = res_sub;
	  }
      result = new_list_cons;
      new_list_cons->cdr = res_next;
      if (!res_next) last_constructed = new_list_cons;
    }

  if((!new_list)||(t->tag & LIST_NEXT))
    {
      if(!res_sub) 
	{
	  connected= res_next;
	}
      else
	if(!res_next)
	  {
	    connected = res_sub;
	  }
	else
	  {
	    last_constructed_sub->cdr = res_next;
	    connected = res_sub;
	  }
    }
  if(!new_list)
    {
      if(!sym)
	{
	  result = connected;	  
	}
      else
	if(sym)
	  {
	    sym_cons->cdr = connected;
	    result = sym_cons;
	  }
    }

  if  (!(t->tag & LIST) && (t->tag & LIST_NEXT))
    {
      if(sym)
	{
	  sym_cons->cdr = connected;
	  new_list->val = sym_cons;
	}
      else
	if(!sym)
	  {
	    new_list->val = connected;
	  }
      last_constructed = new_list_cons;
      result = new_list_cons;
    }
  END_FUNCTION(dt_mem,return result;,2);
}
#endif

void dump_tree(parser_master_t*p)
{
  BEGIN_FUNCTION(dump_tree,0);
#if !defined NDEBUG
  fflush(fp_error);
  if (!answ_tree) answ_tree = fopen(file_name("TEMP","/kk-nice-little-scratch-buffer_600102.el"), "w+" );
  fprintf(answ_tree,"(setq\n bison_syntax\n");
  if (p->top) dt_mem_dump(dt_mem(p->top));
  fprintf(answ_tree,"\n)(setq kk-buffer-evaluated t)\n");
  fflush(answ_tree);
  fclose(answ_tree);
  answ_tree=NULL;
  answ_tree = fopen(file_name("TEMP","/syntax_tree_in_python.py"), "w+" );
  fprintf(answ_tree,"bison_syntax=[\n");
  if (p->top) dt_mem_dump2(dt_mem(p->top));
  fprintf(answ_tree,"\n]\n");
  fflush(answ_tree);
  fclose(answ_tree);
  answ_tree=NULL;
#endif
  END_FUNCTION(dump_tree,return;,0);
}

void dump_tree_mem(parser_master_t*p)
{
  BEGIN_FUNCTION(dump_tree_mem,0);
#ifndef NDEBUG  
  fflush(fp_error);
  if (!answ_tree) answ_tree = fopen(file_name("TEMP","/kk-nice-little-scratch-buffer_600102.el"), "w+" );
  fprintf(answ_tree,"(setq\n bison_syntax\n");
  if (p->top) dt_mem_dump(dt_mem(p->top));
  fprintf(answ_tree,"\n)(setq kk-buffer-evaluated t)\n");
  fflush(answ_tree);
  fclose(answ_tree);
#endif
  END_FUNCTION(dump_tree_mem,return;,0);
}


#if !defined NDEBUG
RBT_CMP_FUNCTIONS_INT(token_string_prop,token_table_t,id)

void load_token_string_prop()
{
  BEGIN_FUNCTION(load_token_string_prop,0);
  long i =0;
  token_string_prop = createTree(token_string_prop_cmpLT,token_string_prop_cmpEQ,NULL,NULL,NULL,NULL);
  while (token_table[i].id)
    insertKey(token_string_prop,&token_table[i++],0);
  END_FUNCTION(load_token_string_prop,return;,0);
}

static long string_token_prop_cmpLT(void *a,void* b)
{
  return (strcmp(
		 ((token_table_t*)a)->str,
		 ((token_table_t*)b)->str
		 )>0
	  );
}

static long string_token_prop_cmpEQ(void *a,void* b)
{
  return (!strcmp(
		  ((token_table_t*)a)->str,
		  ((token_table_t*)b)->str
		  )
	  );
}

void load_string_token_prop()
{
  BEGIN_FUNCTION(load_string_token_prop,0);
  long i =0;
  string_token_prop = createTree(string_token_prop_cmpLT,string_token_prop_cmpEQ,NULL,NULL,NULL,NULL);
  while (token_table[i].id)
    insertKey(string_token_prop,&token_table[i++],0);
  END_FUNCTION(load_string_token_prop,return;,0);
}
#endif

#if ! defined NDEBUG
void db_init()
{
#if 1
  db_trace_0=fopen(file_name("RM","/trace.txt"), "w+" );
  db_trace_1=fopen(file_name("RM","/trace1.txt"), "w+" );
  db_trace_2=fopen(file_name("RM","/trace2.txt"), "w+" );
#elif 1
  db_trace_0=fopen("/dev/null", "w+" );
  db_trace_1=fopen("/dev/null", "w+" );
  db_trace_2=fopen("/dev/null", "w+" );
#endif
}
#endif

/*initialization function*/
//DOC_FUNC_DEF(general_main_init DG_BISON_COMMON)
void general_main_init()
{
  BEGIN_FUNCTION(general_main_init,2);
#ifndef NDEBUG
  yydebug=1;
#else
  yydebug=0;
#endif
  END_FUNCTION(general_main_init,return;,2);
}

#if !defined NDEBUG
long search_token_table(char *token_str)
{
  BEGIN_FUNCTION(search_token_table,2);
  token_table_t * found;
  RBT_FIND_KEY_STR(string_token_prop,token_table_t,str,token_str,found);
  END_FUNCTION(search_token_table,return (found ? found->id : 0);,2);
}

char* search_table_token(long token)
{
  BEGIN_FUNCTION(search_table_token,2);
  token_table_t * found;
  RBT_FIND_KEY_INT(token_string_prop,token_table_t,id,token,found);
  END_FUNCTION(search_table_token,return (found ? found->str : "NOT_FOUND_SEARCHED_STRING_AND_SHOULD_NEVER_BE_A_TOKEN");,2);
}
#endif


#ifndef NDEBUG
/*create bison symbol*/
//DOC_FUNC_DEF(lisp_pleaf DG_COL)
col_t* lisp_pleaf(pleaf_t p)
{
  col_t* lisp_symbol;
  STORAGE_LISP_VAR(lisp_symbol,PLEAFP,p);
  return lisp_symbol;
}


#endif

/*create list from branch*/
//DOC_FUNC_DEF(dt_mem2_body DG_BISON_LIST_FROM_BRANCH)
static lisp_cons_cell_t* dt_mem2_body(pleaf_t t, lisp_cons_cell_t** last_constructed)
{
  BEGIN_FUNCTION(dt_mem2_body,2);
  unsigned long hide_show;
  lisp_cons_cell_t* new_list_cons=NULL;
  lisp_cons_cell_t* sym_cons=NULL;
  col_t* new_list=NULL;
  col_t* sym=NULL;
  //static lisp_cons_cell_t* last_constructed=NULL;
  lisp_cons_cell_t* res_sub=NULL;
  lisp_cons_cell_t* res_next=NULL;
  lisp_cons_cell_t* last_constructed_sub=NULL;
  lisp_cons_cell_t* result=NULL;
  lisp_cons_cell_t* connected=NULL;
  if (!t) {END_FUNCTION(  dt_mem2_body,return NULL;,2);}
  hide_show = (!strcmp(IFDEFXX,"00") ? !(t->tag & HIDE) : t->tag & SHOW);
  if (t->tag & (LIST | LIST_NEXT))
    {
      //hide_show=1;//no force show if listed
      new_list_cons = (lisp_cons_cell_t*)col_new_cons(NULL,NULL);
      new_list = (col_t*)bound_new_mem (sizeof(col_t));
      new_list->mm_handle=mm_handle;

      new_list_cons->cdr=NULL;
      new_list_cons->car=new_list;
#ifndef NDEBUG
      new_list_cons->comment=t;
#endif
      new_list->val= NULL;
      new_list->type=LISTP;
    }
  if (hide_show)
    {
      sym_cons = (lisp_cons_cell_t*)col_new_cons(NULL,NULL);
      sym = (col_t*)t;
      sym_cons->cdr=NULL;
      sym_cons->car=sym;
      *last_constructed = sym_cons;
    }
  res_sub = dt_mem2_body(t->sub,last_constructed);
  last_constructed_sub = *last_constructed;
  res_next = dt_mem2_body(t->next,last_constructed);
  if (t->tag & LIST)
    {
      if(sym)
	{
	  sym_cons->cdr = res_sub;
	  new_list->val = sym_cons;
	}
      else
	if(!sym)
	  {
	    new_list->val = res_sub;
	  }
      result = new_list_cons;
      new_list_cons->cdr = res_next;
      if (!res_next) *last_constructed = new_list_cons;
    }

  if((!new_list)||(t->tag & LIST_NEXT))
    {
      if(!res_sub) 
	{
	  connected= res_next;
	}
      else
	if(!res_next)
	  {
	    connected = res_sub;
	  }
	else
	  {
	    last_constructed_sub->cdr = res_next;
	    connected = res_sub;
	  }
    }
  if(!new_list)
    {
      if(!sym)
	{
	  result = connected;	  
	}
      else
	if(sym)
	  {
	    sym_cons->cdr = connected;
	    result = sym_cons;
	  }
    }

  if  (!(t->tag & LIST) && (t->tag & LIST_NEXT))
    {
      if(sym)
	{
	  sym_cons->cdr = connected;
	  new_list->val = sym_cons;
	}
      else
	if(!sym)
	  {
	    new_list->val = connected;
	  }
      *last_constructed = new_list_cons;
      result = new_list_cons;
    }
  END_FUNCTION(dt_mem2_body,return result;,2);
}
/*create list from branch*/
//DOC_FUNC_DEF(dt_mem2 DG_BISON_LIST_FROM_BRANCH)
lisp_cons_cell_t* dt_mem2(pleaf_t t)
{
  BEGIN_FUNCTION(dt_mem2,2);
  lisp_cons_cell_t* last_constructed=NULL;
  lisp_cons_cell_t* result=NULL;
  result = dt_mem2_body(t,&last_constructed);
  END_FUNCTION(dt_mem2,return result;,2);
}
/*last terminal symbol that was recognized in a 'real' file, not an internally created buffer*/
//DOC_FUNC_DEF(misc_store_last_symbol DG_BISON_COMMON)
void misc_store_last_symbol(parser_master_t*p, pleaf_t l)
{
  if (l->id<TERMINAL_MAX_MIN_NONTERMINAL)
    {
      p->recorded_last_symbol_from_an_input_file = (l->text_heap_heap->file_ptr?l:p->recorded_last_symbol_from_an_input_file);
    }
}
/*fetch text value of symbol recursively*/
//DOC_FUNC_DEF(symbol_text_rec DG_BISON_SYMBOL_ATTRIBUTES)
col_t* symbol_text_rec(pleaf_t b,col_t*r,col_t*(*st)(pleaf_t))
{
  if (b)
    {
      if (TERMINAL_MAX_MIN_NONTERMINAL>b->id)
	{
	  r=col_concat_xstring(r,DER(st)(b));
	}
      else
	{
	  r=symbol_text_rec(b->sub,r,st);
	}
      r=symbol_text_rec(b->next,r,st);
    }
  return r;
}

/*fetch text value of symbol version 6*/
//DOC_FUNC_DEF(symbol_text6 DG_BISON_SYMBOL_ATTRIBUTES)
col_t * symbol_text6(pleaf_t sym,col_t*(*st)(pleaf_t))
{
  BEGIN_FUNCTION(symbol_text6,1);
  col_t*result=NEW_XSTRING_CONST("");
  ASSERT(sym);
  if (TERMINAL_MAX_MIN_NONTERMINAL>sym->id)
    {
      result=col_concat_xstring(result,DER(st)(sym));
    }
  else
    {
      result=symbol_text_rec(sym->sub,result,st);
    }
  END_FUNCTION(symbol_text6,return result;,1);
}
/*new terminal dummy is a terminal ignored by lexer, i.e. the one not forwarded to the bison parser: at the end of the function there is macro to use if necessary (but the macro is unusable in precompiled library). On such a terminal, the lexer 'falls through' and doesn't return but goes on scanning the next terminal.*/
//DOC_FUNC_DEF(new_terminal_dummy DG_BISON_COMMON)
void new_terminal_dummy(parser_master_t*p,long id, long pos0 ,long pos1)
{
  BEGIN_FUNCTION(new_terminal_dummy,0);
  leaf_t ct_dummy;
  pleaf_t ct=&ct_dummy;
  ct->id =id;
  ct->pos[0]=pos0;
  ct->pos[1]=pos1;
  ct->next = NULL;
  ct->sub = NULL;
  ct->next_all = NULL;
  ct->sub_all = NULL;
  ct->tag = 0;
  ct->pos_end[0]=pos0;
  ct->pos_end[1]=pos1;
  ct->text_heap_heap = p->current_text_heap;
  DEBUG_DUMP_PLEAF(0,ct);
#ifndef MISC_MACRO_AFTER_NEW_TERMINAL_DUMMY
#define MISC_MACRO_AFTER_NEW_TERMINAL_DUMMY()
#endif
  MISC_MACRO_AFTER_NEW_TERMINAL_DUMMY();
  END_FUNCTION(new_terminal_dummy,return;,0);
}
