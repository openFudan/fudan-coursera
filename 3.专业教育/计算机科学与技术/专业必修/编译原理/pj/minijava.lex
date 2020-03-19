%{
#include "stand.h"
#include "util.h"
#include "error.h"
#include "absyn.h"
#include "state.h"
#include "minijava.tab.h"

int yywrap(void){
    state_pos = 1;
    return 1;
}

#define ADJ do{\
    token_pos = state_pos;\
    state_pos += yyleng;\
} while (0)
#define RECORD_ID do{\
    last_token_len[0] = last_token_len[1];\
    last_token_len[1] = yyleng;\
    last_token_pos[0] = last_token_pos[1];\
    last_token_pos[1] = token_pos;\
}while(0)
#define MAX_LENGTH 2048

#define ADJ_STR do{\
    state_pos += yyleng;\
} while(0)
#define ERROR(...) do{\
    record_error(token_pos,yyleng);\
    show_error(__VA_ARGS__);\
}while(0)
int com_depth;
char string_buf [MAX_LENGTH];
char *string_ptr;
;
%}
%x string comment1 comment2
%%
<string>{

  \"  {
    ADJ_STR;
    *string_ptr='\0';
    if (string_buf[0] != '\0')
      yylval.sval=String(string_buf);
    else
      yylval.sval=String("[EMPTY]");
    BEGIN(INITIAL);
    RECORD_ID;
    return STRING;
  }

  \\[0-9]{3} {
    ADJ_STR;
    int result = atoi(yytext + 1);
    if (result > 0xff) {
        ERROR("illegal character\n");
        continue;
    }
    *string_ptr++ = result;
  }

  \\n     {ADJ_STR; *string_ptr++ = '\n';}
  \\t     {ADJ_STR; *string_ptr++ = '\t';}
  \\\"    {ADJ_STR; *string_ptr++ = '\"';}
  \\\\    {ADJ_STR; *string_ptr++ = '\\';}
  \\\^[\0-\037]   {
    ADJ_STR;
    *string_ptr++ = yytext[2];
  }

  \\[ \t\n\r]+\\ {
    ADJ_STR;
    char *yytextptr = yytext;
    while (*yytextptr != '\0')
    {
      if (*yytextptr == '\n')
        state_newline();
      ++yytextptr;
    }
  }

  \\. {ADJ_STR; ERROR("illegal escape char\n");}

  \n  {
    ADJ_STR;
    state_newline();
    ERROR("string terminated with newline\n");
    continue;
  }

  [^\\\n\"]+        {
    ADJ_STR;
    char *yptr = yytext;
    while (*yptr)
      *string_ptr++ = *yptr++;
  }
}

<*>"/*" {
    ADJ;
    com_depth++;
    BEGIN(comment1);
}
<comment1>{
    \n  {
        ADJ;
        state_newline();
    }
    "*/"  {
        ADJ;
        --com_depth;
        if(!com_depth) BEGIN(INITIAL);
    }
    .  {
        ADJ;
    }
}
<*>"//" {
    ADJ;
    BEGIN(comment2);
}
<comment2>{
    \n {
        ADJ;
        state_newline();
        BEGIN(INITIAL);
    }
    . {
        ADJ;
    }
}
<INITIAL>{
    (" "|"\t")  {ADJ;} 
    "\n"	  {ADJ; state_newline();}
    "," {ADJ;RECORD_ID;return COMMA;}
    ";" {ADJ;RECORD_ID;return SEMICOLON;}
    "(" {ADJ;RECORD_ID;return LPAREN;}
    ")" {ADJ;RECORD_ID;return RPAREN;}
    "{" {ADJ;RECORD_ID;return LBRACE;}
    "}" {ADJ;RECORD_ID;return RBRACE;}
    "[" {ADJ;RECORD_ID;return LBRACK;}
    "]" {ADJ;RECORD_ID;return RBRACK;}
    "=" {ADJ;RECORD_ID;return ASSIGN;}
    "!" {ADJ;RECORD_ID;return REVERSE;}
    "<" {ADJ;RECORD_ID;return LT;}
    ">" {ADJ;RECORD_ID;return GT;}
    "&&" {ADJ;RECORD_ID;return AND;}
    "+" {ADJ;RECORD_ID;return PLUS;}
    "-" {ADJ;RECORD_ID;return MINUS;}
    "*" {ADJ;RECORD_ID;return TIMES;}
    "." {ADJ;RECORD_ID;return DOT;}
    class {ADJ;RECORD_ID;return CLASS;}
    void {ADJ; RECORD_ID;return VOID;}
    public {ADJ;RECORD_ID;return PUBLIC;}
    static {ADJ;RECORD_ID;return STATIC;}
    main {ADJ;RECORD_ID;return MAIN;}
    extends {ADJ;RECORD_ID;return EXTENDS;}
    return {ADJ;RECORD_ID;return RETURN;}
    int {ADJ; RECORD_ID;return INT_ID;}
    boolean {ADJ;RECORD_ID;return BOOLEAN_ID;}
    String {ADJ;RECORD_ID;return STRING_ID;}
    if {ADJ;RECORD_ID;return IF;}
    else {ADJ;RECORD_ID;return ELSE;}
    while {ADJ;RECORD_ID;return WHILE;}
    "System.out.println" {ADJ;RECORD_ID;return PRINT;}
    length {ADJ;RECORD_ID;return LENGTH;}
    true {ADJ;RECORD_ID;return TRUE;}
    false {ADJ;RECORD_ID;return FALSE;}
    new {ADJ;RECORD_ID;return NEW;}
    this {ADJ;RECORD_ID;return THIS;}
    
    [0-9]+	 {ADJ; yylval.ival=atoi(yytext); RECORD_ID;return INT;}
    [a-zA-Z][a-zA-Z0-9_]* {ADJ; yylval.sval=String(yytext); RECORD_ID;return ID;}
    
    \"   {
        ADJ;
        string_ptr = string_buf;
        BEGIN(string);
    }
}

. {
    ADJ;
    ERROR("illegal token '%s'\n",yytext);
}

