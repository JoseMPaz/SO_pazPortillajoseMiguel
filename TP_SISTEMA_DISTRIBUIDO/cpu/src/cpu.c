#include "cpu.h"

int main(int argc, char* argv[]) 
{


    // -------CREACION DE LOS LOGS-------
	cpu_logger = iniciar_logger ("cpu.log", "CPU_LOG");
    
    // -------CREACION DE CONFIGS-------
	cpu_config = iniciar_config("../cpu/cpu.config");
    
    // ------- EXTRAER VALORES DE LOS CONFIGS -------
	ip_memoria = config_get_string_value(cpu_config, "IP_MEMORIA");
	puerto_memoria = config_get_string_value(cpu_config, "PUERTO_MEMORIA");
	puerto_escucha_dispatch = config_get_string_value(cpu_config, "PUERTO_ESCUCHA_DISPATCH");
	puerto_escucha_interrupt = config_get_string_value(cpu_config, "PUERTO_ESCUCHA_INTERRUPT");
	//cant_entradas_tlb = config_get_int_value(cpu_config, "CANTIDAD_ENTRADAS_TLB");
	//algoritmo_tlb = config_get_string_value(cpu_config, "ALGORITMO_TLB");

	//--------CPU SE CONECTA A MEMORIA--------
	fd_memoria 	= crear_conexion (ip_memoria, puerto_memoria);
	enviar_mensaje ("Hola memoria, soy cpu, te voy a hacer peticiones", fd_memoria); //ESTO NO FUNCIONA
	

	//Por ahora solo uso el puerto de despacho del cpu	
	//--------CPU SE INICIA COMO SERVIDOR--------
	fd_cpu = iniciar_servidor(puerto_escucha_dispatch , cpu_logger , "CPU INICIADO CORRECTAMENTE"); //creamos el socket
	
	//------ ESPERA CONEXION DE KERNEL -----
	fd_kernel = esperar_cliente(fd_cpu, cpu_logger, "KERNEL");
	
	//------ ATIENDE A KERNEL -----
	realizar_operacion (fd_kernel, cpu_logger);
	
	
	    
    
	//--------LIBERAMOS MEMORIA----------
	config_destroy(cpu_config);

    //ESTO NO SE QUE ES, BORRENLO
	//Luego conecto el CPU como cliente y la MEMORIA como servidor
	//Creo conexión con la memoria
	// fd_memoria_CPU_CLIENTE = crear_conexion(ip_memoria, puerto_memoria);
	//Inicio al CPU como servidor
	// fd_cpu = iniciar_servidor(puerto_escucha_dispatch, cpu_logger, "CPU INICIADO CORRECTAMENTE");
	//espero al kernel
	// fd_kernel = esperar_cliente(fd_cpu, cpu_logger, "Kernel");
	
    return EXIT_SUCCESS;
}


