#include <utils/util.h>

t_log * iniciar_logger (char * ubicacion_de_archivo, char * nombre_del_proceso)
{
	t_log * nuevo_logger;

	nuevo_logger = log_create (ubicacion_de_archivo, nombre_del_proceso, true, LOG_LEVEL_INFO);
	
	if(nuevo_logger == NULL)
	{
		fprintf(stderr, "%s\n", "Error al crear el logger");
		exit(EXIT_FAILURE);
	}
	
	return nuevo_logger;
}

t_config * iniciar_config (char* path)
{
	t_config * nuevo_config;
	
	nuevo_config = config_create (path);
	
	if(nuevo_config ==NULL)
	{
		printf("error en la creacion del config");
		exit(EXIT_FAILURE);
	}
	
	return nuevo_config;
}

void liberar_conexion (int socket_cliente)
{
	close(socket_cliente);
	
	return;
}

void realizar_operacion (int fd_cliente, t_log * logger_servidor)
{
	t_list * lista = NULL;
	int cod_op;
	
	while (true) 
	{
		cod_op = recibir_operacion (fd_cliente);
		
		switch (cod_op) 
		{
			case MENSAJE:
 				recibir_mensaje (fd_cliente, logger_servidor);
				break;
			case PAQUETE:
				lista = recibir_paquete(fd_cliente);
				log_info (logger_servidor, "Me llegaron los siguientes valores:\n");
				//list_iterate (lista, (void*) iterator);
				if (lista != NULL) 
					list_destroy (lista);
				break;
			case -1:
				log_error (logger_servidor, "Desconexion: Terminando servidor");
				exit(EXIT_FAILURE);
				break;
			default:
				log_warning (logger_servidor, "Operacion desconocida");
		}
	}
	return;
}

void* recibir_buffer ( int * size, int socket_cliente)
{
	void * buffer;

	recv (socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc (*size);
	recv (socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

int crear_conexion (char * ip, char * puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo (ip, puerto, &hints, &server_info);

	// Ahora vamos a crear el socket.
	int socket_cliente = socket (server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);


	// Ahora que tenemos el socket, vamos a conectarlo
	connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);
	freeaddrinfo(server_info);

	return socket_cliente;
}

/*cambios que hice en la funcion iniciar servidor:
- Cambie el puerto porque estaba hardcodeado y nosotros
 lo tenemos que sacar de un archivo de config
- Agregue el log y el msnesaje que viene del servidor
*/
int iniciar_servidor (char * puerto_escucha_del_servidor, t_log * logger_servidor, char * mensaje_de_inicio_del_servidor)
{

	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, puerto_escucha_del_servidor, &hints, &servinfo);

	// Creamos el socket de escucha del servidor
	
	socket_servidor = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	// Asociamos el socket a un puerto

    bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);    
	
	//my_addr: Es un puntero a una estructura sockaddr que contiene la IP de la máquina local y el número de puerto que se va a asignar al socket 
    //addrlen: debe estar establecido al tamaño de la estructura anterior, utilizando para ello la función sizeof()
	
	//bind() está recibiendo el puerto que debe ocupar a partir de los datos que le suministramos al getaddrinfo con anterioridad.

	// Escuchamos las conexiones entrantes

	freeaddrinfo(servinfo);
	log_info(logger_servidor, "SERVER: %s", mensaje_de_inicio_del_servidor);

	listen(socket_servidor,SOMAXCONN);

	//Segundo parametro de listen: Número máximo de conexiones en la cola de entrada de conexiones.
	//Las conexiones entrantes quedan en estado de espera en esta cola hasta que sean aceptadas mediante la función accept().

	return socket_servidor;
}


int esperar_cliente (int socket_servidor , t_log* logger , char* mensajeDelCliente) 
{

	// Aceptamos un nuevo cliente
	int socket_cliente = accept(socket_servidor , NULL, NULL);

	
	log_info(logger , "Se conecto el cliente %s!" , mensajeDelCliente );

	return socket_cliente;
}

int recibir_operacion (int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente , &cod_op, sizeof(int) , MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void enviar_mensaje(char * mensaje, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	eliminar_paquete(paquete);
	return;
}

void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}

void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
	return;
}

void recibir_mensaje (int socket_cliente, t_log* logger_servidor)
{
	int size;
	char * buffer = recibir_buffer (&size, socket_cliente);
	log_info(logger_servidor, "Me llego el mensaje: %s", buffer);
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
