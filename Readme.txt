		f-stiva_void.c
	
	InitS
 Creeaza stiva vida cu elemente de dimensiune d. Se aloca memorie pentru noua stiva si se intializeaza varful cu NULL.

 	Push
 Pune elementul ae in varful stivei. Creez o noua celula de lista in care copiez informatia din ae si o inserez in varful stivei, apoi mut varful pe noul element.

 	Top
 Copiaza elementul din varful stivei la adresa ae.
	
	Pop
Extrage elementul din varful stivei. Copiaza informatia din varf la adresa ae si muta varful pe elementul urmator din stiva

	DistrS
Retin varful intr-o noua celula pe care o distrug, aopi trec mai departe, actualizand varful. Operatia se repeta pentru fiecare element din stiva.

		f_coada_void.c

	InitQ
Creeaza coada vida cu elemente de dimensiune d. Se aloca memorie pentru noua coada si se intializeaza inceputul si sfarsitul cu NULL.

	IntrQ
 Pune elementul ae la finalul cozii. Creez o noua celula de lista in care copiez informatia din ae si o inserez la sfrsit, apoi mut sfarsitul pe noul element.

 	ExtrQ
Extrage elementul din varful cozii. Copiaza informatia din inceput laadresa ae si actualizeaza inceputul.

	DistrQ
Retin inceputul intr-o noua celula pe care o distrug, aopi trec mai departe, actualizand inceputul. Operatia se repeta pentru fiecare element din coada.

	PrimQ
Copiez in ae informativa din inceputul cozii, fara a-l modifica.

		
		main.c

	free_switch
Elibereaza element de tip TSwitch
	
	convert_ip
Functie de convertire a ip-ului in numar. Retin campul ipV4 al elemetului dat. Apoi, separandu-l in componente dupa . convertesc fiecare componenta in parte intr-un numar si le retin intr-un vector. La final shiftez fiecare componenta si le "adun", astfel incat sa obtin numarul dorit.

	sort_ip
Calculeaza ip-ul adoua elemente folosind convert_ip si returneaza diferenta.

	Afi_Switch
Afiseaza in fisier id-ul,ipV4 si denumirea switch-ului

	nr_Elem
Returneaza numarul de elemente din stiva. Extrag din stiva, retin elementele intr-o stiva auxiliara si actualizez un contor la fiecare element. Apoi refac stiva si returnez contorul.

	Afi_Stack
Extrag din stiva, retin elementele intr-o stiva auxiliara si afisez fiecare elemen, apoi refac stiva.

	sort_id
Returneaza diferenta dintre id-urile a doua switch-uri.

	PrintQ
Cat timp sunt elemente in coada le extrag, afisez id-ul elementului si il introduc in coada auxiliara, apoi refac coada intiala.

	addQ
creez elementul ce urmeaza a fi inserat si o coada auxiliara. Extrag elemente din coada si le pun in auxiliara pana ajung in locul unde trebuie inserat elementul dorit. Introduc apoi elementul dorit si restul elemtelor pana la baza in auxiliar si refac coada initiala.

	Ins_Ord_Stack
extrag elementele din stiva cat timp au id-ul mai mic decat elementul de inserat sau pana ajung la baza stivei si le introduc in stiva auxiliara. Apoi inserez in auxiliara elementul dorit si restul elementelor. La final refac stiva auxiliara.

	add_Stack
Creez elementul de inserat. Daca stiva e nula inserez direct elementul. 

Daca elementul de inserat trebuie introdus la baza extrag toate elementele din stiva si le introduc in auxiliar, retinand sepaat vechea  baza, inserez elementul dorit la baza. Introduc apoi elementele din auxiliar in stiva intiala si inserez ordonat la final vechea baza.

Daca elementul de insersat nu inlocuie baza inserez la fel ca in Ins_Ord_Stack.

	show
Afisez coada si toatele elementele din vectorul de stive conform enuntului folosind functiile de afisare de mai sus.

	ipmin
Daca coadaeste nula se afiseaza 0. Altfel copiez informatia din varful cozii *aici se afla switch-ul cu ip-ul cel mai mic*, il convertesc in numar si il afisez.

	del
Caut elementul intai in coada, apoi in stive. Extrag elementele din stva/coada si le introduc intr-o auxiliara atata timp cat nu au id-ul specificat, apoi refac stiva/coada intiala. Daca elementul a fost gasit ma opresc la urmatoarea cautare. 

	setQ
Daca functionalitatea elementului dat este "SINGLE" caut doar in stive, deoarece daca elementul cautat se afla in coada nu trebuie efectuata nicio modificare. Extrag elementele si le introduc intr-o auxiliara atata timp cat nu au id-ul specificat, apoi refac stiva intiala. Daca a fost gasit elementul dorit, acesta este inserat in coada folosind addQ.

	set_Stack
Caut elementul intai in coada, apoi in stive. Extrag elementele din stva/coada si le introduc intr-o auxiliara atata timp cat nu au id-ul specificat, apoi refac stiva/coada intiala. Daca elementul a fost gasit il inserez in stivaspecificata folosind add_Stack si ma opresc la urmatoarea cautare.

	main
Citesc argumentele, deschid fisierele din intrare si iesire, citesc numarul de stive din fisier si intializez vectorul de stive + componente, coada si sirurile in care voi citii parametrii. 
Citesc cate o operatie pana la sfrsitul fisierului si in functie de aceasta citesc parametrii necesari si apelez functiile corespunzatoare

Punctaj checker local: 77/85