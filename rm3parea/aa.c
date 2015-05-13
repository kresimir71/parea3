//#include "goals.h"
#include "stdlib.h"
#include "col.h"
#include "rbt.h"
#include "mm2.h"
#include "aa.h"
#include "limits.h"
//#include "goals.h"
#include "string.h"

/*give begin reference associated with data for use in next and prev array walk*/
//DOC_FUNC_DEF(aa_begin DG_AA)
void* aa_begin(col_t* arr,col_t* index)
{
  aa_data_t i_data;
  i_data.key = index;
  return rbt_begin(arr->val,&i_data);
}

/*given current reference, find next in array, returns aa_data_t*, assignes new reference*/
//DOC_FUNC_DEF(aa_next DG_AA)
aa_data_t* aa_next(col_t* arr,void** ref)
{
  assert(arr->type==AAP);
  *ref= rbt_next(arr->val,*ref);
  return rbt_data(*ref);
}

/*length of array*/
//DOC_FUNC_DEF(aa_length DG_AA)
long aa_length(col_t* arr)
{
  return ((aa_master_t*)arr)->length;
}
/*unbound one data unit of array */
//DOC_FUNC_DEF(aa_unbound_pcol_col_element DG_AA)
static void aa_unbound_pcol_col_element(void* data)
{
  aa_data_t*d=(aa_data_t*)data;
  if (((col_t*)(d->key))->val) col_unbound_col(((col_t*)(d->key))->val);
  col_unbound_col(d->key);
  if (d->value) col_unbound_col(d->value);
  mm2_unbound_mem(d->mm_handle);
}
/*unbound the whole array */
//DOC_FUNC_DEF(aa_unbound_pcol_col DG_AA)
long aa_unbound_pcol_col(col_t*array)
{
  long result;
  if (!(result=mm2_unbound_mem(array->mm_handle)))
    {
      /*!!begin critical section: uses unbounded result!!*/
      mm2_bound_new_forbidden=1;
      unbound_rbt(array->val,NULL,aa_unbound_pcol_col_element);
      mm2_bound_new_forbidden=0;
      /*!!end critical section: uses unbounded result!!*/
    }
  return result;
}
/*unbound data unit of array*/
//DOC_FUNC_DEF(aa_unbound_element DG_AA)
static void aa_unbound_element(void* data)
{
  aa_data_t*d=(aa_data_t*)data;
  col_unbound_col(d->key);
  if (d->value) col_unbound_col(d->value);
  mm2_unbound_mem(d->mm_handle);
}
/*unbound array of general col_t*/
//DOC_FUNC_DEF(aa_unbound_col DG_AA)
long aa_unbound_col(col_t*array)
{
  long result;
  if (!(result=mm2_unbound_mem(array->mm_handle)))
    {
      /*!!begin critical section: uses unbounded result!!*/
      mm2_bound_new_forbidden=1;
      unbound_rbt(array->val,NULL,aa_unbound_element);
      mm2_bound_new_forbidden=0;
      /*!!end critical section: uses unbounded result!!*/
    }
  return result;
}
/*for each element of array*/
//DOC_FUNC_DEF(aa_foreach DG_AA)
void aa_foreach(col_t*array,void(*process_data)(void*))
{
  process_tree_in_order(array->val,NULL,process_data);
}
/*unbound array*/
//DOC_FUNC_DEF(aa_unbound DG_AA)
void aa_unbound(col_t*array,void(*unbound_data)(void*))
{
  unbound_rbt(array->val,NULL,unbound_data);
  unbound_mem_from_handle(array->mm_handle);
}
/*unbound int xstring array element*/
//DOC_FUNC_DEF(unbound_int_xstring DG_AA)
void unbound_int_xstring(void* data)
{
  aa_data_t*d=(aa_data_t*)data;
  assert(d);assert(d->key);assert(d->value);assert(d->key->type==INTP||d->key->type==STRINGP||d->key->type==XSTRINGP);assert(d->value->type==XSTRINGP||d->value->type==STRINGP||d->value->type==INTP);
  unbound_col(d->key);
  unbound_col(d->value);
  unbound_mem_from_handle(d->mm_handle);
}
/*unbound int xstring array*/
//DOC_FUNC_DEF(unbound_int_xstring_array DG_AA)
void unbound_int_xstring_array(col_t*array)
{
  aa_unbound(array,unbound_int_xstring);
}
#ifndef NDEBUG
/*debug*/
//DOC_FUNC_DEF(debug_print_array_pair_to_xstring DG_AA)
col_t* debug_print_array_pair_to_xstring(void*pair)
{
  aa_data_t*p= (aa_data_t*)pair;
  col_t*result=NEW_XSTRING_CONST("");
  if(p)
    {
      col_t* index = print_col_to_xstring(p->key);
      col_t* value = print_col_to_xstring(p->value);
      result =concat_xstring(result,NEW_XSTRING_CONST("i:"));
      result =concat_xstring(result,index);
      result =concat_xstring(result,NEW_XSTRING_CONST("\nval:"));
      result =concat_xstring(result,value);
      result =concat_xstring(result,NEW_XSTRING_CONST("\n"));
    }
  return result;
}
#endif
/*array comparation function LT*/
//DOC_FUNC_DEF(aa_cmpLT DG_AA)
long aa_cmpLT(void *a,void* b)
{
  col_t* x = ((aa_data_t*)a)->key;
  col_t* y = ((aa_data_t*)b)->key;
  assert(x && y && (x->type == INTP || x->type == STRINGP|| x->type == XSTRINGP) && (y->type == INTP || y->type == STRINGP|| y->type == XSTRINGP));
  if ((x->type==INTP) && (y->type==INTP)) return (long)(x->val)<(long)(y->val);
  if ((x->type==STRINGP || x->type == XSTRINGP) && (y->type==STRINGP|| y->type == XSTRINGP|| y->type == XSTRINGP)) return strcmp(val_xstring_or_string(x),val_xstring_or_string(y))<0;
  if (x->type==INTP)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}
