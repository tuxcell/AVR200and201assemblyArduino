// **** A P P L I C A T I O N   N O T E   A V R 2 0 0 ************************
// *
// * Title:		Multiply and Divide Routines
// * Version:		1.1
// * Last updated:	97.07.04
// * Target:		AT90Sxxxx (All AVR Devices)
// *
// * Support E-mail:	avr@atmel.com
// *
// * DESCRIPTION
// * This Application Note lists subroutines for the following
// * Muliply/Divide applications:
// *
// * 8x8 bit unsigned
// * 8x8 bit signed
// * 16x16 bit unsigned
// * 16x16 bit signed
// * 8/8 bit unsigned
// * 8/8 bit signed
// * 16/16 bit unsigned
// * 16/16 bit signed
// *
// * All routines are Code Size optimized implementations

// Modified by Jose Gama as inline assembly in a C header file for the Arduino, May 2015

// *
// ***************************************************************************
// *
// * "mpy8u" - 8x8 Bit Unsigned Multiplication
// *
// * This subroutine multiplies the two register variables r17 and r16.
// * The result is placed in registers r18, r17
// *  
// * Number of words	:9 + return
// * Number of cycles	:58 + return
// * Low registers used	:None
// * High registers used  :4 (r17,r16/r17,r18,r19)	
// *
// * Note: Result Low byte and the multiplier share the same register.
// * This causes the multiplier to be overwritten by the result.
// *
// ***************************************************************************

// ***** Subroutine Register Variables

//r16 multiplicand
//r17 multiplier
//r17 result Low byte
//r18 result High byte
//r19 loop counter

// ***** Code
uint16_t mpy8u(uint8_t multiplicand, uint8_t multiplier)
{
uint16_t result;
__asm__ __volatile__ ( \
"	clr	%B0 \n\t" /*clear result High byte*/ \
"	mov %A0,%A2 \n\t" \
"	ldi	r19,8 \n\t" /*init loop counter*/ \
"	lsr	%A0 \n\t" /*rotate multiplier*/ \
"m8u_1:	brcc	m8u_2 \n\t" /*carry set */ \
"	add 	%B0,%A1 \n\t" /*   add multiplicand to result High byte*/ \
"m8u_2:	ror	%B0 \n\t" /*rotate right result High byte*/ \
"	ror	%A0 \n\t" /*rotate right result L byte and multiplier*/ \
"	dec	r19 \n\t" /*decrement loop counter*/ \
"	brne	m8u_1 \n\t" /*if not done, loop more*/ \
: "=&a" (result) \
: "a" (multiplicand),  "a" (multiplier) \
: "r19" \
);
return result;
}

// ***************************************************************************
// *
// * "mpy8s" - 8x8 Bit Signed Multiplication
// *
// * This subroutine multiplies signed the two register variables r17 and 
// * r16. The result is placed in registers r18, r17
// * The routine is an implementation of Booth's algorithm. If all 16 bits
// * in the result are needed, avoid calling the routine with
// * -128 ($80) as multiplicand
// *  
// * Number of words	:10 + return
// * Number of cycles	:73 + return
// * Low registers used	:None
// * High registers used  :4 (r16,r17/r17,r18,r19)	
// *
// ***************************************************************************

// ***** Subroutine Register Variables

//r16 multiplicand
//r17 multiplier
//r17 result Low byte
//r18 result High byte
//r19 loop counter

// ***** Code
uint16_t mpy8s(int8_t multiplicand, int8_t multiplier)
{
int16_t result;
__asm__ __volatile__ ( \
"mpy8s:	sub	%B0,%B0 \n\t" /*clear result High byte and carry*/ \
"	ldi	r19,8 \n\t" /*init loop counter*/ \
"m8s_1:	brcc	m8s_2 \n\t" /*if carry (previous bit) set*/ \
"	add	%B0,%A1 \n\t" /*    add multiplicand to result High byte*/ \
"m8s_2:	sbrc	%A2,0 \n\t" /*if current bit set*/ \
"	sub	%B0,%A1 \n\t" /*    subtract multiplicand from result High*/ \
"	asr	%B0 \n\t" /*shift right result High byte*/ \
"	ror	%A2 \n\t" /*shift right result L byte and multiplier*/ \
"	dec	r19 \n\t" /*decrement loop counter*/ \
"	brne	m8s_1 \n\t" /*if not done, loop more*/ \
"	mov %A0,%A2 \n\t" \
: "=&a" (result) \
: "a" (multiplicand),  "a" (multiplier)\
: "r19" \
);
return result;
}

