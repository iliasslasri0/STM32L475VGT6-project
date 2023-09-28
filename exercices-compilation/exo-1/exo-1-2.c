#include <stdio.h>
#include <stdlib.h>


void allocation_pile2();

int main(){
	int x = 100;
	printf("adresse de la 1ère var locale non static : %p\n", &x);

	allocation_pile2();
	return 0;
}

void allocation_pile2(){
	int y= 299;
	printf("adresse de la 2ème var locale non static : %p\n", &y);
}


// dans ce cas, le compilateur peut juste remplacer le code et faire qlqchose qui va ruiner notre objectif
// Mais dans un premier temps, le premier résultat est satisfaisant
// on essaye avec une structure de donnée, le compilateur dans ce cas est obligé à les placer dans le tas 
// dans l'ordre ( peut etre) 