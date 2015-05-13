/*
*/

#define RM2PAREA_LIBRARY_HEADER


#include "python.h"
#include <iostream>


using namespace std;

void test_callback(long tok_id, char* tokentext, int tokentextlen){
  
  cout << tokentext;

}

int main( int argc,  char **argv)
{

  python_specific_subscribe(2,test_callback);
  python_main_init(argc,argv);

}

