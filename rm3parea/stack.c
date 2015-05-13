#include "stdlib.h"
#include "stdio.h"
#include "col.h"
#include "rbt.h"
#include "aa.h"
#include "mm2.h"
//#include "mm.h"
//#include "debug.h"
#include "stack.h"
//#include "goals.h"
//#include "debug2.h"
/*create stack*/
//DOC_FUNC_DEF(stack_create DG_STACK)
col_t* stack_create(void)
{
  rm2_stack_t*var=(rm2_stack_t*)mm2_bound_new_mem(sizeof(rm2_stack_t));
  var->type=STACKP;
  var->mm_handle=mm2_handle;
  var->val=NULL;
  var->nr =0;
  return (col_t*)var;
}
/*data portion of a stack element*/
//DOC_FUNC_DEF(val_col_stack_elm DG_STACK)
stack_elm_t** val_col_stack_elm(col_t*col_symbol)
{
  assert(col_symbol && col_symbol->type==STACKP );
  return (stack_elm_t**)&(col_symbol->val);
}
/*current size of stack*/
//DOC_FUNC_DEF(stack_size DG_STACK)
long stack_size(col_t* stack)
{
  rm2_stack_t*s;
  assert(stack);
  s=(rm2_stack_t*)stack;
  return s->nr;
}
/*push new top stack element*/
//DOC_FUNC_DEF(stack_push DG_STACK)
void stack_push(col_t* stack,void* data)
{
  stack_elm_t*var=(stack_elm_t*)mm2_bound_new_mem(sizeof(stack_elm_t));
  rm2_stack_t*s;
  var->mm_handle = mm2_handle;
  s=(rm2_stack_t*)stack;
  s->nr++;
  var->data=data;
  var->next=*(val_col_stack_elm(stack));
  *(val_col_stack_elm(stack))=var;
}
/*get and remove top stack element*/
//DOC_FUNC_DEF(stack_pop DG_STACK)
void* stack_pop(col_t* stack)
{
  void* result;
  stack_elm_t **elm;
  if (!stack)
    {
      assert(0);
      result = NULL;
    }
  else
    {
      elm =val_col_stack_elm(stack);
      if(*elm)
	{
	  stack_elm_t *elm2;
	  result=(*elm)->data;
	  elm2=*elm;
	  *elm=(*elm)->next;
	  ((rm2_stack_t*)stack)->nr--;
	  mm2_unbound_mem((elm2)->mm_handle);
	}
      else
	{
	  result = NULL;
	}
    } 
  return result;
}
/*value of the top stack element*/
//DOC_FUNC_DEF(stack_top_val DG_STACK)
void* stack_top_val(col_t* stack)
{
  void* result;
  stack_elm_t **elm;
  if (!stack)
    {
      assert(0);
      result = NULL;
    }
  else
    {
      elm =val_col_stack_elm(stack);
      if(*elm)
	{
	  result=(*elm)->data;
	}
      else
	{
	  result = NULL;
	}
    } 
  return result;
}
/*unbound stack of col_t* : NULLs on stack allowed!*/
//DOC_FUNC_DEF(stack_unbound DG_STACK)
long stack_unbound(col_t* stack)
{
  col_t*e;
  long result;
  assert(stack);
  result=mm2_unbound_mem(stack->mm_handle);
  if(!result)
    {
      /*!!begin critical section: uses unbounded result!!*/
      mm2_bound_new_forbidden=1;
      while((e=(col_t*)stack_pop(stack))||stack_size(stack))
	{
	  if (e)
	    col_unbound_col(e);
	}
      mm2_bound_new_forbidden=0;
      /*!!end critical section: uses unbounded result!!*/
    }
  return result;
}
#ifndef NDEBUG
#ifdef STACK_DEBUG
#define TEST_SIZE (100)
/*
gcc -g -I. -DSTACK_DEBUG aa.c mm2.c mm.c debug.c col.c rbt.c list.c stack.c misc.c inc.c lex.yy_.c x_rm1.tab.c $RM/main_stub.c
*/
static test_stack()
  {
    col_t*stack1=(col_t*)stack_create();
    long *i,j;
    for (j=0;j<TEST_SIZE;j++)
      {i=(long*)bound_new_mem(sizeof(long));*i=j;stack_push(stack1,i);}
    STACK_WALK(stack1,long,elm,{assert(*elm==--j);});
    for (j=0;j<TEST_SIZE;j++)
      { assert(*(long*)(stack_pop( stack1) )==TEST_SIZE-j-1);}
    STACK_WALK(stack1,long,elm,{j=31;});
    assert(j!=31);
  }
int main(int argc, 
	 char **argv) 
{
  mm_create();
  test_stack();
  printf("TEST OK\n");
}
#endif
#endif
