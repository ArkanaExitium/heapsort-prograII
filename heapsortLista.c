/*Para compilar este programa en Linux
gcc -c TADListaDobleLigada.c

gcc -o -pedantic -Wall -std=c99  heapsortLista heapsortLista.c TADListaDobleLigada.o

./heapsortLista

*/
#include <stdio.h>
#include <stdlib.h>	
#include <string.h> 
#include <time.h> 
#include "TADLista.h"
void display(lista listaArbitraria,int numeroElementos) 
{
	int i;
	posicion p1;	
	p1=First(&listaArbitraria);
	p1=Following(&listaArbitraria,p1);
	for(i = 1; i < numeroElementos; i++) {
		printf("%d ", Position(&listaArbitraria,p1).n);
		p1=Following(&listaArbitraria,p1);
	}
	printf("\n \n");
}
void minHeap(lista listaDesordenada,int indice) 
{
	int i, indiceleftSon, indicerightSon, aux, val;
	elemento auxiliar1;
	for(i = indice / 2; i >= 1; i--) 
	{
		/*Sea 1 el indice inicial. Si el nodo padre = i entonces leftSon= 2i y rightSon = 2i+1*/
		aux = i;
		indiceleftSon = (2 * i);
		indicerightSon = (2 * i) + 1;
		if(indiceleftSon < indice && Element(&listaDesordenada,indiceleftSon+1).n < Element(&listaDesordenada,aux+1).n) 
			aux = indiceleftSon;
		if(indicerightSon < indice && Element(&listaDesordenada,indicerightSon+1).n < Element(&listaDesordenada,aux+1).n) 
			aux = indicerightSon;
		if(aux != i)
 		{
			printf ("Proceso empieza en la division entera de %d/2 = %d:\n",indice-1,(indice-1)/ 2);
			val = Element(&listaDesordenada,i+1).n;
			Replace(&listaDesordenada,ElementPosition(&listaDesordenada,i+1),Element(&listaDesordenada,aux+1));
			auxiliar1.n=val;
			Replace(&listaDesordenada,ElementPosition(&listaDesordenada,aux+1),auxiliar1);
			printf ("Transformando heap en minHeap:\n");
			if(i!=1)
			{
				printf ("Swap de %d y %d\n",i,aux);
			}
			printf ("Heap:\t");
			display(listaDesordenada,indice);
			minHeap(listaDesordenada,indice);
		}
		if(aux > i && Size(&listaDesordenada)<3)
		{
			printf ("Heap:\t");
			display(listaDesordenada,indice);
		}
	}
}
void heapSort(lista listaDesordenada,int numeroElementos) 
{
	int i, j;
	lista listaOrdenada;
	elemento auxiliar2;
	Initialize(&listaOrdenada);
	auxiliar2.n=0;
	Add(&listaOrdenada,auxiliar2);
	for(i = 0; i < numeroElementos; i++) 
	{
		Add(&listaOrdenada,auxiliar2);		
	}
	for(i = numeroElementos+1 , j = 1; i >= 1; i--, j++) //bug,esto puede mejorar
	{
		if(j<numeroElementos+1)
		{
			minHeap(listaDesordenada, i);
			printf ("El heap tiene la forma de un minHeap? Si\n");
			if(ValidatePosition(&listaOrdenada, ElementPosition(&listaOrdenada,j+1))==TRUE)
				Replace(&listaOrdenada,ElementPosition(&listaOrdenada,j+1),Element(&listaDesordenada,2));
			printf ("Agregando elemento %d de la lista desordenada a la lista ordenada\n",j);
			if(ValidatePosition(&listaDesordenada, ElementPosition(&listaDesordenada,2))==TRUE)
				Replace(&listaDesordenada,ElementPosition(&listaDesordenada,2),Element(&listaDesordenada,i));	//el primer indice es el 2 por como está programada la lista		
			printf ("Trasladando al ultimo elemento del Heap al nodo raíz\n");
			printf ("Lista Ordenada:\t");
			display(listaOrdenada,j+1);
		}
	}
	for(i = 0; i < numeroElementos; i++) 
	{
		if(ValidatePosition(&listaDesordenada, ElementPosition(&listaDesordenada,i+1))==TRUE && i>=1)
			Replace(&listaDesordenada,ElementPosition(&listaDesordenada,i+1),Element(&listaOrdenada,i+1));
	}
	Destroy(&listaOrdenada);

}
void procedimiento(void)
{
	clock_t start, end;
	lista listaDesordenada;	
	int numeroElementos,contador,numeroAuxiliar;
	elemento auxiliar1;
	printf ("¿Cuántos elementos quieres ordenar? ");
	scanf ("%d", &numeroElementos);
	Initialize(&listaDesordenada);
	auxiliar1.n=0;
	Add(&listaDesordenada,auxiliar1);
	for(contador = 0; contador < numeroElementos; contador++) 
	{
		printf ("Ingresar entero #%d:\t",contador+1);
		scanf("%d",&numeroAuxiliar);
		auxiliar1.n=numeroAuxiliar;
		Add(&listaDesordenada,auxiliar1);
	}
	printf ("Etapa Inicial del Heap\n");
	display(listaDesordenada,numeroElementos);
	start = clock(); 
	heapSort(listaDesordenada,numeroElementos);
	end = clock(); 
	printf("Tiempo de ejecución: %f segundos\n", (end - start) /(float) CLOCKS_PER_SEC); 
	Destroy(&listaDesordenada);
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
