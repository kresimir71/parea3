//#ifndef SI2
#include "col.h"
//#else
//#define   FINALIZE_DEBUG()
//#endif
#include "string.h"
#include "stdio.h"
#include "rbt.h"
#include "rbt_shortcuts.h"
#include "mm2.h"
#include "stdlib.h"
//#include "goals.h"
//#include "debug2.h"

typedef struct 
{
  rm2_rbt_node_t *root;
  long (*cmpLT) (void*, void*);
  long (*cmpEQ) (void*, void*);
  void (*print_data)(void*);
  rm2_rbt_node_t leaf;
  void (*free_data)(void*);
  void* (*rbt_malloc)(size_t);
  void (*rbt_free)(void*);
  void* mm_handle;
  /*tree struct*/
  //DOC_TYPEDEF(rbtree_t DG_RBT)
} rbtree_t;
/*data from rm2_rbt_node_t*/
//DOC_FUNC_DEF(rbt_data DG_RBT)
void* rbt_data(rm2_rbt_node_t*t)
{
  if (t) return t->data;
  return NULL;
}
/*create tree. 1)free_data is used to delete user data when adding(with replacement) and removing node, if NULL then 'free' is used BUT unbound_rbt function requires specifying non NULL unbound_data function argument once again 2)rbt_free_arg and rbt_malloc_arg are used only to malloc/free rbt internal structures - not for user data: if both NULL then mm2 lib is used*/
//DOC_FUNC_DEF(createTree DG_RBT)
void * createTree(  long (*cmpLT) (void*, void*), long (*cmpEQ) (void*, void*), void (*print_data)(void*), void (*free_data)(void*),void* (*rbt_malloc_arg)(size_t),void (*rbt_free_arg)(void*))
{
  rbtree_t* rbtreeptr;
  if (!rbt_malloc_arg&&!rbt_free_arg){
    rbtreeptr = (rbtree_t*)mm2_bound_new_mem(sizeof(rbtree_t));
    rbtreeptr->rbt_malloc=NULL;
    rbtreeptr->rbt_free=NULL;
  }else if(rbt_malloc_arg&&rbt_free_arg){
    rbtreeptr = (rbtree_t*)rbt_malloc_arg(sizeof(rbtree_t));
    rbtreeptr->rbt_malloc=rbt_malloc_arg;
    rbtreeptr->rbt_free=rbt_free_arg;    
  }else{
    printf("rbt createTree fatal error:one of rbt_free_arg, rbt_malloc_arg NULL, other non NULL\n");exit(1);
  }
  rbtreeptr->mm_handle=mm2_handle;
  rbtreeptr->root = &((rbtree_t *)rbtreeptr)->leaf;
  rbtreeptr->cmpLT = cmpLT;
  rbtreeptr->cmpEQ = cmpEQ;
  rbtreeptr->print_data = print_data;
  rbtreeptr->leaf.l=&(rbtreeptr->leaf);
  rbtreeptr->leaf.r=&(rbtreeptr->leaf);
  rbtreeptr->leaf.p=0;
  rbtreeptr->leaf.c=RM2_RBT_COLOR_BLACK;
  rbtreeptr->leaf.data=0;
  rbtreeptr->free_data=free_data;
  return rbtreeptr;
}

SHIFT(l,r)
SHIFT(r,l)
     /*add restore*/
     //DOC_FUNC_DEF(addRestore DG_RBT)
