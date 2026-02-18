//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#ifndef lab0_iregister_h
#define lab0_iregister_h

/**
 *  iRegister
 *  An iRegister is a structure which represents an 32-bit register and
 *  is equipped with standard operations to modify and display them.
 */
typedef struct
{
       unsigned int content;
} iRegister;

/**
 *  Bellow you find the declarations for the functions to modify and display the
 *  memory content of a iRegister data structure. Before each declaration, a brief
 *  description about what the function shall do is given.
 *  Later in this file, the documentation for the resetBit function is given.
 *  Students should follow that format.
 */

/**
 * @brief resets all the bits of the iRegister (to 0)
 *
 *  @param r A pointer to a memory location of an iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition:
 *    1. iRegister != NULL
 *
 *  Post-condition:
 *    1. After resetAll(r), every bit of the register is 0.
 *    2. The register value becomes 0x00000000.
 *
 *  Properties:
 *    1. For all j where 0 <= j < 32:
 *        getBit(j, r_after) = 0
 *    2. r_after = 0x00000000
 *
 *  Test-cases:
 *    1. If r = 0xFFFFFFFF, after resetAll(&r), r = 0x00000000.
 *    2. If r = 0x12345678, after resetAll(&r), r = 0x00000000.
 *    3. If r = 0x00000000, after resetAll(&r), r = 0x00000000 (unchanged).
 */
void resetAll(iRegister *);

/**
 *  @brief sets the i'th bit of the iRegister (to 1)
 *
 *  @param i The bit position to set where  0≤ i < 32
 *
 *  @param r A pointer to a memory location of an iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition:
 *    1. 0 ≤ i < 32
 *    2. iRegister != NULL
 *
 *  Post-condition:
 *    1. After setBit(i, r), the i'th bit of the register is 1.
 *    2. All other bits remain unchanged.
 *
 *  Properties:
 *    1. setBit(i, r):
 *        r_after = r_before | (1 << i)
 *    2. For the modified bit:
 *        getBit(i, r_after) = 1
 *    3. For all j ≠ i:
 *        getBit(j, r_after) = getBit(j, r_before)
 *
 *  Test-cases:
 *    1. If r = 0x00000000 and i = 0, after setBit(0, &r), r = 0x00000001.
 *    2. If r = 0x00000000 and i = 5, after setBit(5, &r), r = 0x00000020.
 *    3. If r = 0xFFFFFFFF and i = 10, after setBit(10, &r), r = 0xFFFFFFFF (unchanged).
 *    4. If r = 0x0000FF00 and i = 31, after setBit(31, &r), r = 0x8000FF00.
 */
void setBit(int, iRegister *);

/**
 * @brief sets all the bits of the iRegister (to 1)
 *
 *  @param r A pointer to a memory location of an iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition:
 *    1. iRegister != NULL
 *
 *  Post-condition:
 *    1. After setAll(r), every bit of the register is 1.
 *    2. The register value becomes 0xFFFFFFFF.
 *
 *  Properties:
 *    1. For all j where 0 <= j < 32:
 *        getBit(j, r_after) = 1
 *    2. r_after = 0xFFFFFFFF
 *
 *  Test-cases:
 *    1. If r = 0x00000000, after setAll(&r), r = 0xFFFFFFFF.
 *    2. If r = 0x12345678, after setAll(&r), r = 0xFFFFFFFF.
 *    3. If r = 0xFFFFFFFF, after setAll(&r), r = 0xFFFFFFFF (unchanged).
 */
void setAll(iRegister *);

/** @brief returns the i'th bit of the iRegister as an integer (1 if it is set, or 0 otherwise)
 *   @param i The bit position to retrieve such that 0 ≤ i < 32
 *
 *  @param r A pointer to a memory location of an iRegister data structure.
 *
 *  @return int
 *          1. 1 if the i'th bit is set
 *          2. 0 if the i'th bit is not set
 *
 *  Pre-condition:
 *    1. 0 ≤ i < 32
 *    2. iRegister != NULL
 *
 *  Post-condition:
 *    1. The returned value reflects the state of the i'th bit of the register
 *    2. Original bits of the register remain unchanged
 *
 *  Properties:
 *    1. getBit(i, r) = ( (*r) >> i ) & 0x1
              (Mask logic: get i'th bit to LSB and Perform AND operation to extract exact bit )
 *    2. Result is always either 0 or 1
 *
 *  Test-cases:
 *    1. If r = 0x00000001 and i = 0, getBit(0, &r) = 1
 *    2. If r = 0x00000001 and i = 1, getBit(1, &r) = 0
 *    3. If r = 0x80000000 and i = 31, getBit(31, &r) = 1
 *    4. If r = 0x00000000 and i = 15, getBit(15, &r) = 0
 */
