#include "memoria_config.h"
void cargar_configuracion_memoria(char* path){
    t_config* config = cargarConfiguracion(path);

    memoria_config = (memoria_config_t *) malloc (sizeof(memoria_config_t));

    memoria_config->ip_memoria = config_get_string_value(config,"IP_MEMORIA");
    memoria_config->puerto_escucha = string_from_format("%d", config_get_int_value(config, "PUERTO_ESCUCHA"));
    memoria_config->ip_filesystem = config_get_string_value(config,"IP_FILESYSTEM");
    memoria_config->puerto_filesystem = string_from_format("%d", config_get_int_value(config, "PUERTO_FILESYSTEM"));
    memoria_config->tam_memoria = config_get_int_value(config, "TAM_MEMORIA");
    memoria_config->path_instrucciones = config_get_string_value(config,"PATH_INSTRUCCIONES");
    memoria_config->retardo_respuesta = config_get_int_value(config,"RETARDO_RESPUESTA");
    memoria_config->esquema = config_get_string_value(config,"ESQUEMA");
    memoria_config->algoritmo_busqueda = config_get_string_value(config,"ALGORITMO_BUSQUEDA");
    memoria_config->particiones = config_get_string_value(config,"PARTICIONES");

    log_info(logger,"Configuracion cargada");

}
