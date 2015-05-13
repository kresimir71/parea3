//#include "goals.h"
#include "stdlib.h"
#include "string.h"
//#include "mm.h"
#include "mm2.h"
#include "stdio.h"
#include "rbt.h"
#include "aa.h"
//#include "debug.h"
#include "col.h"
#include "stack.h"
#include "list.h"
//#include "goals.h"
//#include "debug2.h"
#include "assert.h"

/*bound storage*/
//DOC_FUNC_DEF(bound_new_col_symbol DG_COL)
void bound_new_col_symbol(col_t** var,col_type_t col_type,void* val)
{
  col_t *var_loc= (col_t*)mm2_bound_new_mem(sizeof(col_t));
  var_loc->type=col_type;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=val;
  *var=var_loc;
}
/*bound storage*/
//DOC_FUNC_DEF(new_col_symbol DG_COL)
col_t* new_col_symbol(col_type_t col_type)
{
  col_t *var_loc= (col_t*)mm2_bound_new_mem(sizeof(col_t));
  var_loc->type=col_type;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=NULL;
  return var_loc;
}
/*string value*/
//DOC_FUNC_DEF(val_xstring_or_string DG_COL)
char* val_xstring_or_string(col_t* s)
{
  char* str;
  assert(s->type==XSTRINGP||s->type==STRINGP);
  str =(s->type==STRINGP?(char*)(s->val):val_xstring(s));
  return str;
}

/*string value of xstring*/
//DOC_FUNC_DEF(col_val_xstring DG_SET)
char* (*col_val_xstring)(col_t* s)=val_xstring;

/*string value of xstring*/
//DOC_FUNC_DEF(val_xstring DG_SET)
char* val_xstring(col_t* s)
{
  char* result;
  assert(s);
  assert(XSTRINGP==s->type);
  result=(char*)s+COL_STRUCT_SIZEOF(col_t);
  return result;
}
/*length of xstring*/
//DOC_FUNC_DEF(col_length_xstring DG_SET)
long (*col_length_xstring)(col_t* s)=length_xstring;

/*length of xstring*/
//DOC_FUNC_DEF(length_xstring DG_SET)
long length_xstring(col_t* s)
{
  long result;
  assert(XSTRINGP==s->type);
  result=(long)(s->val);
  return result;
}
/*make a physical copy of xstring*/
//DOC_FUNC_DEF(duplicate_xstring DG_SET)
col_t* duplicate_xstring(col_t* xs)
{
  return col_new_xstring(length_xstring(xs),val_xstring(xs),XSTRING_STRCPY);
}
/*empty set (all bits zero)*/
//DOC_FUNC_DEF(set0_xstring DG_SET)
col_t* set0_xstring(col_t*s)
{
  assert(s->type==XSTRINGP);
  memset(val_xstring(s),0,length_xstring(s));
  return s;
}
/*check if element (if the corresponding bit is set)*/
//DOC_FUNC_DEF(is_elm_xstring DG_SET)
long is_elm_xstring(col_t*s,long elm)
{
  assert(s->type==XSTRINGP);
  return DER(val_xstring(s)+elm/8)&(1<<(elm%8));
}
/*add an element (set the corresponding bit)*/
//DOC_FUNC_DEF(add_elm_xstring DG_SET)
void add_elm_xstring(col_t*s,long elm)
{
  assert(s->type==XSTRINGP);
  DER(val_xstring(s)+elm/8)|=(1<<(elm%8));
}
/*remove an element (zero the corresponding bit)*/
//DOC_FUNC_DEF(del_elm_xstring DG_SET)
void del_elm_xstring(col_t*s,long elm)
{
  assert(s->type==XSTRINGP);
  DER(val_xstring(s)+elm/8)&=~(1<<(elm%8));
}
/*generate new xstring*/
//DOC_FUNC_DEF(new_xstring DG_XSTRING)
col_t* new_xstring(long length, char* init)
{
  return col_new_xstring(length,init,XSTRING_STRCPY);
}
/*unbound xstring*/
//DOC_FUNC_DEF(unbound_xstring DG_XSTRING)
void unbound_xstring(col_t*str)
{
  assert(XSTRINGP==str->type);
  col_unbound_xstring(str);
}
/*unbound storage*/
//DOC_FUNC_DEF(unbound_col DG_COL)
void unbound_col(col_t*s)
{
  assert(STRINGP==s->type || XSTRINGP==s->type || INTP==s->type);
  if(XSTRINGP==s->type)
    {
      col_unbound_xstring(s);
    }
  else if(INTP==s->type)
    {
      unbound_mem_from_handle(s->mm_handle);
    }
  else if(STRINGP==s->type)
    {
      unbound_mem_from_handle(s->mm_handle);
    }
}

