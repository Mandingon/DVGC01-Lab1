/**********************************************************************/
/* lab 1 DVG C01 - Operator Table OBJECT                              */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define NENTS 4

static int optab[][NENTS] = {
   {'+', integer, integer, integer},
   {'+', real,    real,    real},
   {'+', integer, real,    real},
   {'+', real,    integer, real},
   {'*', integer, integer, integer},
   {'*', real,    real,    real},
   {'*', integer, real,    real},
   {'*', real,    integer, real},
   {'$', undef,   undef,   undef}
   };

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
static void p_oprow(int row)
{
   printf(" %10c, %10s, %10s, %10s \n ", optab[row][0], tok2lex(optab[row][1]), tok2lex(optab[row][2]), tok2lex(optab[row][3]));
}

static void p_hr() { printf("________________________________________________________\n "); }

static void p_op_header()
{
   p_hr();
   printf("THE OPERATOR TABLE\n");
   p_hr();
   printf("   operator        arg1        arg2      result\n");
   p_hr();
}
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* display the op tab                                                 */
/**********************************************************************/
void p_optab()
{
   p_op_header();
   int i;
   for(i = 0; optab[i][0] != '$'; i++)
	{
     	   p_oprow(i);
  	}

   p_hr();
}
/**********************************************************************/
/* return the type of a binary expression op arg1 arg2                */
/**********************************************************************/
int get_otype(int op, int arg1, int arg2)
{  
   int i;

   for(i = 0; optab[i][0] != '$'; i++)	
        { 
	  if(op == optab[i][0] && arg1 == optab[i][1] && arg2 == optab[i][2])
	  {		
             return optab[i][3];
	  }
	}
return undef;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
