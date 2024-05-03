#include "kernel_io.h"


void atender_io ()
{
	t_list * lista = NULL;
	int cod_op;
	
	while (true) 
	{
		cod_op = recibir_operacion (fd_entradasalida);
		
		switch (cod_op) 
		{
			case MENSAJE:
 				recibir_mensaje (fd_entradasalida, kernel_logger);
				break;
			case PAQUETE:
				lista = recibir_paquete(fd_entradasalida);
				log_info (kernel_logger, "Me llegaron los siguientes valores:\n");
				//list_iterate (lista, (void*) iterator);
				if (lista != NULL) 
					list_destroy (lista);
				break;
			case -1:
				log_error (kernel_logger, "Desconexion: Terminando servidor");
				exit(EXIT_FAILURE);
				break;
			default:
				log_warning (kernel_logger, "Operacion desconocida");
		}
	
	}
}
