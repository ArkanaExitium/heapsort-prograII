/*
Para compilar este programa en Linux
gcc -o -pedantic -Wall -std=c99  heapsortDynArray heapsortDynArray.c 

./heapsortDynArray

*/
#include <stdio.h>
#include <stdlib.h>	
#include <string.h> 
#include <time.h> 
void display(int arregloArbitrario[], int numeroElementos) {
	int i;
	for(i = 1; i < numeroElementos; i++) {
		printf("%d ", arregloArbitrario[i]);
	}
	printf("\n \n");
}
void minHeap(int arregloDesordenado[], int numeroElementos) {
	int i, leftSon, rightSon, aux, val;

	for(i = numeroElementos / 2; i >= 1; i--) {
		/*Sea 1 el indice inicial. Si el nodo padre = i entonces leftSon= 2i y rightSon = 2i+1*/
		aux = i;
		leftSon = (2 * i);
		rightSon = (2 * i) + 1;

		if(leftSon < numeroElementos && arregloDesordenado[leftSon] < arregloDesordenado[aux]) {
			aux = leftSon;
		}

		if(rightSon < numeroElementos && arregloDesordenado[rightSon] < arregloDesordenado[aux]) {
			aux = rightSon;
		}
		if(aux != i) {
			printf ("Proceso empieza en la division entera de %d/2 = %d:\n",numeroElementos-1,(numeroElementos-1) / 2);
			val = arregloDesordenado[i];
			arregloDesordenado[i] = arregloDesordenado[aux];
			arregloDesordenado[aux] = val;
			printf ("Transformando heap en minHeap:\n");
			printf ("Heap:\t");
			display(arregloDesordenado,numeroElementos);
			if(i-1!=0)
				printf ("Swap de %d y %d\n",i,aux);
			minHeap(arregloDesordenado, numeroElementos);
		}
	}
}
void heapSort(int arregloDesordenado[], int numeroElementos) {
	int i, j, arregloOrdenado[numeroElementos];
	arregloOrdenado[0] = 0;	
	for(i = 1; i < numeroElementos; i++) {
		arregloOrdenado[i]=0;
	}
	for(i = numeroElementos , j = 1; i > 1; i--, j++) {
		minHeap(arregloDesordenado, i);
		printf ("El heap tiene la forma de un minHeap? Si\n");
		arregloOrdenado[j] = arregloDesordenado[1];
		printf ("Agregando elemento %d de la lista desordenada a la lista ordenada\n",j);
		arregloDesordenado[1] = arregloDesordenado[i - 1];	
		printf ("Trasladando al ultimo elemento del Heap al nodo raíz\n");
		printf ("Lista Ordenada:\t");
		display(arregloOrdenado,j+1);
	}
	for(i = 0; i < numeroElementos; i++) {
		arregloDesordenado[i] = arregloOrdenado[i];
	}
}

void procedimiento(void)
{
	clock_t start, end;	
	int numeroElementos,contador;
	int* arregloDesordenado;
	printf ("¿Cuántos elementos quieres ordenar? ");
	scanf ("%d", &numeroElementos);
	numeroElementos++;
	arregloDesordenado = (int*)malloc((numeroElementos)*sizeof(int));
	if (arregloDesordenado==NULL)
	{
		perror("Problemas reservando memoria para arreglos");
		exit (1);
	}
	arregloDesordenado[0]=0;
	for(contador = 1; contador < numeroElementos; contador++) 
	{
		scanf("%d",&arregloDesordenado[contador]);
	}
	printf ("Etapa Inicial del Heap\n");
	display(arregloDesordenado,numeroElementos);
	start = clock(); 
	heapSort(arregloDesordenado,numeroElementos);
	end = clock(); 
	printf("Tiempo de ejecución: %f segundos\n", (end - start) /(float) CLOCKS_PER_SEC); 
	free (arregloDesordenado);
}
void Menu(void)
{
	int selector;
	do{
		printf("\nMétodo de Ordenamiento Heapsort \n");
		printf("Seleccione cualquier una opcion del menu: \n");
		printf("1.-Empezar con el programa \n");
		printf("2.-Salir del programa \n");
		printf("Opcion: ");
		scanf("%d",&selector);
		switch(selector)
		{
			case 1:
				system("clear");
				procedimiento();
			break;
			case 2:
				system("clear");
			break;
		}
	}while(selector!=2);
	return;
}	
int main(void)
{
	Menu();
	return 0;
}
