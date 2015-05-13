#ifndef _LIST_H
#define _LIST_H

#include "col.h"
//#include "goals.h"
//#include "debug2.h"

typedef struct tag1
{
  void* data;
  struct tag1*next;
  struct tag1*prev;
  void *mm_handle;
  /*list element*/
  //DOC_TYPEDEF(list_elm_t DG_CLIST)
} list_elm_t;
typedef struct 
{
   /*type of variable*/
  lisp_type_t type;
  /* value */
  void * val;
  /* mm handle of cell*/
  void* mm_handle;
  list_elm_t*first;
  list_elm_t*last;
  unsigned long nr;
#ifndef NDEBUG
  char* (*debug_print_data)(void*data);
#endif
  void (*unbound_data)(void*);
  /*list master*/
  //DOC_TYPEDEF(list_t DG_CLIST)
} list_t;

/*list walk function*/
//DOC_DEFINE(LIST_WALK)
#define LIST_WALK(list,type,var,code_block)\
{\
  list_elm_t* var##list;\
  var##list=(*(val_col_list_elm(list)))->first;\
  while(var##list)\
    {\
      type * var=(type*)(var##list->data);code_block;var##list=var##list->next;\
    }\
}
long list_size(col_t* l);
long unbound_list2(col_t*list,  void (*unbound_data)(void*));
long unbound_list(col_t*list);
void list_push_last(col_t* list,void* data);
void* list_pop_last(col_t* list);
void* list_pop(col_t* list);
void* list_destroy(col_t* list, list_elm_t *del_elm);
void list_push(col_t* list,void* data);
col_t* list_create(void (*unbound_data)(void*));
list_t** val_col_list_elm(col_t*col_symbol);
#endif
