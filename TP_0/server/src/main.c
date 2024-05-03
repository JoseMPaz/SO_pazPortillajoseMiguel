#include "main.h"

int main(void) 
{
	int server_fd, cliente_fd, cod_op;
	t_list * lista = NULL;
	
	//Crea un flujo hacia el archivo "log_server.log"
	logger = log_create ("log_server.log", "NEW_LOG_SERVER", true, LOG_LEVEL_DEBUG);

	server_fd = iniciar_servidor();//Retorna el file descriptor -> descripto de archivo: 
	
	log_info (logger, "Servidor listo para recibir al cliente");
	
	cliente_fd = esperar_cliente(server_fd);

	while (true) 
	{
		cod_op = recibir_operacion (cliente_fd);
		
		switch (cod_op) 
		{
			case MENSAJE:
				recibir_mensaje(cliente_fd);
				break;
			case PAQUETE:
				lista = recibir_paquete(cliente_fd);
				log_info(logger, "Me llegaron los siguientes valores:\n");
				list_iterate(lista, (void*) iterator);
				break;
			case -1:
				log_error(logger, "el cliente se desconecto. Terminando servidor");
				return EXIT_FAILURE;
			default:
				log_warning(logger,"Operacion desconocida. No quieras meter la pata");
		}
	}
	return EXIT_SUCCESS;
}

void iterator(char* value) 
{
	log_info (logger,"%s", value);
}