static void addRestore(void *rbtreeptr, rm2_rbt_node_t *node_a) 
{
  while (node_a != ((rbtree_t *)rbtreeptr)->root && 
	 node_a->p->c == RM2_RBT_COLOR_RED) 
    {    
      if (node_a->p == node_a->p->p->l) 
	{
	  ADD_RESTORE(l,
		      r);
	} 
      else 
	{
	  ADD_RESTORE(r,
		      l);
	}      
    }
  ((rbtree_t *)rbtreeptr)->root->c = RM2_RBT_COLOR_BLACK;
}
/*add node*/
//DOC_FUNC_DEF(addNode DG_RBT)
static rm2_rbt_node_t *addNode(void *rbtreeptr, void* data, rbt_flags_t flag) 
{
  rm2_rbt_node_t *this, *p, *node_a;
  this = ((rbtree_t *)rbtreeptr)->root;
  p = 0;
  while (this != &((rbtree_t *)rbtreeptr)->leaf) 
    {
      if ((*(((rbtree_t *)rbtreeptr)->cmpEQ))(data, 
					      this->data)) 
	{
	  if (flag & RETURN_NULL_IF_EXISTS)
	    return NULL;
	  if (flag & (FREE_OLD_DATA_IF_EXISTS | INSERT_NEW_DATA_IF_EXISTS))
	    {
	      if (((rbtree_t*)rbtreeptr)->free_data)
		{
		  (*(((rbtree_t*)rbtreeptr)->free_data))(this->data);
		}
	      else
		{
		  free(this->data);
		}
	    }
	  if (flag & INSERT_NEW_DATA_IF_EXISTS)
	    {
	      this->data = data;
	    }
	  return (this);
	}
      p = this;
      this = (*(((rbtree_t *)rbtreeptr)->cmpLT))(data, 
						 this->data) ?
	this->l : this->r;
    }
  if (!(((rbtree_t*)rbtreeptr)->rbt_malloc)&&!(((rbtree_t*)rbtreeptr)->rbt_free)){
    node_a = (rm2_rbt_node_t*)mm2_bound_new_mem(sizeof(*node_a));
  }else{
    node_a = (rm2_rbt_node_t*)(((rbtree_t*)rbtreeptr)->rbt_malloc)(sizeof(*node_a));
  }
  node_a->mm_handle=mm2_handle;
  node_a->c = RM2_RBT_COLOR_RED;
  node_a->l = &((rbtree_t *)rbtreeptr)->leaf;
  node_a->p = p;
  node_a->r = &((rbtree_t *)rbtreeptr)->leaf;
  node_a->data = data;
  if(p) 
    {
      if((*(((rbtree_t *)rbtreeptr)->cmpLT))(data, 
					     p->data))
	p->l = node_a;
      else
	p->r = node_a;
    } else {
      ((rbtree_t *)rbtreeptr)->root = node_a;
    }
  addRestore(((rbtree_t *)rbtreeptr),
	     node_a);
  return(node_a);
}
/*remove restore*/
//DOC_FUNC_DEF(removeRestore DG_RBT)
static void removeRestore(void *rbtreeptr, rm2_rbt_node_t *node_a) 
{
  while (node_a != ((rbtree_t *)rbtreeptr)->root && 
	 node_a->c == RM2_RBT_COLOR_BLACK) 
    {
      if (node_a == node_a->p->l) 
	{
	  REMOVE_RESTORE(l,
			 r);
	} 
      else 
	{
	  REMOVE_RESTORE(r,
			 l);
	}
    }
  node_a->c = RM2_RBT_COLOR_BLACK;
}
/*remove element*/
//DOC_FUNC_DEF(removeNode DG_RBT)
static void removeNode(void *rbtreeptr, rm2_rbt_node_t *node_c) 
{
  rm2_rbt_node_t *node_a, *node_b;

  if (!node_c || 
      node_c == &((rbtree_t *)rbtreeptr)->leaf) return;
  if (node_c->l == &((rbtree_t *)rbtreeptr)->leaf || 
      node_c->r == &((rbtree_t *)rbtreeptr)->leaf) 
    {
    
      node_b = node_c;
    } else {
    
      node_b = node_c->r;
      while (node_b->l != &((rbtree_t *)rbtreeptr)->leaf) node_b = node_b->l;
    }  
  if (node_b->l != &((rbtree_t *)rbtreeptr)->leaf)
    node_a = node_b->l;
  else
    node_a = node_b->r;
  node_a->p = node_b->p;
  if (node_b->p)
    if (node_b == node_b->p->l)
      node_b->p->l = node_a;
    else
      node_b->p->r = node_a;
  else
    ((rbtree_t *)rbtreeptr)->root = node_a;
  if (node_b != node_c) node_c->data = node_b->data;
  if (node_b->c == RM2_RBT_COLOR_BLACK)
    removeRestore (((rbtree_t *)rbtreeptr),
		   node_a);
  if (!(((rbtree_t*)rbtreeptr)->rbt_malloc)&&!(((rbtree_t*)rbtreeptr)->rbt_free)){
    unbound_mem_from_handle(node_b->mm_handle);
  }else{
    (((rbtree_t*)rbtreeptr)->rbt_free)((void*)node_b);
  }
}
/*find largest not larger than in tree*/
//DOC_FUNC_DEF(rbt_find_largest_not_larger_than DG_RBT)
void * rbt_find_largest_not_larger_than(void *rbtreeptr, void* data, void *this, void *searched)
{

  rm2_rbt_node_t* node=rbt_find_node_largest_not_larger_than(rbtreeptr,data,this,searched);
  if (node){
    return node->data;
  }
  return NULL;

/*   rm2_rbt_node_t * t = (rm2_rbt_node_t*)this; */
/*   if (!this) return rbt_find_largest_not_larger_than(rbtreeptr, data, ((rbtree_t *)rbtreeptr)->root,NULL); */
/*   if (this==&((rbtree_t *)rbtreeptr)->leaf) return (searched ? ((rm2_rbt_node_t*)searched)->data : NULL); */
/*   if((*(((rbtree_t *)rbtreeptr)->cmpEQ))(data, t->data)) return t->data; */
/*   if((*(((rbtree_t *)rbtreeptr)->cmpLT))(data, t->data)) {return rbt_find_largest_not_larger_than(rbtreeptr,data,t->l,searched);} */
/*   else  */
/*     { */
/*       if(!searched || (*(((rbtree_t *)rbtreeptr)->cmpLT))(((rm2_rbt_node_t*)searched)->data,t->data)) */
/* 	{searched = t;} */
/*       return rbt_find_largest_not_larger_than(rbtreeptr,data,t->r,searched); */
/*     }  */
}
/*find least not less than in tree*/
//DOC_FUNC_DEF(rbt_find_least_not_less_than DG_RBT)
void * rbt_find_least_not_less_than(void *rbtreeptr, void* data, void *this, void *searched)
{
  rm2_rbt_node_t* node=rbt_find_node_least_not_less_than(rbtreeptr,data,this,searched);
  if (node){
    return node->data;
  }
  return NULL;

/*   rm2_rbt_node_t * t = (rm2_rbt_node_t*)this; */
/*   if (!this) return rbt_find_least_not_less_than(rbtreeptr, data, ((rbtree_t *)rbtreeptr)->root,NULL); */
/*   if (this==&((rbtree_t *)rbtreeptr)->leaf) return (searched ? ((rm2_rbt_node_t*)searched)->data : NULL); */
/*   if((*(((rbtree_t *)rbtreeptr)->cmpEQ))(data, t->data)) return t->data; */
/*   if(!(*(((rbtree_t *)rbtreeptr)->cmpLT))(data, t->data)) {return rbt_find_least_not_less_than(rbtreeptr,data,t->r,searched);} */
/*   else  */
/*     { */
/*       if(!searched || !((*(((rbtree_t *)rbtreeptr)->cmpLT))(((rm2_rbt_node_t*)searched)->data,t->data)||(*(((rbtree_t *)rbtreeptr)->cmpEQ))(((rm2_rbt_node_t*)searched)->data,t->data))) */
/* 	{searched = t;} */
/*       return rbt_find_least_not_less_than(rbtreeptr,data,t->l,searched); */
/*     }  */
}
/*find largest not larger than in tree*/
//DOC_FUNC_DEF(rbt_find_node_largest_not_larger_than DG_RBT)
void * rbt_find_node_largest_not_larger_than(void *rbtreeptr, void* data, void *this, void *searched)
{
  rm2_rbt_node_t * t = (rm2_rbt_node_t*)this;
  if (!this) return rbt_find_node_largest_not_larger_than(rbtreeptr, data, ((rbtree_t *)rbtreeptr)->root,NULL);
  if (this==&((rbtree_t *)rbtreeptr)->leaf) return (searched ? ((rm2_rbt_node_t*)searched) : NULL);
  if((*(((rbtree_t *)rbtreeptr)->cmpEQ))(data, t->data)) return t;
  if((*(((rbtree_t *)rbtreeptr)->cmpLT))(data, t->data)) {return rbt_find_node_largest_not_larger_than(rbtreeptr,data,t->l,searched);}
  else 
    {
/*       if(!searched || (*(((rbtree_t *)rbtreeptr)->cmpLT))(((rm2_rbt_node_t*)searched)->data,t->data)) */
/* 	{searched = t;} */
      return rbt_find_node_largest_not_larger_than(rbtreeptr,data,t->r,t);
    } 
}
/*find least not less than in tree*/
//DOC_FUNC_DEF(rbt_find_node_least_not_less_than DG_RBT)
void * rbt_find_node_least_not_less_than(void *rbtreeptr, void* data, void *this, void *searched)
{
  rm2_rbt_node_t * t = (rm2_rbt_node_t*)this;
  if (!this) return rbt_find_node_least_not_less_than(rbtreeptr, data, ((rbtree_t *)rbtreeptr)->root,NULL);
  if (this==&((rbtree_t *)rbtreeptr)->leaf) return (searched ? ((rm2_rbt_node_t*)searched) : NULL);
  if((*(((rbtree_t *)rbtreeptr)->cmpEQ))(data, t->data)) return t;
  if(!(*(((rbtree_t *)rbtreeptr)->cmpLT))(data, t->data)) {return rbt_find_node_least_not_less_than(rbtreeptr,data,t->r,searched);}
  else 
    {
/*       if(!searched || !((*(((rbtree_t *)rbtreeptr)->cmpLT))(((rm2_rbt_node_t*)searched)->data,t->data)||(*(((rbtree_t *)rbtreeptr)->cmpEQ))(((rm2_rbt_node_t*)searched)->data,t->data))) */
/* 	{searched = t;} */
      return rbt_find_node_least_not_less_than(rbtreeptr,data,t->l,t);
    } 
}
/*search element*/
//DOC_FUNC_DEF(search_node DG_RBT)
static rm2_rbt_node_t *search_node(void *rbtreeptr, void* data, rm2_rbt_node_t *this) 
{
  if (this==&((rbtree_t *)rbtreeptr)->leaf) return NULL;
  if((*(((rbtree_t *)rbtreeptr)->cmpEQ))(data, this->data)) return this;
  if((*(((rbtree_t *)rbtreeptr)->cmpLT))(data, this->data)) {return search_node(rbtreeptr,data,this->l);}
  else return search_node(rbtreeptr,data,this->r);
}
#ifndef SI2
#ifndef NDEBUG
//DOC_FUNC_DEF(dump_tree_inorder DG_RBT)
void dump_tree_inorder(void *rbtreeptr,	rm2_rbt_node_t *this) 
{
  if (!this) {dump_tree_inorder(rbtreeptr,((rbtree_t *)rbtreeptr)->root);return;}
  assert( ( (rbtree_t *)rbtreeptr )->print_data);
  assert(this);
  if (this==&((rbtree_t *)rbtreeptr)->leaf) return ;
  dump_tree_inorder(rbtreeptr,this->l);
  ( *( ( (rbtree_t *)rbtreeptr )->print_data) ) (this->data);
  dump_tree_inorder(rbtreeptr,this->r);
}

