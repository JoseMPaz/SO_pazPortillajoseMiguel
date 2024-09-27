#include "cpu_config.h"
void cargar_configuracion_cpu(char* path){
    t_config* config = cargarConfiguracion(path);

    cpu_config = malloc(sizeof(cpu_config_t));

    cpu_config->ip_cpu = config_get_string_value(config,"IP_CPU");
    cpu_config->puerto_escucha_dispatch = string_from_format("%d", config_get_int_value(config, "PUERTO_ESCUCHA_DISPATCH"));
    cpu_config->puerto_escucha_interrupt = string_from_format("%d", config_get_int_value(config, "PUERTO_ESCUCHA_INTERRUPT"));
    cpu_config->ip_memoria = config_get_string_value(config,"IP_MEMORIA");
    cpu_config->puerto_memoria = string_from_format("%d", config_get_int_value(config, "PUERTO_MEMORIA"));

    log_info(logger,"Configuracion cargada");

}