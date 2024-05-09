#include <utils/utils.h>

void crear_conexion (int * socket_cliente, char * puerto_servidor, char * ip_servidor, t_log * log)
{
	t_addrinfo hints, * server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(ip_servidor, puerto_servidor, &hints, &server_info);//llamada al sistema
	if ( (*socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol)) < 0)
	{
		log_error (log, "%s%s", "No se logro crear el socket del cliente con el puerto: ", puerto_servidor);
		exit (EXIT_FAILURE);
	}
	log_info(log, "Se creo el socket cliente");
	solicitar_atencion (*socket_cliente, puerto_servidor, server_info, log);
	freeaddrinfo(server_info);
	return;
}

void iniciar_log (t_log ** log, char * archivo_log, char * etiqueta_log)
{
	*log = log_create (archivo_log, etiqueta_log, true, LOG_LEVEL_INFO);
	
	if (*log == NULL)
	{
		log_error (*log, "%s%s", ERROR_APERTURA_LOG, archivo_log);
		exit (EXIT_FAILURE);
	}
	log_info (*log, "%s", DELIMITADOR_LOG);
	log_info (*log, "%s%s", APERTURA_DE_ARCHIVO, archivo_log);
	
	return;
}

void iniciar_config (t_config ** config, char * archivo_config, t_log * log)
{
	*config = config_create (archivo_config);
	
	if (*config == NULL)
	{
		log_error (log, "%s%s", ERROR_APERTURA_CONFIG, archivo_config);
		exit (EXIT_FAILURE);
	}
	log_info (log, "%s%s", APERTURA_DE_ARCHIVO, archivo_config);
	
	return;
}

bool leer_valor_de_config (t_config * config, char * clave, char ** valor , t_log * log)
{
	if (config_has_property (config, clave))//Valida que existan las claves en config
	{
		*valor = config_get_string_value(config, clave);//Guarda el ip del servidor que se encontraba en config
		log_info (log, "%s%s%s%s", VALOR_DE_CONFIG, clave, " = ", *valor);
		return true;
	}
	log_error (log, "%s%s", CLAVE_NO_ENCONTRADA , clave);
	return false;
}

void leer_de_consola_a_log (t_log * log)
{
	char * leido = NULL;
	
	do
	{
		if ( strcmp ( ( leido = readline ("Ingrese cadena(finaliza con un enter):") ), CADENA_VACIA) == 0 )
			continue;
		log_info (log, "%s%s", "Consola: ", leido);
		free (leido);
	}while( strcmp ( leido , CADENA_VACIA) != 0 );
	free (leido);
		
	return;
}