//DOC_FUNC_DEF(dump_mm_tree_inorder_to_string DG_RBT)
char* dump_mm_tree_inorder_to_string(void *rbtreeptr, rm2_rbt_node_t *this, char*(*data_to_string)(void*))
{
  static char* result;
  static long length;
  if (!this) 
    {  
      //    COL_BOUND_MEM_NO_HANDLE_SIZE(str_res1,char,1);
      char*str_res1 = (char*)malloc(1);
      result = str_res1;
      *str_res1=0;
      length =0;
      return dump_mm_tree_inorder_to_string(rbtreeptr,((rbtree_t *)rbtreeptr)->root,data_to_string);
    }
  assert(this);
  if (this==&((rbtree_t *)rbtreeptr)->leaf) return result;
  dump_mm_tree_inorder_to_string(rbtreeptr,this->l,data_to_string);
  {
    char*c = (*data_to_string)(this->data);
    long len = strlen(c);
    //    result=concat_unbound(result,length,c,len);
    result=concat_free(result,length,c,len);
    length +=len;
  }
  dump_mm_tree_inorder_to_string(rbtreeptr,this->r,data_to_string);
  return result;
}

//DOC_FUNC_DEF(dump_tree_inorder_to_string DG_RBT)
char* dump_tree_inorder_to_string(void *rbtreeptr, rm2_rbt_node_t *this, char*(*data_to_string)(void*))
{
  static char* result;
  static long length;
  if (!this) 
    {  
      COL_BOUND_MEM_NO_HANDLE_SIZE(str_res1,char,1);
      //char*str_res1 = (char*)malloc(1);
      result = str_res1;
      *str_res1=0;
      length =0;
      return dump_tree_inorder_to_string(rbtreeptr,((rbtree_t *)rbtreeptr)->root,data_to_string);
    }
  assert(this);
  if (this==&((rbtree_t *)rbtreeptr)->leaf) return result;
  dump_tree_inorder_to_string(rbtreeptr,this->l,data_to_string);
  {
    char*c = (*data_to_string)(this->data);
    long len = strlen(c);
    result=concat_unbound(result,length,c,len);
    //result=concat_free(result,length,c,len);
    length +=len;
  }
  dump_tree_inorder_to_string(rbtreeptr,this->r,data_to_string);
  return result;
}

