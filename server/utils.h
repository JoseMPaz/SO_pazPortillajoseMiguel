#ifndef _UTILS_H_		/* REVISA QUE _UTILS_H_ NO SE HAYA DEFINIDO ANTES */
#define _UTILS_H_		/* INICIO DE DEFINICION DE _UTILS_H_ */

/*Bibliotecas*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include<assert.h>

#define PUERTO "4444"

typedef enum
{
	MENSAJE = 0,
	PAQUETE = 1
}op_code;

extern t_log * 	logger;

void * 				recibir_buffer(int*, int);
int 					iniciar_servidor (void);
int 					esperar_cliente (int);
t_list * 			recibir_paquete (int);
void 					recibir_mensaje (int);
int 					recibir_operacion (int);

#endif /* FIN DE DEFINICION DE UTILS_H_ */
