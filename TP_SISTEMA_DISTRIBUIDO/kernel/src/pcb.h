#ifndef _PCB_H_
#define _PCB_H_

#include <utils/utils.h>

typedef struct
{
    uint32_t pc;
    uint8_t ax;
    uint8_t bx;
    uint8_t cx;
    uint8_t dx;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t si;
    uint32_t di;
}t_registros_cpu;

typedef struct 
{
    int identificador_de_proceso;
    int contador_de_programa;
    int quantum;
    t_registros_cpu registros_cpu;
}t_pcb;

t_pcb * crear_pcb (void);
void destruir_pcb (void * pcb_a_eliminar);


#endif