//DOC_FUNC_DEF(dump_tree_to_xstring DG_RBT)
col_t* dump_tree_to_xstring(void *rbtreeptr, rm2_rbt_node_t *this, col_t*(*data_to_xstring)(void*))
{
  static col_t* result;
  if (!this) 
    {  
      result = NEW_XSTRING_CONST("");
      return dump_tree_to_xstring(rbtreeptr,((rbtree_t *)rbtreeptr)->root,data_to_xstring);
    }
  assert(this);
  if (this==&((rbtree_t *)rbtreeptr)->leaf) return result;
  dump_tree_to_xstring(rbtreeptr,this->l,data_to_xstring);
  {
    col_t*c = (*data_to_xstring)(this->data);
    result=concat_xstring(result,c);
  }
  dump_tree_to_xstring(rbtreeptr,this->r,data_to_xstring);
  return result;
}
#endif
#endif
/*process all elements */
//DOC_FUNC_DEF(process_tree_in_order DG_RBT)
void process_tree_in_order(void *rbtreeptr, rm2_rbt_node_t *this, void(*process_data)(void*))
{
  if (!this) 
    {  
      process_tree_in_order(rbtreeptr,((rbtree_t *)rbtreeptr)->root,process_data);
    }
  else
    {
      assert(this);
      if (this!=&((rbtree_t *)rbtreeptr)->leaf)
	{
	  process_tree_in_order(rbtreeptr,this->l,process_data);
	  (*process_data)(this->data);
	  process_tree_in_order(rbtreeptr,this->r,process_data);
	}
    }
  return;
}
/*unbound tree*/
//DOC_FUNC_DEF(unbound_rbt DG_RBT)
void unbound_rbt(void *rbtreeptr, rm2_rbt_node_t *this_node, void(*unbound_data)(void*))
{
  if (!this_node) 
    {  
      unbound_rbt(rbtreeptr,((rbtree_t *)rbtreeptr)->root,unbound_data);
      if (!(((rbtree_t*)rbtreeptr)->rbt_malloc)&&!(((rbtree_t*)rbtreeptr)->rbt_free)){
	unbound_mem_from_handle(((rbtree_t *)rbtreeptr)->mm_handle);
      }else{
	(((rbtree_t*)rbtreeptr)->rbt_free)((void*)rbtreeptr);
      }
    }
  else
    {
      assert(this_node);
      if (this_node!=&((rbtree_t *)rbtreeptr)->leaf)
	{
	  unbound_rbt(rbtreeptr,this_node->l,unbound_data);
	  unbound_rbt(rbtreeptr,this_node->r,unbound_data);
	  (*unbound_data)(this_node->data);
	  if (!(((rbtree_t*)rbtreeptr)->rbt_malloc)&&!(((rbtree_t*)rbtreeptr)->rbt_free)){
	    unbound_mem_from_handle(this_node->mm_handle);
	  }else{
	    (((rbtree_t*)rbtreeptr)->rbt_free)((void*)this_node);
	  }
	}
    }
  return;
}
/*find element*/
//DOC_FUNC_DEF(findKey DG_RBT)
void * findKey(void *rbtreeptr, void* data)
{
  rm2_rbt_node_t *t;
  if ((t = search_node(rbtreeptr,data,((rbtree_t *)rbtreeptr)->root)) != NULL) 
    {
      return t->data;
    }
  else
    {
      return NULL;
    }
}
/*delete element*/
//DOC_FUNC_DEF(deleteKey DG_RBT)
void* deleteKey(void *rbtreeptr, void* data, rbt_flags_t flag)
{
  rm2_rbt_node_t *t;
  if ((t = search_node(rbtreeptr,data,((rbtree_t *)rbtreeptr)->root)) != NULL) 
    {
      void* data = t->data;
      removeNode(rbtreeptr,
		 t);
      if (flag & FREE_OLD_DATA_IF_EXISTS)
	{
	  if (((rbtree_t*)rbtreeptr)->free_data)
	    {
	      (*(((rbtree_t*)rbtreeptr)->free_data))(data);
	    }
	  else
	    {
	      assert(0);
	      free(data);
	    }
	}
      return data;
    }
  else
    {
      return NULL;
    }
}
/*insert element*/
//DOC_FUNC_DEF(insertKey DG_RBT)
long insertKey(void *rbtreeptr, void* data, rbt_flags_t flag)
{
  return (long)addNode(rbtreeptr,
		      data,
		      flag);
}
/*replace element*/
//DOC_FUNC_DEF(replaceKey DG_RBT)
long replaceKey(void *rbtreeptr, void* data, rbt_flags_t flag)
{
  return (long)addNode(rbtreeptr,
		      data,
		      flag | INSERT_NEW_DATA_IF_EXISTS);
}
/*give begin reference associated with data for use in next and prev in-order tree walk*/
//DOC_FUNC_DEF(rbt_begin DG_RBT)
void* rbt_begin(void*rbtreeptr,void*data)
{
  rm2_rbt_node_t* result = search_node(rbtreeptr,data,((rbtree_t *)rbtreeptr)->root);
  return result;
}
/*return next above*/
//DOC_FUNC_DEF(rbt_first_right_parent DG_RBT)
static rm2_rbt_node_t* rbt_first_right_parent(rm2_rbt_node_t*x)
{
  if (!x->p) return NULL;
  if (x->p->l==x) return x->p;
  return rbt_first_right_parent(x->p);
}
/*return next below*/
//DOC_FUNC_DEF(rbt_last_left DG_RBT)
static rm2_rbt_node_t* rbt_last_left(void*rbtreeptr,rm2_rbt_node_t*x)
{
  assert(x);
  if(x->l==&((rbtree_t *)rbtreeptr)->leaf) return x;
  return rbt_last_left(rbtreeptr,x->l);
}
/*given current reference, find next in in-order tree walk, returns new reference*/
//DOC_FUNC_DEF(rbt_next DG_RBT)
void* rbt_next(void*rbtreeptr,void*current)
{
  rm2_rbt_node_t* c = (rm2_rbt_node_t*)current;
  if (c)
    {
     if(c->r!=&((rbtree_t *)rbtreeptr)->leaf) return rbt_last_left(rbtreeptr,c->r);
     return rbt_first_right_parent(c);
    }
  else
    return NULL;
}

