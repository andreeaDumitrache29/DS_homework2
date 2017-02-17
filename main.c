/*DUMITRACE Daniela Andreea 311CB*/

#include "TStiva.h"
#include "TCoada.h"

#define max_char 256 /*numar maxim caracterepentru denumirea switch-urilor*/

typedef struct     /*structura de switch*/
{
	int id;
	char *denumire;
	char *functionare;
	char *ipV4;
}TSwitch;

void free_Switch(void*a)    /*functie de eliberat element de tip TSwitch*/
{
	TSwitch *aux = (TSwitch*)a;
	free(aux->ipV4);
	free(aux->denumire);
	free(aux->functionare);
	free(aux);
}

unsigned long convert_ip(void*a) /*functie de convertire a ip-ului in numar*/
{	
	TSwitch *x = (TSwitch*)a;
	char *ip = strdup(x->ipV4);   /*extragem campul ipV4 al elementului dat*/
	int i = 0;
	unsigned long v[4];  /*vector pentru a retine cele 4 componente ale ip-ului*/
	char *p = strtok(ip,"."); /*despart ip-ul in componente dupa .*/
	while (p != NULL)
	{
		v[i] = atoi(p);  /*convertesc componentele la int si le introduc in vector*/
		i++;   
    	p = strtok(NULL,".");
	}
	v[0] = v[0]<<23;  /*realizez shiftari pentru a aduce fiecare componenta pe pozitia potrivita*/
	v[0] = v[0]*2;
	v[1] = v[1]<<16;
	v[2] = v[2]<<8;
	unsigned long nr = v[0] | v[1] | v[2] | v[3]; /*fac sau pe biti intre componente pentru a obtine numarul dorit si returnez rezultatul*/
	return nr;
}

int sort_ip(void* a, void* b) /*calculeaza ip-ul pentru 2 elemente si le compara*/
{
	TSwitch x = *(TSwitch*)a;
	TSwitch y = *(TSwitch*)b;

	unsigned long x1 = convert_ip(&x); /*valorile numerice ale ip-urilor*/
	unsigned long y1 = convert_ip(&y);
	return x1 -y1;	/*copararea*/
}

void Afi_Switch(void *ae, FILE *f) /*afiseaza in fisier id-ul,ipV4 si denumirea switch-ului*/
{
	TSwitch *a = (TSwitch*)ae;   
	fprintf(f, "%d %s %s\n", a->id,  a->ipV4, a->denumire);
}

int nr_Elem(void *s)  /*calculeaza numarul de elemente dintr-o stiva*/
{
  AStiva *aux = InitS(DIME_S(s)); /*stiva auxiliara*/
	TSwitch a;
	int nr = 0;

	while(VF(s) != NULL)  /*cat timp exista elemente din stiva */
	{
		Pop(s, &a);  /*le extrag*/
		nr++;        //le numar
		Push(aux, &a);   /*le introduc in noua stiva*/
	}

	while(VF(aux) != NULL) /*extrag tot din stiva auxiliara si reintroduc in stiva initiala*/
	{ 
		Pop(aux, &a);
		Push(s, &a);
	}
	DistrS(aux, free_Switch); /*distruge stiva auxiliara*/
	return nr;
}

void Afi_Stack(void* s, FILE *f) /*afiseaza elementele din stiva*/
{
	AStiva *aux = InitS(DIME_S(s));
	TSwitch a;

	/*extrag elementele din stia, le alisez si le introduc in stiva auxiliara*/
	while(VF(s) != NULL)
	{
		Pop(s, &a);
		Afi_Switch(&a, f);
		Push(aux, &a);
	}

	/*extrag elementele din stiva auxiliara si le reintroduc in stiva initiala*/
	while(VF(aux) != NULL)
	{ 
		Pop(aux, &a);
		Push(s, &a);
	}
	DistrS(aux, free_Switch); /*distruge stiva auxiliara*/
}

