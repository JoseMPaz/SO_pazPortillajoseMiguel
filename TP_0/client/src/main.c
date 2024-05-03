#include "main.h"

/*Debe existir una funcion main para poder generar el ejecutable*/
int main(void)
{
	t_config * config = NULL;//Para configurar
	int conexion = 0;
	char * valor, * ip, * puerto;

	
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	/* ---------------- INICIO LOGGING ---------------- */
	
	if ( (logger = iniciar_logger()) == NULL)
	{
		fprintf (stderr, "%s\n", "Error al crear el logger");//Muestra por stderr->pantalla la cadena
		return EXIT_FAILURE;//Finaliza con falla
	}
	
	//		Usando el logger creado previamente
	// 	void	log_info(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));	
	log_info(logger, "%s", "Soy un Log");
	
	/* ---------------- FIN LOGGING ---------------- */

	/* ---------------- INICIO ARCHIVOS DE CONFIGURACION ---------------- */

	if ( (config = iniciar_config()) == NULL)
	{
		fprintf (stderr, "%s\n", "Error al crear un config");
		return EXIT_FAILURE;
	}
	// Usando el config creado previamente, leemos los valores del archivo cliente.config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	
	//	char * config_get_string_value (t_config*, char *key); Retorna un string con el valor asociado a key.	
	valor		= config_get_string_value(config, "CLAVE");
	ip			= config_get_string_value(config, "IP");
	puerto	= config_get_string_value(config, "PUERTO");

	// Loggeamos el valor de config
	log_info (logger, "%s%s", "Clave: ", valor);

	/* ---------------- FIN ARCHIVOS DE CONFIGURACION ---------------- */
	
	/* ---------------- INICIO LEER DE CONSOLA ---------------- */

	 leer_consola (logger);

	/* ---------------- FIN LEER DE CONSOLA ---------------- */
	
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él(Completar modulo server))

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion (ip, puerto);//La variable puerto guarda el PUERTO del servidor que es 4444

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje (valor, conexion);

	// Armamos y enviamos el paquete
	paquete (conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
	puts ("CLIENTE FINALIZADO EXITOSAMENTE");
	return EXIT_SUCCESS;
}


