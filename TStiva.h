#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <ctype.h>

/*DUMITRACE Daniela Andreea 311CB*/

typedef struct celst    /*structura pentru lista generica simplu inlantuita*/
{
	struct celst *urm;
	void* info;
}TCelStiva, *ACelStiva;

typedef struct stiva  /*structura pentru stiva*/
{ 
	size_t 	dime; 		
	ACelStiva vf;
} TStiva, *AStiva;

typedef void (*my_free_Stack)(void*);  /*functie de eiberat ele

/*- macrodefinitii - acces campuri */
#define DIME_S(a) (((AStiva)(a))->dime)
#define VF(a) 	(((AStiva)(a))->vf)

void* InitS(size_t d);    /* initializeaza stiva cu elem.de dimensiune d;
				  					anumite implementari pot necesita si alti parametri */
int Push(void* a, void* ae);  /* pune element in varful stivei */
int Pop (void* a, void* ae);  /* extrage elementul din varful stivei la adresa ae */
int Top (void* a, void* ae);  /* copiaza elementul din varful stivei la adresa ae */
void DistrS (void* aa, my_free_Stack f);      /* elibereaza intregul spatiu ocupat de stiva */



