#include "main.h"

void * enviar_saludo (void * arg);

int main(int argc, char* argv[]) 
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * ip_memoria, * puerto_memoria;
	int * socket_cpu;
	pthread_t hilo;
	
	iniciar_log (&log, "cpu.log", "CPU_LOG");
	iniciar_config (&config, "cpu.config", log);
	leer_valor_de_config (config, "IP_MEMORIA", &ip_memoria , log);
	leer_valor_de_config (config, "PUERTO_MEMORIA", &puerto_memoria , log);
	socket_cpu = (int *) malloc (sizeof (int));
	crear_conexion (socket_cpu, puerto_memoria, ip_memoria, log);//Inicia la conexion con la memoria
	pthread_create (&hilo, NULL, enviar_saludo , (void *) socket_cpu);
	pthread_detach(hilo);
	   
	leer_de_consola_a_log (log);
    
	pthread_exit (NULL);
	free (socket_cpu);
	log_destroy (log);
	config_destroy (config);

	
	
    return EXIT_SUCCESS;
}

void * enviar_saludo (void * socket_cpu)
{
	int i;
	
	for (i = 0; i < 20; i++)
	{
		enviar_mensaje ("HOLA MEMORIA, SOY CPU", *((int *)socket_cpu));
		sleep (2);
	}
	return NULL;
}