int sort_id(void*a, void*b)  /*returneaza diferenta dintre id-urile a doua switch-uri*/
{
	TSwitch x = *(TSwitch*)a;
	TSwitch y = *(TSwitch*)b;
	return x.id - y.id;
}


void PrintQ(void* c, FILE *f)
{
	ACoada aux = InitQ(DIME(c)); /*coada auxiliara*/
	TSwitch a;

	fprintf(f, "{");

	/* cat timp sunt elemente in coada le extrag, afisez id-ul elementului si il introduc in coada auxiliara*/
	while(IC(c) != NULL)
	{ 
		ExtrQ(c, &a);
		fprintf(f, "%d ", a.id);
		IntrQ(aux, &a);
	}

	/*elimin elementele din coada auxiliara si le reintroduc in cea initiala*/
	while(IC(aux) != NULL)
	{	
		ExtrQ(aux, &a);
		IntrQ(c, &a);
	}
	fprintf(f, "}\n");
	DistrQ(aux, free_Switch);  /*distruge coada auxiliara*/
}

int addQ(int id, char *nume, char* ip, char* funct,  void* c)
{	
	/*creez elementul ce urmeaza a fi inserat*/
	TSwitch sw; 
	sw.id = id;
	sw.denumire = strdup(nume);
	sw.functionare = strdup(funct);
	sw.ipV4 = strdup(ip);
	
	ACoada aux_c = InitQ(DIME(c)); /*coada auxiliara*/
	TSwitch a;

	/*cat timp ip-ul elementului de inserat este mai mare decat al elementului curent*/
	while((IC(c) != NULL) && (sort_ip(&sw, IC(c)->info) > 0))
	{	
		ExtrQ(c, &a);  /*extrag elementul curent*/
		IntrQ(aux_c, &a); /*il introduc in coada auxiliara*/
	}

	IntrQ(aux_c, &sw); /*introduc elementul de inserat in coada auxiliara*/

	while(IC(c) != NULL)  /*introduc restul elementelor din coada in coada auxiliara*/
	{	
		ExtrQ(c, &a);
		IntrQ(aux_c, &a);
	}
	/*refac coada initiala*/
	while(IC(aux_c) != NULL)
	{	
		ExtrQ(aux_c, &a);
		IntrQ(c, &a);	
	}
	DistrQ(aux_c, free_Switch); /*distruge coada auxiliara*/
	return 1;
}

int Ins_Ord_Stack(void* b, void *s)
{
	AStiva aux = InitS(DIME_S(s)); /*stiva auxiliara*/
	if(!aux)
		return 0;
	TSwitch a;

	/*extrag elementele din stiva cat timp au id-ul mai mic decat elementul de inserat*/
	while(VF(s) != NULL && sort_id(b, VF(s)->info) > 0)
	{	
		if(nr_Elem(s) == 1) /*conditie pentru a nu modifica baza stivei*/
			break;
		Pop(s, &a);
		Push(aux, &a); 
	}

	Push(aux, b); /*elementul de intserat*/

	/*introduc restul elementelor din stiva in stiva auxiliara pana la baza*/
	while(VF(s) != NULL)
	{	if(nr_Elem(s) == 1)
			break;
		Pop(s, &a);
		Push(aux, &a);
	}
	/*refac stiva initiala*/
	while(VF(aux) != NULL)
	{
		Pop(aux, &a);
		Push(s, &a);
	}
	DistrS(aux, free_Switch);
	return 1;
}

