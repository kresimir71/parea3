 /*strip python program of comment-braces */ 

#define RM2PAREA_LIBRARY_HEADER

#include <stdlib.h>
#include "pyscan3parea/python.h"
#include "pyscan3parea/x_rm1.tab.h"
#include <iostream>
#include <list>

namespace pyindent3parea_strip {
  class TokenRec{
  public:
    std::string text;
    int id;
  };

  std::list<TokenRec> TokenList;
  int NumberOfDedents=0; /*number of DEDENTS in the current burst, initially zero */
  
  void printAllCleanStack(){
    std::list<TokenRec>::iterator iii=TokenList.begin();
    for ( ; iii!=TokenList.end();iii++){
      std::cout << iii->text;
    }
    TokenList.clear();
  }

  std::list<TokenRec>::reverse_iterator searchBackToken(int id){
    std::list<TokenRec>::reverse_iterator iii=TokenList.rbegin();
    for ( ; iii!=TokenList.rend();iii++){
      if (id==iii->id){
	break;
      }
    }
    return iii;
  }

  void insertTokenRec(std::list<TokenRec>::reverse_iterator succ, int id, std::string txt){
    TokenRec temp;
    temp.id=id;
    temp.text=txt;
    TokenList.insert((++succ).base(),temp);
  }

  bool correctBracesContruct(std::string &txt){
    for (std::string::iterator iii = txt.begin();iii!=txt.end();iii++){
      if (iii == txt.begin() && *iii !='#'){
	break; // never!?
      }
      if (iii == txt.begin() && *iii =='#'){
	continue; // always *iii =='#'
      }
      if (*iii == '}'){
	continue;
      }
      if (iii-1 == txt.begin() && *iii !='}'){
	break;
      } else if (*iii !='}'){
	std::string tmp = std::string("#")+std::string(NumberOfDedents,'}');
	txt.replace(txt.begin(),iii,tmp);
	return true; //correcting success!
      }
      break;
    }
    return false; //correcting failed
  }
  int handle_token(){
    std::list<TokenRec>::reverse_iterator iii;
    iii=TokenList.rbegin();
    std::list<TokenRec>::reverse_iterator TokNL;
    std::list<TokenRec>::reverse_iterator TokBeforeNL;

    if (TOK_INDENT==iii->id){
      TokNL = searchBackToken(TOK_NEWLINE);
      if (TokNL==TokenList.rend()){
	//fatal error, misplaced NL, Before TOK_NEWLINE there has to be some tokens, because TOK_INDENT
	return 1;
      }
      TokBeforeNL=TokNL;
      TokBeforeNL++;
      if (TokBeforeNL==TokenList.rend()){
	//fatal error, misplaced NL, Before any TOK_NEWLINE there has to be some tokens, because TOK_INDENT
	return 1;
      }
    
      if(TOK_COMMENT!=TokBeforeNL->id){
	//insert token between TokBeforeNL and TokNL with id=TOK_COMMENT, text = " #{"
	insertTokenRec(TokNL,TOK_COMMENT," #{");
      }else{
	if(std::string(TokBeforeNL->text,0,2)=="#{"){
	  //already there, nothing todo
	}else{
	  //prepend TokBeforeNL.text with "#{"
	  TokBeforeNL->text=std::string("#{")+TokBeforeNL->text;
	}
      }
      //printAllCleanStack();
    }else if(TOK_DEDENT==iii->id){
      NumberOfDedents++;
    }else{
      // no indent, no dedent
      if (NumberOfDedents){
	TokNL = searchBackToken(TOK_NEWLINE);
	if (TokNL==TokenList.rend()){
	  //fatal error, misplaced NL, Before any TOK_NEWLINE there has to be some tokens
	  return 1;
	}
	TokBeforeNL=TokNL;
	TokBeforeNL++;
	if(TOK_COMMENT!=TokBeforeNL->id){
	  //insert token between TokBeforeNL and TokNL with id=TOK_COMMENT, text = "#}...}", number of braces equals NumberOfDedents
	  insertTokenRec(TokNL,TOK_COMMENT,std::string(" #") + std::string(NumberOfDedents,'}') + std::string(""));
	}else{
	  if(correctBracesContruct(TokBeforeNL->text)){ // any positive number of braces in "#}...}..."
	    //replace with "#}...}...", number of braces equals NumberOfDedents (already done in function)
	  }else{
	    //prepend TokBeforeNL.text with "#}...}", number of braces equals NumberOfDedents
	    TokBeforeNL->text=std::string("#")+std::string(NumberOfDedents,'}')+TokBeforeNL->text;

	  }
	}
	//printAllCleanStack();
      }
      NumberOfDedents=0;
    }
    return 0;
  }

  void scan_callback(long tok_id, char* tokentext, int tokentextlen){
  
    TokenRec NewTok;
    NewTok.id=tok_id;
    NewTok.text=std::string(tokentext,tokentextlen);
    TokenList.push_back(NewTok);
    //  std::cout << tokentext;
    if (handle_token()){
      std::cerr << "fatal error";
      exit (1);
    }
    if (tok_id==TOK_EXIT){
      printAllCleanStack();
      //std::cerr << "ready";
    }
  }

}