void solicitar_atencion (int socket_cliente, char * puerto_servidor, t_addrinfo * server_info, t_log * log)
{
	log_info (log, "%s", "Solicita atencion al servidor");
	
	if ( connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
	{
		log_error (log, "%s%s", "No se logro establecer la conexion con el cliente del puerto: ", puerto_servidor);
		exit (EXIT_FAILURE);
	}
	log_info (log, "%s", "Inicia la atencion");
	return;
}

/*************************************************************************************/
/*Para enviar mensajes*/
void enviar_mensaje (char * mensaje, int socket_cliente)
{
	t_paquete * paquete;
	int bytes_to_send;
	
	/*Agrega el mensaje en un paquete*/
	paquete = (t_paquete *) malloc ( sizeof (t_paquete) );
	
	paquete->codigo_operacion = MENSAJE;
	paquete->temporal = (t_temporal *) malloc ( sizeof (t_temporal));
	
	paquete->temporal->longitud_dato = strlen (mensaje) + 1;
	paquete->temporal->dato = (void *) malloc (paquete->temporal->longitud_dato);
	
	memcpy (paquete->temporal->dato, mensaje, paquete->temporal->longitud_dato);//Copia el mensaje al paquete
	/*Serializo el paquete*/
	bytes_to_send = paquete->temporal->longitud_dato + 2 * sizeof(int);//Cantidad de bytes a enviar
	void * mensaje_serializado = serializar_paquete(paquete, bytes_to_send);//Serializo el paquete con el mensaje
	send(socket_cliente, mensaje_serializado, bytes_to_send, 0);//Envio el mensaje serializado desde al servidor
	/*Eliminacion de estructuras temporales*/
	free(mensaje_serializado);//Elimino el mensaje serializado
	eliminar_paquete(paquete);//Elimino el paquete
	return;
}

void* serializar_paquete (t_paquete * paquete, int bytes_to_send)
{
	void * mensaje_serializado;
	int desplazamiento = 0;
	
	mensaje_serializado = malloc (bytes_to_send);
	/*Ingreso el paquete al mensaje serializado*/
	memcpy ( mensaje_serializado + desplazamiento, &(paquete->codigo_operacion), sizeof (int) );
	desplazamiento += sizeof (int);
	memcpy ( mensaje_serializado + desplazamiento, &(paquete->temporal->longitud_dato), sizeof (int) );
	desplazamiento += sizeof (int);
	memcpy ( mensaje_serializado + desplazamiento, paquete->temporal->dato, paquete->temporal->longitud_dato );
	desplazamiento += paquete->temporal->longitud_dato;

	return mensaje_serializado;
}

void eliminar_paquete (t_paquete * paquete)
{
	free(paquete->temporal->dato);
	free(paquete->temporal);
	free(paquete);
	return;
}

/*Para enviar paquetes desde consola*/
void enviar_paquete_desde_consola (int socket_cliente)
{
	char * leido = NULL;
	t_paquete * paquete = crear_paquete ();

	do
	{
		if ( strcmp ( ( leido = readline ("Ingrese cadena(finaliza con un enter):") ), CADENA_VACIA) == 0 )
			continue;
		agregar_a_paquete (paquete, leido, strlen (leido) + 1);
		free (leido);
	}while( strcmp ( leido , CADENA_VACIA) != 0 );
	
	free (leido);
	enviar_paquete (paquete, socket_cliente);	//Enviar paquete
	eliminar_paquete (paquete);//Liberar paquete
	
	return;
}

void enviar_paquete (t_paquete * paquete, int socket_cliente)
{
	int bytes_to_send;
	void * mensaje_serializado;
	
	bytes_to_send = paquete->temporal->longitud_dato + 2 * sizeof (int);
	mensaje_serializado = serializar_paquete (paquete, bytes_to_send);
	send (socket_cliente, mensaje_serializado, bytes_to_send, 0);
	free (mensaje_serializado);
	
	return;
}

t_paquete* crear_paquete (void)
{
	t_paquete * paquete = (t_paquete *) malloc (sizeof ( t_paquete ));
	
	paquete->codigo_operacion = PAQUETE;
	crear_buffer(paquete);
	
	return paquete;
}

void crear_buffer (t_paquete * paquete)
{
	paquete->temporal = (t_temporal *) malloc (sizeof (t_temporal));
	paquete->temporal->longitud_dato = 0;
	paquete->temporal->dato = NULL;
}

void agregar_a_paquete (t_paquete * paquete, void * valor, int longitud)
{
	paquete->temporal->dato = realloc ( paquete->temporal->dato, paquete->temporal->longitud_dato + longitud + sizeof (int) );
	memcpy ( paquete->temporal->dato + paquete->temporal->longitud_dato, &longitud, sizeof (int) );
	memcpy ( paquete->temporal->dato + paquete->temporal->longitud_dato + sizeof(int), valor, longitud);
	paquete->temporal->longitud_dato += longitud + sizeof (int);
	
	return;
}

/***************************************************************************************/
int crear_socket_servidor (char * puerto_servidor, t_log * log)
{
	int socket_servidor;
	t_addrinfo hints, * server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;//IP LOCAL
	getaddrinfo(NULL, puerto_servidor, &hints, &server_info);//llamada al sistema, devuelve información de red sobre la IP y puerto de servidor
	if ( (socket_servidor = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol)) < 0)
	{
		log_error (log, "%s%s", "No se logro crear el socket del servidor con el puerto: ", puerto_servidor);
		exit (EXIT_FAILURE);
	}
	log_info(log, "Se creo el socket servidor");
	asignar_direccion_local_a_socket ( &socket_servidor, server_info, log);
	freeaddrinfo(server_info);
	marcar_como_socket_de_escucha (&socket_servidor, log);
	return socket_servidor;
}