int add_Stack(int id, char *nume, char* ip, char* funct,  void* s, char* principal)
{	
	/*elementul de inserat*/
	TSwitch sw; 
	sw.id = id;
	sw.denumire = strdup(nume);
	sw.functionare = strdup(funct);
	sw.ipV4 = strdup(ip);

	if(VF(s) == NULL) /*daca stiva e vida, inserez direct elementul*/
	{
		Push(s, &sw);
		return 1;
	}

	else
	{	
		AStiva aux = InitS(DIME_S(s)); /*stiva auxiliara*/
		if(!aux)
			return 0;

		TSwitch a, old_base;

		if(strcmp(principal, "BASE") == 0) /*trebuie schimbata baza stivei*/
		{
			while(VF(s) != NULL) /*cat timp sunt elemete in stiva*/
			{	
				if(nr_Elem(s) > 1) /*daca nu am ajunsla baza extrag din stiva si inserez in stiva auxiliara*/
				{
					Pop(s, &a);
					Push(aux, &a);
				}
				else if(nr_Elem(s) == 1) /*retin vechea baza*/
					Pop(s, &old_base);	
			}

			Push(s, &sw); /*introduc  noua baza*/
			
			while(VF(aux) != NULL) /*inserez in stiva initiala elementele din stiva auxiliara*/
			{
				Pop(aux, &a);
				Push(s, &a);
			}
			DistrS(aux, free_Switch); /*distrug stiva auxiliara*/
			Ins_Ord_Stack(&old_base, s); /*inserez vechea baza in stiva initiala*/
			return 1;
		}

		else if(strcmp(principal,"NON_BASE") == 0) /*nu se modifica baza*/
		{	
			/*extrag elementele din stiva cat timp au id-ul mai mic decat elementul de inserat* si le introduc in stiva auxiliara*/
			while(VF(s) != NULL && sort_id(&sw, VF(s)->info) > 0)
			{	
				if(nr_Elem(s) == 1) /*conditie pentru a nu extrage si baza stivei*/
					break;
				Pop(s, &a);
				Push(aux, &a); 
			}

			Push(aux, &sw); /*introdul elementul de inserat in stiva auxiliara*/

			/*extrag si restul elementelor din stiva initiala pana la  baza si le introduc in noua stiva*/
			while(VF(s) != NULL)
			{
				if(nr_Elem(s) == 1)
					break;
				Pop(s, &a);
				Push(aux, &a);
			}

			while(VF(aux) != NULL) /*extrag elementele din stiva auxiliara si le reintroduc in stiva initiala*/
			{
				Pop(aux, &a);
				Push(s, &a);
			}
			DistrS(aux, free_Switch); /*distruge stiva auxiliara*/
			return 1;
		}
	}
}

void show(void *c, void**s, FILE*f, int n)
{	
	PrintQ(c,f); /*printeaza id-urile elementelor din coada*/
	int i;
	for(i = 0; i<n; i++) /*pentru fiecare stiva*/
	{
		fprintf(f, "%d:\n", i); /*afiseaza indicele ei elementele*/
		Afi_Stack(s[i], f);
	}
}

int ipmin(FILE *f, void*c)
{
	if(IC(c) == NULL) /*daca coadae nula afiseaza 0*/
	{
		fprintf(f, "ipmin=0\n");
		return 0;
	}
	else
	{
		TSwitch a;
		PrimQ(c,&a); /*copiaza in a primul element din coada*/
		unsigned long ip = convert_ip(&a); /*calculeaza ip-ul acestuia si il afiseaza*/
		fprintf(f, "ipmin=%lu\n", ip);
		return 1;
	}
}

