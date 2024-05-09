#include "main.h"

int main(void)
{
	t_log * log = NULL;
	t_config * config = NULL;
	char * ip_servidor = NULL, * puerto_servidor = NULL;
	int socket_cliente;

	iniciar_log (&log, "cliente.log", "CLIENTE_LOG");//Apertura de archivo historico
	iniciar_config (&config, "cliente.config", log);//Apertura de archivo de configuraciones
	leer_valor_de_config (config, "IP_SERVIDOR", &ip_servidor, log);
	leer_valor_de_config (config, "PUERTO_SERVIDOR", &puerto_servidor, log);
	leer_de_consola_a_log (log);

	/*--------------------------------------------------- CLIENTE -------------------------------------------------------------*/
	crear_conexion (&socket_cliente, puerto_servidor, ip_servidor, log);//Inicia la conexion con el servidor
	enviar_mensaje ("HOLA MUNDO", socket_cliente);	// Enviamos al servidor el mensaje HOLA MUNDO
	enviar_paquete_desde_consola (socket_cliente);// Armamos y enviamos un paquete

	/*--------------------------------------------------- LIBERO RECURSOS -------------------------------------------------------------*/	
	log_destroy (log);
	config_destroy (config);
	close (socket_cliente);
	
	return EXIT_SUCCESS;
}

