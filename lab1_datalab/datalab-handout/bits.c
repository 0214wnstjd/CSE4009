/* 
 * CS:APP Data Lab 
 * 
 * <ParkJunsung 2019007892>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	// exploit ~ and & to perform ^ operator
  return ((~(x&y))&(~(~x&~y)));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	//exploit shifts to compute tmin
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	/*
	 * exploit +, ~, !, & operators to check x is whether Tmax or not
	 * !(~(x+x+1)) returns 1 when x is Tmax or -1
	 * !!(x+1) returns 1 when x is not -1
	 */
  return (!(~(x+x+1)))&(!!(x+1));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	/* 
	 * use constant 0xAA with <<, | operators to make 0xAAAAAAAA
	 * x & aaaaaaaa returns 0xAAAAAAAA if x's all odd numbered bits set to 1
	 * check if b^aaaaaaaa returns 0
	 */ 
  int aa = 0xAA;
  int aaaa = (aa<<8)|aa;
  int aaaaaaaa = (aaaa<<16)|aaaa;
  int b = x & aaaaaaaa;
  return !(b^aaaaaaaa);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	// use the rule: -x = ~x +1
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	/* 
	 * compute x - 0x30 and assign at y
	 * check 0x00<=y<=0x07 with shift operator or y==0x08 or y==0x09
	 */
  int y = x + (~0x30 + 1);
  int x7 = !(y>>3);
  return (x7|!(y^0x08)|!(y^0x09));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/*
	 * convert x into 0 or -1 depends on if x is 0
	 * if con is 0, return z as x is 0
	 * if con is -1, return y as x is not 0;
	 */
  int con=!x + (~1+1);
  return (con&y)|(~con&z);
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
	 * yp returns 1 when y is positive
	 * xn returns 1 when x is negative
	 * yx returns 1 when y-x is positive
	 * if y is positive and x is negative, returns 1
	 * if y is negative and x is positive, returns 0
	 * if y is positive or x is negative, return value depends on y-x>=0 or not
	 */ 
  int yp=!(y>>31);
  int xn=!((x>>31)+1);
  int yx=!((y+(~x+1))>>31);
  return ((yp&xn)|((yp|xn)&yx));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	/*
	 * check whether all bits are 0 or not
	 * use >>, | operators to gather all bits to the least significant bit
	 * use &, ^ operator to decide return value depend on the least 
	 * significnat bit
	 */
  int x1=x|(x>>16);
  int x2=x1|(x1>>8);
  int x3=x2|(x2>>4);
  int x4=x3|(x3>>2);
  int x5=x4|(x4>>1);
  return ((x5&1)^1);
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int minus1 = ~1 +1;
  int a = (x & (~(x>>31))) | (~x & (x>>31));

  int x16 = a>>16;
  int con16 = !x16 + minus1;
  int b = (con16&x16) | (~con16&(a&((1<<16) + minus1)));

  int x8 = b>>8;
  int con8 = !x8 + minus1;
  int c = (con8&x8) | (~con8&(b&((1<<8) + minus1)));
 
  int x4 = c>>4;
  int con4 = !x4 + minus1;
  int d = (con4&x4) | (~con4&(c&((1<<4) + minus1)));
  
  int x2 = d>>2;
  int con2 = !x2 + minus1;
  int e = (con2&x2) | (~con2&(d&((1<<2) + minus1)));
  
  int x1 = e>>1;
  int con1 = !x1 + minus1;
  int f = (con1&x1) | (~con1&(e&1)); 
  
  return (!!x16<<4) + (!!x8<<3) + (!!x4<<2) + (!!x2<<1) + (!!x1) + f + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	/*
	 * divide uf into 3 fields(sign, exp, frac)
	 * check uf is a normalized or denormalized or special value according
	 * to exp, especially when exp == 0, we need to modify frac part also.
	 * use | operator to complete 2*uf
	 */
  int sign = uf&0x80000000;
  int exp = (uf >> 23) & 0xFF;
  int frac = uf & 0x7FFFFF;
  if (exp == 0xFF) return uf;
  if (exp == 0) {
	  frac <<=1;
	  if(!!(frac>>23)){
		  exp=1;
		  frac=frac&0x7FFFFF;
	  }
  }
  else{
	  exp++;
  }
  return sign | (exp<<23) | frac ;

}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	/*
	 * Divide uf into 3 fields
	 * if uf < 1 and uf > -1, return 0 as this is an integer value
	 * if exp - 127 > 30, out of range of int(-2^31-1 ~ 2^31-1) or special value.
	 * return (int)uf
	 */
	int sign = uf&0x80000000;
	int exp = (uf >> 23) & 0xFF;
	int frac = uf & 0x7FFFFF;
	if(exp<127) return 0;
	if(exp-127 > 30) return 0x80000000u;
	return ((sign | (1<<30) | (frac<<7))>>30)>>(127-exp);
	
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
	/*
	 * divide into 4 range
	 * 1. x>127, which means exp=11111111. return +INF(0x7F800000)
	 * 2. 126<=x<=127, which means x is E(noramalized value). return 2.0^x
	 * 3. -149<=x<126, which means return is denormalized value(closest to 0.0). use shift operator to set
	 * one of bits in M area.
	 * 4. x<-149, return 0 
	 */

    if(x>127) return 0x7F800000;
    if(x>=-126) return (x+127)<<23;
    if(x>=-149) return 1<<(149+x);
    return 0;
}