void del(int id, void*c, void**s, int n)
{
	ACoada aux_Q = InitQ(DIME(c)); /*coada auxiliara*/
	TSwitch a;
	int i, ok = 0;
	/*caut intai in coada elementul dorit*/

	/*extrag elementele din coada si le introduc in coada auxiliara daca nu au id-ul elementului cautat*/
	while(IC(c) != NULL) 
	{
		ExtrQ(c, &a);
		if(a.id != id)
			IntrQ(aux_Q, &a);
		else
			ok = 1;
	}

	/*introduc si restul elementelor in coada auxiliara*/
	while(IC(aux_Q) != NULL)
	{
		ExtrQ(aux_Q, &a);
		IntrQ(c, &a);
	}

	DistrQ(aux_Q, free_Switch); /*distruge coada auxiliara*/

	if(ok == 1) /*daca nu am gasit elementul in coada caut si in stive*/
		return;
	
	for (i = 0; i < n; i++)
	{	
		AStiva aux_S = InitS(DIME_S(s[i])); /*stiva auxliara*/
		if(s[i] != NULL)
		{
			while(VF(s[i]) != NULL)
			{
				Pop(s[i], &a);
				if(a.id != id)
					Push(aux_S, &a);
				else
					ok = 1;				
			}

			while(VF(aux_S) != NULL)
			{
				Pop(aux_S, &a);
				Push(s[i], &a);
			}
		}
		DistrS(aux_S, free_Switch);

		if(ok == 1)
			return;
	}

}

void setQ(int id, void*c, void**s, int n) /*set pentrufunctionare "SINGLE"*/
{
	TSwitch a;
	int i, ok = 0;
	/*caut doar in stive, deoarece daca elementul cautat se afla in coada nu trebuie efectuata nicio modificare*/
	for (i = 0; i < n; i++) //pentru fiecare stiva
	{
	AStiva aux_S = InitS(DIME_S(s[i])); /*stiva auxiliara*/
	
		while(VF(s[i]) != NULL)
		{
			Pop(s[i], &a);  
			if(a.id != id)/*extrag elementele din stiva si verific dau au id-ul elementului cautat*/
				Push(aux_S, &a); /*daca nu le introduc in stiva auxiliara*/
			else
			{
				addQ(a.id, a.denumire, a.ipV4, a.functionare, c); /*daca da, il introduc in coada*/
				ok = 1;
			}
		}

		/*reintroduc elementele din stiva auxiliara in cea intiala*/
		while(VF(aux_S) != NULL)
		{
			Pop(aux_S, &a);
			Push(s[i], &a);
		}

		DistrS(aux_S, free_Switch); /*distruge stiva auxiliara*/
		if(ok == 1) /*conditie de iesire daca s-a gasit deja elementul*/
			return;		
	}
}

/*set pentru functionare "STACK"*/
void set_Stack(int id, int id_stiva, char *principal, void*c, void**s, int n)
{
	ACoada aux_Q = InitQ(DIME(c)); /*coada auxiliara*/
	TSwitch a;
	int i, ok = 0, sw = 0;
	/*caut elementul intai in coada*/
	while(IC(c) != NULL)
	{
		ExtrQ(c, &a);
		if(a.id != id) /*daca elementul extras nu are id-ul dorit il introduc in coada auxiliara*/
			IntrQ(aux_Q, &a);
		else
		{	ok = 1; sw = 1;
			add_Stack(a.id, a.denumire, a.ipV4, a.functionare, s[id_stiva], principal); /*altfel il inserez in stiva indicata*/
			break;
		}
	}

	if(ok == 1) /*insereaza si restul elementelor in coada auxiliara pentru a pastra ordinea*/
	{
		while(IC(c) != NULL)
		{
			ExtrQ(c, &a);
			IntrQ(aux_Q, &a);
		}
	}

	while(IC(aux_Q) != NULL) /*reintroduce elementele in vechea coada*/
	{
		ExtrQ(aux_Q, &a);
		IntrQ(c, &a);
	}

	DistrQ(aux_Q, free_Switch);
	if(sw == 1)
		return;

	for (i = 0; i < n; i++) /*daca nu a fost gasit elementul in coada caut in fiecare stiva*/
	{
		AStiva aux_S = InitS(DIME_S(s[i]));
		
		while(VF(s[i]) != NULL)
		{
			Pop(s[i], &a); /*extrag din stiva*/
			if(a.id != id)
				Push(aux_S, &a); /*daca nu e elementul dorit il inserez in stiva auxiliara*/
			else
			{	
				ok = 1; sw == 1; /*altfel il inserez in stiva indicata*/
				add_Stack(a.id, a.denumire, a.ipV4, a.functionare, s[id_stiva], principal);
				break;
			}
		}		

		if(ok == 1)
		{
			while(VF(s[i]) != NULL)
			{ 
				Pop(s[i], &a); /*extrag si restul elementelor si le pun in stiva auxiliara*/
				Push(aux_S, &a);
			}
		}

		/*reintroduc elementele in stiva initala*/
		while(VF(aux_S) != NULL)
		{
			Pop(aux_S, &a);
			Push(s[i], &a);
		}
		
		DistrS(aux_S, free_Switch); /*distruge stiva auxiliara*/
		if(sw == 1) /*nu mai cauta si in restul stivelor daca a fost gasit elementul*/
			break;
	}
}

