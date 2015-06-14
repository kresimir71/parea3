#include "col.h"
//#include "inc.h"
#include "stdarg.h"
#include "misc.h"
#include "assert.h"
//#include "debug.h"
//#include "goals.h"
//#include "debug2.h"


/*number of chars flex gets on its request*/
//DOC_VARIABLE(number_of_chars_to_read_for_flex DG_FLEX_READCHAR)
long number_of_chars_to_read_for_flex=128;


/* Called by yyparse on error */
//DOC_FUNC_DEF(yyerror DG_BISON_COMMON)
int yyerror(char *s)
{
#if !defined NDEBUG && DEBUG_DISABLE==0
       fprintf (fp_error,"%s\n", s);
#endif
       return 0;
}
/*print error: not used*/
//DOC_FUNC_DEF(yyprint DG_BISON_COMMON)
int yyprint( FILE *file, int type, YYSTYPE value)
{
  return 0;
}
/*Call flex to find next symbol.Note that the main function of flex is called yylex and flex defines macro yylex to be yy_lex.Parser needs yylex function.*/
//DOC_FUNC_DEF(yylex DG_FLEX_ENTRY_POINT)
int yylex(YYSTYPE *t, void*current_misc_master_record)
{ 
  long result;
  parser_master_t*m=(parser_master_t*)current_misc_master_record;
  /*usually, misc_yylex is in fact called here*/
  result= DER(m->col01_yylex)(t,current_misc_master_record);
  return result;
}
/*call flex to find next symbol*/
//DOC_FUNC_DEF(misc_yylex DG_FLEX_ENTRY_POINT)
long misc_yylex(YYSTYPE *t, void*current_misc_master_record)
{ 
  long result=0;
  parser_master_t*m=(parser_master_t*)current_misc_master_record;
  for(;;){
    m->misc_flex_try_again=0;
    result = yylex_(m);
    misc_macro_after_symbol(m);
    if (m->misc_flex_try_again)
      {
	continue;
	//result = misc_yylex(t,current_misc_master_record);
      }
    break;
  }
  *t=m->yylval;
  return result;
}
/*finalization function*/
//DOC_FUNC_DEF(yylex_close DG_BISON_COMMON)
int yylex_close()
{
  return 0;
}
/*continue call flex to find next symbol*/
//DOC_FUNC_DEF(yylex_ DG_FLEX_ENTRY_POINT)
long yylex_(parser_master_t*p)
{
  pleaf_t false_token;
  fflush(fp_error);
  if (!(false_token=(pleaf_t)list_pop_last(p->additional_token_list)))
    {
      long result=0;
      /*calling flex: usually, yy_lex or similar (depending on chosen suffix) is in fact called here*/
      result=DER(p->col01_flex_call)(NULL);
      main_after_symbol_macro(&result);
      return result;
    }
  else
    {
      p->yylval=false_token;
      return false_token->id;
    }
  return 0;
}

/*New parser. gc gets next character for flex, yyl gets next symbol for parser, flex_yyl is call flex to get next symbol.*/
//DOC_FUNC_DEF(misc_new_parser DG_BISON_COMMON)
parser_master_t* misc_new_parser(long (*gc)(parser_master_t*), long (*yyl)(YYSTYPE *, void*),int (*flex_yyl)(void**))
{
  parser_master_t*m=(parser_master_t*)mm2_bound_new_mem(sizeof(parser_master_t));
  col_t*var=(col_t*)m;
  var->type=PARSERP;
  var->mm_handle=mm2_handle;
  var->val=NULL;
  m->misc_parse_error_list =aa_array();
  m->change_pos=0;
  m->change_state=-1;
  m->connecting_nonterminal=NULL;
  m->recorded_last_symbol_from_an_input_file=NULL;
  m->recorded_last_symbol=NULL;
  m->parser_user_data=NULL;
  m->current_text_heap=NULL;
  m->current_terminal=NULL;
  m->current_nonterminal=NULL;
  m->top=NULL;
  m->additional_token_list = list_create(NULL);
  m->misc_parser_for_flex = NULL;
  m->col01_flex_getchar = gc;
  m->col01_yylex = yyl;
  m->col01_flex_call = flex_yyl;
  m->misc_yychar=NULL;
  m->misc_yyempty=2;
  //  m->col01_scanner_at_eof=0;
  if(flex_yyl) {
    void *p;
    DER(m->col01_flex_call)(&p);
    m->misc_parser_for_flex = p;

/*     long parser_in_flex = DER(m->col01_flex_call)(); */
/*     long parser_in_flex_HI64bit=0;DER(m->col01_flex_call)(); //used only on 64bit systems: higher 32 bits */
/*     m->misc_parser_for_flex=(parser_master_t**)(((unsigned long)parser_in_flex)+(((unsigned long)parser_in_flex_HI64bit)<<32)); */

    *(m->misc_parser_for_flex)=m;
  }
  return m;
}

