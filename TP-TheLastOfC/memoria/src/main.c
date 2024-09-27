#include <utils/cliente_servidor.h>
#include <memoria_config.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <pthread.h>

/* Variables globales */
t_log * logger = NULL;
memoria_config_t * memoria_config = NULL;

void * enviar_saludo (void * socket_cpu);

int main(int argc, char* argv[]) {

	int * socket_a_filesystem = (int *) malloc (sizeof(int)); 
	int * socket_escucha = (int *) malloc (sizeof(int));
	pthread_t hilo_a_filesystem, hilo_escucha;
    // Iniciar el logger
    logger = crear_logger();
    log_info(logger, "Iniciando memoria");

    // Cargar la configuracion
    cargar_configuracion_memoria("memoria.config");
    
    *socket_a_filesystem = conectar_a_servidor (memoria_config->ip_filesystem, memoria_config->puerto_filesystem);
    log_info(logger, "Conectado a Memoria, socket: %d", *socket_a_filesystem);

	*socket_escucha = iniciar_servidor(
        memoria_config->ip_memoria,
        memoria_config->puerto_escucha);
        
	pthread_create (&hilo_escucha, NULL, atender_clientes , (void *) socket_escucha);
	pthread_detach(hilo_escucha);


	pthread_create (&hilo_a_filesystem, NULL, enviar_saludo, (void *) socket_a_filesystem);
	pthread_detach(hilo_a_filesystem);
	
	pthread_exit (NULL);
	//Saludar a FileSystem
	
	
    /*enviar_mensaje("TEST MENSAJE",socket_filesystem);
    log_info(logger,"Envio mensaje %d\n",1);*/

    return 0;
    
}

void * enviar_saludo (void * socket_cpu)
{
	int i;
	
	for (i = 0; i<5; i++)
	{
		enviar_mensaje ("HOLA FileSystem, SOY Memoria", *((int *)socket_cpu));
		sleep (2);
	}
	return NULL;
}