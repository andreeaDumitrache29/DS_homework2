#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/*DUMITRACE Daniela Andreea 311CB*/

typedef struct cel    /*structura pentru lista generica simplu inlantuita*/
{
	struct cel *urm;
	void* info;
}TCel, *ACel;

typedef struct    /*structura pentru coada*/
{ 
	size_t dime;
	ACel ic, sc;
} TCoada, *ACoada;

typedef void (*my_free)(void*);  /*functie de  eliberat element */

/*- macrodefinitii - acces campuri -*/
#define IC(a) 	(((ACoada)(a))->ic)
#define SC(a) 	(((ACoada)(a))->sc)
#define DIME(a) (((ACoada)(a))->dime)

void* InitQ(size_t d); /* creeaza coada vida cu elemente de dimensiune d;
							  anumite implementari pot necesita si alti parametri */
int IntrQ(void* a, void* ae); /* adauga element la sfarsitul cozii */
int ExtrQ(void* a, void* ae); /* extrage primul element din coada la adresa ae */
void DistrQ(void *c, my_free f);  /*elibereaza memoria alocata pentru coada*/
void PrimQ(void*c, void*a);   /*copiaza primul element din coada la adresa ae*/

