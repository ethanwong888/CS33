/* 
 * CS:APP Data Lab 
 * 
 * <Ethan Wong 305319001>
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
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  //split the integer into smaller and smaller chunks
  //using XOR operation on the smaller chunks gives the
  //  parity of the original value (the one that hasn't been split up)
       //any value XORed with 0 is left unchanged
  //continue doing this until no more smaller chunks can be made, & with 1
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  x = (x & 1);
  return x;
}




/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  //first, shift x by (32 - n) positions --> gets n bits to the front of the number
  //this represents the bits that will be put into the empty space 
  int scoot = (1 + ~n) + 32;
  int move = x << scoot;
  //next, x >> n to create empty space in the beginning of the integer
   x = x >> n;
  //next, create a mask  -->  Tmax >> (n - 1)
  x = x & (~(1 << 31)) >> (n + (1 + ~1));
  return (move | x); 
}


/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  //first, acquire the two bytes that need to be switched
  //and "OR" them together
  int mByte = x & (255 << (m << 3));
  int nByte = x & (255 << (n << 3));
  int MN = mByte | nByte;

  //next, determine where the bytes should go
  int mMove = 255 & (mByte >> (m << 3));
  int nMove = 255 & (nByte >> (n << 3));

  int mPosition = mMove << (n << 3);
  int nPosition = nMove << (m << 3);
 
  MN = x & (~MN);
  //finally, "OR" them together to set the final integer and return
  return (MN | mPosition | nPosition);
}




/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  //shift left by 16 then right by 16  -->  this will sign fill based on MSB
  //X-or is used to check if the x remains the same
  //if x remains the same, it CAN be represented by a 'short'
  return !((x << 16) >> 16 ^ x);
}




/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  //get the opposite of each and then use |  --> basically
  //    doing the inverse of '&'
  //reutrning the ~ (opposite) of that result yields the normal '&'
  int oppositeX = ~x;
  int oppositeY = ~y;
  int result = ~(oppositeX|oppositeY);
  return result;
}




/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  //overflow for subtraction occurs when 
  //   x and y have opposite signs
  //   the Answer has a different sign than x
  //need to check both of these conditions to see whehter return 1 or 0
  int subtractionResult = x + (~y + 1);  //this is basically x - y
  int signOfAnswer = subtractionResult ^ x;
  int signOfOperands = y ^ x;
  
  int result = !((signOfAnswer & signOfOperands) >> 31);
  return result;
}




/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  //first check if x is greater than y (regardless of sign)
  //next take the sign bits of x and y into account
  int answer = x + ~y;         //this is saying "x - y"
  answer = !(answer >> 31);    //answer will be 1 if x > y (regardless of sign)

  y = y >> 31;  //getting the sign bit
  x = x >> 31;  //getting the sign bit

  //if x is positive and y is negative, automatically return 1
  //otherwise, "answer" will be returned if x ISN'T negative and y IS positive
  return (((!x) | y) & answer) | ((!x) & y);
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
  //first, find the amount of high order bits that remain after
  //   using 'n' lower order bits
  //sign-fill the high order bits by shifting left and then shifting right
  // !(____ ^ x)  -->  ____ == x
  int opposite = ~n;
  int pop = opposite + 33;   //this is adding a negative number to 33)

  return !(((x << pop) >> pop) ^ x);
}




/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (( ~x) + 1);
}




/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  //if x is Tmax, xPlusOne will be Tmin
  //if x is Tmax, x + xPlusOne = -1
  //if x is Tmax, the following steps will yield x = 000....0000
  //returning !x makes it into 1111....1111 (true) 
  //will return false if the preliminary conditio are not met
  int xAddOne = x + 1;
  x = x + xAddOne;
  x = ~x;
  xAddOne = !xAddOne;
  x = xAddOne | x;
  return !x;
}
