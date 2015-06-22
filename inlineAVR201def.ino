// ****************************************************************************
// *
// * Test Program
// *
// * This program calls all the subroutines as an example of usage and to 
// * verify correct verification.
// *
// ****************************************************************************

// created by Jose Gama for the Arduino, May 2015
// based on the test code from AVR201

#include <Arduino.h>
#include "inlineAVR201def.h"
  
void setup()
 {
 Serial.begin(9600);
 Serial.println("Start");
 }

void loop()
 {
 uint16_t i, j, k;
 int16_t is, js;
 uint32_t m;
 int32_t ms;
 
 // *	mul16x16_16	- Multiply of two 16bits numbers with 16bits result.
 i = 2500;
 j = 15;
 mul16x16_16(k, i, j);
 Serial.print("mul16x16_16 ");
 Serial.print(i);
 Serial.print(" * ");
 Serial.print(j);
 Serial.print(" = ");
 Serial.println(k);
 
 // *	mul16x16_32	- Unsigned multiply of two 16bits numbers with 32bits result.
 i = 8192;
 j = 12;
 mul16x16_32(m, i, j);
 Serial.print("mul16x16_32 ");
 Serial.print(i);
 Serial.print(" * ");
 Serial.print(j);
 Serial.print(" = ");
 Serial.println(m);
 
 // *	mul16x16_24	- Unsigned multiply of two 16bits numbers with 24bits result.
 i = 555;
 j = 256;
 mul16x16_24(m, i, j);
 Serial.print("mul16x16_24 ");
 Serial.print(i);
 Serial.print(" * ");
 Serial.print(j);
 Serial.print(" = ");
 Serial.println(m);

// *	muls16x16_32	- Signed multiply of two 16bits numbers with 32bits result.

 is = 9035;
 js = -78;
 muls16x16_32(ms, is, js);
 Serial.print("muls16x16_32 ");
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(" = ");
 Serial.println(ms); 
 
// *	muls16x16_24	- Signed multiply of two 16bits numbers with 24bits result.

 is = 5014;
 js = -7;
 muls16x16_24(ms, is, js);
 ms +=0xFF000000; //invert bits 24 to 31 because the storage is in 32 bits signed
 Serial.print("muls16x16_24 ");
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(" = ");
 Serial.println(ms); 

// *	mac16x16_24	- Signed multiply accumulate of two 16bits numbers with a 24bits result.

 is = 5013;
 js = -5;
 ms = 10000;
 Serial.print("mac16x16_24 ");
 Serial.print(ms);
 Serial.print(" + ");
 mac16x16_24(ms, is, js);
 ms +=0xFF000000;
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(" = ");
 Serial.println(ms); 

// *	mac16x16_32	- Signed multiply accumulate of two 16bits numbers with a 32bits result.

 is = -1844;
 js = 55;
 ms = 2000;
 Serial.print("mac16x16_32 ");
 Serial.print(ms);
 Serial.print(" + ");
 mac16x16_32(ms, is, js);
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(" = ");
 Serial.println(ms); 

// *	mac16x16_32_method_B	- Signed multiply accumulate of two 16bits numbers with a 32bits result.

 is = -1845;
 js = 99;
 ms = 3000;
 Serial.print("mac16x16_32_method_B ");
 Serial.print(ms);
 Serial.print(" + ");
 mac16x16_32_method_B(ms, is, js);
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(" = ");
 Serial.println(ms); 

// *	fmuls16x16_32	- Signed fractional multiply of two 16bits numbers with 32bits result.

 is = -1000;
 js = 99;
 fmuls16x16_32(ms, is, js);
 Serial.print("fmuls16x16_32 (");
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(") < 1 = ");
 Serial.println(ms); 

// *	fmac16x16_32	- Signed fractional multiply accumulate of two 16bits numbers with a 32bits result.
 
 is = -2000;
 js = -44;
 ms = 333;
 Serial.print("fmac16x16_32 (");
 Serial.print(ms);
 Serial.print(" + ");
 fmac16x16_32(ms, is, js);
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(") < 1 = ");
 Serial.println(ms); 

// *	fmac16x16_32_method_B - uses two temporary registers (r4,r5), but reduces cycles/words by 2
 is = -3000;
 js = -89;
 ms = 567;
 Serial.print("fmac16x16_32_method_B (");
 Serial.print(ms);
 Serial.print(" + ");
 fmac16x16_32_method_B(ms, is, js);
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(") < 1 = ");
 Serial.println(ms);

 delay(10000);
 }
