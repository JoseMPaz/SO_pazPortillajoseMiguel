#include "main.h"

void * enviar_saludo (void * socket_kernel);

int main (void)
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * puerto_escucha_kernel, * ip_memoria, * puerto_memoria, * ip_cpu, * puerto_cpu_dispatch, * puerto_cpu_interrupt;
	int * socket_kernel_a_memoria = (int *) malloc (sizeof (int));
	int * socket_kernel_a_cpu_dispatch = (int *) malloc (sizeof (int));
	int * socket_kernel_a_cpu_interrupt = (int *) malloc (sizeof (int));
	pthread_t hilo_memoria, hilo_consola, hilo_kernel, hilo_cpu_dispatch, hilo_cpu_interrupt;
	t_escucha * kernek_log = (t_escucha *) malloc (sizeof (t_escucha));
	int socket_escucha_kernel;
	
	iniciar_log (&log, "kernel.log", "KERNEL_LOG");
	iniciar_config (&config, "kernel.config", log);
	
	leer_valor_de_config (config, "PUERTO_ESCUCHA", &puerto_escucha_kernel, log);
	leer_valor_de_config (config, "IP_MEMORIA", &ip_memoria, log);
	leer_valor_de_config (config, "PUERTO_MEMORIA", &puerto_memoria, log);
	leer_valor_de_config (config, "IP_CPU", &ip_cpu, log);
	leer_valor_de_config (config, "PUERTO_CPU_DISPATCH", &puerto_cpu_dispatch, log);
	leer_valor_de_config (config, "PUERTO_CPU_INTERRUPT", &puerto_cpu_interrupt, log);
	
	socket_escucha_kernel = crear_socket_servidor (puerto_escucha_kernel, log);//Se marca como socket de escucha

	crear_conexion (socket_kernel_a_memoria, puerto_memoria, ip_memoria, log);//Inicia la conexion con la memoria
	crear_conexion (socket_kernel_a_cpu_dispatch, puerto_cpu_dispatch, ip_cpu, log);//Inicia la conexion con cpu dispatch
	crear_conexion (socket_kernel_a_cpu_interrupt, puerto_cpu_interrupt, ip_cpu, log);//Inicia la conexion con cpu interrupt
	
	/*conecta como servidor kernel*/
	kernek_log->socket = socket_escucha_kernel;
	kernek_log->log = log;
	pthread_create (&hilo_kernel, NULL, atender_clientes , (void *) kernek_log);
	pthread_detach(hilo_kernel);
	
	/*Hilo de consola*/
	pthread_create (&hilo_consola, NULL, leer_de_consola_a_log , (void *) log);
	pthread_detach(hilo_consola);
	
	/*Saluda a la memoria*/
	pthread_create (&hilo_memoria, NULL, enviar_saludo , (void *) socket_kernel_a_memoria);
	pthread_detach(hilo_memoria);
	   
	/*Saluda a cpu dispatch*/
	pthread_create (&hilo_cpu_dispatch, NULL, enviar_saludo , (void *) socket_kernel_a_cpu_dispatch);
	pthread_detach(hilo_cpu_dispatch);
	
	/*Saluda a cpu interrupt*/
	pthread_create (&hilo_cpu_interrupt, NULL, enviar_saludo , (void *) socket_kernel_a_cpu_interrupt);
	pthread_detach(hilo_cpu_interrupt);

	pthread_exit (NULL);
	
	free (kernek_log);
	close (*socket_kernel_a_memoria);
	free (socket_kernel_a_memoria);
	close (*socket_kernel_a_cpu_dispatch);
	free (socket_kernel_a_cpu_dispatch);
	close (*socket_kernel_a_cpu_interrupt);
	free (socket_kernel_a_cpu_interrupt);
	log_destroy (log);
	config_destroy (config);


	return EXIT_SUCCESS;
}

void * enviar_saludo (void * socket_kernel)
{
	int i;
	
	for (i = 0; i < 5; i++)
	{
		enviar_mensaje ("HOLA, SOY KERNEL", *((int *)socket_kernel));
		sleep (1.5);
	}
	return NULL;
}

