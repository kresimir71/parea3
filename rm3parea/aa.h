#ifndef _AA_H
#define _AA_H
#include "rbt.h"
#include "col.h"
#include "mm2.h"

typedef struct 
{
  col_t* key;
  col_t* value;
  void* mm_handle;
  /*one key and value element of the array*/
  //DOC_TYPEDEF(aa_data_t DG_AA)
} aa_data_t;
typedef struct 
{
  col_t c;
  long length;
  /*main record of an array*/
  //DOC_TYPEDEF(aa_master_t DG_AA)
} aa_master_t;
/*produces static functions to act on aa_data_t for each element of array*/
//DOC_DEFINE(AA_FOREACH_FUNCTIONS DG_AA)
#define AA_FOREACH_FUNCTIONS(name,array,code)\
static void name##_element(void*d)\
{\
 aa_data_t*data=(aa_data_t*)d;\
 {\
  code\
 }\
}\
static void name##_all(void)\
{\
 process_tree_in_order(array->val,NULL,name##_element);\
}
aa_data_t* aa_next(col_t* arr,void** ref);
void* aa_begin(col_t* arr,col_t* index);
long aa_length(col_t* arr);
static void aa_unbound_pcol_col_element(void* data);
long aa_unbound_pcol_col(col_t*array);
long aa_unset_col_col(col_t* arr,col_t* i);
static void aa_unbound_element(void* data);
long aa_unbound_col(col_t*array);
void aa_foreach(col_t*array,void(*process_data)(void*));
void aa_unbound(col_t*array,void(*unbound_data)(void*));
void unbound_int_xstring(void* data);
void unbound_int_xstring_array(col_t*array);
long aa_cmpLT(void *a,void* b);
long aa_cmpEQ(void *a,void* b);
void aa_unset_xstring_xstring(col_t* arr,col_t* i);
aa_data_t* aa_greatest_not_gt(col_t* arr,col_t* val);
col_t* aa_greatest_not_gt_index(col_t* arr,col_t* val);
col_t* aa_greatest_not_gt_data(col_t* arr,col_t* val);
aa_data_t* aa_least_not_lt(col_t* arr,col_t* val);
col_t* aa_least_not_lt_index(col_t* arr,col_t* val);
col_t* aa_least_not_lt_data(col_t* arr,col_t* val);
#ifndef NDEBUG
col_t* debug_print_array_pair_to_xstring(void*pair);
#endif
long aa_assign_sint_xstring(col_t* array,long index,col_t*data,rbt_flags_t flag);
long aa_assign_xstring_xstring(col_t* array,col_t* index,col_t*data,rbt_flags_t flag);
long aa_assign_sstring_xstring(col_t* array,char* index,col_t* data,rbt_flags_t flag);
void aa_push_xstring(col_t* array,col_t*data);
col_t* xstring_aa_value_sint(col_t* array,long index);
col_t* xstring_aa_value_xstring(col_t* array,col_t* index);
col_t* xstring_aa_value_sstring(col_t* array,char* index);
char* xstring_aa_value_sint2(col_t* array,long index);
char* xstring_aa_value_xstring2(col_t* array,col_t* index);
char* xstring_aa_value_sstring2(col_t* array,char* index);
long aa_assign_raw(col_t* array, void*index,lisp_type_t index_type, long index_mm_sort, mm2_unit_t* index_mm_handle, void* data,lisp_type_t data_type, long data_mm_sort, mm2_unit_t* data_mm_handle,rbt_flags_t flag);
void aa_push_raw(col_t* array, void*data,lisp_type_t data_type, long data_mm_sort, mm2_unit_t* data_mm_handle);
col_t*aa_value_raw(col_t* array, void*index,lisp_type_t index_type, long index_mm_sort, mm2_unit_t* index_mm_handle);
void aa_unset(col_t* arr,col_t* i);
col_t* aa_value(col_t* arr,col_t* i);
void aa_push_array(col_t* arr,  col_t* val);
long aa_assign(col_t* arr, col_t* i, col_t* val, rbt_flags_t flag);
col_t* aa_array(void);
#endif
