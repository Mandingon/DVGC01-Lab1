/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
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
#define BUFSIZE 1024
#define LEXSIZE   30
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int  pbuf  = 0;               /* current index program buffer  */
static int  plex  = 0;               /* current index lexeme  buffer  */

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/
/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/

void get_prog() {

	int  i = 0;

    	while ((buffer[i]=fgetc(stdin))!=EOF)
	{
		 i++;
	}
	buffer[i] = '$';
   	buffer[i+1]='\0';
     
}     

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/  

 void pbuffer() {
   printf("\n");
   printf("______________________________________________________________");
   printf("\nTHE PROGRAM TEXT\n");
   printf("______________________________________________________________");
   printf("\n%s", buffer );
  // printf("\n --------- end of file text \n ");
      
}

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char()
{   
	lexbuf[plex] =	buffer[pbuf];
	plex++;
	pbuf++;
   }

/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/
int get_token(){

	memset(lexbuf, 0, sizeof(lexbuf));
	

	while(1)
	{

		if(isalpha(buffer[pbuf]))
		{
			while(isalnum(buffer[pbuf])) 
			{
				get_char();
			}
				
				plex = 0;
				return key2tok(lexbuf);
			
		}
		else if(isdigit(buffer[pbuf])) 
		{
			while(isdigit(buffer[pbuf])) 
			{
				get_char();
			}
			plex = 0;
			return number;
		}
		else if(isspace(buffer[pbuf]))
		{
			pbuf++;
			memset(lexbuf,0,sizeof(lexbuf));
			continue;
		}
		else
		{
			if(buffer[pbuf] == ':' && buffer[pbuf+1] == '=') {
				get_char();
				continue;
			}
			get_char();
			plex = 0;
			return lex2tok(lexbuf);
			
		}
	}
	
	plex = 0;

	return error;

}

/**********************************************************************/
/* Return a lexeme                                                    */
/**********************************************************************/
char * get_lexeme()
{	

	return  lexbuf;
   }

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
