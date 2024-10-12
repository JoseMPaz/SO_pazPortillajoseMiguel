#ifndef _TRADUCCION_H_
#define _TRADUCCION_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define SIZE_STRING 100
typedef struct
{
	char ingles[SIZE_STRING];
	char espanol[SIZE_STRING];
}traduccion_t;

traduccion_t * crear_traduccion (char ingles[], char espanol[]);
void mostrar_traduccion (void * generico);

#endif