/*BEGIN si2 functions*/


/* ... */
//DOC_FUNC_DEF(si2_createTree DG_RBT_SI2)
void * si2_createTree(  long (*cmpLT) (void*, void*),  long (*cmpEQ) (void*, void*), void (*free_data)(void*),void* (*rbt_malloc_arg)(size_t),void (*rbt_free_arg)(void*))
{
  return createTree(cmpLT, cmpEQ, NULL, free_data, rbt_malloc_arg, rbt_free_arg);
}
/* ... */
//DOC_FUNC_DEF(si2_insertKey DG_RBT_SI2)
long si2_insertKey(void *rbtreeptr, void* data,si2_rbt_flags_t flag){
  return insertKey(rbtreeptr,data,flag);
}
/* ... */
//DOC_FUNC_DEF(si2_findKey DG_RBT_SI2)
void * si2_findKey(void *rbtreeptr, void* data){
  return findKey(rbtreeptr,data);
}
/* ... */
//DOC_FUNC_DEF(si2_findNode DG_RBT_SI2)
rm2_rbt_node_t * si2_findNode(void *rbtreeptr, void* data){
  rm2_rbt_node_t *t;
  if ((t = search_node(rbtreeptr,data,((rbtree_t *)rbtreeptr)->root)) != NULL) 
    {
      return t;
    }
  else
    {
      return NULL;
    }
}
/* ... */
//DOC_FUNC_DEF(si2_deleteKey DG_RBT_SI2)
void* si2_deleteKey(void *rbtreeptr, void* data,si2_rbt_flags_t flag){
  return deleteKey(rbtreeptr, data, flag);
}
/* ... */
//DOC_FUNC_DEF(si2_replaceKey DG_RBT_SI2)
long si2_replaceKey(void *rbtreeptr, void* data,si2_rbt_flags_t flag){
  return replaceKey(rbtreeptr,data,flag);
}
/* ... */
//DOC_FUNC_DEF(si2_unbound_rbt DG_RBT_SI2)
void si2_unbound_rbt(void *rbtreeptr, void(*unbound_data)(void*)){
  unbound_rbt(rbtreeptr,NULL,unbound_data);
}
/*void** si2_... to allow replacing data: DON'T CHANGE THE KEY NOT TO DISTURBE THE TREE STRUCTURE!!!*/
//DOC_FUNC_DEF(si2_rbt_data DG_RBT_SI2)
void** si2_rbt_data(void *rbt_node){
  if (rbt_node&&((rm2_rbt_node_t*)rbt_node)->data) return &(((rm2_rbt_node_t*)rbt_node)->data);
  return NULL;
}
/* ... */
//DOC_FUNC_DEF(si2_rbt_begin DG_RBT_SI2)
void* si2_rbt_begin(void*rbtreeptr,void*data){
  return rbt_begin(rbtreeptr,data);
}
/* ... */
//DOC_FUNC_DEF(si2_rbt_next DG_RBT_SI2)
void* si2_rbt_next(void*rbtreeptr,void*current){
  return rbt_next(rbtreeptr,current);
}
/* ... */
//DOC_FUNC_DEF(si2_process_tree_in_order DG_RBT_SI2)
void si2_process_tree_in_order(void *rbtreeptr, void(*process_data)(void*)){
  process_tree_in_order(rbtreeptr,NULL,process_data);
}

