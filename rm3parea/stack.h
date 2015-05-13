#ifndef _STACK_H
#define _STACK_H
//#include "goals.h"
//#include "debug2.h"

typedef struct 
{
   /*type of variable*/
  lisp_type_t type;
  /* value:first element */
  void * val;
  /* mm handle of cell*/
  void* mm_handle;
  /*number of elements*/
  unsigned long nr;
  /*stack master*/
  //DOC_TYPEDEF(rm2_stack_t DG_STACK)
} rm2_stack_t;

typedef struct tag2
{
  void* data;
  struct tag2*next;
  void *mm_handle;
  /*stack element*/
  //DOC_TYPEDEF(stack_elm_t DG_STACK)
} stack_elm_t;

long stack_unbound(col_t* stack);
long stack_size(col_t* stack);
col_t* stack_create(void);
void* stack_top_val(col_t* stack);
void stack_push(col_t* stack,void* data);
void* stack_pop(col_t* stack);
stack_elm_t** val_col_stack_elm(col_t*col_symbol);
/*stack walk function*/
//DOC_DEFINE(STACK_WALK)
#define STACK_WALK(stack,type,var,code_block)\
{\
  stack_elm_t* var##stack;\
  var##stack=*(val_col_stack_elm(stack));\
  while(var##stack)\
    {\
      type * var=(type*)(var##stack->data);code_block;var##stack=var##stack->next;\
    }\
}

#endif
