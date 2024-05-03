#include "kernel.h"

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

int main (void)
{

    
    //void * (*pf)(void *);
    //pf = iniciar_consola;
    // -------CREACION DE LOGS-------
    kernel_logger = iniciar_logger ("kernel.log", "KERNEL_LOG");              

    // -------LOG PROPIO-------
   // nuestro_log_kernel = iniciar_logger("nuestro_kernel.log", "nuestro_log_kernel");              
    
    // -------CREACION DE CONFIGS-------
    kernel_config = iniciar_config ("../kernel/kernel.config");

    inicializar_kernel();

	// ------- CONEXIONES -------
	/* El Kernel debe poder conectarse al CPU y a la memoria */

	//------ KERNEL SE CONECTA A CPU-----------
	fd_cpu = crear_conexion (IP_CPU, PUERTO_CPU_DISPATCH);
    

	// ------- KERNEL SE CONECTA A MEMORIA-------
	fd_memoria = crear_conexion (IP_MEMORIA , PUERTO_MEMORIA);	

    //------- Inicio al Kernel como servidor ---------
	fd_kernel = iniciar_servidor (PUERTO_ESCUCHA, kernel_logger, "KERNEL INICIADO CORRECTAMENTE");
    
    //-------- KERNEL ESPERA A I/O-----------
	
    fd_entradasalida = esperar_cliente (fd_kernel, kernel_logger, "ENTRADA SALIDA");

    //-------- KERNEL ATIENDE A I/O----------
	pthread_t hilo_consola;
	pthread_create(&hilo_consola, NULL, iniciar_consola, NULL);	
	pthread_join(hilo_consola,NULL);
	
	pthread_t hilo_io;
	pthread_create(&hilo_io, NULL, (void*)atender_io, NULL);
	pthread_join(hilo_io,NULL);
	//pthread_detach(hilo_io);
		

    //realizar_operacion (fd_entradasalida, kernel_logger);

    

    //--------INICIALIZAR CONSOLA------
    /* int pthread_create(	pthread_t * hilo, const pthread_attr_t * atributos_de_hilo,
                   			void *	(*funcion_a_ejecutar) (void *), void * argumentos de la funcion);	*/

	//pthread_detach(hilo_consola);

	//pthread_join(hilo_io,NULL);
	
	//puts ("Antes de consola\n");
   //iniciar_consola(NULL);
	//puts ("Despues de consola\n");
	//pthread_exit (NULL);
//--------LIBERAMOS MEMORIA----------
	config_destroy (kernel_config);
	//pthread_join(hilo_io,NULL);

	return EXIT_SUCCESS;
}