/*array comparation function EQ*/
//DOC_FUNC_DEF(aa_cmpEQ DG_AA)
long aa_cmpEQ(void *a,void* b)
{
  col_t* x = ((aa_data_t*)a)->key;
  col_t* y = ((aa_data_t*)b)->key;
  assert(x && y);
  assert((x->type == INTP || x->type == STRINGP || x->type == XSTRINGP) && (y->type == INTP || y->type == STRINGP || y->type == XSTRINGP));
  if ((x->type==INTP) && (y->type==INTP)) return (long)(x->val)==(long)(y->val);
  if ((x->type==STRINGP || x->type==XSTRINGP) && (y->type==STRINGP || y->type==XSTRINGP)) return strcmp(val_xstring_or_string(x),val_xstring_or_string(y))==0;
  return 0;
}
/*create array*/
//DOC_FUNC_DEF(aa_array DG_AA)
col_t* aa_array()
{
  col_t * result_var;
  void *result=createTree(aa_cmpLT,aa_cmpEQ,NULL,NULL,NULL,NULL);
  //  bound_new_col_symbol(&result_var,AAP,result);
  result_var=(col_t*)mm2_bound_new_mem(sizeof(aa_master_t));
  result_var->type=AAP;
  result_var->mm_handle = mm2_handle;
  result_var->val=result;
  ((aa_master_t*)result_var)->length=0;
  return result_var;
}
/*assign element of array*/
//DOC_FUNC_DEF(aa_assign DG_AA)
long aa_assign(col_t* arr,col_t* i,col_t* val,rbt_flags_t flag)
{
  long res;
  aa_data_t *data;
  assert(arr && arr->type==AAP && arr->val);
  assert(i->type==INTP || i->type==STRINGP || i->type==XSTRINGP);
  data=(aa_data_t*)mm2_bound_new_mem(sizeof(aa_data_t));
  data->mm_handle=mm2_handle;
  data->key=i;
  data->value=val;
  if (!flag) flag=RETURN_NULL_IF_EXISTS;
  res =insertKey(arr->val,data,flag);
  assert(flag==RETURN_NULL_IF_EXISTS);
  if(!res && flag ==RETURN_NULL_IF_EXISTS)
    {
      mm2_unbound_mem(data->mm_handle);
    }
  else
    {
      ((aa_master_t*)arr)->length++;
    }
  return res;
}
/*return greatest not greater than in array*/
//DOC_FUNC_DEF(aa_greatest_not_gt DG_AA)
aa_data_t* aa_greatest_not_gt(col_t* arr,col_t* val)
{
  aa_data_t* result;
  aa_data_t aa_data;
  aa_data.key=val;
  result = (aa_data_t *)rbt_find_largest_not_larger_than(arr->val,&aa_data,NULL,NULL);
  return result;
}