/*create list from branch element*/
//DOC_FUNC_DEF(dt_mem2_from_current_list DG_BISON_LIST_FROM_BRANCH)
lisp_cons_cell_t* dt_mem2_from_current_list(col_t* current)
{
  assert(LISTP==current->type);  
  return (lisp_cons_cell_t*)(current->val);
}
/*push a string ahead of flex input*/
//DOC_FUNC_DEF(misc_push_ahead DG_FLEX_BUFFERS)
void misc_push_ahead(text_heap_heap_t* h,col_t*x)
{
  assert(XSTRINGP==x->type);
  h->misc_ahead_xstring=col_concat_xstring(h->misc_ahead_xstring,x);
  return;
}
/*gets pointer to the next ahead char if any as NULL or 1 char xstring*/
//DOC_FUNC_DEF(misc_get_next_ahead DG_FLEX_BUFFERS)
col_t* misc_get_next_ahead(text_heap_heap_t* h)
{
  col_t*x=h->misc_ahead_xstring;
  col_t* result=NULL;
  if (length_xstring(x))
    {
      if (h->misc_ahead_read<length_xstring(x))
	{
	  h->misc_ahead_read++;
	  result = col_new_xstring2(1,val_xstring(x)+h->misc_ahead_read-1,1);
	}
      if (h->misc_ahead_read>=length_xstring(x))
	{
	  col_unbound_col(x);
	  x=h->misc_ahead_xstring=NEW_XSTRING_CONST("");
	  h->misc_ahead_read=0;
	}
    }
  return result;
}
/*sets free a branch of the parse tree*/
//DOC_FUNC_DEF(misc_unbound_rec_from_misc_parse_error_list DG_BISON_COMMON)
void misc_unbound_rec_from_misc_parse_error_list(pleaf_t b)
{
  if (b)
    {
      misc_unbound_rec_from_misc_parse_error_list(b->sub_all);
      misc_unbound_rec_from_misc_parse_error_list(b->next_all);
      col_unbound_col(b);
    }
  return;
}
/*unbound misc_parse_error_list*/
//DOC_FUNC_DEF(misc_unbound_parse_error_list_step DG_BISON_COMMON)
void misc_unbound_parse_error_list_step(aa_data_t*a)
{
  col_t*c;
  pleaf_t p;
  c=a->key;
  assert(c);
  p = (pleaf_t)(c->val);
  assert(p);
  misc_unbound_rec_from_misc_parse_error_list(p->sub_all);
  misc_unbound_rec_from_misc_parse_error_list(p->next_all);
}
/*unbound misc_parse_error_list*/
//DOC_FUNC_DEF(misc_unbound_parse_error_list DG_BISON_COMMON)
void misc_unbound_parse_error_list(parser_master_t*p)
{
  aa_foreach(p->misc_parse_error_list,(col_data_function_t)misc_unbound_parse_error_list_step);
  aa_unbound_pcol_col(p->misc_parse_error_list);
}

/*remove from misc_parse_error_list terminals not involved in parse error*/
//DOC_FUNC_DEF(misc_adopt_symbol DG_BISON_COMMON)
void misc_adopt_symbol(pleaf_t l)
{
  col_t*i=new_int((long)l);
  parser_master_t*p=l->text_heap_heap->ps01_parser;
  long res;
  if (!(l->tag&COL_TEXT_HEAP_BOUNDED))
    col_bound_col((col_t*)(l->text_heap_heap));
  l->tag|=COL_TEXT_HEAP_BOUNDED;
  res=aa_unset_col_col(p->misc_parse_error_list,i);
  assert(res);
  col_unbound_col(i);
  /* */
  misc_store_last_symbol(p,l);
}
/*Create buffer from command line. Every argv[i] is a null terminated string. argv[i] is pushed to input with a zero at the end. After the last argv[i], three zeros ar pushed followed by two zeros and EOF=255 */
//DOC_FUNC_DEF(push_arguments_to_buffer_0 DG_COMMAND_LINE_COMMON)
void push_arguments_to_buffer_0(parser_master_t*p,long argc,char**argv,long state)
{
  long i;
  char n[2]={'%','\0'};
  char e[]={'%','%','%','\0'};
  long previous_zero=0;
  long current_zero=0;
  p->current_text_heap = open_text_file_for_read(p,"--",NULL);
  for (i=1;i<argc;i++)
    {
      current_zero=!*(argv[i]); 
      if (current_zero && previous_zero){
	//only -Da= "" has sense (silently ignore two "" "" - should this be removed and tested? problem is that many of "" can seem like correct pp_end_of_cmdln  - maybe we should prependa character to every argv[i] - what about special status of EOF?)
	continue;
      }
      previous_zero=current_zero;
      col_t*x= NEW_XSTRING_CONST(argv[i]);
      col_t*z= NEW_XSTRING_CONST(n);
      DER(val_xstring(z))=0;
      flex_pushstring2(p,x);
      flex_pushstring2(p,z);
    }
  col_t*t= NEW_XSTRING_CONST(e);
  DER(val_xstring(t))=0;
  DER(val_xstring(t)+1)=0;
  DER(val_xstring(t)+2)=0;
  flex_pushstring2(p,t);		      
  flex_pushstring2null(p);
  rewind_scanner(p,state,0);
  return;
}
/*print error on begin of symbol*/
//DOC_FUNC_DEF(error_text DG_ERROR_HANDLING)
void error_text(pleaf_t p, char* text)
{
  if (p)
    {
      fprintf(stderr,"%s:%d: %s\n",symbol_file(p),line_number_middle(p),text);
    }
  else
    {
      fprintf(stderr," %s\n",text);
    }
  return;
}
/*print error on end of symbol*/
//DOC_FUNC_DEF(error_text_end DG_ERROR_HANDLING)
void error_text_end(pleaf_t p, char* text)
{
  if (p)
    {
      fprintf(stderr,"%s:%d: %s\n",symbol_file(p),line_number_end(p),text);
    }
  else
    {
      fprintf(stderr," %s\n",text);
    }
  return;
}
/*report fatal error*/
//DOC_FUNC_DEF(misc_fatal_error_exit DG_ERROR_HANDLING)
void misc_fatal_error_exit(parser_master_t*p,char*message)
{
  error_text(last_symbol_from_an_input_file(p),message); 
  EXIT_(1);
  return;
}
/*last recorded symbol from 'real' file, not from a buffer*/
//DOC_FUNC_DEF(last_symbol_from_an_input_file DG_BISON_COMMON)
pleaf_t last_symbol_from_an_input_file(parser_master_t*p)
{
  return p->recorded_last_symbol_from_an_input_file;
}


