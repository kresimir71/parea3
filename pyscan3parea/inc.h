#ifndef _INC_H
#define _INC_H
#include "appl.h"
     #include "math.h"
     #include "stdio.h"
     #include "rm1.h"
     #include "x_io1.h"
     #include "rbt.h"
     #include "rbt_shortcuts.h"
     #include "main.h"
#include "goals.h"
#include "debug2.h"

#if defined APPL_MAIN_APPLICATION_IDENTIFIER_PYTHON && APPL_MAIN_APPLICATION_IDENTIFIER_PYTHON!=0
#include "python.h"
#else
 error no application specified
#endif


#endif
