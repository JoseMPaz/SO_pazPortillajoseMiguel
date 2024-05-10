#include "main.h"

int main(void)
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * ip_servidor = NULL, * puerto_servidor = NULL;
	int socket_cliente;
	t_dato_conexion * datos_conexion = (t_dato_conexion *) malloc (sizeof (t_dato_conexion));
	pthread_t hilo;

	iniciar_log (&log, "cliente.log", "CLIENTE_LOG");//Apertura de archivo historico
	iniciar_config (&config, "cliente.config", log);//Apertura de archivo de configuraciones
	leer_valor_de_config (config, "IP_SERVIDOR", &ip_servidor, log);
	leer_valor_de_config (config, "PUERTO_SERVIDOR", &puerto_servidor, log);
	leer_de_consola_a_log (log);

	/*--------------------------------------------------- CLIENTE -------------------------------------------------------------*/
	socket_cliente = crear_socket_cliente (puerto_servidor, ip_servidor, log);
	datos_conexion->socket_cliente = socket_cliente;
	datos_conexion->puerto_servidor = puerto_servidor;
	datos_conexion->ip_servidor = ip_servidor;
	datos_conexion->log = log;
	datos_conexion->proceso = saludar_a_cliente;
	
	pthread_create (&hilo, NULL, conectar_a_servidor , (void *) datos_conexion);
	pthread_detach(hilo);
	
	pthread_exit (NULL);
	
	//crear_conexion (&socket_cliente, puerto_servidor, ip_servidor, log);//Inicia la conexion con el servidor
	//enviar_mensaje ("HOLA MUNDO", socket_cliente);	// Enviamos al servidor el mensaje HOLA MUNDO
	//enviar_paquete_desde_consola (socket_cliente);// Armamos y enviamos un paquete

	/*--------------------------------------------------- LIBERO RECURSOS -------------------------------------------------------------*/	
	free (datos_conexion);
	log_destroy (log);
	config_destroy (config);
	close (socket_cliente);
	
	return EXIT_SUCCESS;
}