/*unbound list from branch*/
//DOC_FUNC_DEF(dt_mem_unbound DG_BISON_LIST_FROM_BRANCH)
void dt_mem_unbound(lisp_cons_cell_t* t)
{
  if (t)
    {
      if (t->car && t->car->type == LISTP)
	{
	  if (t->car->val)
	    dt_mem_unbound((lisp_cons_cell_t*)(t->car->val));
	  if (t->cdr)
	    dt_mem_unbound(t->cdr);
	  unbound_mem_from_handle(t->car->mm_handle);
	  unbound_mem_from_handle(t->mm_handle);
	}
      else if (t->car && t->car->type == PLEAFP)
	{
	  if (t->cdr)
	    dt_mem_unbound(t->cdr);
	  unbound_mem_from_handle(t->mm_handle);
	}
      else
	{
	  assert(!t->cdr);
	  assert(0);
	  unbound_mem_from_handle(t->mm_handle);
	}
    }
  return;
}
/*open file in given path*/
//DOC_FUNC_DEF(text_file_for_read DG_FLEX_BUFFERS)
FILE* text_file_for_read(parser_master_t*p,col_t* dirs, col_t*file_name)
{
  col_t* dir;
  long i=0;
  FILE*result=NULL;
  assert(AAP==dirs->type && XSTRINGP==file_name->type);
  while((dir=xstring_aa_value_sint(dirs,i++)))
    {
      col_t* dir_copy=duplicate_xstring(dir);
      col_t* file_name_copy=duplicate_xstring(file_name);
      if ((result=probe_text_file_for_read(p,dir_copy,file_name_copy)))
	{
	  break;
	}
    }
  if (!result)
    {
      memcpy(p->full_name_of_last_open_file,val_xstring(file_name),MIN(511,length_xstring(file_name)));
      DER(p->full_name_of_last_open_file+511)=0;
    }
  return result;
}
/*open file in given directory*/
//DOC_FUNC_DEF(probe_text_file_for_read DG_FLEX_BUFFERS)
FILE* probe_text_file_for_read(parser_master_t*p,col_t* dir, col_t*file_name)
{
  col_t*name;
  FILE* result;
  assert(XSTRINGP==dir->type && XSTRINGP==file_name->type);
  name=concat_xstring(concat_xstring(dir,NEW_XSTRING_CONST("/")),file_name);
  result = fopen(val_xstring(name), "r" );
  if (result)
    {
      strncpy(p->full_name_of_last_open_file,val_xstring(name),511);
      DER(p->full_name_of_last_open_file+511)=0;
    }
  unbound_xstring(name);
  return result;
}
/*push token to parser input*/
//DOC_FUNC_DEF(push_additional_token_list DG_BISON_PUSHSYMBOL)
void push_additional_token_list(parser_master_t*p,long id,long pos0,long pos1)
{
  pleaf_t token=new_terminal(p,id ,pos0 ,pos1);
  list_push(p->additional_token_list,token);
  return;
}

