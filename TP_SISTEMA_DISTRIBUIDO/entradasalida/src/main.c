#include "main.h"

void * enviar_saludo (void * socket_entradasalida);

int main (void) 
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * ip_memoria, * puerto_memoria, * ip_kernel, * puerto_kernel;
	int * socket_entradasalida_memoria = (int *) malloc (sizeof (int));
	int * socket_entradasalida_kernel = (int *) malloc (sizeof (int));
	pthread_t hilo_memoria, hilo_kernel, hilo_consola;

	iniciar_log 	(&log, 		"entradasalida.log", 	"ENTRADASALIDA_LOG");
	iniciar_config (&config, 	"entradasalida.config", log);
	
	leer_valor_de_config (config, "IP_MEMORIA", 		&ip_memoria , 		log);
	leer_valor_de_config (config, "PUERTO_MEMORIA", &puerto_memoria , log);
	leer_valor_de_config (config, "IP_KERNEL", 		&ip_kernel , 		log);
	leer_valor_de_config (config, "PUERTO_KERNEL", 	&puerto_kernel , 	log);
	
	crear_conexion (socket_entradasalida_memoria, puerto_memoria, ip_memoria, log);//Inicia la conexion con la memoria
	crear_conexion (socket_entradasalida_kernel, puerto_kernel, ip_kernel, log);//Inicia la conexion con el kernel
	
	/*Saluda a la memoria*/
	pthread_create (&hilo_memoria, NULL, enviar_saludo , (void *) socket_entradasalida_memoria);
	pthread_detach(hilo_memoria);
	
	/*Saluda al kernel*/
	pthread_create (&hilo_kernel, NULL, enviar_saludo , (void *) socket_entradasalida_kernel);
	pthread_detach(hilo_kernel);
	
	/*Hilo de consola*/
	pthread_create (&hilo_consola, NULL, leer_de_consola_a_log , (void *) log);
	pthread_detach(hilo_consola);
	
	pthread_exit (NULL);
	close (*socket_entradasalida_kernel);
	free (socket_entradasalida_kernel);
	close (*socket_entradasalida_memoria);
	free (socket_entradasalida_memoria);
	log_destroy (log);
	config_destroy (config);
	
	return EXIT_SUCCESS;
}

void * enviar_saludo (void * socket_entradasalida)
{
	int i;
	
	for (i = 0; i < 20; i++)
	{
		enviar_mensaje ("HOLA! SOY ENTRADASALIDA", *((int *)socket_entradasalida));
		sleep (2.5);
	}
	return NULL;
}
