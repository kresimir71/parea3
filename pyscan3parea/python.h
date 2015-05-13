#ifndef PYTHON_H
#define PYTHON_H

#if defined(__cplusplus)
extern "C" {
#endif

void python_main_init(int argc,char**argv);

#ifndef RM2PAREA_LIBRARY_HEADER

extern parser_master_t* misc_parser;

#define MAIN_INIT(argc,argv)\
python_main_init(argc,argv)

#define MISC_MACRO_AFTER_FLEX_GET_CHAR()

//params ar of the form '(MISC_MASTER,UNUSED_TOK_EXIT,&$$,2,$1)'
#define MISC_MACRO_AFTER_PRODUCTION \
{\
   if (count>1){/*if there are any dependancies*/\
      parser_master_t*p=(dep[0])->text_heap_heap->ps01_parser;\
      if(!xstring_aa_value_sint(p->connecting_nonterminal,(dep[0])->id)&&(dep[0])->id>TERMINAL_MAX_MIN_NONTERMINAL){list_n(dep[0]);}/*don't list terminals,don't list connecting nonterrminals*/\
   }\
}

void python_stop(parser_master_t*m);//m known?

#endif


// SPECIFIC PYTHON

typedef void (*python_token_callback_type) (long tok_id, char* tokentext, int tokentextlen);

void python_specific_subscribe(long mode, python_token_callback_type callback);

// END SPECIFIC PYTHON



#if defined(__cplusplus)
}
#endif

#endif
