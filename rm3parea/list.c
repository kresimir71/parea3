#include "stdlib.h"
#include "stdio.h"
#include "col.h"
#include "rbt.h"
#include "aa.h"
//#include "mm.h"
#include "mm2.h"
//#include "debug.h"
#include "list.h"
//#include "goals.h"
//#include "debug2.h"

/*data portion of a list element*/
//DOC_FUNC_DEF(val_col_list_elm DG_CLIST)
list_t** val_col_list_elm(col_t*col_symbol)
{
  assert(col_symbol && col_symbol->type==CLISTP);
  return (list_t**)&(col_symbol->val);
}
/*number of elements in list*/
//DOC_FUNC_DEF(list_size DG_CLIST)
long list_size(col_t* l)
{
  assert(l);
  return (*(val_col_list_elm(l)))->nr;
}
/*create list*/
//DOC_FUNC_DEF(list_create DG_CLIST)
col_t* list_create(void (*unbound_data)(void*))
{
  col_t*col_var=(col_t*)mm2_bound_new_mem(sizeof(list_t));
  list_t*var=(list_t*)col_var;
  col_var->type=CLISTP;
  var->mm_handle=mm2_handle;
  *(val_col_list_elm(col_var))=var;
  var->unbound_data=unbound_data;
  var->nr=0;
  var->first=NULL;
  var->last=NULL;
  return col_var;
}
/*add last element*/
//DOC_FUNC_DEF(list_push_last DG_CLIST)
void list_push_last(col_t* list,void* data)
{
  list_elm_t*var=(list_elm_t*)mm2_bound_new_mem(sizeof(list_elm_t));
  var->mm_handle = mm2_handle;
  var->data=data;
  var->next = NULL;
  var->prev=(*(val_col_list_elm(list)))->last;
  if (var->prev)
    {
      var->prev->next=var;
    }
  else
    {
      (*(val_col_list_elm(list)))->first=var;
    }
  (*(val_col_list_elm(list)))->last=var;
  (*(val_col_list_elm(list)))->nr++;
}
/*add first element*/
//DOC_FUNC_DEF(list_push DG_CLIST)
void list_push(col_t* list,void* data)
{
  list_elm_t*var=(list_elm_t*)mm2_bound_new_mem(sizeof(list_elm_t));
  var->mm_handle = mm2_handle;

  var->data=data;
  var->prev = NULL;
  var->next=(*(val_col_list_elm(list)))->first;
  if (var->next)
    {
      var->next->prev=var;
    }
  else
    {
      (*(val_col_list_elm(list)))->last=var;
    }
  (*(val_col_list_elm(list)))->first=var;
  (*(val_col_list_elm(list)))->nr++;
}
/*unbound list*/
//DOC_FUNC_DEF(unbound_list DG_CLIST)
long unbound_list(col_t*list)
{
  list_elm_t* varlst;
  list_elm_t* nextvarlst;
  list_t*h=(*(val_col_list_elm(list)));
  long result;
  assert(list->type==CLISTP);
  result=mm2_unbound_mem(h->mm_handle);
  if(!result)
    {
      /*!!begin critical section: uses unbounded result!!*/
      mm2_bound_new_forbidden=1;
      varlst=h->first;
      while(varlst)
	{
	  void * var=(void*)(varlst->data);
	  nextvarlst=varlst->next;
	  if(h->unbound_data)
	    {
	      DER(h->unbound_data)(var);
	    }
	  mm2_unbound_mem(varlst->mm_handle);
	  varlst=nextvarlst;
	}
      mm2_bound_new_forbidden=0;
      /*!!end critical section: uses unbounded result!!*/
    }
  return result;
} 