/*return greatest not greater than in array*/
//DOC_FUNC_DEF(aa_greatest_not_gt_index DG_AA)
col_t* aa_greatest_not_gt_index(col_t* arr,col_t* val)
{
  aa_data_t* result=aa_greatest_not_gt(arr,val);
  return (result?result->key:NULL);
}
/*return greatest not greater than in array*/
//DOC_FUNC_DEF(aa_greatest_not_gt_data DG_AA)
col_t* aa_greatest_not_gt_data(col_t* arr,col_t* val)
{
  aa_data_t* result=aa_greatest_not_gt(arr,val);
  return (result?result->value:NULL);
}
/*return least not less than in array*/
//DOC_FUNC_DEF(aa_least_not_lt DG_AA)
aa_data_t* aa_least_not_lt(col_t* arr,col_t* val)
{
  aa_data_t* result;
  aa_data_t aa_data;
  aa_data.key=val;
  result = (aa_data_t *)rbt_find_least_not_less_than(arr->val,&aa_data,NULL,NULL);
  return result;
}
/*return least not less than in array*/
//DOC_FUNC_DEF(aa_least_not_lt_index DG_AA)
col_t* aa_least_not_lt_index(col_t* arr,col_t* val)
{
  aa_data_t* result=aa_least_not_lt(arr,val);
  return (result?result->key:NULL);
}
/*return least not less than in array*/
//DOC_FUNC_DEF(aa_least_not_lt_data DG_AA)
col_t* aa_least_not_lt_data(col_t* arr,col_t* val)
{
  aa_data_t* result=aa_least_not_lt(arr,val);
  return (result?result->value:NULL);
}
/*add element with the next integer index*/
//DOC_FUNC_DEF(aa_push_array DG_AA)
void aa_push_array(col_t* arr,
		   col_t* val)
{
  aa_data_t * result;
  long res;
  aa_data_t aa_data;
  col_t* i;
  col_t i_aa;
  bound_new_col_symbol(&i,INTP,(void*)0);
  aa_data.key = &i_aa;
  aa_data.key->type=INTP;
  aa_data.key->val=(col_t*)INT_MAX;
  result = (aa_data_t *)rbt_find_largest_not_larger_than(arr->val,&aa_data,NULL,NULL);
  assert(result==0 || result->key->type==STRINGP || result->key->type==INTP || result->key->type==XSTRINGP);
  if(!result || result->key->type==STRINGP || result->key->type==XSTRINGP)
    {
    }
  else
    {
      i->val = (col_t*)((long)(result->key->val)+1);
    }
  res = aa_assign(arr,i,val,RETURN_NULL_IF_EXISTS);
  assert(res!=0);
}			 
/*add xstring indexed by integer*/
//DOC_FUNC_DEF(aa_assign_sint_xstring DG_AA)
long aa_assign_sint_xstring(col_t* array,long index,col_t*data,rbt_flags_t flag)
{
  return aa_assign_raw(array, &index,SINTP, 0, NULL, data,XSTRINGP, 0, NULL,flag);
}
/*add xstring indexed by xstring*/
//DOC_FUNC_DEF(aa_assign_xstring_xstring DG_AA)
long aa_assign_xstring_xstring(col_t* array,col_t* index,col_t*data,rbt_flags_t flag)
{
  return aa_assign_raw(array, index,XSTRINGP, 0, NULL, data,XSTRINGP, 0, NULL,flag);
}
/*add xstring indexed by string*/
//DOC_FUNC_DEF(aa_assign_sstring_xstring DG_AA)
long aa_assign_sstring_xstring(col_t* array,char* index,col_t* data,rbt_flags_t flag)
{
  return aa_assign_raw(array, index,SSTRINGP, 0, NULL, data,XSTRINGP, 0, NULL,flag);
}
/*add xstring indexed by the next integer index*/
//DOC_FUNC_DEF(aa_push_xstring DG_AA)
void aa_push_xstring(col_t* array,col_t*data)
{
  assert(XSTRINGP==data->type);
  return aa_push_raw(array, data,XSTRINGP, 0, NULL);
}
/* xstring value indexed by integer*/
//DOC_FUNC_DEF(xstring_aa_value_sint DG_AA)
col_t* xstring_aa_value_sint(col_t* array,long index)
{
  return aa_value_raw(array, &index,SINTP, 0, NULL);
}
/* xstring value indexed by xstring*/
//DOC_FUNC_DEF(xstring_aa_value_xstring DG_AA)
col_t* xstring_aa_value_xstring(col_t* array,col_t* index)
{
  return aa_value_raw(array, index,XSTRINGP, 0, NULL);
}
/* xstring value indexed by sstring*/
//DOC_FUNC_DEF(xstring_aa_value_sstring DG_AA)
col_t* xstring_aa_value_sstring(col_t* array,char* index)
{
  return aa_value_raw(array, index,SSTRINGP, 0, NULL);
}
/* string from xstring value indexed by integer*/
//DOC_FUNC_DEF(xstring_aa_value_sint2 DG_AA)
char* xstring_aa_value_sint2(col_t* array,long index)
{
  return val_xstring(xstring_aa_value_sint(array,index));
}
/* string from xstring value indexed by xstring*/
//DOC_FUNC_DEF(xstring_aa_value_xstring2 DG_AA)
char* xstring_aa_value_xstring2(col_t* array,col_t* index)
{
  return val_xstring(xstring_aa_value_xstring(array,index));
}
/* string from xstring value indexed by string*/
//DOC_FUNC_DEF(xstring_aa_value_sstring2 DG_AA)
char* xstring_aa_value_sstring2(col_t* array,char* index)
{
  return val_xstring(xstring_aa_value_sstring(array,index));
}
/*create new element*/
//DOC_DEFINE(AA_MAKE_EL DG_AA)
#define AA_MAKE_EL(index_type,new_index,index)\
  if (index_type==SINTP)\
    {\
      new_index=new_int(*(long*)index);\
    }\
  else if(index_type==SSTRINGP)\
    {\
      new_index=new_xstring(strlen(index),index);\
    }\
  else if(index_type==INTP || index_type==STRINGP ||index_type==XSTRINGP)\
    {\
      new_index=(col_t*)index;\
    }
     /* general assign function*/
