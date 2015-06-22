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
#include "inlineAVR200Bdef.h"
 
void setup()
 {
 Serial.begin(9600);
 }

void loop()
 {
 uint8_t a, b, c, d;
 uint16_t i, j, k, l;
 uint32_t m;
 
 //***** Multiply Two Unsigned 8-Bit Numbers (250 * 4)
 a = 250;
 b = 4;
 mpy8u(i, a, b);
 Serial.print("mpy8u ");
 Serial.print(a);
 Serial.print(" * ");
 Serial.print(b);
 Serial.print(" = ");
 Serial.println(i);

 //***** Multiply Two Unsigned 16-Bit Numbers (5050 * 10,000) = 50,500,000
 i = 5050;
 j = 10000;
 mpy16u(m,i,j);
 Serial.print("mpy16u ");
 Serial.print(i);
 Serial.print(" * ");
 Serial.print(j);
 Serial.print(" = ");
 Serial.println(m);

 //***** Divide Two Unsigned 8-Bit Numbers (100/3) = 33  remainder 1
 a = 100;
 b = 3;
 div8u(c, d, a, b);
 Serial.print("div8u ");
 Serial.print(a);
 Serial.print(" / ");
 Serial.print(b);
 Serial.print(" = ");
 Serial.print(c);
 Serial.print(" rem= ");
 Serial.println(d);

 //***** Divide Two Unsigned 16-Bit Numbers (50,000/24,995) = 2  remainder 10
 i = 50000;
 j = 24995;
 div16u(k, l, i, j);
 Serial.print("div16u ");
 Serial.print(i);
 Serial.print(" / ");
 Serial.print(j);
 Serial.print(" = ");
 Serial.print(k);
 Serial.print(" rem= ");
 Serial.println(l);
  
 delay(10000);
 }