// ***************************************************************************
// *
// * "mpy16u" - 16x16 Bit Unsigned Multiplication
// *
// * This subroutine multiplies the two 16-bit register variables 
// * r19:r18 and r17:r16.
// * The result is placed in r21:r20:r19:r18.
// *  
// * Number of words	:14 + return
// * Number of cycles	:153 + return
// * Low registers used	:None
// * High registers used  :7 (r18,r19,r16/r18,r17/r19,r20,
// *                          r21,r22)	
// *
// ***************************************************************************

// ***** Subroutine Register Variables

//r16 multiplicand low byte
//r17 multiplicand high byte
//r18 multiplier low byte
//r19 multiplier high byte
//r18 result byte 0 (LSB)
//r19 result byte 1
//r20 result byte 2
//r21 result byte 3 (MSB)
//r22 loop counter

// ***** Code
uint32_t mpy16u(uint16_t multiplicand, uint16_t multiplier)
{
uint32_t result;
__asm__ __volatile__ ( \
"mpy16u:	clr	%D0 \n\t" /*clear 2 highest bytes of result*/ \
"	clr	%C0 \n\t" \
"	ldi	r22,16 \n\t" /*init loop counter*/ \
"	lsr	%B2 \n\t" \
"	ror	%A2 \n\t" \
"m16u_1:	brcc	noad8 \n\t" /*if bit 0 of multiplier set*/ \
"	add	%C0,%A1 \n\t" /*add multiplicand Low to byte 2 of res*/ \
"	adc	%D0,%B1 \n\t" /*add multiplicand high to byte 3 of res*/ \
"noad8:	ror	%D0 \n\t" /*shift right result byte 3*/ \
"	ror	%C0 \n\t" /*rotate right result byte 2*/ \
"	ror	%B2 \n\t" /*rotate result byte 1 and multiplier High*/ \
"	ror	%A2 \n\t" /*rotate result byte 0 and multiplier Low*/ \
"	dec	r22 \n\t" /*decrement loop counter*/ \
"	brne	m16u_1 \n\t" /*if not done, loop more*/ \
"	mov %A0,%A2 \n\t" \
"	mov %B0,%B2 \n\t" \
: "=&r" (result) \
: "a" (multiplicand),  "a" (multiplier)\
: "r22" \
);
return result;
}

// ***************************************************************************
// *
// * "mpy16s" - 16x16 Bit Signed Multiplication
// *
// * This subroutine multiplies signed the two 16-bit register variables 
// * r19:r18 and r17:r16.
// * The result is placed in r21:r20:r19:r18.
// * The routine is an implementation of Booth's algorithm. If all 32 bits
// * in the result are needed, avoid calling the routine with
// * -32768 ($8000) as multiplicand
// *  
// * Number of words	:16 + return
// * Number of cycles	:210/226 (Min/Max) + return
// * Low registers used	:None
// * High registers used  :7 (r18,r19,r16/r18,r17/r19,
// *			    r20,r21,r22)	
// *
// ***************************************************************************

// ***** Subroutine Register Variables

//r16 multiplicand low byte
//r17 multiplicand high byte
//r18 multiplier low byte
//r19 multiplier high byte
//r18 result byte 0 (LSB)
//r19 result byte 1
//r20 result byte 2
//r21 result byte 3 (MSB)
//r22 loop counter