#define EXCHANGE(a,b,temp)\
temp=a;\
a=b;\
b=temp;

#define MAX(a,b)\
(a<b?b:a)

/*convert to xstring*/
//DOC_FUNC_DEF(print_col_to_xstring DG_XSTRING)
col_t* print_col_to_xstring(col_t* c)
{
  col_t*result;
  if (c && (c->val || INTP==c->type))
    {
      if (XSTRINGP==c->type)
	{
	  result=duplicate_xstring(c);
	}
      else if(STRINGP==c->type)
	{
	  result=NEW_XSTRING_CONST(val_xstring_or_string(c));
	}
      else if(INTP==c->type)
	{
	  char number[100];
	  sprintf(number,"%d",(long)(c->val));
	  result=NEW_XSTRING_CONST(number);
	}
      else 
	{
	  result=NEW_XSTRING_CONST("#");
	}
    }
  else
    {
      result=NEW_XSTRING_CONST("(NULL)");
    }
  return result;
}

/*concatinate xstrings*/
//DOC_FUNC_DEF(concat_xstring DG_XSTRING)
col_t * concat_xstring(col_t *str1,col_t *str2)
{
  return col_concat_xstring(str1,str2);
}
/*take substring of xstring*/
//DOC_FUNC_DEF(xstring_substring DG_XSTRING)
col_t* xstring_substring(col_t* str,long p1, long p2,xstring_substring_flags_t flag)
{
  /*sub("0123",0,0)=="0";sub("0123",0,-1)=="0123";sub("0123",0,3)=="0123";sub("0123",-1,-1)=="3";*/
  return col_xstring_substring(str,p1,(p2==-1?0:1),p2+1,flag);
}
//#if ! defined APPL_MAIN_APPLICATION_IDENTIFIER_CPP2
/*concatinate strings*/
//DOC_FUNC_DEF(concat_unbound DG_COL)
char * concat_unbound(char *str1,long length1, char *str2, long length2)
{
  COL_BOUND_MEM_NO_HANDLE_SIZE(str_res,char,length1+length2+2);//2used!!
  memcpy(str_res,str1,length1);
  memcpy(str_res+length1,str2,length2);
  *(str_res+length1+length2) = 0;
  /*used only in debug:not unbound*/
  //  unbound_mem(str1);
  //unbound_mem(str2);
  return str_res;
}
/*concatinate strings*/
//DOC_FUNC_DEF(concat_free DG_COL)
char * concat_free(char *str1,long length1, char *str2, long length2)
{
  //  DEBUG_BOUND_MEM_NO_HANDLE_SIZE(str_res,char*,length1+length2+1);
  char* str_res = (char*)malloc(length1+length2+1);
  memcpy(str_res,str1,length1);
  memcpy(str_res+length1,str2,length2);
  *(str_res+length1+length2) = 0;
  free(str1);
  free(str2);
  return str_res;
}
/*concatinate strings*/
char * concat(char*c, char*d)
{
  char *e;
  long l1,l2;
  long l;
  assert(c&&d);
  l= (l1=strlen(c))+(l2=strlen(d));
  STORAGE(e,(char*),(l+1));
  memcpy(e,c,l1);memcpy(e+l1,d,l2+1);
  return e;
}

/*string downcase*/
//DOC_FUNC_DEF(downcase DG_COL)
char * downcase(char*c)
{
  char *d =c;
  for(;*c;c++)
    {
      if (*c>='A' && *c<='Z') *c= 'a'+*c-'A';
    }
  return d;
}
/*string uppercase*/
//DOC_FUNC_DEF(upper DG_COL)
char * upper(char*c)
{
  char *d =c;
  for(;*c;c++)
    {
      if (*c>='a' && *c<='z') *c= 'A'+*c-'a';
    }
  return d;
}