/*open a buffer for storing read characters*/
//DOC_FUNC_DEF(open_text_file_for_read DG_FLEX_BUFFERS)
text_heap_heap_t* open_text_file_for_read(parser_master_t*p,char* file,col_t*dir_array)
{
  static long text_heap_counter = 0;
  text_heap_heap_t *new_text_heap;
  assert(!dir_array || AAP==dir_array->type);
  new_text_heap = (text_heap_heap_t *)col_new_file();
  new_text_heap->eof_flag=0;
  new_text_heap->cnt_nl=aa_array();
  new_text_heap->cnt_nl_length=0;
  new_text_heap->id = text_heap_counter++;
  p->current_text_heap = new_text_heap;
  new_text_heap->ps01_parser=p;
  new_text_heap->flex_num_chars =0;
  new_text_heap->array_pos =0;
  new_text_heap->xstring=NEW_XSTRING_CONST("");
  new_text_heap->misc_ahead_xstring=NEW_XSTRING_CONST("");
  new_text_heap->misc_ahead_read=0;
  if (strcmp(file,"--")) 
    {
      if (!dir_array)
	{
	  new_text_heap->file_name = COL_NEW_XSTRING_CONST(file);
	  new_text_heap->file_ptr = fopen( val_xstring(new_text_heap->file_name), "r" );
	  if (new_text_heap->file_ptr == 0) 
	    {
	      fprintf (stderr,"File '%s' can not be read\n",val_xstring(new_text_heap->file_name));
	      EXIT_(1);
	    }
	}
      else
	{
	  col_t*fn=NEW_XSTRING_CONST(file);
	  new_text_heap->file_ptr = text_file_for_read(p,dir_array,fn);
	  new_text_heap->file_name = COL_NEW_XSTRING_CONST(p->full_name_of_last_open_file);
	  unbound_xstring(fn);
	}
    }
  else
    {
      new_text_heap->file_name = COL_NEW_XSTRING_CONST(file);
      new_text_heap->file_ptr=NULL;
    }

  return new_text_heap;
}


/*fetch text value of symbol version 3*/
//DOC_FUNC_DEF(symbol_text3 DG_BISON_SYMBOL_ATTRIBUTES)
col_t * symbol_text3(pleaf_t sym)
{
  col_t*result;
  long pos_beg = pleaf_pos(sym)-1;
  long pos_end = pleaf_pos_end(sym)-1;
  long length =pos_end-pos_beg;
  assert(length>-1);
  if(length)
    {
      result = xstring_substring(sym->text_heap_heap->xstring,pos_beg,pos_end-1,XSTRING_BOUNDNEW);
    }
  else
    {
      result=NEW_XSTRING_CONST("");
    }
  return result;
}
/*open a buffer for storing read characters and push a string*/
//DOC_FUNC_DEF(flex_create_new_read_xstring DG_FLEX_PUSHSTRING)
void flex_create_new_read_xstring(parser_master_t*p,col_t*xstr,long state)
{
  assert(XSTRINGP==xstr->type);
  open_text_file_for_read(p,"--",NULL);
  flex_pushstring2(p,xstr);
  rewind_scanner(p,state,0);
  return;
}

/*identify all connecting nonterminals (but really finds only first 10 of each, i.e. ...PAR_10 is not found)*/
//DOC_FUNC_DEF(load_connecting_nonterminal DG_BISON_LIST_FROM_BRANCH)
void load_connecting_nonterminal(parser_master_t*p)
{
  long i =0;
  p->connecting_nonterminal = aa_array();
  while (token_table[i].id)
    {
      col_t*xs=NEW_XSTRING_CONST(token_table[i].str);
      long l=length_xstring(xs);
      if (l>4)
	{
	  xs=xstring_substring(xs,-4,-2,XSTRING_REUSE);
	  if (!strcmp(val_xstring(xs),"_EL")||
	      !strcmp(val_xstring(xs),"AR_")||
	      !strcmp(val_xstring(xs),"EQ_")||
	      !strcmp(val_xstring(xs),"PT_"))
	    {
	      long res=aa_assign_sint_xstring(p->connecting_nonterminal,token_table[i].id,xs,RETURN_NULL_IF_EXISTS);
	      res=res;
	      assert(res);
	    }
	  else
	    {
	      unbound_xstring(xs);
	    }
	}
      i++;
    }
  return;
}

/*compile pcre */
//DOC_FUNC_DEF(compile_pcre DG_BISON_COMMON)
void compile_pcre(pcre **re, char *pattern)
{
  const char *error;
  long erroffset;
  *re = pcre_compile(
		    pattern,              /* the pattern */
		    0,                    /* default options */
		    &error,               /* for error message */
		    &erroffset,           /* for error offset */
		    NULL);                /* use default character tables */
  if (*re == NULL)
   {
     printf("PCRE compilation failed for pattern %s at offset %d: %s\n", pattern, erroffset, error);
     EXIT_(1);
   }

  return;
}

