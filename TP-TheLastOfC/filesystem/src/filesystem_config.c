#include "filesystem_config.h"
void cargar_configuracion_filesystem(char* path){
    t_config* config = cargarConfiguracion(path);

    filesystem_config = malloc(sizeof(filesystem_config_t));

    filesystem_config->ip_filesystem = config_get_string_value(config,"IP_FILESYSTEM");
    filesystem_config->puerto_escucha = string_from_format("%d", config_get_int_value(config, "PUERTO_ESCUCHA"));
    filesystem_config->mount_dir = config_get_string_value(config,"MOUNT_DIR");
    filesystem_config->block_size = config_get_int_value(config, "BLOCK_SIZE");
    filesystem_config->block_count = config_get_int_value(config, "BLOCK_COUNT");
    filesystem_config->retardo_acceso_bloque = config_get_int_value(config, "RETARDO_ACCESO_BLOQUE");

    log_info(logger,"Configuracion cargada");

}