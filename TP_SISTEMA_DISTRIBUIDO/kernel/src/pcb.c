#include "pcb.h"

t_pcb * crear_pcb (void)
{
    t_pcb * nuevo_pcb = (t_pcb *) malloc (sizeof (t_pcb));
    return nuevo_pcb;
}

void destruir_pcb (void * pcb_a_eliminar)
{
    free (pcb_a_eliminar);
    return;
}
