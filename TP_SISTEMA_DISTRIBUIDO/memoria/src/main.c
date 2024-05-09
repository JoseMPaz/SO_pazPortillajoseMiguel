#include "main.h"

int main (void)
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * puerto_escucha;
	int socket_memoria;
	
	iniciar_log (&log, "memoria.log", "MEMORIA_LOG");
	iniciar_config (&config, "memoria.config", log);
	leer_valor_de_config (config, "PUERTO_ESCUCHA", &puerto_escucha , log);
	socket_memoria = crear_socket_servidor (puerto_escucha,log);
	atender_clientes (socket_memoria, log);
	log_destroy (log);
	config_destroy (config);
	close (socket_memoria);
	
	return EXIT_SUCCESS;
}
