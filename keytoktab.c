/**********************************************************************/
/* lab 1 DVG C01 - Driver OBJECT                                      */
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
/**********************************************************************/
/* type definitions                                                   */
/**********************************************************************/
typedef struct tab {
	char 	* text;
	int 	token;
	} tab;
	
/**********************************************************************/
/* data objects (tables)                                              */
/**********************************************************************/
static tab tokentab[ ] = {
        {"id", 	        id},
	{"number", 	number},
	{":=", 	        assign},
	{"undef", 	undef},
	{"predef", 	predef},
	{"tempty", 	tempty},
	{"error",        error},
	{"type",         typ},
	{"$",            '$'},
	{"(",            '('},
	{")",            ')'},
	{"*",            '*'},
	{"+",            '+'},
	{",",            ','},
	{"-",            '-'},
	{".",            '.'},
	{"/",            '/'},
	{":",            ':'},
	{";",            ';'},
	{"=",            '='},
	{"TERROR", 	nfound}
        };


static tab keywordtab[ ] = {
	{"program", 	program},
	{"input", 	input},
	{"output", 	output},
	{"var", 	var},
	{"begin", 	begin},
	{"end", 	end},
	{"boolean", 	boolean},
	{"integer", 	integer},
	{"real", 	real},
	{"KERROR", 	nfound}
	} ;
   
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Display the tables                                                 */
/**********************************************************************/
void p_toktab()
{  
   	int i = 0;
	printf("____________________\n");	
	printf("THE PROGRAM KEYWORDS\n");
	printf("____________________\n");	
	while(keywordtab[i].token != nfound)
	{
		printf("%10s  %5d\n", keywordtab[i].text, keywordtab[i].token);
		i++;
	} 

	i = 0;
	printf("____________________\n");	
	printf("THE PROGRAM TOKENS \n");
	printf("____________________\n");	
	while(tokentab[i].token != nfound){
	
		printf("%10s " "%6d\n", tokentab[i].text, tokentab[i].token);	
		i++;
	}
}

/**********************************************************************/
/* lex2tok - convert a lexeme to a token                              */
/**********************************************************************/
toktyp lex2tok(char * fplex)
{
   printf("\n *** TO BE DONE");  return 0;
   }

/**********************************************************************/
/* key2tok - convert a keyword to a token                             */
/**********************************************************************/
toktyp key2tok(char * fplex) {
   	int i = 0;
	while(keywordtab[i].token != nfound) {
		if(fplex != NULL && !strcmp(fplex, keywordtab[i].text))
   			printf("\n *** KEY2TOK: %d", keywordtab[i].token);

		i++;  
	} 
	return 0;
   }

/**********************************************************************/
/* tok2lex - convert a token to a lexeme                              */
/**********************************************************************/
char * tok2lex(toktyp ftok)
{

	int i = 0;
	while(keywordtab[i].token != nfound)
	{
		if(ftok == keywordtab[i].token)
		{
			return keywordtab[i].text;
		}
		i++;
	}

	i = 0;
	while(tokentab[i].token != nfound)
	{
		if(ftok == tokentab[i].token)
		{	
			return tokentab[i].text;
		}
		i++;
	}
	return 0;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/

