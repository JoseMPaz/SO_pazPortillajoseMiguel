#include "main.h"

void * enviar_saludo (void * socket_entradasalida);

int main (void) 
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * ip_memoria, * puerto_memoria;
	int * socket_entradasalida;
	pthread_t hilo;

	iniciar_log (&log, "entradasalida.log", "ENTRADASALIDA_LOG");
	iniciar_config (&config, "entradasalida.config", log);
	leer_valor_de_config (config, "IP_MEMORIA", &ip_memoria , log);
	leer_valor_de_config (config, "PUERTO_MEMORIA", &puerto_memoria , log);
	socket_entradasalida = (int *) malloc (sizeof (int));
	crear_conexion (socket_entradasalida, puerto_memoria, ip_memoria, log);//Inicia la conexion con la memoria
	pthread_create (&hilo, NULL, enviar_saludo , (void *) socket_entradasalida);
	pthread_detach(hilo);
	leer_de_consola_a_log (log);
	pthread_exit (NULL);
	free (socket_entradasalida);
	log_destroy (log);
	config_destroy (config);
	
	return EXIT_SUCCESS;
}

void * enviar_saludo (void * socket_entradasalida)
{
	int i;
	
	for (i = 0; i < 20; i++)
	{
		enviar_mensaje ("HOLA MEMORIA, SOY ENTRADASALIDA", *((int *)socket_entradasalida));
		sleep (2.5);
	}
	return NULL;
}
