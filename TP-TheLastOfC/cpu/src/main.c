#include <utils/cliente_servidor.h>
#include <cpu_config.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <pthread.h>

/* Variables globales */
t_log * logger = NULL;
cpu_config_t* cpu_config = NULL;

void * enviar_saludo (void * socket_memoria);

int main(int argc, char* argv[]) {

    int * socket_a_memoria = (int *) malloc (sizeof(int)); 
    int * socket_escucha_dis = (int *) malloc (sizeof(int)); 
    int * socket_escucha_int = (int *) malloc (sizeof(int)); 
    pthread_t hilo_a_memoria, hilo_escucha_dis, hilo_escucha_int;
    //Iniciar el logger
    logger = crear_logger();
    log_info(logger, "Iniciando CPU");

    //Cargar la configuracion
    cargar_configuracion_cpu("cpu.config");

    //Conexion con el servidor Memoria
    *socket_a_memoria =conectar_a_servidor(cpu_config->ip_memoria,cpu_config->puerto_memoria);
    log_info(logger, "Memoria conectada a CPU, socket: %d", *socket_a_memoria);

    //Iniciar servidor
    *socket_escucha_dis = iniciar_servidor(
        cpu_config->ip_cpu,
        cpu_config->puerto_escucha_dispatch);

    *socket_escucha_int = iniciar_servidor(
        cpu_config->ip_cpu,
        cpu_config->puerto_escucha_interrupt);

    pthread_create(&hilo_a_memoria, NULL, enviar_saludo, (void*)socket_a_memoria);
    pthread_detach(hilo_a_memoria);

    pthread_create(&hilo_escucha_dis, NULL, atender_clientes, (void *)socket_escucha_dis);
    pthread_detach(hilo_escucha_dis);

    pthread_create(&hilo_escucha_int, NULL, atender_clientes, (void *)socket_escucha_int);
    pthread_detach(hilo_escucha_int);

    pthread_exit(NULL);

    return 0;

}

void * enviar_saludo (void * socket_memoria)
{
	for (int i = 0; i < 6; i++)
	{
		enviar_mensaje ("HOLA Memoria, SOY CPU", *((int *)socket_memoria));
		sleep (2);
	}
	return NULL;
}
