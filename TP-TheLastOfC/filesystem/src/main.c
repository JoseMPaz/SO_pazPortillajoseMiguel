#include <utils/cliente_servidor.h>
#include <filesystem_config.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <pthread.h>


/* Variables globales */
t_log * logger = NULL;
filesystem_config_t* filesystem_config = NULL;




int main(int argc, char* argv[]) {
    
    // Iniciar el logger
    logger = crear_logger();
    log_info(logger, "Iniciando FileSystem");

    // Cargar la configuracion
    cargar_configuracion_filesystem("filesystem.config");
    
    // Iniciar el servidor
    int socket_servidor = iniciar_servidor(
        filesystem_config->ip_filesystem,
        filesystem_config->puerto_escucha);

    log_info(logger, "Servidor listo para recibir al cliente");

	while (true) {
        pthread_t hilo;
        int * socket_bidireccional = (int *) malloc (sizeof(int));
        *socket_bidireccional =  accept (socket_servidor, NULL, NULL);	//se queda ahi hasta que se acepte un cliente
		pthread_create (&hilo, NULL, atender, (void *) socket_bidireccional);
	}
    
    return 0;
}


