%{
#include "stand.h"
#include "util.h"
#include "sym.h"
#include "absyn.h"
#include "error.h"
#include "state.h"
extern int yyleng;
extern int yychar;
extern string yytext;
int yylex();
A_goal root;
/* record error */
void yyerror(char const *msg){
    record_error(token_pos,yyleng);
    show_error(msg);
    err->kind = E_unknown;
}
/*
#define ERROR_NO_SEMICOLON() do{\
    record_error(last_token_pos[0]+last_token_len[0],0);\
    show_error(E_NO_SEMICOLON,err->given);\
}while(0)

#define ERROR_NO_RETURN() do{\
    record_error(token_pos,yyleng);\
    show_error(E_NO_RETURN,err->given);\
}while(0)

#define ERROR_NO_MATCH() do{\
    record_error(token_pos,yyleng);\
    show_error(E_NO_MATCH,err->given);\
}while(0)
*/
#define ERROR_NO_SEMICOLON() 
#define ERROR_NO_RETURN()
#define ERROR_NO_MATCH()

%}
%define parse.error verbose
%define parse.lac full
%union {
    int pos;
    int ival;
    string sval;
    
    A_goal goal;
    A_main main;
    A_class class;
    A_class_list class_list;

    A_method method;
    A_method_list method_list;

    A_arg_dec arg_dec;
    A_arg_dec_list arg_dec_list;

    A_var_dec var_dec;
    A_var_dec_list var_dec_list;

    A_type type;

    A_stm stm;
    A_stm_list stm_list;

    A_exp exp;
    A_exp_list exp_list;
}
%token <sval> ID STRING
%token <ival> INT

%token 
    CLASS PUBLIC STATIC VOID LPAREN RPAREN LBRACK RBRACK 
    LBRACE RBRACE EXTENDS SEMICOLON BOOLEAN IF 
    WHILE PRINT LENGTH DOT THIS NEW ASSIGN PLUS MINUS TIMES 
    DIVIDE EQ LE LT GE GT AND REVERSE TRUE FALSE ELSE COMMA MAIN 
    RETURN INT_ID BOOLEAN_ID STRING_ID UMINUS

%type <goal> goal
%type <main> main
%type <class> class
%type <class_list> classes
%type <method> method
%type <method_list> methods
%type <arg_dec> arg_dec arg_dec_next
%type <arg_dec_list>arg_dec_nexts arg_dec_next_more arg_decs
%type <var_dec> var
%type <var_dec_list> vars
%type <type> type
%type <stm> stm stm_sem
%type <stm_list> stms
%type <exp> exp exp_next return
%type <exp_list> exps exp_nexts exp_next_more

/* 先执行的排在下面*/
%nonassoc LT AND
%left PLUS MINUS
%left TIMES
%left UMINUS

%right REVERSE
%left LBRACK
%left DOT
%start program

%%

program: goal {root = $1;}
    ;

goal: main classes { $$ = A_goal_init($1,$2);}
    ;

return: RETURN exp SEMICOLON { $$ = $2;}
/*    | RETURN error {} */
    | RETURN exp error { }
    ;

main: CLASS ID LBRACE PUBLIC STATIC VOID MAIN LPAREN STRING_ID LBRACK RBRACK ID RPAREN LBRACE stm RBRACE RBRACE {$$ = A_main_init(S_symbol($2),S_symbol($12),$15);}
    ;

classes: {$$ = A_class_list_init_null();}
    | class classes { $$ = A_class_list_init_classes($1,$2);}
    | error {}
    ;

class: CLASS ID LBRACE vars methods RBRACE { $$ = A_class_init(S_symbol($2),NULL,$4,$5);}
    | CLASS ID EXTENDS ID LBRACE vars methods RBRACE { $$ = A_class_init(S_symbol($2),S_symbol($4),$6,$7);}
    ;
methods: { $$ = A_method_list_init_null();}
    | method methods {$$ = A_method_list_init_methods($1,$2);}
    ;

method: PUBLIC type ID LPAREN arg_decs RPAREN LBRACE stms return RBRACE {$$ = A_method_init($2,S_symbol($3),$5,$8,$9);}
    ;

arg_dec_next: COMMA type ID {$$ = A_arg_dec_init($2,S_symbol($3));}

arg_dec_nexts: {$$ = A_arg_dec_list_init_null();}
    | arg_dec_next arg_dec_nexts {$$ = A_arg_dec_list_init_arg_decs($1,$2);}
    ;

