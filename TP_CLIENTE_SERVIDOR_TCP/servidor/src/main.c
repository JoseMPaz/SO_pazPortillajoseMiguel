#include "main.h"

int main(void) 
{
	t_log * log = NULL;
	int socket_servidor;
	pthread_t hilo_cliente, hilo_consola;
	t_escucha * escucha = (t_escucha *) malloc (sizeof (t_escucha));
	
	iniciar_log (&log, "servidor.log", "SERVIDOR_LOG");
	
	socket_servidor = crear_socket_servidor (PUERTO_SERVIDOR,log);
	
	escucha->socket = socket_servidor;
	escucha->log = log;	
	pthread_create (&hilo_cliente, NULL, atender_clientes , (void *) escucha);
	pthread_detach(hilo_cliente);
	
	pthread_create (&hilo_consola, NULL, leer_de_consola_a_log , (void *) log);
	pthread_detach(hilo_consola);
	
	pthread_exit (NULL);
	
	free (escucha);
	log_destroy (log);
	close (socket_servidor);
	
	return EXIT_SUCCESS;
}
