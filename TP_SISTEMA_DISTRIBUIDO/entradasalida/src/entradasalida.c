#include "entradasalida.h"

/* La entradasalida en cliente de kernel y de memoria */
int main (void) 
{
	char * ip_kernel, * ip_memoria, * puerto_kernel, * puerto_memoria;

	////------------ CREACION DE LOG //------------
	logger_entradasalida = iniciar_logger ("entradasalida.log","ENTRADASALIDA_LOG");
	
	////------------ CREACION DE CONFIG a partir del archivo entradasalida.config//------------
	entradasalida_config = iniciar_config("../entradasalida/entradasalida.config"); 
	
	//------------EXTRAEMOS LOS VALORES de CONFIG PARA LA CONEXION -----------------
	
	ip_kernel 					= config_get_string_value(entradasalida_config, "IP_KERNEL");
	puerto_kernel 				= config_get_string_value(entradasalida_config, "PUERTO_KERNEL");
	ip_memoria 					= config_get_string_value(entradasalida_config, "IP_MEMORIA");
	puerto_memoria				= config_get_string_value(entradasalida_config, "PUERTO_MEMORIA");
	
	//------------ OTRO LOS VALORES de CONFIG -----------------
	/*TIPO_INTERFAZ			= config_get_string_value(entradasalida_config, "TIPO_INTERFAZ");
	TIEMPO_UNIDAD_TRABAJO 	= config_get_string_value(entradasalida_config, "TIEMPO_UNIDAD_TRABAJO");
	PATH_BASE_DIALFS 			= config_get_string_value(entradasalida_config, "PATH_BASE_DIALFS");
	BLOCK_SIZE 					= config_get_string_value(entradasalida_config, "BLOCK_SIZE");
	BLOCK_COUNT					= config_get_string_value(entradasalida_config, "BLOCK_COUNT"); */



	//--------ENTRADASALIDA SE CONECTA A MEMORIA --------
	fd_memoria 	= crear_conexion (ip_memoria, puerto_memoria);
	enviar_mensaje ("Hola memoria, soy entradasalida, te voy a hacer peticiones", fd_memoria );//NO FUNCIONA
	
	//--------ENTRADASALIDA SE CONECTA A KERNEL --------
	fd_kernel 	= crear_conexion(ip_kernel , puerto_kernel);
	enviar_mensaje ("Hola kernel, soy entradasalida, te voy a hacer peticiones", fd_kernel );
	
	

	//----------LIBERAMOS MEMORIA--------------
	config_destroy(entradasalida_config);
	printf ("%s\n", "MODULO ENTRADA SALIDA FINALIZO CORRECTAMENTE");

	return(EXIT_SUCCESS);
}