/*duplicate storage*/
//DOC_FUNC_DEF(copy_lisp_symbol DG_COL)
col_t* copy_lisp_symbol(col_t*lisp_symbol)
{
  col_t* lisp_symbol2;
  assert(!lisp_symbol);
  STORAGE_LISP_VAR(lisp_symbol2,INTP,0);
  lisp_symbol2->val = lisp_symbol->val;
  lisp_symbol2->type = lisp_symbol->type;
  return lisp_symbol2;
}
//#endif
/*string value*/
//DOC_FUNC_DEF(val_lisp_string DG_COL)
char* val_lisp_string(col_t*lisp_symbol)
{
  assert(lisp_symbol && lisp_symbol->type==STRINGP);
  return (char *)(lisp_symbol->val);
}
/*int value*/
//DOC_FUNC_DEF(val_lisp_int DG_COL)
long* val_lisp_int(col_t*lisp_symbol)
{
  assert(lisp_symbol && lisp_symbol->type==INTP);
  return (long *)&(lisp_symbol->val);
}
//#ifndef NDEBUG
/*create string*/
//DOC_FUNC_DEF(lisp_string DG_COL)
col_t* lisp_string(char *str)
{
  col_t* lisp_symbol;
  char* new_str;
  STORAGE(new_str,(char*),(strlen(str)+1));
  strcpy(new_str,str);
  STORAGE_LISP_VAR(lisp_symbol,STRINGP,new_str);
  return lisp_symbol;
}
/*substring function*/
//DOC_FUNC_DEF(substring DG_COL)
char* substring(char* str,long p1, long p2)
{
  long q1,q2;  
  char* new_str;
  char*old_str;
  if(!(old_str=str))
    {
      STORAGE(new_str,(char*),(1));
      *new_str = 0;
    }
  else
    {
      long l = strlen(old_str);
      long d;
      q1 = (p1<0 ? l+p1:p1);
      q2 = (p2<0 ? l+p2-1:p2);
      q1 = (q1<0 ? 0:q1);
      q2 = (q2<0 ? 0:q2);
      q1 = (q1>l-1 ? l-1:q1);
      q2 = (q2>l-1 ? l-1:q2);
      d = (q2>=q1?q2-q1+1:1);
      STORAGE(new_str,(char*),d+1);
      memcpy(new_str,old_str+q1,d);
      *(new_str+d+(q2<q1?-1:0)) = 0;
    }
  return new_str;
}
/*substring function*/
//DOC_FUNC_DEF(lisp_substring DG_COL)
col_t* lisp_substring(col_t* str,long p1, long p2)
{
  long q1,q2;  
  col_t* lisp_symbol;
  char* new_str;
  char*old_str;
  assert(str && str->type==STRINGP);
  if(!(old_str=val_lisp_string(str)))
    {
      q1=q2=0;
      STORAGE(new_str,(char*),(1));
      STORAGE_LISP_VAR(lisp_symbol,STRINGP,new_str);
      *new_str = 0;
    }
  else
    {
      long l = strlen(old_str);
      long d;
      q1 = (p1<0 ? l+p1:p1);
      q2 = (p2<0 ? l+p2-1:p2);
      q1 = (q1<0 ? 0:q1);
      q2 = (q2<0 ? 0:q2);
      q1 = (q1>l-1 ? l-1:q1);
      q2 = (q2>l-1 ? l-1:q2);
      d = (q2>=q1?q2-q1+1:1);
      STORAGE(new_str,(char*),d+1);
      memcpy(new_str,old_str+q1,d);
      *(new_str+d+(q2<q1?-1:0)) = 0;
      STORAGE_LISP_VAR(lisp_symbol,STRINGP,new_str);
    }
  return lisp_symbol;
}
/*list function*/
//DOC_FUNC_DEF(lisp_list DG_COL)
col_t* lisp_list(lisp_cons_cell_t* cell)
{
  col_t* lisp_symbol;
  STORAGE_LISP_VAR(lisp_symbol,LISTP,cell);
  return lisp_symbol;
}

