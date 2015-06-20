
  class TokenRec{
  public:
    std::string text;
    int id;
  };

  std::list<TokenRec> TokenList;

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

  void scan_callback(long tok_id, char* tokentext, int tokentextlen){
  
    TokenRec NewTok;
    NewTok.id=tok_id;
    NewTok.text=std::string(tokentext,tokentextlen);
    TokenList.push_back(NewTok);
    //  std::cout << tokentext;
    int handle_token();
    if (handle_token()){
      std::cerr << "fatal error";
      exit (1);
    }
    if (tok_id==TOK_EXIT){
      printAllCleanStack();
      //std::cerr << "ready";
    }
  }