// ***** Code
int32_t mpy16s(int16_t multiplicand, int16_t multiplier)
{
int32_t result;
__asm__ __volatile__ ( \
"mpy16s:	clr	%D0 \n\t" /*clear result byte 3*/ \
"	sub	%C0,%C0 \n\t" /*clear result byte 2 and carry*/ \
"	ldi	r22,16 \n\t" /*init loop counter*/ \
"m16s_1:	brcc	m16s_2 \n\t" /*if carry (previous bit) set*/ \
"	add	%C0,%A1 \n\t" /*    add multiplicand Low to result byte 2*/ \
"	adc	%D0,%B1 \n\t" /*    add multiplicand High to result byte 3*/ \
"m16s_2:	sbrc	%A2,0 \n\t" /*if current bit set*/ \
"	sub	%C0,%A1 \n\t" /*    sub multiplicand Low from result byte 2*/ \
"	sbrc	%A2,0 \n\t" /*if current bit set*/ \
"	sbc	%D0,%B1 \n\t" /*    sub multiplicand High from result byte 3*/ \
"	asr	%D0 \n\t" /*shift right result and multiplier*/ \
"	ror	%C0 \n\t" \
"	ror	%B2 \n\t" \
"	ror	%A2 \n\t" \
"	dec	r22 \n\t" /*decrement counter*/ \
"	brne	m16s_1 \n\t" /*if not done, loop more	*/ \
"	mov %A0,%A2 \n\t" \
"	mov %B0,%B2 \n\t" \
: "=&r" (result) \
: "a" (multiplicand),  "a" (multiplier)\
: "r22" \
);
return result;
}

// ***************************************************************************
// *
// * "div8u" - 8/8 Bit Unsigned Division
// *
// * This subroutine divides the two register variables "r16" (dividend) and 
// * "r17" (divisor). The result is placed in "r16" and the remainder in
// * "r15".
// *  
// * Number of words	:14
// * Number of cycles	:97
// * Low registers used	:1 (r15)
// * High registers used  :3 (r16/r16,r17,r18)
// *
// ***************************************************************************

// ***** Subroutine Register Variables

//r15 remainder
//r16 result
//r16 dividend
//r17 divisor
//r18 loop counter

// ***** Code
void div8u(uint8_t *result, uint8_t *remainder, uint8_t dividend, uint8_t divisor)
{
__asm__ __volatile__ ( \
"div8u:	sub	%A1,%A1 \n\t" /*clear remainder and carry*/ \
"	ldi	r18,9 \n\t" /*init loop counter*/ \
"d8u_1:	rol	%A2 \n\t" /*shift left dividend*/ \
"	dec	r18 \n\t" /*decrement counter*/ \
"	brne	d8u_2 \n\t" /*if done*/ \
"	rjmp d8u_4 \n\t" /*    return*/ \
"d8u_2:	rol	%A1 \n\t" /*shift dividend into remainder*/ \
"	sub	%A1,%A3 \n\t" /*remainder = remainder - divisor*/ \
"	brcc	d8u_3 \n\t" /*if result negative*/ \
"	add	%A1,%A3 \n\t" /*    restore remainder*/ \
"	clc \n\t" /*    clear carry to be shifted into result*/ \
"	rjmp	d8u_1 \n\t" /*else*/ \
"d8u_3:	sec \n\t" /*    set carry to be shifted into result*/ \
"	rjmp	d8u_1 \n\t" \
"d8u_4:	mov %A0,%A2 \n\t" \
"	mov %A1,%A1 \n\t" \
: "+a" (*result), "+a" (*remainder) \
: "a" (dividend),  "a" (divisor)\
: "r18"\
);
}

// ***************************************************************************
// *
// * "div8s" - 8/8 Bit Signed Division
// *
// * This subroutine divides the two register variables "r16" (dividend) and 
// * "r17" (divisor). The result is placed in "r16" and the remainder in
// * "r15".
// *  
// * Number of words	:22
// * Number of cycles	:103
// * Low registers used	:2 (r14,r15)
// * High registers used  :3 (r16/r16,r17,r18)
// *
// ***************************************************************************

// ***** Subroutine Register Variables

//r14 sign register
//r15 remainder
//r16	 result
//r16 dividend
//r17 divisor
//r18 loop counter