/*integer function*/
//DOC_FUNC_DEF(lisp_long DG_COL)
col_t* lisp_int(long i)
{
  col_t* lisp_symbol;
  STORAGE_LISP_VAR(lisp_symbol,INTP,i);
  return lisp_symbol;
}
//#endif
/*create new integer*/
//DOC_FUNC_DEF(new_long DG_COL)
col_t* new_int(long init)
{
  col_t *var_loc= (col_t*)mm2_bound_new_mem(sizeof(col_t));
  var_loc->type=INTP;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=(void*) init;
  return var_loc;
}
/*value of integer*/
//DOC_FUNC_DEF(val_int DG_COL)
long* val_int(col_t* s)
{
  return (long*)&(s->val);
}
/*nth function for list*/
//DOC_FUNC_DEF(col_nth DG_COL)
col_t* col_nth(col_t* l, long n)
{
  long i;
  lisp_cons_cell_t*c;
  assert(l && l->type==LISTP);
  c=(lisp_cons_cell_t*)(l->val);
  assert(n>=0);
  for (i=0;i<n;i++)
    {
      assert(c&&c->cdr);
      c=c->cdr;
    }
  return c->car;
}
/*nth function for list, version2*/
//DOC_FUNC_DEF(col_nth2 DG_COL)
col_t* col_nth2(lisp_cons_cell_t* c, long n)
{
  long i;
  assert(n>=0);
  for (i=0;i<n;i++)
    {
      assert(c&&c->cdr);
      c=c->cdr;
    }
  return c->car;
}

// functions that use mm2
/*bound storage*/
//DOC_FUNC_DEF(col_bound_col DG_COL)
col_t* col_bound_col(col_t* c)
{
  mm2_bound_mem(c->mm_handle);
  return c;
}
/*bound storage*/
//DOC_FUNC_DEF(col_new_col_symbol DG_COL)
col_t* col_new_col_symbol(col_type_t col_type)
{
  col_t *var_loc= (col_t*)mm2_bound_new_mem(sizeof(col_t));
  var_loc->type=col_type;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=NULL;
  return var_loc;
}
/*create new cons cell*/
//DOC_FUNC_DEF(col_new_cons DG_COL)
col_t* col_new_cons(col_t* car, void* cdr)
{
  lisp_cons_cell_t *var_cons=(lisp_cons_cell_t*)mm2_bound_new_mem(sizeof(lisp_cons_cell_t));
  col_t *var_loc=(col_t*)var_cons;
  var_loc->type=CONSP;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=(void*)car;
  var_cons->cdr=(lisp_cons_cell_t*)cdr;
#ifndef NDEBUG
  var_cons->comment=NULL;
#endif
  return var_loc;
}
/*duplicate xstring*/
//DOC_FUNC_DEF(col_duplicate_xstring DG_SET)
col_t* col_duplicate_xstring(col_t* xs, col_duplicate_flags_t flag)
{
  col_t* result;
  assert(XSTRINGP==xs->type);
  assert(XSTRING_STRCPY==flag || XSTRING_MEMCPY==flag);
  result = col_new_xstring(length_xstring(xs),val_xstring(xs),flag);
  return result;
}
/*create new file*/
//DOC_FUNC_DEF(col_new_file DG_COL)
col_t* col_new_file(void)
{
  col_t *var_loc=(col_t*)mm2_bound_new_mem(sizeof(text_heap_heap_t));
  memset(var_loc,0,sizeof(text_heap_heap_t));
  var_loc->type=FILEP;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=NULL;
  {
    text_heap_heap_t*var=(text_heap_heap_t*)var_loc;
    var->cnt_nl=NULL;
    var->add_info=NULL;
    var->ps01_parser=NULL;
  }
  return var_loc;
}
/*generate new xstring*/
//DOC_FUNC_DEF(col_new_xstring DG_XSTRING)
col_t* col_new_xstring(long length, char* init,col_duplicate_flags_t flag)
{
  long xstroffset = COL_STRUCT_SIZEOF(col_t);
  col_t *var_loc= (col_t*)mm2_bound_new_mem(xstroffset+length+1);
  char* value_val;
  assert(!init || XSTRING_STRCPY==flag || XSTRING_MEMCPY==flag);
  var_loc->type=XSTRINGP;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=(void*)length;
  value_val=(char*)var_loc+xstroffset;
  *(value_val)=0;
  if(init)
    {
      if(XSTRING_STRCPY==flag)
	{
	  //reserved space is length, declared len is  min(strlen(init),length)
	  long i=0;
	  while(*(init+i )&&i<length)
	    {
	      *(value_val+i)=*(init+i);
	      i++;
	    }
	  *(value_val+i)=0;
	  var_loc->val=(void*)i;
	  //	strncpy(value_val,init,length);
	}
      else
	{
	  memcpy(value_val,init,(long)(var_loc->val));
	  *(value_val+(long)(var_loc->val))=0;
	}
    }
  return var_loc;
}

