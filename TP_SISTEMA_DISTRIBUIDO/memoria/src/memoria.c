#include "memoria.h"

int main (void)
{
	t_log * memoria_logger;
	char * puerto_escucha;
	t_config * memoria_config;

	
	// -------CREACION DE LOGS-------
	// -------LOG OBLIGATORIO-------
	memoria_logger = iniciar_logger ("memoria.log", "MEMORIA_LOG");

	// ------- CREACION DE CONFIGS -------
	memoria_config = iniciar_config("../memoria/memoria.config");
 
	//------ EXTRAER VALOR DE LOS CONFIGS ------
	puerto_escucha = config_get_string_value (memoria_config , "PUERTO_ESCUCHA");
	//TAM_MEMORIA = config_get_int_value (memoria_config , "TAM_MEMORIA");
	//TAM_PAGINA = config_get_int_value (memoria_config , "TAM_PAGINA");
	//PATH_INSTRUCCIONES = config_get_string_value (memoria_config , "PATH_INSTRUCCIONES");
	//RETARDO_RESPUESTA = config_get_int_value (memoria_config , "RETARDO_RESPUESTA");

	//------ INICIAR MEMORIA QUE ES UN SERVIDOR PARA TODOS LOS MODULOS -----
	fd_memoria = iniciar_servidor (puerto_escucha , memoria_logger , "MEMORIA INICIADA CORRECTAMENTE"); //creamos el socket
	
	
		
	//------ MEMORIA ESPERA A CPU-----		
	fd_cpu = esperar_cliente(fd_memoria , memoria_logger , "CPU"); 
	//------ MEMORIA ESPERA A KERNEL-----
	fd_kernel = esperar_cliente(fd_memoria , memoria_logger , "KERNEL");
	//------ MEMORIA ESPERA A I/O-----		
	fd_entradasalida = esperar_cliente(fd_memoria , memoria_logger , "ENTRADA SALIDA"); 



	//------ MEMORIA ATIENDE A KERNEL-----
	realizar_operacion(fd_kernel,memoria_logger);
	//------ MEMORIA ATIENDE A CPU -----
	realizar_operacion(fd_cpu,memoria_logger); //aca se pone el fd de la CONEXION
	//------ MEMORIA ATIENDE A I/O -----
	realizar_operacion(fd_entradasalida,memoria_logger);  


    //--------LIBERAMOS MEMORIA----------
    config_destroy(memoria_config);


	//------ esto no se que es----- , BORRENLO

	//fd_cliente = esperar_cliente(fd_memoria, memoria_logger, "");
	//realizar_operacion (fd_cliente, memoria_logger);
	
	/*fd_memoria = iniciar_servidor (puerto_escucha , memoria_logger , "MEMORIA INICIADA CORRECTAMENTE");
	fd_cliente = esperar_cliente(fd_memoria, memoria_logger, "");
	realizar_operacion (fd_cliente, memoria_logger);
	liberar_conexion (fd_memoria);*/
	

    return EXIT_SUCCESS;
}
