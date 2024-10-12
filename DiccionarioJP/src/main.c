#include <stdio.h>
#include <commons/collections/list.h>
#include <string.h>
#include <commons/string.h>
#include "traduccion.h"

void menu (void);
void ejecutar (int opcion);

t_list * lista = NULL;

int main(int argc, char* argv[]) 
{
	int opcion;
	lista = list_create ();
	
	do
	{
		menu ();
		scanf ("%d", &opcion);
		ejecutar (opcion);
   }while (opcion != 0);
   
	return 0;
}

void menu (void)
{
	printf ("\t\t\t%s\n", "Diccionario");
	printf ("%s\n", "0.- Salir");
	printf ("%s\n", "1.- Agregar nueva palabra");
	printf ("%s\n", "2.- Mostrar palabras");
	return;
}

void ejecutar (int opcion)
{
	char ingles[SIZE_STRING];
	char espanol[SIZE_STRING];
	void (*closure)(void*) = mostrar_traduccion;
	 
	switch (opcion)
	{
		case 1:
			printf ("\t\t\t%s\n", "Opcion 1");
			printf ("%s\n", "Ingrese palabra en ingles: ");
			scanf ("%s", ingles);
			printf ("%s\n", "Ingrese palabra en español: ");
			scanf ("%s", espanol);
			list_add(lista, (void *) crear_traduccion (ingles,espanol));
			break;
		case 2:
			printf ("\t\t\t%s\n", "Opcion 2");
			list_iterate (lista, closure);
			break;
		default:
			;
	}
	return;
}




