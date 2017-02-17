/*--elementele stivei sunt memorate intr-o lista generica simplu inlantuita--*/

/*DUMITRACE Daniela Andreea 311CB*/

#include "TStiva.h"

/* creeaza stiva vida cu elemente de dimensiune d;*/
void* InitS(size_t d)      
{ 
	AStiva a = (AStiva)malloc(sizeof (TStiva));			/* adresa descriptor alocat */
  	if(!a)
      return 0;

  	DIME_S(a) = d;

  	/* actualizeaza adrese  */
  	VF(a) = NULL;  
  	return (void*)a;
}

/* pune element in varful stivei */
int Push(void* a, void *ae)     
{ 
  ACelStiva aux = malloc(sizeof(TCelStiva));
  if(!aux) return 0;
  aux->info = malloc(DIME_S(a));
  if(!aux->info)
    {free(aux); return 0;}
  memcpy(aux->info, ae, DIME_S(a));

 if(VF(a) != NULL)
    aux->urm = VF(a);
  VF(a) = aux;
  return 1;
}

/* copiaza elementul din varful stivei la adresa ae */
int Top(void* a, void* ae)
{
  if(VF(a) == NULL)
    return 0;
  memcpy(ae , VF(a)->info, DIME_S(a)); /*copiaza elementul din varful stivei*/
  return 1;
}

/* extrage elementul din varful stivei la adresa ae */
int Pop(void* a, void *ae)
{
  if(!VF(a))
    return 0;
  memcpy(ae , VF(a)->info,DIME_S(a)); /*copiaza elementul din varful stivei*/
  VF(a) = VF(a)->urm;
  return 1;

}

void DistrS(void *a, my_free_Stack f) /*distrgue stiva*/
{ 
ACelStiva aux;
  while(VF(a)) /*cat timp sunt elemente*/
  {
    aux = VF(a);
    VF(a) = VF(a)->urm; /*retin varful si trec mai departe*/
    f(aux->info); /*eliberez informatia*/
    free(aux); /*eliberez celula*/
  }
 
  free(a);
a = NULL;

}

