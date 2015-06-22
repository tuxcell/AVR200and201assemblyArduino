// ****************************************************************************
// *
// * Test Program
// *
// * This program calls all the subroutines as an example of usage and to 
// * verify correct verification.
// *
// ****************************************************************************

// created by Jose Gama for the Arduino, May 2015
// based on the test code from AVR200

#include <Arduino.h>
#include "inlineAVR200def.h"
 
void setup()
 {
 Serial.begin(9600);
 }

void loop()
 {
 uint8_t a, b, c, d;
 int8_t as, bs, cs, ds;
 uint16_t i, j, k, l;
 int16_t is, js, ks, ls;
 uint32_t m;
 int32_t ms;
  
 // ***** Multiply Two Unsigned 8-Bit Numbers (250 * 4) = 1000
 a = 250;
 b = 4;
 mpy8u(i, a, b);
 Serial.print("mpy8u ");
 Serial.print(a);
 Serial.print(" * ");
 Serial.print(b);
 Serial.print(" = ");
 Serial.println(i);
 
 // ***** Multiply Two Signed 8-Bit Numbers (-99 * 88) = -8712
 as = -99;
 bs = 88;
 mpy8s(is, as, bs);
 Serial.print("mpy8s ");
 Serial.print(as);
 Serial.print(" * ");
 Serial.print(bs);
 Serial.print(" = ");
 Serial.println(is);

 // ***** Multiply Two Unsigned 16-Bit Numbers (5050 * 10,000) = 50,500,000
 i = 5051;
 j = 10003;
 mpy16u(m,i,j);
 Serial.print("mpy16u ");
 Serial.print(i);
 Serial.print(" * ");
 Serial.print(j);
 Serial.print(" = ");
 Serial.println(m);

 // ***** Multiply Two Signed 16-Bit Numbers (-12345*(-4321)) = 53342745
 is = -12345;
 js = -4321;
 mpy16s(ms,is,js);
 Serial.print("mpy16s ");
 Serial.print(is);
 Serial.print(" * ");
 Serial.print(js);
 Serial.print(" = ");
 Serial.println(ms);

 // ***** Divide Two Unsigned 8-Bit Numbers (100/3) = 33  remainder 1
 a = 100;
 b = 3;
 div8u(c, d, a, b);
 Serial.print(a);
 Serial.print(" / ");
 Serial.print(b);
 Serial.print(" = ");
 Serial.print(c);
 Serial.print(" rem= ");
 Serial.println(d);

 // ***** Divide Two Signed 8-Bit Numbers (-113/-11) = 10 rem 3
 as = -113;
 bs = 11;
 div8s(cs, ds, as, bs);
 Serial.print(as);
 Serial.print(" / ");
 Serial.print(bs);
 Serial.print(" = ");
 Serial.print(cs);
 Serial.print(" rem= ");
 Serial.println(ds);

 // ***** Divide Two Unsigned 16-Bit Numbers (50,000/60,000) = 0  remainder 50,000
 i = 50000;
 j = 60000;
 div16u(k, l, i, j);
 Serial.print(i);
 Serial.print(" / ");
 Serial.print(j);
 Serial.print(" = ");
 Serial.print(k);
 Serial.print(" rem= ");
 Serial.println(l);

 // ***** Divide Two Signed 16-Bit Numbers (-22,222/10) = -2222 rem 2
 is = -22222;
 js = 10;
 div16s(ks, ls, is, js);
 Serial.print(is);
 Serial.print(" / ");
 Serial.print(js);
 Serial.print(" = ");
 Serial.print(ks);
 Serial.print(" rem= ");
 Serial.println(ls); 

 delay(10000);
 }
