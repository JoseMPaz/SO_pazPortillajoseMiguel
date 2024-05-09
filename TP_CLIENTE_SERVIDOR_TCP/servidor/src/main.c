#include "main.h"

int main(void) 
{
	t_log * log = NULL;
	int socket_servidor;
	
	iniciar_log (&log, "servidor.log", "SERVIDOR_LOG");
	socket_servidor = crear_socket_servidor (PUERTO_SERVIDOR,log);
	atender_clientes (socket_servidor, log);
		
	log_destroy (log);
	close (socket_servidor);
	
	return EXIT_SUCCESS;
}