/*generate new xstring, with zero in init possible*/
//DOC_FUNC_DEF(col_new_xstring2 DG_XSTRING)
col_t* col_new_xstring2(long length, char* init, long copy_length)
{
  col_t* x=col_new_xstring(length,"",XSTRING_STRCPY);
  assert(length>=copy_length);
  memcpy(val_xstring(x),init,copy_length);
  DER(val_xstring(x)+copy_length)=0;
  x->val = (void*)copy_length;
  return x;
}
/*insert xstring*/
//DOC_FUNC_DEF(col_xstring_insert DG_XSTRING)
col_t* (*col_xstring_insert)(col_t*x,col_t*to_insert,long pos)=col_insert;

/*insert xstring*/
//DOC_FUNC_DEF(col_insert DG_XSTRING)
col_t* col_insert(col_t*x,col_t*to_insert,long pos)
{
  col_t*part1;col_t*part2;col_t*part3;
  if (pos<0) pos=0;
  part3=col_xstring_substring(x,pos,0,0,XSTRING_BOUNDNEW);
  part2=to_insert;
  part1=col_xstring_substring(x,0,1,pos,XSTRING_REUSE);
  x=col_concat_xstring(col_concat_xstring(part1,part2),part3);
  return x;
}
/*cut xstring*/
//DOC_FUNC_DEF(col_cut_xstring DG_XSTRING)
col_t* col_cut_xstring(col_t*x,long pos1,long pos2)
{
  //(the optimal method is to shift part3)
  col_t*part3=col_xstring_substring(x,pos2,0,0,XSTRING_BOUNDNEW);
  col_t*part1=col_xstring_substring(x,0,1,pos1,XSTRING_REUSE);
  assert(pos2>=pos1);
  x=col_concat_xstring(part1,part3);
  return x;
}
/*generate new xstring*/
//DOC_FUNC_DEF(col_space DG_XSTRING)
col_t* col_space(long length)
{
  col_t* x;
  if (length<0) length=0;
  x=col_new_xstring(length,"",XSTRING_STRCPY);
  memset(val_xstring(x),' ',length);
  DER(val_xstring(x)+length)=0;
  x->val = (void*)length;
  return x;
}
/*generate new xstring*/
//DOC_FUNC_DEF(col_xstring_space DG_XSTRING)
col_t* (*col_xstring_space)(long )=col_space;

