#include "utils/config.h"
#include "utils/logger.h"
#include <commons/string.h>

typedef struct {
    char* ip_filesystem;
    char* puerto_escucha;
    char* mount_dir;
    int block_size;
    int block_count;
    int retardo_acceso_bloque;
} filesystem_config_t;

void cargar_configuracion_filesystem(char* path);

extern filesystem_config_t* filesystem_config;