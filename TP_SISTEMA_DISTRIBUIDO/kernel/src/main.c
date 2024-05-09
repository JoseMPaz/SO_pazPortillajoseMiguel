#include "main.h"

void * enviar_saludo (void * socket_kernel);

int main (void)
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * ip_memoria, * puerto_memoria;
	int * socket_kernel;
	pthread_t hilo_memoria;
	
	iniciar_log (&log, "kernel.log", "KERNEL_LOG");
	iniciar_config (&config, "kernel.config", log);
	leer_valor_de_config (config, "IP_MEMORIA", &ip_memoria , log);
	leer_valor_de_config (config, "PUERTO_MEMORIA", &puerto_memoria , log);
	socket_kernel = (int *) malloc (sizeof (int));
	crear_conexion (socket_kernel, puerto_memoria, ip_memoria, log);//Inicia la conexion con la memoria
	pthread_create (&hilo_memoria, NULL, enviar_saludo , (void *) socket_kernel);
	pthread_detach(hilo_memoria);
	   
	leer_de_consola_a_log (log);
    
	pthread_exit (NULL);
	close (*socket_kernel);
	free (socket_kernel);
	log_destroy (log);
	config_destroy (config);


	return EXIT_SUCCESS;
}

void * enviar_saludo (void * socket_kernel)
{
	int i;
	
	for (i = 0; i < 20; i++)
	{
		enviar_mensaje ("HOLA MEMORIA, SOY KERNEL", *((int *)socket_kernel));
		sleep (1.5);
	}
	return NULL;
}
/*
	pthread_create: Esta función se utiliza para crear un nuevo hilo. Su prototipo es:
	
	int pthread_create (	pthread_t * puntero_de_identificador_de_hilo, const pthread_attr_t * puntero_atributos_del_hilo, 
								void * (*puntero_a_funcion_que_se_va_a_ejecutar) (void *), void * puntero_a_argumento_de_funcion_a_ejecutar);
								
	pthread_t * puntero_de_identificador_de_hilo: Un puntero a una variable donde se almacenará el identificador del hilo creado.
	const pthread_attr_t * puntero_atributos_del_hilo:	Un puntero a un objeto pthread_attr_t que contiene los atributos del hilo que se creará. 
																		Puedes pasar NULL si quieres usar los atributos por defecto.
	void * (*puntero_a_funcion_que_se_va_a_ejecutar)(void *): Un puntero a la función que se ejecutará en el hilo recién creado.
	void * puntero_a_argumento_de_funcion_a_ejecutar: Un puntero a un argumento que se pasará a la función a ejecutar.
*/

/*
	pthread_detach: Esta función se utiliza para indicar que el hilo en cuestión debe ser desvinculado (detached) de su hilo padre. Su prototipo es:
	
	int pthread_detach(pthread_t puntero_de_identificador_de_hilo);
	
	pthread_t puntero_de_identificador_de_hilo: El identificador del hilo que se va a desvincular.
												
	Cuando un hilo es desvinculado, los recursos asociados con él se liberan automáticamente una vez que el hilo termina su ejecución.
*/


/*
	pthread_join: Esta función se utiliza para esperar a que un hilo termine su ejecución. Su prototipo es:

	int pthread_join(pthread_t puntero_de_identificador_de_hilo, void ** puntero_del_valor_de_retorno_del_hilo);

	pthread_t puntero_de_identificador_de_hilo: El identificador del hilo del que se quiere esperar la terminación.
	void ** puntero_del_valor_de_retorno_del_hilo:	Un puntero donde se almacenará el valor de retorno del hilo. 
																	Puedes pasar NULL si no necesitas este valor.
	
	Cuando llamas a pthread_join, el hilo que llama se bloquea hasta que el hilo especificado termina su ejecución. 
	Si puntero_del_valor_de_retorno_del_hilo no es NULL, el valor retornado por el hilo se almacenará en la dirección de memoria 
	apuntada por puntero_del_valor_de_retorno_del_hilo.
*/
