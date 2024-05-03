#ifndef UTIL_H_ /*Si  no esta definido UTIL_H_*/
#define UTIL_H_	/*Entonces lo definimo a UTIL_H_*/

/*Bibliotecas utilizadas*/
#include <stdlib.h>
#include <stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h> 
#include<commons/config.h>

#include<readline/readline.h>
#include "hello.h"

typedef enum
{
	MENSAJE,
	PAQUETE
    //aca vamos a agregar mas cosas despues, por ej crearproceso
}op_code;
typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;


/*Aca deberian declararse las funciones de logger y config*/
t_log* iniciar_logger (char * ubicacion_de_archivo, char * nombre_del_proceso);
t_config* iniciar_config (char * path);
void liberar_conexion(int socket_cliente);
int recibir_operacion(int socket_cliente);
void realizar_operacion (int fd_cliente, t_log * logger_servidor);
int crear_conexion(char *ip, char* puerto);
int iniciar_servidor(char* puerto, t_log* logger, char* mensajeDelServer);
int esperar_cliente(int socket_servidor, t_log* logger, char* mensajeDelCliente);
int recibir_operacion(int socket_cliente);
void enviar_mensaje(char* mensaje, int socket_cliente);
void* serializar_paquete(t_paquete* paquete, int bytes);
void eliminar_paquete(t_paquete* paquete);
void recibir_mensaje (int socket_cliente, t_log* logger_servidor);
t_list* recibir_paquete(int socket_cliente);
void* recibir_buffer ( int * size, int socket_cliente);

#endif /*Termino de definir a UTIL_H_*/

 