/* ... */
//DOC_FUNC_DEF(si2_rbt_find_node_least_not_lt DG_RBT_SI2)
void * si2_rbt_find_node_least_not_lt(void *rbtreeptr, void* data){
  return rbt_find_node_least_not_less_than(rbtreeptr,data,NULL,NULL);
}
/* ... */
//DOC_FUNC_DEF(si2_rbt_find_node_greatest_not_gt DG_RBT_SI2)
void * si2_rbt_find_node_greatest_not_gt(void *rbtreeptr, void* data){
  return rbt_find_node_largest_not_larger_than(rbtreeptr,data,NULL,NULL);
}

/*END si2 functions*/

#ifndef NDEBUG
#ifdef RBT_DEBUG

/*RBT TEST*/
/*
cd $RM2;gcc -DNDEBUG=1 -DNDEBUGFLEX=1 -DDEBUG_DISABLE=1 -DASSERT_IN_ANY_CASE=1 -O3 -g0 -I. -DRBT_DEBUG mm2.c mm.c rbt.c
DD01_HOWTO(DD01_rm2_rbt_test) 
---

// RBTREE is a binary search tree where each path has equal number of
// black nodes. In perfect case all nodes are black but this seldom
// happens. Therefore red nodes may be inserted on paths but there may
// be no two consecutive red nodes on a path. The root is black and
// the leafs contain no data and are also black. So to say red nodes
// can disturbe equality of paths for roughly at most twice.

----

 On insertion and deletion the root and other parts are shifted in order to preserve a kind of balance that guarantees required properties.

The following test inserts and deletes a random tree and on every step checks the:

//RBT PROPERTY: 1)ROOT AND LEAFS ARE BLACK 2)CHILDREN OF RED ARE BLACK 3) THERE ARE EQUALY MANY BLACK IN LEFT AND RIGHT SUBTREE FOR EACH NODE

*/
long compareLT(void* a, void* b)
{
  return (*(long*)a < *(long*)b);
}
long compareEQ(void* a, void* b)
{
  return (*(long*)a == *(long*)b);
}
long test_red_black_properties(rm2_rbt_node_t *ptr,
			      void* rbtreeptr)
{
  long black;
  long nl;
  long nr;
  // the second expression in the following is a constant pointer with the meaning:end point
  if (ptr==&((rbtree_t *)rbtreeptr)->leaf)
    {
      if (ptr->c != RM2_RBT_COLOR_BLACK)
	{
	  printf("NOT OK:violated (leaf is not black)\n");exit(1);
	}
      else
	{
	  return 1;
	}
    }
  if (ptr->c == RM2_RBT_COLOR_RED)
    {
      black=0;
      if ((ptr->l->c != RM2_RBT_COLOR_BLACK) ||
	  (ptr->r->c != RM2_RBT_COLOR_BLACK))
	{
	  printf("NOT OK:violated (consecutive red nodes)\n");exit(1);
	}
    }
  if (ptr->c == RM2_RBT_COLOR_BLACK)
    {
      black =1;
    }
  nl = test_red_black_properties(ptr->l,
				 rbtreeptr);
  nr = test_red_black_properties(ptr->r,
				 rbtreeptr);
  if (nl!=nr)
    {
      printf("NOT OK:violated (two subpaths do not agree on the number of black nodes => two paths also)\n") ;exit(1);
    }
  return nl+black;
}