// ***** Code
void div8s(int8_t *result, int8_t *remainder, int8_t dividend, int8_t divisor)
{
__asm__ __volatile__ ( \
"div8s:	mov	r14,%A2 \n\t" /*move dividend to sign register*/ \
"	eor	r14,%A3 \n\t" /*xor sign with divisor*/ \
"	sbrc	%A3,7 \n\t" /*if MSB of divisor set*/ \
"	neg	%A3 \n\t" /*    change sign of divisor*/ \
"	sbrc	%A2,7 \n\t" /*if MSB of dividend set*/ \
"	neg	%A2 \n\t" /*    change sign of divisor*/ \
"	sub	%A1,%A1 \n\t" /*clear remainder and carry*/ \
"	ldi	r18,9 \n\t" /*init loop counter*/ \
"r14_1:	rol	%A2 \n\t" /*shift left dividend*/ \
"	dec	r18 \n\t" /*decrement counter*/ \
"	brne	r14_2 \n\t" /*if done*/ \
"	sbrc	r14,7 \n\t" /*    if MSB of sign register set*/ \
"	neg	%A2 \n\t" /*        change sign of result*/ \
"	rjmp r14_4 \n\t" /*    return*/ \
"r14_2:	rol	%A1 \n\t" /*shift dividend into remainder*/ \
"	sub	%A1,%A3 \n\t" /*remainder = remainder - divisor*/ \
"	brcc	r14_3 \n\t" /*if result negative*/ \
"	add	%A1,%A3 \n\t" /*    restore remainder*/ \
"	clc \n\t" /*    clear carry to be shifted into result			*/ \
"	rjmp	r14_1 \n\t" /*else*/ \
"r14_3:	sec \n\t" /*    set carry to be shifted into result*/ \
"	rjmp	r14_1 \n\t" \
"r14_4:	mov %A0,%A2 \n\t" \
: "+a" (*result), "+a" (*remainder) \
: "a" (dividend),  "a" (divisor)\
: "r14", "r18"\
);
}

// ***************************************************************************
// *
// * "div16u" - 16/16 Bit Unsigned Division
// *
// * This subroutine divides the two 16-bit numbers 
// * "r16H:r16L" (dividend) and "r19:r18" (divisor). 
// * The result is placed in "r17:r16" and the remainder in
// * "r15:r14".
// *  
// * Number of words	:19
// * Number of cycles	:235/251 (Min/Max)
// * Low registers used	:2 (r14,r15)
// * High registers used  :5 (r16/r16,r17/r17,r18,r19,
// *			    r20)
// *
// ***************************************************************************

// ***** Code
void div16u(uint16_t *result, uint16_t *remainder, uint16_t dividend, uint16_t divisor)
{
__asm__ __volatile__ ( \
"div16u:	clr	%A1 \n\t" /*clear remainder Low byte*/ \
"	sub	%B1,%B1 \n\t" /*clear remainder High byte and carry*/ \
"	ldi	r20,17 \n\t" /*init loop counter*/ \
"d16u_1:	rol	%A2 \n\t" /*shift left dividend*/ \
"	rol	%B2 \n\t" \
"	dec	r20 \n\t" /*decrement counter*/ \
"	brne	d16u_2 \n\t" /*if done*/ \
"	rjmp d16u_4 \n\t" /*    return*/ \
"d16u_2:	rol	%A1 \n\t" /*shift dividend into remainder*/ \
"	rol	%B1 \n\t" \
"	sub	%A1,%A3 \n\t" /*remainder = remainder - divisor*/ \
"	sbc	%B1,%B3 \n\t" /**/ \
"	brcc	d16u_3 \n\t" /*if result negative*/ \
"	add	%A1,%A3 \n\t" /*    restore remainder*/ \
"	adc	%B1,%B3 \n\t" \
"	clc \n\t" /*    clear carry to be shifted into result*/ \
"	rjmp	d16u_1 \n\t" /*else*/ \
"d16u_3:	sec \n\t" /*    set carry to be shifted into result*/ \
"	rjmp	d16u_1 \n\t" \
"d16u_4:	mov %A0,%A2 \n\t" \
"	mov %B0,%B2 \n\t" \
: "+r" (*result), "+r" (*remainder) \
: "a" (dividend),  "a" (divisor)\
: "r20" \
);
}

