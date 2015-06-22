# AVR200and201assemblyArduino
AVR200 and AVR201 Atmel(r) application notes as inline statements for the Arduino

Jose Gama June, 2015

Atmel(r) released the application note AVR200 in 1996 with AVR Assembly language code for fixed-point multiplication and division. This application note is divided in AVR200 (optimized for size) and AVR200 (optimized for speed).
In 2005, Atmel(r) released the application note AVR201 with AVR Assembly language code for fixed-point multiplication and division for Atmel(r) microcontrollers with hardware multiplication.
Using Assembly language with the Arduino IDE requires either modifying the IDE or using inline statements. The code presented here has versions of the application notes AVR200 and AVR201, with inline statements, as functions or C preprocessor macros.

Contents of the application notes:

200b
"mpy8u" - 8x8 Bit Unsigned Multiplication
"mpy16u" - 16x16 Bit Unsigned Multiplication
"div8u" - 8/8 Bit Unsigned Division
"div16u" - 16/16 Bit Unsigned Division

200
"mpy8u" - 8x8 Bit Unsigned Multiplication
"mpy8s" - 8x8 Bit Signed Multiplication
"mpy16u" - 16x16 Bit Unsigned Multiplication
"mpy16s" - 16x16 Bit Signed Multiplication
"div8u" - 8/8 Bit Unsigned Division
"div8s" - 8/8 Bit Signed Division
"div16u" - 16/16 Bit Unsigned Division
"div16s" - 16/16 Bit Signed Division

201
"mul16x16_16" - Multiply of two 16bits numbers with 16bits result.
"mul16x16_32" - Unsigned multiply of two 16bits numbers with 32bits result.
"mul16x16_24" - Unsigned multiply of two 16bits numbers with 24bits result.
"muls16x16_32" - Signed multiply of two 16bits numbers with 32bits result.
"muls16x16_24" - Signed multiply of two 16bits numbers with 24bits result.
"mac16x16_24" - Signed multiply accumulate of two 16bits numbers with a 24bits result.
"mac16x16_32" - Signed multiply accumulate of two 16bits numbers with a 32bits result.
"fmuls16x16_32" - Signed fractional multiply of two 16bits numbers with 32bits result.
"fmac16x16_32" - Signed fractional multiply accumulate of two 16bits numbers with a 32bits result.



References:
AVR200: Multiply and Divide Routines 1996
Atmel(r) application note

AVR201: Using the AVR(r) Hardware Multiplier 2005
Atmel(r) application note

