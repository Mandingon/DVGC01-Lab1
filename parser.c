/**********************************************************************/
/* lab 1 DVG C01 - Parser OBJECT                                      */
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
#include "keytoktab.h"               /* when the keytoktab is added   */
#include "lexer.h"                   /* when the lexer     is added   */
#include "symtab.h"                  /* when the symtab    is added   */
#include "optab.h"                   /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1
static int  lookahead=0;
static int  is_parse_ok=1;
void expr();
void get_prog();
void pbuffer();
/**********************************************************************/
/* RAPID PROTOTYPING - simulate the token stream & lexer (get_token)  */
/**********************************************************************/
/**********************************************************************/
/* Simulate the token stream for a given program                      */
/**********************************************************************/
static int tokens[] = {program, id, '(', input, ',', output, ')', ';',
               '$' };

/**********************************************************************/
/*  Simulate the lexer -- get the next token from the buffer          */
/**********************************************************************/
/*static int pget_token()
{  
   static int i=0;
   if (tokens[i] != '$') return tokens[i++]; else return '$';
   }*/

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
   if(DEBUG) printf("\n --------In match expected: %10s, found: %10s", tok2lex(t), tok2lex(lookahead));
 
  if (lookahead == t) lookahead = get_token();

   else {
      is_parse_ok=0;
      printf("\n *** Unexpected Token: expected: %10s found: %10s (in match)", tok2lex(t), tok2lex(lookahead));
      }
   }

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/
static toktyp  operand() 
{
	if(DEBUG) printf("\n *** In operand");

	if(lookahead == id)
	{ 
		if(!find_name(get_lexeme())) 
		{
			printf("\nSEMANTCIC: ID NOT DECLARED: %s", get_lexeme());
			is_parse_ok = 0;
		}
		
		toktyp tt = get_ntype(get_lexeme());
		(match(id);
		return tt;
	}
	
	else if(lookahead == number)
	{
		match(number);
		return integer;
	}
	
	else 
	{
		printf("\n SYNTAX: OPERAND EXPECTED");
		return errror;
	}
}
static toktyp factor() 
{
	if(DEBUG) printf("\n *** In factor");
	toktyp tt; 
	if(lookahead == '(') {
		match('(');
	 	tt = expr();
		match(')');
	}
	else 
		tt = operand();

return tt;
}
void term()
{

	if(DEBUG) printf("\n *** In term");
	toktyp tt = factor();
	if(lookahead == '*') {
		match('*');
		return get_otype('*', term(), tt);
		
	}
return tt;
}
void expr()
{

	if(DEBUG) printf("\n *** In expr");
	toktyp tt = term();
	if(lookahead == '+') {
		match('+');
		return get_otype('+', expr(), tt);
		
	}
return tt;
}
void assign_stat() 
{
	
	if(DEBUG) printf("\n *** In assign_ stat");
	if(!find_name(get_lexeme()))
	{
		addv_name(get_lexeme());
	}
	
	match(id);
	match(assign);
	expr();
}
void stat() {
	if(DEBUG) printf("\n *** In stat");
	assign_stat();
}
void stat_list() {
	if(DEBUG) printf("\n *** In stat_list");
	stat();
	if(lookahead == ';') {
		match(';');
		stat_list();
	}
}
void stat_part() {
	if(DEBUG) printf("\n *** In stat_part");
	match(begin);
	stat_list();
	match(end);
	match('.');
}
void type() {
	if(lookahead == integer)
	{	
		setv_type(integer);
		match(integer);
	}
	else if(lookahead == real)
	{
		setv_type(real);
		match(real);
	}
	else if(lookahead == boolean)
	{	
		setv_type(boolean);
		match(boolean); 
	}
/*	else 
	{
		setv_type(error)
		printf(" \n"
	}*/
}
void id_list() {
	 
	if(!find_name(get_lexeme()))
	{
		addv_name(get_lexeme());	
	}
	match(id);
	if(lookahead == ',') {
		match(',');
		id_list();
	}
}
void var_dec() {
	id_list();
	match(':');
	type();
	match(';');
}
void var_dec_list() {
	var_dec();
	if(lookahead == id)
		var_dec_list();
}
void var_part() {
	
	if(DEBUG) printf("\n *** In var_part");
	match(var);
	var_dec_list();
}

static void program_header()
{
   if (DEBUG) printf("\n *** In  program_header");
   match(program); addp_name(get_lexeme()); match(id); match('('); match(input);
   match(','); match(output); match(')'); match(';');
   }
   
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
   if (DEBUG) printf("\n *** In  parser");
   get_prog();
   pbuffer();
   lookahead = get_token();       // get the first token
   program_header();               // call the first grammar rule
   var_part();			   // call the 2nd grammar rule
   stat_part();			   // call the 3rd grammar rule
   p_symtab();
   return is_parse_ok;             // status indicator
   }

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/