arg_dec_next_more: arg_dec_next arg_dec_nexts {$$ = A_arg_dec_list_init_arg_decs($1,$2);}
    ;

arg_dec: type ID { $$ = A_arg_dec_init($1,S_symbol($2));}
    ;

/* arg_decs mean 0 ~ N arg dec */
arg_decs: arg_dec arg_dec_next_more {$$ = A_arg_dec_list_init_arg_decs($1,$2);}
    | arg_dec {$$ = A_arg_dec_list_init_arg_dec($1);}
    | {$$ = A_arg_dec_list_init_null();}
    | error{}
    ;

vars: {$$ = A_var_dec_list_init_null();}
    | var vars {$$ = A_var_dec_list_init_vars($1,$2);}
    | error{}
    ;

var: type ID SEMICOLON { $$ = A_var_dec_init($1,S_symbol($2));}
    | type ID error {ERROR_NO_SEMICOLON();}
    ;

type: INT_ID {$$ = A_type_init_int();}
    | STRING_ID {$$ = A_type_init_string();}
    | BOOLEAN_ID {$$ = A_type_init_boolean();}
    | INT_ID LBRACK RBRACK {$$ = A_type_init_array();}
    | ID {$$ = A_type_init_sym(S_symbol($1));}
    ;

stms: {$$ = A_stm_list_init_null();}
    | stm stms {$$ = A_stm_list_init_stms($1,$2);}
    ;

stm_sem:
      PRINT LPAREN exp RPAREN {$$ = A_stm_init_print($3);}
    | ID ASSIGN exp {$$ = A_stm_init_assign(S_symbol($1),$3);}
    | ID LBRACK exp RBRACK ASSIGN exp { $$ = A_stm_init_sub(S_symbol($1),$3,$6);}
    ;

stm: LBRACE stms RBRACE {$$ = A_stm_init_stmlist($2);}
    | IF LPAREN exp RPAREN stm ELSE stm {$$ = A_stm_init_cond($3,$5,$7);}
    | WHILE LPAREN exp RPAREN stm { $$ = A_stm_init_loop($3,$5);}
    | var {$$ = A_stm_init_var($1);}
    | stm_sem SEMICOLON { $$ = $1;}
    ;

exp:  ID { $$ = A_exp_init_id(S_symbol($1));}
    | INT { $$ = A_exp_init_intval($1);}
    | TRUE { $$ = A_exp_init_boolval(true);}
    | FALSE { $$ = A_exp_init_boolval(false);}
    | THIS { $$ = A_exp_init_this();}
    | NEW ID LPAREN RPAREN {$$ = A_exp_init_newid(S_symbol($2));}
    | NEW INT_ID LBRACK exp RBRACK { $$ = A_exp_init_array($4);}
    | REVERSE exp { $$ = A_exp_init_reverse($2);}
    | LPAREN exp RPAREN {$$ = A_exp_init_exp($2);}
    | exp PLUS exp %prec PLUS { $$ = A_exp_init_op($1,A_plus,$3);}
    /* DONE: not support -132 */
    | MINUS exp %prec UMINUS{ $$ = A_exp_init_uminus($2);}
    | exp MINUS exp %prec MINUS { $$ = A_exp_init_op($1,A_minus,$3);}
    | exp TIMES exp %prec TIMES { $$ = A_exp_init_op($1,A_times,$3);}
    | exp AND exp %prec AND { $$ = A_exp_init_op($1,A_and,$3);}
    | exp LT exp %prec LT { $$ = A_exp_init_op($1,A_lt,$3);}
    | exp LBRACK exp RBRACK { $$ = A_exp_init_sub($1,$3);}
    | exp DOT LENGTH { $$ = A_exp_init_length($1);}
    /* DONE: only suport no arg_decs */
    | exp DOT ID LPAREN exps RPAREN { $$ = A_exp_init_method($1,S_symbol($3),$5);}
    ;

exp_next: COMMA exp {$$ = $2;}

exp_nexts: {$$ = A_exp_list_init_null();}
    | exp_next exp_nexts {$$ = A_exp_list_init_exps($1,$2);}
    ;

exp_next_more: exp_next exp_nexts {$$ = A_exp_list_init_exps($1,$2);}
    ;

/* exps mean 0 ~ N arg */
exps: exp exp_next_more {$$ = A_exp_list_init_exps($1,$2);}
    | exp {$$ = A_exp_list_init_exp($1);}
    | {$$ = A_exp_list_init_null();}
    ;


