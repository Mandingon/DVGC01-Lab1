/**********************************************************************/
/* lab 1 DVG C01 - Happy Hacker version  Donald Ross  060422          */
/**********************************************************************/

/***********************************************************************/
/* Include files                                                       */
/***********************************************************************/
#include <stdio.h>
#define DEBUG 1

void expr();
/**********************************************************************/
/* define tokens + keywords                                           */
/**********************************************************************/
enum tvalues { program = 257, id, input, output, var, integer, begin, assign, number, end };

/**********************************************************************/
/* Global Data Objects                                                */
/**********************************************************************/

int  lookahead=0;
int  is_parse_ok=1;
int tokens[] = {program, id, '(', input, ',', output, ')', ';', 
		var, id, ',', id, ',', id, ':', integer, ';',
		id, ',', id, ',', id, ':', integer, ';',
		begin,
		id, assign, id, '+', id, '*', number, ';',
		id, assign, id, '+', id, '*', number,
		end, '.', '$' };

/**********************************************************************/
/* Get the nexttoken from the buffer  (simulate the lexer)            */
/**********************************************************************/

int get_token() {
  
   static int i=0;
   if (tokens[i] != '$') return tokens[i++]; else return '$';
   }

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/

void match(int t) {

   if(DEBUG) printf("\n --------In match expected: %3d, found: %3d", 
                     t, lookahead);
   if (lookahead == t) lookahead = get_token();
   else {
      is_parse_ok=0;
      printf("\n *** Unexpected Token: expected: %3d found: %3d",
              t, lookahead);
      }
   }

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/

void program_header() {

   if (DEBUG) printf("\n *** In  program_header");
   match(program); match(id); match('('); match(input);
   match(','); match(output); match(')'); match(';');
   }
void operand() {
	if(lookahead == id) 
		match(id);
	else if(lookahead == number)
		match(number);

}
void factor() {
	if(lookahead == '(') {
		match('(');
		expr();
		match(')');
	}
	else 
		operand();
}
void term() {
	factor();
	if(lookahead == '*') {
		match('*');
		term();
	}
}
void expr() {
	term();
	if(lookahead == '+') {
		match('+');
		expr();
	}

}
void assign_stat() {
	match(id);
	match(assign);
	expr();
}
void stat() {
	assign_stat();
}
void stat_list() {
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
		match(integer);
/*	else if(lookahead == real)
		match(real);
	else if(lookahead == boolean)
		match(boolean); */
}
void id_list() {
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

int prog() {

   if (DEBUG) printf("\n *** In  program");
   lookahead = get_token();        // get the first token
   program_header();               // call the first grammar rule
   var_part();			   // call the 2nd grammar rule
   stat_part();			   // call the 3rd grammar rule
   return is_parse_ok;             // status indicator
   }
/**********************************************************************/
/* The main function (the driver)                                     */
/**********************************************************************/

int main() {   
   return prog() ? printf(" \n Parse Successful! \n")
                 : printf(" \n Parse Failed! \n");
   }

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