/*use pcre */
//DOC_FUNC_DEF(use_pcre DG_BISON_LIST_FROM_BRANCH)
long use_pcre(pcre *re, char *subject, long subject_length, long *rc,long ovector[],long oveccount)
{
  const char *error;
  long erroffset;
  *rc = pcre_exec(
		  re,                   /* the compiled pattern */
		  NULL,                 /* no extra data - we didn't study the pattern */
		  subject,              /* the subject string */
		  subject_length,       /* the length of the subject */
		  0,                    /* start at offset 0 in the subject */
		  0,                    /* default options */
		  ovector,              /* output vector for substring information */
		  oveccount /* must be multiple of 3 */);

  if (*rc < 0)
    {
      switch(*rc)
	{
	case PCRE_ERROR_NOMATCH: /*printf("No match\n");*/ break;
	  /*
	    Handle other special cases if you like
	  */
	default: /* printf("Matching error %d\n", *rc); */ break;
	}
      return 1;
    }
  if (*rc == 0)
    {
      *rc = oveccount/3; /* take all matches that ARE recorded*/
      //printf("ovector only has room for %d captured substrings\n", *rc - 1);
    }
  { /* This prints main match and the submatches*/
    /*     int i; */
    /*     for (i = 0; i < *rc; i++) */
    /*       { */
    /* 	char *substring_start = subject + ovector[2*i]; */
    /* 	int substring_length = ovector[2*i+1] - ovector[2*i]; */
    /* 	printf("%2d: %.*s\n", i, substring_length, substring_start); */
    /*       } */
  }
  return 0;
}

/*identify all connecting nonterminals version 2, (but really finds only first 10 of each, i.e. ...PAR_10 is not found) */
//DOC_FUNC_DEF(load_connecting_nonterminal2 DG_BISON_LIST_FROM_BRANCH)
void load_connecting_nonterminal2(parser_master_t*p)
{
  long i =0;
  pcre *re1, *re2, *re3, *re4, *re5;
  compile_pcre(&re1,".*_ELM$");
  compile_pcre(&re2,".*PAR_[0-9]+$");
  compile_pcre(&re3,".*SEQ_[0-9]+$");
  compile_pcre(&re4,".*OPT_[0-9]+$");
  compile_pcre(&re5,".*_SEP$");
  p->connecting_nonterminal = aa_array();

  while (token_table[i].id)
    {
      col_t*xs=NEW_XSTRING_CONST(token_table[i].str);
      long l=length_xstring(xs);
      long ovector[9];
      long oveccount=9;
      long rc;
      if (l>4)
	{
	  //	  xs=xstring_substring(xs,-4,-2,XSTRING_REUSE);
	  if (!use_pcre(re1,val_xstring(xs),l,&rc,ovector,oveccount)||
	      !use_pcre(re2,val_xstring(xs),l,&rc,ovector,oveccount)||
	      !use_pcre(re3,val_xstring(xs),l,&rc,ovector,oveccount)||
	      !use_pcre(re4,val_xstring(xs),l,&rc,ovector,oveccount)||
	      !use_pcre(re5,val_xstring(xs),l,&rc,ovector,oveccount))
	    {
	      long res=aa_assign_sint_xstring(p->connecting_nonterminal,token_table[i].id,xs,RETURN_NULL_IF_EXISTS);
	      res=res;
	      assert(res);
	    }
	  else
	    {
	      unbound_xstring(xs);
	    }
	}
      i++;
    }
  free(re1);
  free(re2);
  free(re3);
  free(re4);
  free(re5);
  return;
}

