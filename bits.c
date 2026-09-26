/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x) {
        return !y;
    }
    if (!y) {
        return 0;
    }

    return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int answer = (v > 65535) << 4;
    v = v >> answer;

    int step = (v > 255) << 3;
    answer = answer | step;
    v = v >> step;

    step = (v > 15) << 2;
    answer = answer | step;
    v = v >> step;

    step = (v > 3) << 1;
    answer = answer | step;
    v = v >> step;

    answer = answer | (v > 1);
    return answer;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int shiftN = n << 3;                 
    int shiftM = m << 3;                 
    int byteN = (x >> shiftN) & 0xff;
    int byteM = (x >> shiftM) & 0xff;
    int diff = byteN ^ byteM;

    return x ^ (diff << shiftN) ^ (diff << shiftM);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned mask = 1;
    unsigned answer = 0;
    unsigned count = 0;
    while(~count){
        answer = answer<<1;
        answer += v & mask;
        v = v>>1;
        count = (count<<1) + 1;
    }
    return answer;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = 0x80000000;
    int top  = 0x80000000;
    int back = !!n;
    mask = ~(mask>>n);
    mask = (mask<<back) | back;

    int if0 = ~(!n) + 1;
    return ((x>>n) & mask) | (x & top & if0);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    x = ~x;
    int k = (x>>16) & 0xFFFF;
    k = !k << 4;

    int s1 = 24 + (~k + 1);
    int b1 = (x >> s1) & 0xFF;
    b1 = !b1 << 3;
    k = k + b1;

    int s2 = s1 + 4 + (~b1 + 1);
    int b2 = (x >> s2) & 0xF;
    b2 = !b2 << 2;
    k = k + b2;

    int s3 = s2 + 2 + (~b2 + 1);
    int b3 = (x >> s3) & 3;
    b3 = !b3 << 1;
    k = k + b3;

    int s4 = s3 + 1 + (~b3 + 1);
    int b4 = (x >> s4) & 1;
    k = k + !b4;

    return k + !x;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned xp   = x;
    if(x==0){
        return 0;
    }
    if(x<0){
        xp = ~xp + 1;
        sign = 0x80000000;
    }
    int exp = 1;
    while((xp>>31 & 1) == 0){
        xp = xp<<1;
        exp = exp + 1;
    }
    exp = (127 + (32-exp)) << 23;

    unsigned tail = xp & 0xFF;
    unsigned frac = (xp << 1) >> 9;

    if (tail > 0x80) frac = frac + 1;
    if (tail == 0x80) {
        if (frac & 1) frac = frac + 1;
    }

    return sign + exp + frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp_mask = 0x7F800000;
    unsigned sign = uf & 0x80000000;
    unsigned exp = uf & exp_mask;

    if (exp == exp_mask) {
        return uf;
    }
    if (exp == 0) {
        return sign + ((uf & 0x007FFFFF) << 1);
    }
    if (exp == 0x7F000000) {
        return sign + exp_mask;
    }
    return uf + 0x00800000;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned exp  = (uf2 >> 20) & 0x7FF;
    unsigned sign = uf2 >> 31;

    if (exp < 1023) return 0; 
    if (exp >= 1054) return ~0x7FFFFFFF;

    unsigned e = exp - 1023;
    unsigned high = (uf2 & 0xFFFFF) | 0x100000;
    unsigned mag;

    if (e <= 20) {
        mag = high >> (20 - e);
    } else {
        mag = (high << (e - 20)) | (uf1 >> (52 - e));
    }

    int result = mag;
    if (sign) return -result;
    return result;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x >= 128){
        return 0x7F800000;
    }
    if(x <= -150){
        return 0;
    }
    if(x<-126){
        return (1<<(x+149));
    }else{
        return (x+127)<<23;
    }
}