int main(int argc, char const *argv[])
{	
	char *sursa, *dest;
	sursa = strdup(argv[1]);  //fisierul de intrare
	dest = strdup(argv[2]);   //fisierul de iesire

	FILE *f1 = fopen(sursa, "r");
	FILE *f2 = fopen(dest, "w");

	char *op = calloc(100, sizeof(char)); //operatia
	int n, id, id_stiva, i;
	fscanf(f1, "%d", &n); /*numarul de stive*/
	char *nume = malloc(max_char), *ip = malloc(20); /*parametrii ce urmeaza sa fie cititi*/
	char * funct = malloc(max_char);
	char *principal = malloc(20);

	ACoada c = InitQ(sizeof(TSwitch)); /*creez coada*/
	void **s = malloc(n*sizeof(TStiva));  /*creez vectorul destive*/

	for (i = 0; i < n; ++i)
	{
		s[i] = InitS(sizeof(TSwitch)); /*initializeaza stivele din vector*/
	}

	while(fscanf(f1, "%s", op) == 1) //citesc cate o operatie pana la finalul fisierului
	{	
		/*in functie de operatia citita citesc si restul parametrilor si apelez functiile corespunzatoare*/
		if(strcmp(op, "add") == 0)  
		{	
			fscanf(f1, "%d", &id);
			fscanf(f1, "%s", nume);
			fscanf(f1, "%s", ip);
			fscanf(f1, "%s", funct);
			
			if (strcmp(funct, "SINGLE") == 0)
			{	
				addQ(id, nume, ip, funct, c);					
			}
			else if (strcmp(funct, "STACK") == 0)
			{	
				fscanf(f1, "%d", &id_stiva);
				fscanf(f1, "%s", principal);
				add_Stack(id, nume, ip, funct, s[id_stiva], principal);

			}
		}
		else if(strcmp(op, "show") == 0)
		{	
			show(c, s, f2, n);
			fprintf(f2, "\n");			
		}
		else if(strcmp(op, "ipmin") == 0)
			ipmin(f2, c);
		
		else if(strcmp(op,"del") == 0)
		{
			fscanf(f1, "%d", &id);
			del(id, c, s, n);
		}
		else if(strcmp(op, "set") == 0)
		{
			fscanf(f1, "%d", &id);
			fscanf(f1, "%s", funct);

			if(strcmp(funct,"SINGLE") == 0)
				setQ(id, c, s, n);
			else if(strcmp(funct,"STACK") == 0)
			{	
				fscanf(f1, "%d", &id_stiva);
				fscanf(f1, "%s", principal);
				set_Stack(id, id_stiva, principal, c, s, n);
			}	
		}

	}	
		
	/*eliberez ce am alocat*/
	free(op);
	free(sursa);
	free(dest);
	free(nume); free(ip);
	free(funct);free(principal);
	for(i = 0; i<n; i++)
		DistrS(s[i], free_Switch);
	DistrQ(c, free_Switch);
	free(s);
	fclose(f1);
	fclose(f2);

	return 0;
}
