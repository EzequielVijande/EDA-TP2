#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#define ALLEGRO_STATICLINK
//#include "allegro5/allegro.h"
#include "ParserFunc.h"
//#include "fractals.h"
#include "uData.h"

enum {TRIANGLE,POLYGON, MANDELBROT}; //Fractal types.

#define ON 1	//Flag states.
#define OFF 0

int
Callback(char *key, char *value, void *userData);

/**
*	Callback - Fractals - Luciano Castrogiovanni 
*		This function recieves arguments sorted as a -key with a value by a parser and interprets
*	them passing the value to the respectful owner as well as stopping single parameters or
*   duplicated keys or values with a respectful error message and exit.
**/

int
CheckParameters(userDataType *uData);

/**
*	Check Parameters - Fractals - Luciano Castrogiovanni 
*		This function recieves the user defined values structure after it has been filled by the
*	Callback function and validates each value on its range and respective fractal types checking
*	for incompatibilities. If found, the function exits with a respective error message.
**/

int isanumber(char* value);

/**
*	isnumber - Luciano Castrogiovanni 
*		This function recieves a string and analyzes if it is constituted solely by a number which 
*	can contain a single decimal point. Returns 0 if the string isn't a number and returns 1 
*	otherwise.
**/