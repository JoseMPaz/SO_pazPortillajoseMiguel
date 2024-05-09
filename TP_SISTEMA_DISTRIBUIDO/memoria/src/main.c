#include "main.h"

int main (void)
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * puerto_escucha_memoria;
	int socket_escucha_memoria;
	pthread_t hilo_escucha;
	t_escucha * escucha_log = (t_escucha *) malloc (sizeof (t_escucha));
	
	iniciar_log (&log, "memoria.log", "MEMORIA_LOG");
	iniciar_config (&config, "memoria.config", log);
	
	leer_valor_de_config (config, "PUERTO_ESCUCHA", &puerto_escucha_memoria , log);
	
	socket_escucha_memoria = crear_socket_servidor (puerto_escucha_memoria, log);
	
	escucha_log->socket = socket_escucha_memoria;
	escucha_log->log = log;
	pthread_create (&hilo_escucha, NULL, atender_clientes , (void *) escucha_log);
	pthread_detach(hilo_escucha);
	
	pthread_exit (NULL);

	log_destroy (log);
	config_destroy (config);
	close (socket_escucha_memoria);
	free (escucha_log);
	
	return EXIT_SUCCESS;
}
