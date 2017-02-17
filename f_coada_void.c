/*--elementele cozii sunt memorate intr-o lista generica simplu inlantuita --*/

/*DUMITRACE Daniela Andreea 311CB*/

#include "TCoada.h"

/* creeaza coada vida cu elemente de dimensiune d; */

void* InitQ(size_t d)
{ 
	ACoada a = (ACoada)malloc(sizeof(TCoada));  	/* adresa descriptor alocat */
  	if(!a)
  		return 0;

 	DIME(a) = d; 

  	/* actualizeaza adrese */
  	IC(a) = NULL;
  	SC(a) = NULL;

  	return (void*)a;
}

int IntrQ(void* c, void* ae)
{
  ACel aux = malloc(sizeof(TCel)); /*elementul ce urmeaza a fi inserat*/
  if(!aux) return 0;
  aux->info = malloc(DIME(c)); /*alocari de memorie*/
  aux->urm = NULL;
  if(!aux->info)
    {free(aux); return 0;}
  memcpy(aux->info, ae, DIME(c)); /*copiz informatia in parametru in noua celula*/

	if(IC(c) == NULL) /*daca coada e nulas si sfaristul si inceputul pointeaza la noua celula*/
	{
		IC(c) = aux;
		SC(c) = aux;
	}
	else /*altfel inserez noua celula la sfrsit si actualizez sfarsitul*/
	{
		SC(c)->urm = aux;
		SC(c) = aux;
	}	
	return 1;
}

int ExtrQ(void*c, void* ae)
{
	if(IC(c) == NULL) /*coada nula, nu am ce sa extrag*/
		return 0;
	
	memcpy(ae, IC(c)->info, DIME(c)); /*copiez in ae informatia din inceput*/

	if(IC(c) == SC(c)) /*daca am o singura celula actualizez si inceputul si sfarsitul*/
	{
		IC(c) = IC(c)->urm;
		SC(c) = SC(c)->urm;
	}
	else
		IC(c) = IC(c)->urm; /*altfel actualizez doar inceputul*/

	return 1;
}

void DistrQ(void *c, my_free f) 
{
	while(IC(c) != NULL) /*cat timp exista elemente in coada*/
	{
		ACel aux = IC(c);  /*retin prima celula*/
		IC(c) = IC(c)->urm; /*avans in inceput*/
		f(aux->info); /*eliberez informatia si celula*/
		free(aux);
	}

	free(c);
	c = NULL;
	
}

void PrimQ(void *c, void*ae)
{
	if(IC(c) == NULL) /*daca coada e vida nu am ce sa copiez*/
		return;
	memcpy(ae,IC(c)->info,DIME(c)); /*copiaza in ae informatia din varf*/
}