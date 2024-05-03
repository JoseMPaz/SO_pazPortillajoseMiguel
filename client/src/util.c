#include "util.h"

t_log * iniciar_logger (void)
{
	t_log * logger;
	/*		t_log * log_create	(	char* file, char *program_name, bool is_active_console, t_log_level detail);
			@DESC: Crea una instancia de logger    */
	logger = log_create("log_client.log", "NEW_LOG_CLIENT", true, LOG_LEVEL_INFO);

	return logger;
}

t_config * iniciar_config (void)
{
	t_config * config;
	
	/*		t_config * config_create (char * path);
			@DESC: Crea una estructura t_config 		*/
	config = config_create ("cliente.config");

	return config;
}

void leer_consola(t_log * logger)
{
	char* leido;

	// La primera te la dejo de yapa
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	// ¡No te olvides de liberar las lineas antes de regresar!
	while ( strcmp (leido = readline("> "), CADENA_VACIA) )//Lee lineas mientras no sean ""
	{
	 	log_info (logger, "%s", leido);
	 	free (leido);
	}
	free (leido);//Para cuando se ingrese una cadena vacia y salga del while
	
	return;
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido = NULL;
	t_paquete * paquete = crear_paquete ();

	// Leemos y esta vez agregamos las lineas al paquete
	while ( strcmp (leido = readline("> "), CADENA_VACIA) )//Lee lineas mientras no sean ""
	{
		agregar_a_paquete (paquete, leido, strlen (leido) + 1);
		free (leido);
	}


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free (leido);
	
	//Enviar paquete
	enviar_paquete (paquete, conexion);
		
	//Liberar paquete
	eliminar_paquete (paquete);
	return;
}

void terminar_programa (int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  
	if (logger != NULL)
		log_destroy (logger);
		
	if (config != NULL)
		config_destroy (config);
		
	liberar_conexion (conexion);
	  
	 return;
}
