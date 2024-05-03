#include "inicializar_kernel.h"


    // ------- EXTRAER VALORES DE LOS CONFIGS -------
    

    void inicializar_kernel()
    {    
    IP_MEMORIA = config_get_string_value (kernel_config , "IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value (kernel_config , "PUERTO_MEMORIA");
    IP_CPU = config_get_string_value (kernel_config, "IP_CPU");
    PUERTO_CPU_DISPATCH = config_get_string_value (kernel_config , "PUERTO_CPU_DISPATCH");
    PUERTO_ESCUCHA = config_get_string_value (kernel_config , "PUERTO_ESCUCHA");
    PUERTO_CPU_INTERRUPT = config_get_string_value (kernel_config , "PUERTO_CPU_INTERRUPT");
    ALGORITMO_PLANIFICACION = config_get_string_value (kernel_config , "ALGORITMO_PLANIFICACION");
    QUANTUM = config_get_int_value (kernel_config , "QUANTUM");
    RECURSOS = config_get_array_value(kernel_config , "RECURSOS");
    INSTANCIAS_RECURSOS = config_get_array_value(kernel_config , "INSTANCIAS_RECURSOS");
    }

    