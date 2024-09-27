#include "utils/config.h"
#include "utils/logger.h"
#include <commons/string.h>

typedef struct {
    char* ip_cpu;
    char* puerto_escucha_dispatch;
    char* puerto_escucha_interrupt;
    char* ip_memoria;
    char* puerto_memoria;
} cpu_config_t;

void cargar_configuracion_cpu(char* path);

extern cpu_config_t* cpu_config;