void asignar_direccion_local_a_socket ( int * socket, t_addrinfo * server_info, t_log * log)
{
	if ( bind ( *socket, server_info->ai_addr, server_info->ai_addrlen) == -1)
	{
		log_error (log, "%s", "No se logro asignar direccion al socket");
		exit (EXIT_FAILURE);
	}
	
	return;
}

void marcar_como_socket_de_escucha (int * socket_servidor, t_log * log)
{
	if ( listen (*socket_servidor, SOMAXCONN) == -1 )
	{
		log_error (log, "%s", "No se logro colocar al socket servidor, como socket de escucha");
		exit (EXIT_FAILURE);
	}
	
	return;
}

void atender_clientes (int socket_servidor, t_log * log)
{
	int cantidad_de_conexiones = 0;
	t_parametro_servidor * parametro_servidor = (t_parametro_servidor *) malloc ( sizeof (t_parametro_servidor) );
	
	log_info (log, "%s", "Inicia la atencion a los clientes");
	while (cantidad_de_conexiones < SOMAXCONN)
	{
		pthread_t hilo;
		int * socket_bidireccional = (int *) malloc (sizeof(int));
		
		*socket_bidireccional =  accept (socket_servidor, NULL, NULL);	//se queda ahi hasta que se acepte un cliente
		log_info (log, "%s", "Nueva conexion de un cliente");
		parametro_servidor->socket_bidireccional = *socket_bidireccional;
		parametro_servidor->cantidad_de_conexiones = &cantidad_de_conexiones;
		parametro_servidor->log = log;
		pthread_create (&hilo, NULL, atender, (void *) parametro_servidor);
		pthread_detach(hilo);
		cantidad_de_conexiones++;
	}
	free(parametro_servidor);
	return;
}

void * atender (void * argumento)
{
	t_parametro_servidor * parametro_servidor = (t_parametro_servidor *) argumento;
	int socket_bidireccional = parametro_servidor->socket_bidireccional; 
	int * cantidad_de_conexiones = parametro_servidor->cantidad_de_conexiones; 
	t_log * log = parametro_servidor->log; 
	t_list * lista = NULL;
	
	while (true) 
	{
		int codigo_operacion = recibir_operacion (socket_bidireccional);
		
		switch (codigo_operacion) 
		{
			case MENSAJE:
				recibir_mensaje (socket_bidireccional, log);
				break;
			case PAQUETE:
			lista = recibir_paquete (socket_bidireccional);
			log_info(log, "Mensajes recibidos:");
			loggear_mensajes (lista, log);
			break;
			case -1:
				log_error (log, "el cliente se desconecto. Terminando servidor");
				(*cantidad_de_conexiones)--;
				return NULL;
			default:
				log_warning(log,"Operacion desconocida");
				return NULL;
		}
	}

	return NULL;
}

int recibir_operacion(int socket_cliente)
{
	int codigo_operacion;
	
	if(recv(socket_cliente, &codigo_operacion, sizeof(int), MSG_WAITALL) > 0)
		return codigo_operacion;
	
	close(socket_cliente);
	
	return -1;
}


void recibir_mensaje (int socket_cliente, t_log * log)
{
	int size;
	char * buffer = recibir_buffer (&size, socket_cliente);
	log_info (log, "Me llego el mensaje %s", buffer);
	free(buffer);
	
	return;
}

void * recibir_buffer (int * size, int socket_cliente)
{
	void * buffer;

	recv (socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv (socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}


t_list * recibir_paquete (int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list * valores = list_create();
	int tamanio;

	buffer = recibir_buffer (&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy ( &tamanio, buffer + desplazamiento, sizeof (int) );
		desplazamiento += sizeof (int);
		char * valor = (char *) malloc ( tamanio );
		memcpy (valor, buffer + desplazamiento, tamanio);
		desplazamiento += tamanio;
		list_add (valores, valor);
	}
	free (buffer);
	
	return valores;
}

void loggear_mensajes (t_list * self, t_log * log) 
{
	t_link_element ** indirect = &self->head;
	
	while ((*indirect) != NULL) 
	{
		log_info(log,"%s", (char *)(*indirect)->data);
		indirect = &(*indirect)->next;
	}
	return;
}


