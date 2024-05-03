#include <utils/servidor.h>



t_log * logger;//Variable externa

int iniciar_servidor(void)
{
	// Quitar esta línea cuando hayamos terminado de implementar la funcion
	//assert(!"no implementado!");/*Muestra el mensaje que indica que esta funcion aun no fue implementada*/

	int socket_servidor;

	struct addrinfo hints, * server_info = NULL;

	//memset o bien memory set, establece 0 en la memoria, solo desde inicio de la memoria hasta sizeof(hints)
	memset (&hints, 0, sizeof(hints));
	hints.ai_family 	= AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags 	= AI_PASSIVE;

	getaddrinfo (NULL, PUERTO, &hints, &server_info);

	// Creamos el socket del servidor en modo escucha 
	socket_servidor = socket (server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	// Asociamos el socket a un puerto
	bind (socket_servidor, server_info->ai_addr, server_info->ai_addrlen);

	// Escuchamos las conexiones entrantes
	listen(socket_servidor, SOMAXCONN);
	
	//Libera servinfo
	if (server_info != NULL)
		freeaddrinfo(server_info);
	
	log_trace(logger, "Listo para escuchar a mi cliente");

	return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{
	// Aceptamos un nuevo cliente
	int socket_cliente = accept (socket_servidor, NULL, NULL);
	//logeamos que se conecto un cliente al servido
	log_info(logger, "Se conecto un cliente!");

	return socket_cliente;//Retorno el socket del cliente
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if	( recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0 )
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer ( int * size, int socket_cliente)
{
	void * buffer;

	recv (socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc (*size);
	recv (socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje (int socket_cliente)
{
	int size;
	char * buffer = recibir_buffer (&size, socket_cliente);
	log_info(logger, "Me llego el mensaje: %s", buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}
