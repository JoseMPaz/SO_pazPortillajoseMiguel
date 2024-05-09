#include "main.h"

void * enviar_saludo (void * arg);

int main(int argc, char* argv[]) 
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * ip_memoria, * puerto_memoria, * puerto_escucha_dispatch, * puerto_escucha_interrupt;
	int * socket_cliente_cpu = socket_cliente_cpu = (int *) malloc (sizeof (int)); 
	int socket_escucha_dispatch, socket_escucha_interrupt;
	pthread_t hilo_de_cpu_a_memoria, hilo_dispatch, hilo_interrupt, hilo_consola;
	t_escucha * dispatch_log = (t_escucha *) malloc (sizeof (t_escucha));
	t_escucha * interrup_log = (t_escucha *) malloc (sizeof (t_escucha));
	
	iniciar_log (&log, "cpu.log", "CPU_LOG");
	iniciar_config (&config, "cpu.config", log);
	
	leer_valor_de_config (config, "IP_MEMORIA", &ip_memoria , log);
	leer_valor_de_config (config, "PUERTO_MEMORIA", &puerto_memoria , log);
	leer_valor_de_config (config, "PUERTO_ESCUCHA_DISPATCH", &puerto_escucha_dispatch , log);
	leer_valor_de_config (config, "PUERTO_ESCUCHA_INTERRUPT", &puerto_escucha_interrupt , log);
	
	crear_conexion (socket_cliente_cpu, puerto_memoria, ip_memoria, log);//Inicia la conexion con la memoria
	socket_escucha_dispatch = crear_socket_servidor (puerto_escucha_dispatch, log);
	socket_escucha_interrupt = crear_socket_servidor (puerto_escucha_interrupt, log);
	

	
	/*conecta como servidor dispatch*/
	dispatch_log->socket = socket_escucha_dispatch;
	dispatch_log->log = log;
	pthread_create (&hilo_dispatch, NULL, atender_clientes , (void *) dispatch_log);
	pthread_detach(hilo_dispatch);
	
	/*conecta como servidor interrupt*/
	interrup_log->socket = socket_escucha_interrupt;
	interrup_log->log = log;
	pthread_create (&hilo_interrupt, NULL, atender_clientes , (void *) interrup_log);
	pthread_detach(hilo_interrupt);
		   
	pthread_create (&hilo_consola, NULL, leer_de_consola_a_log , (void *) log);
	pthread_detach(hilo_consola);
    
	/*Saluda a la memoria*/
	pthread_create (&hilo_de_cpu_a_memoria, NULL, enviar_saludo , (void *) socket_cliente_cpu);
	pthread_detach(hilo_de_cpu_a_memoria);

	pthread_exit (NULL);
	close (*socket_cliente_cpu);
	free (socket_cliente_cpu);
	log_destroy (log);
	config_destroy (config);
	free (dispatch_log);
	
	
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