//DOC_FUNC_DEF(aa_assign_raw DG_AA)
long aa_assign_raw(col_t* array, void*index,lisp_type_t index_type, long index_mm_sort, mm2_unit_t* index_mm_handle, void* data,lisp_type_t data_type, long data_mm_sort, mm2_unit_t* data_mm_handle,rbt_flags_t flag)
{
  col_t *new_index=NULL;
  col_t *new_data=NULL;
  long res;
  assert(index_type==SINTP || index_type==INTP || index_type==XSTRINGP || index_type==SSTRINGP || index_type==STRINGP);
  assert(data_type==SINTP || data_type==INTP || data_type==XSTRINGP|| data_type==SSTRINGP|| data_type==STRINGP);
  AA_MAKE_EL(index_type,new_index,index);
  AA_MAKE_EL(data_type,new_data,data);
  res=aa_assign(array,new_index,new_data,flag);
  if (!res)
    {
      if (index_type==SINTP || index_type==SSTRINGP)
	{
	  col_unbound_col(new_index);
	}
      if (data_type==SINTP || data_type==SSTRINGP)
	{
	  col_unbound_col(new_data);
	}
    }
  return res;
}
     /* general add at next integer index function*/
//DOC_FUNC_DEF(aa_push_raw DG_AA)
void aa_push_raw(col_t* array, void*data,lisp_type_t data_type, long data_mm_sort, mm2_unit_t* data_mm_handle)
{
  col_t *new_data=NULL;
  assert(data_type==SINTP || data_type==INTP || data_type==XSTRINGP|| data_type==SSTRINGP|| data_type==STRINGP);
  AA_MAKE_EL(data_type,new_data,data);
  aa_push_array(array,new_data);
}
     /* general value at index function*/
