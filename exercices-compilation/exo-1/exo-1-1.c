#include <stdio.h>
#include <stdlib.h>

extern char etext, edata, end;

// Text and rodata
int const cnst = 0x23;

// .rodata
char *p1 = "solution exo-1!\n";

// .data
char p2[] = "solution exo-1 intelligente\n";

// bss
int bss;
int bss2 = 0;

int main(){
	// pile
	int x = 0x3334;

	// tas
	int *alloc = (int*)malloc(sizeof(int));

	// print les adresses de chaque type
	printf("adresse de text ou rodata : %p \n",&cnst);
	printf("adresse de rodata : %p \n",p1);
	printf("adresse de data : %p \n",p2);
	printf("adresse de bss : %p et ça aussi %p \n",&bss, &bss2);
	printf("adresse de pile : %p \n",&x);
	printf("adresse du tas : %p \n",alloc);
	
	// Utilisation des symboles spéciaux
	
	printf("adresse de fin de .text (etext) : %p\n", &etext);
	// printf("adresse de début de .data (data) : %p\n", &data);
	printf("adresse de fin de .data (edata) : %p\n", &edata);
	printf("adresse de fin de .bss (end) : %p\n", &end);
	
	free(alloc);
	// des opérations pour empecher le compilateur de faire n'importe quoi
	return 0;
}