/*generate new terminal*/
//DOC_FUNC_DEF(new_terminal DG_BISON_COMMON)
pleaf_t new_terminal(parser_master_t*p,long id, long pos0 ,long pos1)
{
  long res;
  p->current_terminal = (pleaf_t)col_new_pleaf();
  p->current_terminal->id =id;
  p->current_terminal->pos[0]=pos0;
  p->current_terminal->pos[1]=pos1;
  p->current_terminal->next = NULL;
  p->current_terminal->sub = NULL;
  p->current_terminal->next_all = NULL;
  p->current_terminal->sub_all = NULL;
  p->current_terminal->tag = 0;
  p->current_terminal->user_attributes = NULL;
  p->current_terminal->pos_end[0]=pos0;
  p->current_terminal->pos_end[1]=pos1;
  p->current_terminal->text_heap_heap = p->current_text_heap;
  p->current_terminal->tag&=~COL_TEXT_HEAP_BOUNDED;
  res=aa_assign(p->misc_parse_error_list,new_int((long)p->current_terminal),new_int(0),RETURN_NULL_IF_EXISTS);
  assert(res);
  return(p->current_terminal);
}
/* buffer position of the current terminal*/
//DOC_FUNC_DEF(current_terminal_pos0 DG_BISON_COMMON)
long current_terminal_pos0(parser_master_t*p)
{
  long result=0;
  if (p->current_terminal ) result=p->current_terminal->pos[0];
  return result;
}
/*generate new nonterminal*/
//DOC_FUNC_DEF(new_nonterminal DG_BISON_COMMON)
pleaf_t new_nonterminal(parser_master_t*p,long id, long pos0 ,long pos1)
{
  long res;
  p->current_nonterminal = (pleaf_t)col_new_pleaf();
  p->current_nonterminal->id =id;
  p->current_nonterminal->pos[0]=pos0;
  p->current_nonterminal->pos[1]=pos1;
  p->current_nonterminal->next = NULL;
  p->current_nonterminal->sub = NULL;
  p->current_nonterminal->next_all = NULL;
  p->current_nonterminal->sub_all = NULL;
  p->current_nonterminal->tag = 0;
  p->current_nonterminal->user_attributes = NULL;
  p->current_nonterminal->pos_end[0]=pos0;
  p->current_nonterminal->pos_end[1]=pos1;
  p->current_nonterminal->text_heap_heap = p->current_text_heap;
  p->current_nonterminal->tag&=~COL_TEXT_HEAP_BOUNDED;
  res=aa_assign(p->misc_parse_error_list,new_int((long)p->current_nonterminal),new_int(0),RETURN_NULL_IF_EXISTS);
  assert(res);
  return(p->current_nonterminal);
}
/*list a branch beginning with given result*/
void list(pleaf_t b)
{
  b->tag |= LIST;
}
/*list a next branch beginning with given symbol*/
//DOC_FUNC_DEF(list_n DG_BISON_SYMBOL_ATTRIBUTES)
void list_n(pleaf_t b)
{
  b->tag |= LIST_NEXT;
}
/*hide symbol from listing*/
void hide(pleaf_t b)
{
  b->tag |= HIDE;
}
/*show symbol in list*/
void show(pleaf_t b)
{
  b->tag |= SHOW;
}
/*show symbols with given id in list*/
//DOC_FUNC_DEF(show_rec_id DG_BISON_SYMBOL_ATTRIBUTES)
void show_rec_id(pleaf_t b,long id)
{
  if (b)
    {
      if (id==b->id) b->tag |= SHOW;
      show_rec_id(b->sub,id);
      show_rec_id(b->next,id);
    }
}
/*find symbol with given id in branch*/
//DOC_FUNC_DEF(find_pleaf_with_id DG_BISON_SYMBOL_ATTRIBUTES)
pleaf_t find_pleaf_with_id(pleaf_t b,long id)
{
  pleaf_t c;
  pleaf_t d;
  if (b)
    {
      if (id==b->id) return b;
      c=find_pleaf_with_id(b->sub,id);
      d=find_pleaf_with_id(b->next,id);
      if (c) return c;
      if (d) return d;
    }
  return NULL;
}
/*show all except connecting*/
//DOC_FUNC_DEF(show_rec_except_conn DG_BISON_SYMBOL_ATTRIBUTES)
void show_rec_except_conn(pleaf_t b)
{
  if (b)
    {
      parser_master_t*p=b->text_heap_heap->ps01_parser;
      if(!xstring_aa_value_sint(p->connecting_nonterminal,b->id)){b->tag |= SHOW;}
      show_rec_except_conn(b->sub);
      show_rec_except_conn(b->next);
    }
}
/*show all*/
//DOC_FUNC_DEF(show_rec DG_BISON_SYMBOL_ATTRIBUTES)
void show_rec(pleaf_t b)
{
  if (b)
    {
      b->tag |= SHOW;
      show_rec(b->sub);
      show_rec(b->next);
    }
}
/*show all except*/
//DOC_FUNC_DEF(show_rec_except_under_id_but_well_under_di DG_BISON_SYMBOL_ATTRIBUTES)
void show_rec_except_under_id_but_well_under_di(pleaf_t b,long id,long di, long do_show)
{
  assert(do_show==0 || do_show==1);
  if(b&& b->id==id) do_show=0;
  if(b&& b->id==di) do_show=1;
  if (b)
    {
      if (do_show) b->tag |= SHOW;
      show_rec_except_under_id_but_well_under_di(b->sub,id,di,do_show);
      show_rec_except_under_id_but_well_under_di(b->next,id,di,do_show);
    }
  return;
}