//DOC_FUNC_DEF(aa_value_raw DG_AA)
col_t*aa_value_raw(col_t* array, void*index,lisp_type_t index_type, long index_mm_sort, mm2_unit_t* index_mm_handle)
{
  col_t*result;
  col_t *new_index=NULL;
  assert(index_type==SINTP || index_type==INTP || index_type==XSTRINGP || index_type==SSTRINGP || index_type==STRINGP);
  AA_MAKE_EL(index_type,new_index,index);
  result = aa_value(array,new_index);  
  if(index_type==SINTP ) unbound_mem_from_handle(new_index->mm_handle);
  if(index_type==SSTRINGP ) unbound_xstring(new_index);
  return result;
}
     /* value at index*/
//DOC_FUNC_DEF(aa_value DG_AA)
col_t* aa_value(col_t* arr, col_t* i)
{
  aa_data_t * result;
  aa_data_t i_data;
  assert(i->type==INTP || i->type==STRINGP || i->type==XSTRINGP);
  i_data.key = i;
  result = (aa_data_t *)findKey(arr->val,&i_data);
  assert(result==0 || result->key->type==XSTRINGP || result->key->type==STRINGP || result->key->type==INTP);
  if(result)
    {
      return result->value;
    }
  else
    {
      return NULL;
    }
}
/*remove element from array*/
//DOC_FUNC_DEF(aa_unset DG_AA)
void aa_unset(col_t* arr, col_t* i)
{
  aa_data_t i_data;
  assert(i->type==INTP || i->type==STRINGP);
  assert(arr && arr->type==AAP);
  i_data.key = i;
  if (deleteKey(arr->val,&i_data,0)) ((aa_master_t*)arr)->length--;
}
/*remove xstring indexed by xstring from array*/
//DOC_FUNC_DEF(aa_unset_xstring_xstring DG_AA)
void aa_unset_xstring_xstring(col_t* arr,col_t* i)
{
  aa_data_t i_data;
  aa_data_t* data;
  col_t* value;
  col_t* key;
  assert(i->type==XSTRINGP);
  assert(arr && arr->type==AAP);
  i_data.key = i;
  //data=findKey(arr->val,&i_data);
  data=(aa_data_t*)deleteKey(arr->val,&i_data,0);
  if(data)
    {
      key = data->key;
      value = data->value;
      //      deleteKey(arr->val,&i_data,0);
      assert(key->type==XSTRINGP);
      unbound_xstring(key);
      if (value) 
	{
	  assert(value->type==XSTRINGP);
	  unbound_xstring(value);
	}
      mm2_unbound_mem(data->mm_handle);
      ((aa_master_t*)arr)->length--;
    }
}
/*remove col_t indexed by col_t from array, return 0 if not found*/
//DOC_FUNC_DEF(aa_unset_col_col DG_AA)
long aa_unset_col_col(col_t* arr,col_t* i)
{
  long result=0;
  aa_data_t i_data;
  aa_data_t* data;
  col_t* value;
  col_t* key;
  assert(i->type==XSTRINGP || i->type==INTP || i->type==STRINGP);
  assert(arr && arr->type==AAP);
  i_data.key = i;
  //data=findKey(arr->val,&i_data);
  data=(aa_data_t*)deleteKey(arr->val,&i_data,0);
  if(data)
    {
      result=1;
      key = data->key;
      value = data->value;
      //      deleteKey(arr->val,&i_data,0);
      col_unbound_col(key);
      if (value) 
	{
	  col_unbound_col(value);
	}
      mm2_unbound_mem(data->mm_handle);
      ((aa_master_t*)arr)->length--;
    }
  return result;
}
