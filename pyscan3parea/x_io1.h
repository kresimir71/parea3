/*-----------------begin*/
/*io1.h*/
#ifndef _IO1_H
#define _IO1_H
#include "rm1.h"
#include "col.h"
#include "misc.h"
#include "goals.h"

#include "stdio.h"


#include "main.h"
#ifndef TOK_TO_BE_PRESENT_IN_ANY_GRAMMAR
#include "x_rm1.tab.h"
#endif
extern int number_of_chars_to_read_for_flex;
/*the flex states*/
//DG_FLEX_STATE_AND_POSITION
/*BEGIN flex DELIMITER*/
extern int mainscannerstate;

/*END flex DELIMITER*/

/*BEGIN define DELIMITER*/
#define IFDEFXX "01"
/*END define DELIMITER*/
#endif
/*-----------------end*/