/*unbound xstring*/
//DOC_FUNC_DEF(col_unbound_xstring DG_XSTRING)
long col_unbound_xstring(col_t*str)
{
  assert(XSTRINGP==str->type);
  return mm2_unbound_mem(str->mm_handle);
}
/*unbound storage*/
//DOC_FUNC_DEF(col_unbound_col DG_COL)
long col_unbound_col(void*t)
{
  col_t*s=(col_t*)t;
  long result=0;
  assert(PARSERP==s->type||AAP==s->type || LISTP==s->type || STRINGP==s->type || CLISTP==s->type || XSTRINGP==s->type || INTP==s->type || CONSP==s->type|| PLEAFP==s->type||FILEP==s->type||STACKP==s->type||COL_NEXT_FREE_TYPE_SLOT<=s->type);
  if(XSTRINGP==s->type)
    {
      result=col_unbound_xstring(s);
    }
  else if(FILEP==s->type)
    {
      text_heap_heap_t*t=(text_heap_heap_t*)s;
      if (!(result=mm2_unbound_mem(s->mm_handle)))
	{
	  /*!!begin critical section: uses unbounded result!!*/
	  mm2_bound_new_forbidden=1;
	  if (t->xstring) col_unbound_col(t->xstring);
	  if (t->misc_ahead_xstring) col_unbound_col(t->misc_ahead_xstring);
	  if (t->file_name) col_unbound_col(t->file_name);
	  if (t->cnt_nl) col_unbound_col(t->cnt_nl);
	  if (t->file_ptr && t->file_ptr!=stdin) fclose(t->file_ptr);
	  if (t->add_info) col_unbound_col(t->add_info);
	  mm2_bound_new_forbidden=0;
	  /*!!end critical section: uses unbounded result!!*/
	}
    }
  else if(PARSERP==s->type)
    {
      parser_master_t*t=(parser_master_t*)s;
      t=t;
      if (!(result=mm2_unbound_mem(s->mm_handle)))
	{
	  /*!!begin critical section: uses unbounded result!!*/
	  mm2_bound_new_forbidden=1;
	  if(t->connecting_nonterminal) col_unbound_col(t->connecting_nonterminal);

/* 	  if (t->xstring) col_unbound_col(t->xstring); */
/* 	  if (t->misc_ahead_xstring) col_unbound_col(t->misc_ahead_xstring); */
/* 	  if (t->file_name) col_unbound_col(t->file_name); */
/* 	  if (t->cnt_nl) col_unbound_col(t->cnt_nl); */
/* 	  if (t->file_ptr && t->file_ptr!=stdin) fclose(t->file_ptr); */
/* 	  if (t->add_info) col_unbound_col(t->add_info); */
	  mm2_bound_new_forbidden=0;
	  /*!!end critical section: uses unbounded result!!*/
	}
    }
  else if(LISTP==s->type)
    {
      if (!(result=mm2_unbound_mem(s->mm_handle)))
	{
	  /*!!begin critical section: uses unbounded result!!*/
	  mm2_bound_new_forbidden=1;
	  if (s->val) col_unbound_col(s->val);
	  mm2_bound_new_forbidden=0;
	  /*!!end critical section: uses unbounded result!!*/
	}
    }
  else if(CONSP==s->type)
    {
      lisp_cons_cell_t*t=(lisp_cons_cell_t*)s;
      if (!(result=mm2_unbound_mem(s->mm_handle)))
	{
	  /*!!begin critical section: uses unbounded result!!*/
	  mm2_bound_new_forbidden=1;
	  if (t->car) col_unbound_col(t->car);
	  if (t->cdr) col_unbound_col(t->cdr);
	  mm2_bound_new_forbidden=0;
	  /*!!end critical section: uses unbounded result!!*/
	}
    }
   else if(PLEAFP==s->type)
     {
       pleaf_t t=(pleaf_t)s;
       if (!(result=mm2_unbound_mem(s->mm_handle)))
 	{
 	  /*!!begin critical section: uses unbounded result!!*/
 	  mm2_bound_new_forbidden=1;
 	  if ((t->tag&COL_TEXT_HEAP_BOUNDED) &&t->text_heap_heap) 
	    {
	      long res = col_unbound_col(t->text_heap_heap);
	      if (res==1)
		col_unbound_col(t->text_heap_heap);
	    }
 	  if (t->user_attributes) col_unbound_col(t->user_attributes);t->user_attributes=NULL;
 	  mm2_bound_new_forbidden=0;
 	  /*!!end critical section: uses unbounded result!!*/
 	}
     }
  else if(INTP==s->type)
    {
      result=mm2_unbound_mem(s->mm_handle);
    }
  else if(STRINGP==s->type)
    {
      result=mm2_unbound_mem(s->mm_handle);
    }
  else if(STACKP==s->type)
    {
      result=stack_unbound(s);
    }
  else if(CLISTP==s->type)
    {
      result=unbound_list2(s,(col_data_function_t)col_unbound_col);
    }
  else if(AAP==s->type)
    {
      result=aa_unbound_col(s);
    }
  else if(COL_NEXT_FREE_TYPE_SLOT<=s->type)
    {
      result=col_extended_type_unbound(s);
    }
  return result;
}
/*convert to xstring*/
//DOC_FUNC_DEF(col_print_col_to_xstring DG_XSTRING)
col_t* col_print_col_to_xstring(col_t* c)
{
  col_t*result;
  if (c && (c->val || INTP==c->type || XSTRINGP==c->type))
    {
      if (XSTRINGP==c->type)
	{
	  result=col_duplicate_xstring(c,XSTRING_MEMCPY);
	}
      else if(STRINGP==c->type)
	{
	  result=COL_NEW_XSTRING_CONST(val_xstring_or_string(c));
	}
      else if(INTP==c->type)
	{
	  char number[100];
	  sprintf(number,"%d",(long)(c->val));
	  result=COL_NEW_XSTRING_CONST(number);
	}
      else 
	{
	  result=COL_NEW_XSTRING_CONST("#");
	}
    }
  else
    {
      result=COL_NEW_XSTRING_CONST("(NULL)");
    }
  assert(XSTRINGP==result->type);
  return result;
}

