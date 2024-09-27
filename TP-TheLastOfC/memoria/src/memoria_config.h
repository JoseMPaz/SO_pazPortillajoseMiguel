#include "utils/config.h"
#include "utils/logger.h"
#include <commons/string.h>


typedef struct {
    char* ip_memoria;
    char* puerto_escucha;
    char* ip_filesystem;
    char* puerto_filesystem;
    int tam_memoria;
    char* path_instrucciones;
    int retardo_respuesta;
    char* esquema;
    char* algoritmo_busqueda;
    char* particiones;
} memoria_config_t;

void cargar_configuracion_memoria(char* path);

extern memoria_config_t* memoria_config;