int getBit(int, iRegister *);

/** @brief set the first (for pos=1) or the second (for pos=2) four bits of iRegsiter
 *
 *  @param int
       pos (1 <= pos <=2) Indicates the nibble to be set:
 *            1. pos = 1 → assign to the least significant nibble (bits 0–3)
 *            2. pos = 2 → assign to the next nibble (bits 4–7)
 *
 *  @param int
       1. value the new 4-bit value to assign (0–15).
 *     2. Only the lowest 4 bits of this parameter are used
       3. higher bits are ignored.
 *
 *  @param r A pointer to a memory location of an iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition:
 *    1. 1 <= pos <= 2
 *    2. 0 <= value <= 15
 *    3. iRegister != NULL
 *
 *  Post-condition:
 *    1. The nibble at the given position is replaced with the given value.
 *    2. All other bits of the register remain unchanged.
 *    3. Return nibble value that should be equal to the value 
 *
 *  Properties:
 *    1. assignNibble(pos, v, r) modifies only bits (0-3) 04 (4-7).
 *    2. After assignment:
 *        getNibble(pos, r) = value & 0xF (0xF masking make sure value remains 4 bits)
 *    3. For all j not in pos={1,2},
 *        getBit(j, r_after) = getBit(j, r_before)
 *
 *  Test-cases:
 *    1. If r = 0x00000000 and assignNibble(1, 0xA, &r),
 *       then r = 0x0000000A.
 *    2. If r = 0x00000000 and assignNibble(2, 0xF, &r),
 *       then r = 0x000000F0.
 *    3. If r = 0xFFFFFFFF and assignNibble(1, 0x0, &r),
 *       then r = 0x0FFFFFFF.
 *    4. If r = 0x12345678 and assignNibble(2, 0x5, &r),
 *       then r = 0x12345578.
 */
int assignNibble(int, int, iRegister *);

/**
*  @brief get the four bits of iRegsiter from pos=0 to pos = 7
*
*  @param
      1. pos (0<=pos<=7) Indicates which nibble to retrieve:
*             - pos = 1 → bits 0-3 (least significant nibble)
*             - pos = 7 → bits 28-31 (Most significant nibble)
*
*  @param r A pointer to a memory location of an iRegister data structure.
*
*  @return int
*          An integer value (0–15) corresponding to the nibble extracted.
*
*  Pre-condition:
*     1. 1 <= pos <= 7
*     2. iRegister != NULL
*
*  Post-condition:
      1. The returned value is between 0-15 i.e 4 bits of the specified nibble
      2. The returned should be shifted to least significant position
      3. Bits outside the first byte are ignored
*
*  Properties:
*     1. getNibble(pos, r) = (r >> (4 * (pos - 1))) & 0xF
*     2. The result is always between 0 and 15 inclusive.
*
*  Test-cases:
*    1. If r = 0x12345678 and pos = 1,
*       getNibble(1, &r) = 0x8 (binary 1000).
*    2. If r = 0x12345678 and pos = 2,
*       getNibble(2, &r) = 0x7 (binary 0111).
*/
int getNibble(int, iRegister *);

/**
*  @brief returns a pointer to an array of 32 characters, with each character
*     representing the corresponding bit of the iRegister, i.e., if the bit is set,
*     then the character is "1" (ASCII char with code 49), or otherwise is "0"
*     (ASCII char with code 48)

*  @param r An iRegister value whose binary representation is to be converted
*           into a string form.
*
*  @return char*
*     1. A pointer to a null-terminated string of length 32 + 1, where:
*     2. Each of the first 32 characters is either '0' or '1'(ASCII 48 or 49), depending on the bit value in the register.
*     3. The last character is the null terminator '\0'.
*
*  Pre-condition:
*     1. iRegister != Null.
*
*  Post-condition:
*     1. The returned string contains exactly 32 characters of '0' or '1' corresponding to the bits of the register, with bit 31 (MSB) at index 0
*       and bit 0 (LSB) at index 31.
*
*  Properties:
*    - For all j where 0 <= j < 32:
*        reg2str(r)[j] = '1' if getBit(31 - j, r) = 1
*        reg2str(r)[j] = '0' if getBit(31 - j, r) = 0
*    - The string is null-terminated at index 32.
*
*  Test-cases:
*    1. Set value of r = 0x00000000 (all bits reset) and pass to the reg2str(r) the output should be,
*       reg2str(r) = "00000000000000000000000000000000"
*    2. Similarly check for r = 0xFFFFFFFF (all bits set),
*       reg2str(r) = "11111111111111111111111111111111"
*    3. If only bit 0 is set,
*       reg2str(r) = "00000000000000000000000000000001"
*    4. If only bit 31 is set,
*       reg2str(r) = "10000000000000000000000000000000"
*/
char *reg2str(iRegister);