/*concatinate xstrings, doesn't handle zero chars:uses prescribed lengths, unbounds one arg*/
//DOC_FUNC_DEF(col_concat_xstring DG_XSTRING)
col_t * col_concat_xstring(col_t *str1,col_t *str2)
{
  char* s1_val;
  char* s2_val;
  col_t* str3;
  long exchanged =0;
  long req_length=((long)(str1->val))+ ((long)(str2->val));
  long avail_length = (1<<MAX(MM2_LOG_SIZE(str1),MM2_LOG_SIZE(str2)) )-COL_STRUCT_SIZEOF(col_t);
  assert(avail_length>0);
  if (avail_length>req_length && (MM2_SIZE(str1) - COL_STRUCT_SIZEOF(col_t)<req_length+1 ))
    {
      EXCHANGE(str1,str2,str3);
      exchanged++;
    }
  s1_val=(char*)str1+COL_STRUCT_SIZEOF(col_t);
  s2_val=(char*)str2+COL_STRUCT_SIZEOF(col_t);
  if (avail_length<=req_length)
    {
      assert(!exchanged);
      str3 = col_new_xstring2(req_length,s1_val,((long)(str1->val)));
      col_unbound_xstring(str1);
      str1=str3;
      s1_val=(char*)str1+COL_STRUCT_SIZEOF(col_t);
    }
  if (!exchanged)
    {
      memcpy(s1_val+((long)(str1->val)),s2_val,((long)(str2->val))+1);
    }
  else
    {
      memmove(s1_val+((long)(str2->val)),s1_val,((long)(str1->val))+1);
      memcpy(s1_val,s2_val,((long)(str2->val)));
    }
  str1->val+=(long)(str2->val);
  col_unbound_xstring(str2);
  return str1;
}
/*take substring of xstring*/
//DOC_FUNC_DEF(col_xstring_substring DG_XSTRING)
col_t* col_xstring_substring(col_t* str,long p1, long p2_used, long p2,xstring_substring_flags_t flag)
{
  /*as lisp substring*/
  /*sub("0123",0,1,0)=="";sub("0123",0,1,-1)=="012";sub("0123",0,1,3)=="012";sub("0123",-1,1,-1)=="";*/
  /*sub("0123",0,0,0)=="0123";sub("0123",0,0,-1)=="0123";sub("0123",0,0,3)=="0123";sub("0123",-1,0,-1)=="3";*/
  long q1,q2;  
  char* new_str=NULL;
  col_t* new_xstr=NULL;
  char*old_str=val_xstring(str);
  long l,d;
  assert(str && str->type==XSTRINGP);
  assert(!(flag&XSTRING_REUSE) || !(flag&(XSTRING_UNBOUNDOLD|XSTRING_BOUNDNEW)));
  l = length_xstring(str);
  q1 = (p1<0 ? l+p1:p1);
  q1 = (q1<0 ? 0:q1);
  if (!p2_used)
    {
      q2=l;
    }
  else
    {
      q2 = (p2<0 ? l+p2:p2);
      q2 = (q2>l-1 ? l:q2);
    }
  d = (q2>q1?q2-q1:0);
  if(XSTRING_REUSE&flag)
    {
      new_xstr=str;
    }
  if(XSTRING_BOUNDNEW&flag)
    {
      new_xstr=col_new_xstring(d,NULL,0);
    }
  new_str=val_xstring(new_xstr);
  if (new_str!=old_str+q1) memmove(new_str,old_str+q1,d);
  if(XSTRING_UNBOUNDOLD&flag)
    {
      col_unbound_xstring(str);
    }
  *(new_str+d) = 0;
  new_xstr->val = (void*)d;
  return new_xstr;
}
/*new col function*/
//DOC_FUNC_DEF(col_new_col DG_COL)
col_t* col_new_col(lisp_type_t t,void* init)
{
  col_t *var_loc;
  var_loc= (col_t*)mm2_bound_new_mem(sizeof(col_t));
  var_loc->type=INTP;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=(void*) init;
  return var_loc;
}
/*new col extended function*/
//DOC_FUNC_DEF(col_bound_new_extended DG_COL)
col_t* col_bound_new_extended(long size,long type,void* init)
{
  col_t *var_loc;
  var_loc= (col_t*)mm2_bound_new_mem(size);
  var_loc->type=type;
  var_loc->mm_handle = mm2_handle;
  var_loc->val=(void*) init;
  return var_loc;
}