// ***************************************************************************
// *
// * "div16s" - 16/16 Bit Signed Division
// *
// * This subroutine divides signed the two 16 bit numbers 
// * "r17:r16" (dividend) and "r19:r18" (divisor). 
// * The result is placed in "r17:r16" and the remainder in
// * "r15:r14".
// *  
// * Number of words	:39
// * Number of cycles	:247/263 (Min/Max)
// * Low registers used	:3 (r13,r14,r15)
// * High registers used  :7 (r16/r16,r17/r17,r18,r19,
// *			    r20H)
// *
// ***************************************************************************

// ***** Subroutine Register Variables

//r13 sign register
//r14 remainder low byte
//r15 remainder high byte
//r16 result low byte
//r17 result high byte
//r16 dividend low byte
//r17 dividend high byte
//r18 divisor low byte
//r19 divisor high byte
//r20 loop counter

// ***** Code
void div16s(int16_t *result, int16_t *remainder, int16_t dividend, int16_t divisor)
{
asm volatile ( \
"div16s:	mov	r13,%B2 \n\t" /*move dividend High to sign register*/ \
"	mov %A2,%A2 \n\t" \
"	mov %B2,%B2 \n\t" \
"	eor	r13,%B3 \n\t" /*xor divisor High with sign register*/ \
"	sbrs	%B2,7 \n\t" /*if MSB in dividend set*/ \
"	rjmp	r13_1 \n\t" \
"	com	%B2 \n\t" /*    change sign of dividend*/ \
"	com	%A2		 \n\t" \
"	subi	%A2,-1 \n\t" \
"	sbci	%A2,-1 \n\t" \
"r13_1:	sbrs	%B3,7 \n\t" /*if MSB in divisor set*/ \
"	rjmp	r13_2 \n\t" \
"	com	%B3 \n\t" /*    change sign of divisor*/ \
"	com	%A3		 \n\t" \
"	subi	%A3,-1 \n\t" \
"	sbci	%B3,-1 \n\t" \
"r13_2:	clr	%A1 \n\t" /*clear remainder Low byte*/ \
"	sub	%B1,%B1 \n\t" /*clear remainder High byte and carry*/ \
"	ldi	r20,17 \n\t" /*init loop counter*/ \
"r13_3:	rol	%A2 \n\t" /*shift left dividend*/ \
"	rol	%B2 \n\t" \
"	dec	r20 \n\t" /*decrement counter*/ \
"	brne	r13_5 \n\t" /*if done*/ \
"	sbrs	r13,7 \n\t" /*    if MSB in sign register set*/ \
"	rjmp	r13_4 \n\t" \
"	com	%B2 \n\t" /*        change sign of result*/ \
"	com	%A2 \n\t" \
"	subi	%A2,-1 \n\t" \
"	sbci	%B2,-1 \n\t" \
"r13_4:	jmp r13_7 \n\t" /*    return*/ \
"r13_5:	rol	%A1 \n\t" /*shift dividend into remainder*/ \
"	rol	%B1 \n\t" \
"	sub	%A1,%A3 \n\t" /*remainder = remainder - divisor*/ \
"	sbc	%B1,%B3 \n\t" /**/ \
"	brcc	r13_6 \n\t" /*if result negative*/ \
"	add	%A1,%A3 \n\t" /*    restore remainder*/ \
"	adc	%B1,%B3 \n\t" \
"	clc \n\t" /*    clear carry to be shifted into result*/ \
"	rjmp	r13_3 \n\t" /*else*/ \
"r13_6:	sec \n\t" /*    set carry to be shifted into result*/ \
"	rjmp	r13_3 \n\t" \
"r13_7:mov %A0,%A2 \n\t" \
"	mov %B0,%B2 \n\t" \
: "+r" (*result), "+r" (*remainder) \
: "r" (dividend),  "r" (divisor)\
: "r13", "r20"\
);
}