/*unbound list version 2*/
//DOC_FUNC_DEF(unbound_list2 DG_CLIST)
long unbound_list2(col_t*list,  void (*unbound_data)(void*))
{
  list_elm_t* varlst;
  list_elm_t* nextvarlst;
  list_t*h=(*(val_col_list_elm(list)));
  long result;
  assert(list->type==CLISTP);
  result=mm2_unbound_mem(h->mm_handle);
  if(!result)
    {
      /*!!begin critical section: uses unbounded result!!*/
      mm2_bound_new_forbidden=1;
      varlst=h->first;
      while(varlst)
	{
	  void * var=(void*)(varlst->data);
	  nextvarlst=varlst->next;
	  if (unbound_data)
	    DER(unbound_data)(var);
	  mm2_unbound_mem(varlst->mm_handle);
	  varlst=nextvarlst;
	}
      mm2_bound_new_forbidden=0;
      /*!!end critical section: uses unbounded result!!*/
    }
  return result;
}
/*unbound list element-return data-data is never unbound*/
//DOC_FUNC_DEF(list_destroy DG_CLIST)
void* list_destroy(col_t* list, list_elm_t *del_elm)
{
  void* result;
  list_t **elm;
  elm =val_col_list_elm(list);
  assert((*elm)->nr!=0);
  assert(del_elm);
  (*elm)->nr--;
  if((*elm)->first == del_elm)
    {
      (*elm)->first=del_elm->next;
    }
  if((*elm)->last == del_elm)
    {
      (*elm)->last=del_elm->prev;
    }
  if(del_elm->prev) del_elm->prev->next=del_elm->next;
  if(del_elm->next) del_elm->next->prev=del_elm->prev;
  result=del_elm->data;
  mm2_unbound_mem(del_elm->mm_handle);
  return result;
}
/*get first element:data is never unbound*/
//DOC_FUNC_DEF(list_pop DG_CLIST)
void* list_pop(col_t* list)
{
  void* result;
  list_t **elm;
  if (!list)
    {
      result = NULL;
    }
  else
    {
      elm =val_col_list_elm(list);
      if(*elm && (*elm)->nr)
	{
	  list_elm_t *elm2=(*elm)->first;
	  assert(!elm2->next || elm2->next->prev==elm2);
	  assert(!elm2->prev);
	  result=elm2->data;
	  assert((*elm)->first);
	  if ((*elm)->first->next) (*elm)->first->next->prev=NULL;
	  (*elm)->first=(*elm)->first->next;
	  (*elm)->nr--;
	  if(!(*elm)->nr) (*elm)->last=NULL;
	  mm2_unbound_mem(elm2->mm_handle);
	}
      else
	{
	  result = NULL;
	}
    } 
  return result;
}
/*get last element:data is never unbound*/
//DOC_FUNC_DEF(list_pop_last DG_CLIST)
void* list_pop_last(col_t* list)
{
  void* result;
  list_t **elm;
  if (!list)
    {
      result = NULL;
    }
  else
    {
      elm =val_col_list_elm(list);
      if(*elm && (*elm)->nr)
	{
	  list_elm_t *elm2=(*elm)->last;
	  result=elm2->data;
	  list_destroy(list,elm2);
	}
      else
	{
	  result = NULL;
	}
    } 
  return result;
}

#ifndef NDEBUG
#ifdef LIST_DEBUG
#define TEST_SIZE (2*50)
/*
gcc -g -I. -DLIST_DEBUG aa.c mm2.c mm.c debug.c col.c rbt.c list.c stack.c misc.c inc.c lex.yy_.c x_rm1.tab.c $RM/main_stub.c
*/

static test_list()
{
  list_elm_t* elmts[TEST_SIZE];
  col_t* list1=list_create(unbound_mem);
  long *i,j;
  for (j=0;j<TEST_SIZE;j++)
    {i=(long*)bound_new_mem(sizeof(long));*i=j;list_push(list1,i);}
  LIST_WALK(list1,long,elm,{assert(*elm==--j);});
  for (j=0;j<TEST_SIZE;j++)
    { assert(*(long*)(list_pop( list1 ) )==TEST_SIZE-j-1);}
  LIST_WALK(list1,long,elm,{j=31;});
  assert(j!=31);
  for (j=0;j<TEST_SIZE;j++)
    {i=(long*)bound_new_mem(sizeof(long));*i=j;list_push(list1,i);}
  j=0;
  LIST_WALK(list1,long,elm,{elmts[j++]=elmlist1;});
  for (j=0;j<TEST_SIZE/2;j++)
    {list_destroy(list1,elmts[2*j]);}
  LIST_WALK(list1,long,elm,{assert(*elm==2*--j);});
  //((list_t*)(list1->val))->unbound_data =NULL;
  assert(j==0);
  while(i=(long*)list_pop_last(list1)){printf("%d\n",*i);assert(*i==2*j++)}
  assert(j==TEST_SIZE/2);
}
long main(long argc, 
	 char **argv) 
{
  mm_create();
  test_list();
  printf("TEST OK\n");
}
#endif
#endif
