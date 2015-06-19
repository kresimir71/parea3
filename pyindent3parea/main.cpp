#define RM2PAREA_LIBRARY_HEADER

#include "pyscan3parea/python.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

//#include "decorate.h"

namespace pyindent3parea_decorate{
  extern void scan_callback(long tok_id, char* tokentext, int tokentextlen);
}
int main( int argc,  char **argv){

  int iflag = 0; //indent
  int bflag = 0; //block
  int rflag = 0; //remove, implies -i
  int fflag = 0; //everywhere force given indent length(otherwise use -n as adviced indent length), implies -i
  char *nvalue = NULL; // indent length in spaces
  //  int index;
  int c;

  opterr = 0;
  while ((c = getopt (argc, argv, "ibfn:")) != -1)
    switch (c)
      {
      case 'i':
        iflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'f':
        bflag = 1;
        break;
      case 'n':
        nvalue = optarg;
        break;
      case '?':
        if (optopt == 'n')
          fprintf (stderr, "Option -%n requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
  //printf ("aflag = %d, bflag = %d, cvalue = %s\n",
  //        aflag, bflag, cvalue);

  //for (index = optind; index < argc; index++)
  //  printf ("Non-option argument %s\n", argv[index]);

  if (bflag || 1){
    python_specific_subscribe(2,pyindent3parea_decorate::scan_callback);
    //python_main_init(argc,argv);
    python_main_init(argc-optind+1,&argv[optind-1]);
  } else if (bflag || 1){
    
  } else if (bflag || 1){
  } else {
    std::cerr << "unrecognised options: see `info pyindent3parea`";
    exit (1);
  }
  //std::cerr << "ready";
  exit (0);

}
