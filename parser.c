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
#define DEBUG 0
static int  lookahead=0;
static int  is_parse_ok=1;
static toktyp expr();
void get_prog();
void pbuffer();
/**********************************************************************/
/* RAPID PROTOTYPING - simulate the token stream & lexer (get_token)  */
/**********************************************************************/
/**********************************************************************/
/* Simulate the token stream for a given program                      */
/**********************************************************************/
/*static int tokens[] = {program, id, '(', input, ',', output, ')', ';',
               '$' };
*/
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
   if(DEBUG) printf("\n --------In match expected: %s, found: %s", tok2lex(t), tok2lex(lookahead));
 
   if (lookahead == t) lookahead = get_token();

   else 
   {
      is_parse_ok=0;
	if(!strcmp(tok2lex(t),"id")) 
	{
		printf("\nSYNTAX: ID expected found %s ",  get_lexeme());
	}
	else
	{
     		printf("\nSYNTAX: Symbol expected %s found %s ", tok2lex(t), get_lexeme());
	}     
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
			printf("\nSEMANTIC: ID NOT declared: %s", get_lexeme());
			is_parse_ok = 0;
		}
		
		toktyp tt = get_ntype(get_lexeme());
		match(id);
		return tt;
	}
	
	else if(lookahead == number)
	{
		match(number);
		return integer;
	}
	
	else 
	{
		printf("\nSYNTAX: Operand expected");
		return error;
	}
}	
static toktyp factor() 
{
	if(DEBUG) printf("\n*** In factor");
	toktyp tt; 
	if(lookahead == '(') {
		match('(');
	 	tt = expr();
		match(')');
	}
	else{ 
		tt = operand();
	}
return tt;
}
static toktyp term()
{

	if(DEBUG) printf("\n*** In term");
	toktyp tt = factor();
	if(lookahead == '*') {
		match('*');
		return get_otype('*', term(), tt);
		
	}
return tt;
}
static toktyp expr()
{

	if(DEBUG) printf("\n*** In expr");
	toktyp tt = term();
	if(lookahead == '+') {
		match('+');
		return get_otype('+',expr(), tt);
		
	}
return tt;
}
static void assign_stat() 
{
	if(DEBUG) printf("\n*** In assign_ stat");
	toktyp tt = get_ntype(get_lexeme());
	
	if(!find_name(get_lexeme()) && lookahead == id) 
	{
		printf("\nSEMANTIC: ID NOT declared: %s ", get_lexeme()); 
		is_parse_ok = 0;
	}
	
	if(lookahead == id) 
	{
		match(id);
	}

	else 
	{
		printf("\nSYNTAX: ID expected found %s", get_lexeme());
	}

	match(assign);	
	toktyp tt2 = expr();

	if(tt == undef) 
	{
		tt = error;
	}
	if(tt != tt2) 
	{
		printf("\nSEMANTIC: Assign types: %s := %s ", tok2lex(tt), tok2lex(tt2));
		is_parse_ok = 0;
	}
}
static void stat() {
	if(DEBUG) printf("\n*** In stat");
	assign_stat();
}
static void stat_list() {
	if(DEBUG) printf("\n*** In stat_list");
	stat();
	if(lookahead == ';') {
		match(';');
		stat_list();
	}
}
static void stat_part() {
	if(DEBUG) printf("\n*** In stat_part");
	match(begin);
	stat_list();
	match(end);
	match('.');
}
static void type() {
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
	else 
	{
		setv_type(error);
		printf("\nSYNTAX: Type name expected found  %s ", get_lexeme());
	}
}
static void id_list() {
	if(DEBUG) printf("\n*** In id_list");
	
	if(lookahead == id) 
	{ 
		if(!find_name(get_lexeme()))
		{
			addv_name(get_lexeme());	
		}
		else 
		{
			printf("\nSEMANTIC: ID already declared: %s ", get_lexeme()); 
			is_parse_ok = 0;
		}
			match(id);
		
	}
	
	else
	{
		printf("\nSYNTAX: ID expected found %s ", get_lexeme()); 
		is_parse_ok = 0;
	}
	if(lookahead == ',') {
		match(',');
		id_list();
	}
}
static void var_dec() {
	if(DEBUG) printf("\n*** In var_dec");
	id_list();
	match(':');
	type();
	match(';');
}
static void var_dec_list() {
	if(DEBUG) printf("\n*** In var_dec_list");
	var_dec();
	if(lookahead == id)
		var_dec_list();
}
static void var_part() {
	
	if(DEBUG) printf("\n*** In var_part");
	match(var);
	var_dec_list();
}

static void program_header()
{
   if (DEBUG) printf("\n*** In  program_header");
   match(program);
	 if(lookahead != id) addp_name("???");
	 else
	 {	
		 addp_name(get_lexeme());	
         }
	 
	 match(id); match('('); match(input); match(','); match(output); match(')'); match(';');
         
   }
   
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
   if (DEBUG) printf("\n*** In  program");
   get_prog();
   pbuffer();
   lookahead = get_token();       // get the first token
   
   if(lookahead == '$')
   {
	printf("\nWARNING: Input file is empty");
	is_parse_ok = 0;
   }
   
   else
   {
   	program_header();               // call the first grammar rule
   	var_part();			// call the 2nd grammar rule
   	stat_part();			// call the 3rd grammar rule

   	if(lookahead != '$') 
	{
		printf("\nSYNTAX: Extra symbols after end of parse!\n");
		while(lookahead != '$') 
		{
			printf("%s ", get_lexeme());
			match(lookahead);
		}
		is_parse_ok = 0;
	}
   }

   if(is_parse_ok) 
   {
   	printf("\nParse successful!");
   }
   p_symtab();
//   p_optab();
   return is_parse_ok;             // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/

