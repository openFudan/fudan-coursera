/* 
 * CS:APP Data Lab 
 * 
 * <15307130228-XiongQian>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */
#if 0

/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */






#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/*
  x&y=~(~(x&y)) 
 */
  return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/*
  (n<<3) is the bits x should move to right 
  and 255 is for extracting lowest 8 bits of moved x 
 */  
  return (x>>(n<<3))&255;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n){
/*
  d is to decide the sign of x
  (x+(d<<31))>>n) is move the sign off and shift n bits to the right
  (d<<(31+(~n)+1)) is make up for the move of the sign of x
 */ 
  int f=x>>31;
  int d=f&1;
  return ((x+(d<<31))>>n)+(d<<(31+(~n)+1));
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
/*
   mask1 is to sum up the number of 1 of every 2 bits of 32 bits
   mask2 is to sum up the number of 1 of every 4 bits of 32 bits basing on 
   the result of using mask1
   ......
   Finnally,all 1s will be sum up to the right
 */
	      int result;  
          int tmp_mask1=(0x55)|(0x55<<8);  
          int mask1=(tmp_mask1)|(tmp_mask1<<16); 
          int tmp_mask2=(0x33)|(0x33<<8);  
          int mask2=(tmp_mask2)|(tmp_mask2<<16);  
	       int tmp_mask3=(0x0f)|(0x0f<<8);  
	       int mask3=(tmp_mask3)|(tmp_mask3<<16);  
		   int mask4=(0xff)|(0xff<<16);  
		   int mask5=(0xff)|(0xff<<8);  
		   result=(x&mask1)+((x>>1)&mask1);  
		   result=(result&mask2)+((result>>2)&mask2);  
		   result=(result&mask3)+((result>>4)&mask3);  
	       result=(result+(result>>8))&mask4;  
   	     result=(result+(result>>16))&mask5;  
         return result;  

}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 
 *   Rating: 4 
 */
int bang(int x) {
/* 
   for (x|(~x+1)):
   if x=0, the sign of result is 0;
   else the sign is 1
   so extract the sign and take the opposite of it
 */
  return ((~((x|(~x+1))>>31))&1);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/*
   the minimum we want is 0x10000000
 */
  return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2

*/
int fitsBits(int x, int n) {
/* 
  If x can be represented as an n-bit,two's complement integer
  (x>>(n-1)) would be 0x00000000 or 0x11111111 depending on its sign
 */
  int f=x>>31;
  int d=f&1;
  int nn=n+(~1)+1;
  return !((x>>nn)^f);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x,int n) {
/* 
   If x>=0 or the lowest n bits of x is all 0, the answer = x>>n
   else the answer = (x>>n)+1 
   that means x<0 and the lowest n bits of x has at least one 1
   using d to represent the sign
   using plus to represent whether the lowest n bits of x has 1 or not
 */
  int f=x>>31;
  int d=f&1;
  int zero=((~0)+(1<<31))>>(32+(~n));
  int is=zero&x;
  int plus=(!(!is));
  return ((x>>n)+(plus&d));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
/*
   the nagate of x is (~x)+1
 */
  return (~x)+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
/* 
   d is the sign of x
   if d=0 x>=0
   if x=0 x^0=0
   so if x>0, d=0 and x^0!=0
 */
  int f=x>>31;
  int d=f&1;
  return (!d)&(!(!(x^0)));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 
 

*/
int isLessOrEqual(int x, int y) {
/*
  If x<0 and y>=0, x<=y
  if the signs of x and y is the same and (y-x)>=0 ,x<=y
  if x>=0 and y<0, x<=y is false
  xx is the sign of x
  yy is the sign of y
  w=1 <==> x<0 and y>=0
  c=1 <==> (y-x)>=0
 */
  int a=y+(~x+1);
  int yy=((y>>31)&1);
  int xx=((x>>31)&1);
  int f=a>>31;
  int d=f&1;
  int c=!d;
  int w=(!yy)&xx;
  return ((c&(!(xx^yy)))|w);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 * 
 Rating: 4
 */
int ilog2(int x) {
/*
  If x>=(2^n),(x>>n)!=0
  first clear out whether left 16 bits of x has at least one 1 or not
  if yes n>=16,else n<16
  basing on result above,
  clear out whether left 8 bits of 16 bits above has at least one 1 or not
  use x>>(n+d) to move d bits to right basing on n bits
 */
 int n=0;  
 n=(!!(x>>16))<<4;  
 n+=((!!(x>>(n+8)))<<3);  
 n+=((!!(x>>(n+4)))<<2);  
 n+=((!!(x>>(n+2)))<<1);  
 n+=(!!(x>>(n+1)));  
 return n;  
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
*/
unsigned float_neg(unsigned uf) {
/*
  If uf is NaN,its 8 bits of E are 255 and lowest 23 bits have at least one 1,return itself
  else change its sign to the opposite
 */
  if (((uf>>23)&255)==255&&(uf&(0xffffff>>1)))
  return uf;
  else 
  return (uf+(1<<31));
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
/*
  Use sign to represent the sign of x
  use afterShift to represent the result of shifting the constant 0 on the left of x
  and removing the first 1
  so the floatpoints of x is afterShift>>9
  use shiftLeft to represent the place of first 1 on the left of x despite of its sign
  so the E of x is (127+32-shiftLeft)
  and if afterShift's lowest 9 bits >=100000000,the result should add 1
 */
  unsigned shiftLeft=0;  
  unsigned afterShift, tmp, flag;  
  unsigned absX=x;   
  unsigned sign=0;  
  if (x==0) return 0;  
  if (x<0)  
  {  
  sign=0x80000000;  
  absX=-x;  
  }  
  afterShift=absX;  
  while (1)  
  {  
  tmp=afterShift;  
  afterShift<<=1;  
  shiftLeft++;  
  if (tmp & 0x80000000) break;  
  }  
  if ((afterShift & 0x01ff)>0x0100)  
  flag=1;  
  else if ((afterShift & 0x03ff)==0x0300)  
  flag=1;  
  else  
  flag=0;  
  return sign + (afterShift>>9) + ((159-shiftLeft)<<23) + flag;
 }
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4

*/
unsigned float_twice(unsigned uf) {
/*
   If the E=0, make the lowest 23 bits double and keep the sign
   if 0<E<255, let E=E+1 
   if the E=255, return itself
 */
    if ((uf & 0x7F800000) == 0) 
    uf = ((uf & 0x007FFFFF)<<1) | (0x80000000 & uf);  
    else  if ((uf & 0x7F800000) != 0x7F800000) 
    uf= uf+0x00800000; 
    return uf; 
}