/*remove all lists in branch*/
//DOC_FUNC_DEF(delist_rec DG_BISON_SYMBOL_ATTRIBUTES)
void delist_rec(pleaf_t b)
{
  if (b)
    {
      b->tag &= ~LIST;
      delist_rec(b->sub);
      delist_rec(b->next);
    }
}
/*unshow all*/
//DOC_FUNC_DEF(deshow_rec DG_BISON_SYMBOL_ATTRIBUTES)
void deshow_rec(pleaf_t b)
{
  if (b)
    {
      b->tag &= ~SHOW;
      deshow_rec(b->sub);
      deshow_rec(b->next);
    }
}
/*unshow all with given id*/
//DOC_FUNC_DEF(deshow_rec_id DG_BISON_SYMBOL_ATTRIBUTES)
void deshow_rec_id(pleaf_t b,long id)
{
  if (b)
    {
      if (b->id==id) b->tag &= ~SHOW;
      deshow_rec_id(b->sub,id);
      deshow_rec_id(b->next,id);
    }
}
/*unshow symbol*/
//DOC_FUNC_DEF(deshow DG_BISON_SYMBOL_ATTRIBUTES)
void deshow(pleaf_t b)
{
  if (b)
    {
      b->tag &= ~SHOW;
    }
}
/*connect next in tree both for user and internal pointer*/
//DOC_FUNC_DEF(misc_connect_next DG_BISON_SYMBOL_ATTRIBUTES)
void misc_connect_next(pleaf_t a, pleaf_t b)
{
  a->next = b;
  a->next_all = b;
}
/*connect sub branch both for user and internal pointer*/
//DOC_FUNC_DEF(misc_connect_sub DG_BISON_SYMBOL_ATTRIBUTES)
void misc_connect_sub(pleaf_t a, pleaf_t b)
{
  a->sub = b;
  a->sub_all = b;
}

/*exchange symbols*/
/* void e(pleaf_t* a, pleaf_t* b) */
/* { */
/*   pleaf_t c=*a; */
/*   *a=*b; */
/*   *b=c; */
/* } */

/*id of a symbol*/
void id(pleaf_t a, long id)
{
  a->id = id;
}
/*return begin position of a symbol*/
//DOC_FUNC_DEF(pleaf_pos DG_BISON_SYMBOL_ATTRIBUTES)
long pleaf_pos(pleaf_t t)
{
  return t->pos[0];
}
/*return end position of a symbol*/
//DOC_FUNC_DEF(pleaf_pos_end DG_BISON_SYMBOL_ATTRIBUTES)
long pleaf_pos_end(pleaf_t t)
{
  return t->pos_end[1];
}


/*change flex state without changing position*/
//DOC_FUNC_DEF(change_flex_state DG_FLEX_REWIND_OR_CHANGE_STATE)
void change_flex_state(parser_master_t*p,long state)
{
  p->change_state = state;
  //  if (p->change_state!=-1){assert(*(p->misc_yychar)==p->misc_yyempty)};
  p->change_pos = -1;
  return;
}
/*change the current lookahead character of the parser to YYEMPTY which is 2:  check that it is 2 or put initialization   m->misc_yyempty=YYEMPTY; at the end of *.y file. This is currently done in the first executed action of the grammar. Better place is at the end of the grammar. Also '#define yyclearin	(yychar = YYEMPTY)' is the official way to clear lookahead - be sure this is the same in all used bison versions.*/
//DOC_FUNC_DEF(misc_empty_lookahead DG_FLEX_REWIND_OR_CHANGE_STATE)
void misc_empty_lookahead(parser_master_t*p)
{
  if(p->misc_yychar){
     *(p->misc_yychar)=p->misc_yyempty;
  }
  return;
}

/*change flex state and position in the current buffer*/
//DOC_FUNC_DEF(rewind_scanner DG_FLEX_REWIND_OR_CHANGE_STATE)
void rewind_scanner(parser_master_t*p,long state_int, long pos)
{
  p->change_state = state_int;
  if(pos!=-1)
    {
      p->change_pos = pos;
      p->current_text_heap->flex_num_chars=p->change_pos;
    }
  else
    {
      p->change_pos=p->current_text_heap->flex_num_chars;
    }
  misc_empty_lookahead(p);
  return;
}
/*change flex state,position and current buffer to suit the end of given symbol*/
//DOC_FUNC_DEF(rewind_after_symbol DG_FLEX_REWIND_OR_CHANGE_STATE)
void rewind_after_symbol(pleaf_t sym, long state)
{
  parser_master_t*p=sym->text_heap_heap->ps01_parser;
  p->change_state = state;
  p->change_pos = pleaf_pos_end(sym)-1;
  p->current_text_heap=  sym->text_heap_heap;
  sym->text_heap_heap->flex_num_chars=p->change_pos;
  //#ifdef NDEBUG
  if (p->change_pos == -1) {
    printf ("no position of symbol (rewind_after_symbol())\n");
    EXIT_(1);
  }
  //#endif
  misc_empty_lookahead(p);
  return;
}
/*change flex state,position and current buffer to suit the beginning of given symbol*/
//DOC_FUNC_DEF(rewind_before_symbol DG_FLEX_REWIND_OR_CHANGE_STATE)
void rewind_before_symbol(pleaf_t sym, long state)
{
  parser_master_t*p=sym->text_heap_heap->ps01_parser;
  p->change_state = state;
  p->change_pos = pleaf_pos(sym)-1;
  p->current_text_heap=  sym->text_heap_heap;
  sym->text_heap_heap->flex_num_chars=p->change_pos;
  assert(p->change_pos != -1);
  misc_empty_lookahead(p);
  return;
}
/*calculate file name from environment variable and file name*/
//DOC_FUNC_DEF(file_name DG_BISON_COMMON)
char *file_name(char* env, char* name)
{
  static char file_name_array[2000];
  if (strlen(name)>1998)
    {
      fprintf(stderr, "%s file name too long\n",name);
      EXIT_(1);
    }
  sprintf(file_name_array,"%s%s",getenv(env),name);
  return file_name_array;
}
/*give file name which contains the given symbol*/
//DOC_FUNC_DEF(symbol_file DG_BISON_SYMBOL_ATTRIBUTES)
char* symbol_file(pleaf_t sym)
{
  return val_xstring(sym->text_heap_heap->file_name);
}
/*give line number of symbol middle*/
//DOC_FUNC_DEF(line_number_middle DG_BISON_SYMBOL_ATTRIBUTES)
long line_number_middle(pleaf_t sym)
{
  long pos_beg = pleaf_pos(sym)-1;
  long pos_end = pleaf_pos_end(sym)-1;
  long length =pos_end-pos_beg;
  long result ;
  if(length>1)
    result=line_number(sym->text_heap_heap,pos_beg+1);
  else
    result=line_number(sym->text_heap_heap,pos_beg);
  return result;
}

