#include "traduccion.h"

traduccion_t * crear_traduccion (char ingles[], char espanol[])
{
	traduccion_t * traduccion_nueva = (traduccion_t *) malloc ( sizeof (traduccion_t) );
	strcpy (traduccion_nueva->ingles, ingles);
	strcpy (traduccion_nueva->espanol, espanol);
	return traduccion_nueva;
}

void mostrar_traduccion (void * generico)
{
	traduccion_t * traduccion = (traduccion_t *) generico;
	printf ("%s: ", traduccion->ingles);
	printf ("%s\n", traduccion->espanol);
	return;
}