/**
 *   @brief shifts all the bits of the iRegister to the right by n palces (appends 0 from the left)
 *
 *   @param i Is i'th place by which the bits to be shift on right
 *
 *   @param r A pointer to a memory location of a iRegister data structure.
 *
 *   @return void
 *
 *  Pre-condition:
        1. 0 <= i < 32 and
        2. iRegister != Null
 *
 *  Post-condition:
        1. after shiftRight(i, r) all the bits should be moved right by i
        2. Leftmost bit (least significant) appends by 0
        3. Rightmost bit (most significant) should be descarded
 *  Properties:
 *      1. if j is the position of the bit before shifting such that (i <= j <32) then for each bit after shiftRight
            getBit(j, r_before) = getBit(j-i, r_after)
        2. for j after shiftRight such that 32 - i <= j < 32:
            getBit(j, r_after) = 0
        3. above function (getBit(j, r_after) = 0 ) for all j where 0<=j<i is true for the rightmost descarded as well
 *
 *  test-cases:
        1. Allocate memory to an iRegister r
        2. first do resetAll(&r)
        3. set the i'th bit of &r by setBit(i, &r) and repeat for some more bits for eg: i = 0, 14, 23
        4. call the shiftRight(i, &r) and display result using
            printf("%s",reg2str(r))
 */
void shiftRight(int, iRegister *);

/**  @brief shifts all the bits of the iRegister to the left by n palces (appends 0 from the right)
 *
 *   @param i Is i'th place by which the bits to be shift on left
 *
 *   @param r A pointer to a memory location of a iRegister data structure.
 *
 *   @return void
 *
 *  Pre-condition:
        1. 0 <= i < 32 and
        2. iRegister != Null
 *
 *  Post-condition:
        1. after shiftLeft(i, r) all the bits should be moved left by i
        2. Rightmost bit (least significant) appends by 0
        3. Leftmost bit (most significant) should be descarded
 *  Properties:
 *      1. if j is the position of the bit before shifting such that (i + j <32) then for each bit after shiftLeft
            getBit(j, r_before) = getBit(i+j, r_after)
        2. for j after shiftLeft such that 0<=j<i
            getBit(j, r_after) = 0
        3. above function (getBit(j, r_after) = 0 ) for all j where 32-i<=j<32 is true for the leftmost descarded as well
 *
 *  test-cases:
        1. Allocate memory to an iRegister r
        2. first do resetAll(&r)
        3. set the i'th bit of &r by setBit(i, &r) and repeat for some more bits for eg: i = 0, 14, 23
        4. call the shiftLeft(i, &r) and display result using
            printf("%s",reg2str(r))
 */
void shiftLeft(int, iRegister *);

/** @brief Resets the i'th bit of the iRegister (to 0)
 *
 *  @param i Is i'th bit of the iRegister to be reset
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition:
        1. 0 <= i < 32 and
        2. iRegister != Null
 *
 *  Post-condition:
        1. after reset(i, r) the i'th bit of iRegister is 0, all other bits remain unchanged
 *  properties:
 *      1. after resetBit(i, r),  getBit(i, r) = 0
 *      2. if getBit(i, r) == 0 then
 *          getBit(j, r) returns the same value for all
 *          0 <= j < 32 and j <> i before and after resetBit(i, r)
 * test-cases:
 *  1. Allocate memory to an iRegister r
 *  2. first do resetAll(&r),
 *  3. then set the i'th bit of &x by setBit(i, &r) for i = 0, 15 and 23 and then
 *  4. display the result after each and every call by
 *      printf("%s",reg2str(r))
 */
void resetBit(int, iRegister *);

#endif