/*give line number of symbol begin*/
//DOC_FUNC_DEF(line_number_beg DG_BISON_SYMBOL_ATTRIBUTES)
long line_number_beg(pleaf_t sym)
{
  return line_number(sym->text_heap_heap,pleaf_pos(sym)-1);
}
/*give line number of symbol end*/
//DOC_FUNC_DEF(line_number_end DG_BISON_SYMBOL_ATTRIBUTES)
long line_number_end(pleaf_t sym)
{
  return line_number(sym->text_heap_heap,pleaf_pos_end(sym)-1);
}
/*give line number of character in buffer*/
//DOC_FUNC_DEF(line_number DG_FLEX_BUFFERS)
long line_number(text_heap_heap_t*txt_heap,long position)
{
  col_t*pos=new_int(position-1);
  col_t*line=aa_greatest_not_gt_data(txt_heap->cnt_nl,pos);
  long l=(long)(line?line->val:(void*)-1);
  unbound_col(pos);
  return l+2;
}
/* is flex at the end of current buffer?*/
//DOC_FUNC_DEF(pointer_at_the_end DG_FLEX_BUFFERS)
long pointer_at_the_end(text_heap_heap_t*txt_heap)
{
 long result;
 result=(txt_heap->flex_num_chars==txt_heap->array_pos);
 return result;
}
/*push string to a buffer*/
//DOC_FUNC_DEF(flex_pushstring DG_FLEX_PUSHSTRING)
void flex_pushstring(parser_master_t*p,char* str)
{
  if (*str)
    {
      col_t*x=NEW_XSTRING_CONST(str);
      flex_pushstring2(p,x);
    }
  else
    {
      flex_pushstring2null(p);
    }    
  return;
}
/*push null marker to a buffer that uses xstring*/
//DOC_FUNC_DEF(flex_pushstring2null DG_FLEX_PUSHSTRING)
void flex_pushstring2null(parser_master_t*p)
{
  col_t*null_xstr=NEW_XSTRING_CONST("   ");
  DER(val_xstring(null_xstr))=0;
  DER(val_xstring(null_xstr)+1)=0;
  DER(val_xstring(null_xstr)+2)=EOF;
  flex_pushstring2(p,null_xstr);
  return;
}
/*push xstring to a current buffer*/
//DOC_FUNC_DEF(flex_pushstring2 DG_FLEX_PUSHSTRING)
void flex_pushstring2(parser_master_t*p,col_t* xstr)
{
    {
      p->current_text_heap->array_pos+=length_xstring(xstr);
      p->current_text_heap->xstring=concat_xstring(p->current_text_heap->xstring,xstr);
    }
    return;
}
/*create new symbol*/
//DOC_FUNC_DEF(col_new_pleaf DG_COL)
col_t* col_new_pleaf(void)
{
  col_t *var_loc=(col_t*)mm2_bound_new_mem(sizeof(leaf_t));
  memset(var_loc,0,sizeof(leaf_t));
  var_loc->type=PLEAFP;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=(void*)var_loc;
  {
    //    leaf_t*var=(leaf_t*)var_loc;
  }
  return var_loc;
}
/*bison symbol value*/
//DOC_FUNC_DEF(val_lisp_pleaf DG_COL)
pleaf_t* val_lisp_pleaf(col_t*lisp_symbol)
{
  assert(lisp_symbol && lisp_symbol->type==PLEAFP);
  return (pleaf_t*)&(lisp_symbol->val);
}