int main(int argc, 
	 char **argv) 
{
  long a, maxnum, rec;
  rm2_rbt_node_t *t;
  long *x;
  void * rbtreeptr;
  long deleted = 0, inserted = 0;
  mm2_create();
  if (argc<2)
    {
      printf("usage:rbt number\ndefault 30000\n");
      maxnum=30000;
    }
  else
    {
      maxnum = atoi(argv[1]);
    }
  rbtreeptr = createTree(compareLT,
			 compareEQ,
			 NULL,
			 NULL,
			 NULL,
			 NULL);

   STORAGE(x,
	  (long*),
	  maxnum*sizeof(long));
  for (rec = maxnum; rec; rec--) 
    {
      a = rand()%5000;
      *(x++)=a;
      if ((t = search_node(rbtreeptr,
			   x-1,
			   ((rbtree_t *)rbtreeptr)->root)) != NULL) 
	{
	  removeNode(rbtreeptr,
		     t);
	  deleted++;
	} 
      else 
	{
	  addNode(rbtreeptr,x-1,
		  0);
	  inserted++;
	}
      test_red_black_properties(((rbtree_t *)rbtreeptr)->root,
				rbtreeptr);
    }
  printf("%d deleted\n",
	 deleted);
  printf("%d inserted\n",
	 inserted);
  printf("TEST OK\n");
}
#endif 
#endif
