/*-----------------begin*/
/*rbt.h*/
#ifndef _RBT_H
#define _RBT_H
//#ifndef SI2
#include "col.h"
//#endif
//#include "goals.h"
//#include "debug2.h"

/*insert new record, forget (don't deallocate) the old one*/
//DOC_DEFINE(INSERT_NEW_DATA_IF_EXISTS DG_RBT)
#define INSERT_NEW_DATA_IF_EXISTS 1
/*free (that is deallocate) the old record*/
//DOC_DEFINE(FREE_OLD_DATA_IF_EXISTS DG_RBT)
#define FREE_OLD_DATA_IF_EXISTS 2
/*return NULL if record with this key already exists*/
//DOC_DEFINE(RETURN_NULL_IF_EXISTS DG_RBT)
#define RETURN_NULL_IF_EXISTS 4 
/*handling flags for RBT*/
//DOC_TYPEDEF(rbt_flags_t DG_RBT)
typedef long rbt_flags_t;

typedef enum 
{ 
  RM2_RBT_COLOR_BLACK, 
  RM2_RBT_COLOR_RED 
  /*color struct*/
  //DOC_TYPEDEF(rm2_rbt_color_t DG_RBT)
} rm2_rbt_color_t;
typedef struct rm2_rbt_node_tag_t 
{
  rm2_rbt_color_t c;            
  struct rm2_rbt_node_tag_t *l;         
  struct rm2_rbt_node_tag_t *r;        
  void* data;                 
  struct rm2_rbt_node_tag_t *p;       
  void* mm_handle;
  /*node struct*/
  //DOC_TYPEDEF(rm2_rbt_node_t DG_RBT)
} rm2_rbt_node_t;
void* rbt_data(rm2_rbt_node_t*t);
void* rbt_begin(void*rbtreeptr,void*data);
void* rbt_next(void*rbtreeptr,void*current);
void process_tree_in_order(void *rbtreeptr, rm2_rbt_node_t *this, void(*process_data)(void*));
#ifndef SI2
#ifndef NDEBUG
col_t* dump_tree_to_xstring(void *rbtreeptr, rm2_rbt_node_t *this, col_t*(*data_to_xstring)(void*));
char* dump_tree_inorder_to_string(void *rbtreeptr, rm2_rbt_node_t *this, char*(*data_to_string)(void*));
char* dump_mm_tree_inorder_to_string(void *rbtreeptr, rm2_rbt_node_t *this, char*(*data_to_string)(void*));
#endif
#endif
void unbound_rbt(void *rbtreeptr, rm2_rbt_node_t *this_node, void(*unbound_data)(void*));
extern void * findKey(void *rbtreeptr, void* data);
extern void* deleteKey(void *rbtreeptr, void* data,rbt_flags_t flag);
extern long insertKey(void *rbtreeptr, void* data,rbt_flags_t flag);
extern long replaceKey(void *rbtreeptr, void* data,rbt_flags_t flag);
extern void * createTree(  long (*cmpLT) (void*, void*),  long (*cmpEQ) (void*, void*),  void (*print_data)(void*),void (*free_data)(void*),void* (*rbt_malloc_arg)(size_t),void (*rbt_free_arg)(void*));
void * rbt_find_least_not_less_than(void *rbtreeptr, void* data, void *this, void *searched);
extern void * rbt_find_largest_not_larger_than(void *rbtreeptr, void* data, void *this, void *searched);
void * rbt_find_node_least_not_less_than(void *rbtreeptr, void* data, void *this, void *searched);
void * rbt_find_node_largest_not_larger_than(void *rbtreeptr, void* data, void *this, void *searched);
/*si2 functions*/

#define SI2_INSERT_NEW_DATA_IF_EXISTS INSERT_NEW_DATA_IF_EXISTS
#define SI2_FREE_OLD_DATA_IF_EXISTS FREE_OLD_DATA_IF_EXISTS
#define SI2_RETURN_NULL_IF_EXISTS RETURN_NULL_IF_EXISTS
typedef rbt_flags_t si2_rbt_flags_t;

void * si2_createTree(  long (*cmpLT) (void*, void*),  long (*cmpEQ) (void*, void*), void (*free_data)(void*),void* (*rbt_malloc_arg)(size_t),void (*rbt_free_arg)(void*));
long si2_insertKey(void *rbtreeptr, void* data,si2_rbt_flags_t flag);
void * si2_findKey(void *rbtreeptr, void* data);
rm2_rbt_node_t * si2_findNode(void *rbtreeptr, void* data);
void* si2_deleteKey(void *rbtreeptr, void* data,si2_rbt_flags_t flag);
long si2_replaceKey(void *rbtreeptr, void* data,si2_rbt_flags_t flag);
void si2_unbound_rbt(void *rbtreeptr, void(*unbound_data)(void*));
void** si2_rbt_data(void *rbt_node); 
void* si2_rbt_begin(void*rbtreeptr,void*data);
void* si2_rbt_next(void*rbtreeptr,void*current);
void* si2_rbt_first(void*rbtreeptr);
void* si2_rbt_last(void*rbtreeptr);

void si2_process_tree_in_order(void *rbtreeptr, void(*process_data)(void*));

void * si2_rbt_find_node_least_not_lt(void *rbtreeptr, void* data);
void * si2_rbt_find_node_greatest_not_gt(void *rbtreeptr, void* data);


/*-----------------end*/
#endif
