#ifndef TOKENS_H
#define TOKENS_H
#include "util.h"
typedef union  {
	int pos;
	int ival;
	string sval;
	} YYSTYPE;

extern YYSTYPE yylval;

#define ID 257
#define CLASS 258
#define PUBLIC 259
#define STATIC 260
#define VOID 261
#define LPAREN 262  //(
#define RPAREN 263  //)
#define LBRACK 264  //[
#define RBRACK 265  //]
#define LBRACE 266  //{
#define RBRACE 267  //}
#define STRING 268 
#define EXTENDS 269
#define SEMICOLON 270//;

#define BOOLEAN 271
#define INT 272
#define IF 273
#define WHILE 274
#define PRINT 275
#define LENGTH 276
#define DOT 277
#define THIS 278
#define NEW 279
#define ASSIGN 280

#define PLUS  281
#define MINUS 282
#define TIMES 283
//#define DIVIDE 284

//#define EQ 285
//#define LE 286
#define LT 287
//#define GE 288
#define GT 289
#define AND 290
#define REVERSE 291
#define TRUE 292
#define FALSE 293

#define ELSE 294
#define COMMA 295
#define MAIN 296
#define RETURN 297
#define INT_ID 298
#define BOOLEAN_ID 299
#define STRING_ID 300






#endif /* !TOKENS_H */
