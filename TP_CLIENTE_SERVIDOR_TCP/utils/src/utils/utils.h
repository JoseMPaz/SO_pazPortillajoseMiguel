#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <readline/readline.h>
#include <pthread.h>
#include <commons/log.h>
#include <commons/string.h>
#include <commons/config.h>

#define CADENA_VACIA ""
#define ERROR_APERTURA_LOG "Error de apertura del archivo log: "
#define ERROR_APERTURA_CONFIG "Error de apertura del archivo config: "
#define APERTURA_DE_ARCHIVO "Apertura de archivo: "
#define VALOR_DE_CONFIG "Config: "
#define CLAVE "Clave: "
#define VALOR "Valor: "
#define CLAVE_NO_ENCONTRADA "No existe en archivo de configuracion la clave: "
#define INICIO_DE_LECTURA_DE_CONSOLA_LOG "INICIO DE LECTURA DE CONSOLA" 
#define FIN_DE_LECTURA_DE_CONSOLA_LOG "FIN DE LECTURA DE CONSOLA" 
#define DELIMITADOR_LOG "#######################################################################"

typedef struct addrinfo t_addrinfo;

typedef enum
{
	MENSAJE = 0,
	PAQUETE = 1
}t_codigo_operacion;

typedef struct
{
	int longitud_dato;
	void * dato;
}t_temporal;

typedef struct
{
	t_codigo_operacion codigo_operacion;
	t_temporal * temporal;
}t_paquete;

typedef struct
{	
	int socket_bidireccional;
	int * cantidad_de_conexiones;
	t_log * log;
}t_parametro_servidor;

typedef struct
{
	int socket;
	t_log * log;
}t_escucha;

typedef struct
{
	int socket_cliente;
	char * puerto_servidor;
	char * ip_servidor;
	t_log * log;
	void * (*proceso) (void *);
}t_dato_conexion;

typedef struct
{
	char * saludo;
	int socket_cliente;	
}t_dato_enviado;

void iniciar_log (t_log ** log, char * archivo_log, char * etiqueta_log);
void iniciar_config (t_config ** config, char * archivo_config, t_log * log);
bool leer_valor_de_config (t_config * config, char * clave, char ** valor , t_log * log);
void * leer_de_consola_a_log (void * arg);
void crear_conexion (int * socket_cliente, char * puerto_servidor, char * ip_servidor, t_log * log);
void solicitar_atencion (int socket_cliente, char * puerto_servidor, t_addrinfo * server_info, t_log * log);

void * conectar_a_servidor (void * datos_conexion);
void * saludar_a_cliente (void * dato);
int crear_socket_cliente (char * puerto_servidor, char * ip_servidor, t_log * log);
void establecer_como_cliente (t_addrinfo ** server_info, char * puerto_servidor, char * ip_servidor);
void enviar_mensaje (char * mensaje, int socket_cliente);
void* serializar_paquete (t_paquete * paquete, int bytes_to_send);
void eliminar_paquete (t_paquete * paquete);
void enviar_paquete_desde_consola (int socket_cliente);
void enviar_paquete (t_paquete * paquete, int socket_cliente);
t_paquete * crear_paquete (void);
void crear_buffer (t_paquete * paquete);
void agregar_a_paquete (t_paquete * paquete, void * valor, int longitud);
void establecer_como_servidor (t_addrinfo **server_info, char * puerto_servidor);

int crear_socket_servidor (char * puerto_servidor, t_log * log);
void asignar_direccion_local_a_socket ( int * socket, t_addrinfo * server_info, t_log * log);
void marcar_como_socket_de_escucha (int * socket_servidor, t_log * log);
void * atender_clientes (void * escucha);
void * atender (void * socket_bidireccional);
int recibir_operacion(int socket_cliente);
void recibir_mensaje (int socket_cliente, t_log * log);
void * recibir_buffer (int * size, int socket_cliente);
t_list * recibir_paquete (int socket_cliente);
void loggear_mensajes (t_list * self, t_log * log);

#endif


