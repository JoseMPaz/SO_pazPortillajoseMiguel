#ifndef _CONSOLA_H_
#define _CONSOLA_H_
#include <stdlib.h>
#include <stdio.h>
#include <commons/log.h> 
#include <commons/config.h>
#include <utils/hello.h>
#include <utils/util.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <readline/readline.h>
#include <commons/string.h> 
#include <pthread.h>
#include <semaphore.h>

#define CADENA_VACIA "\0"
#define BASE_DECIMAL 10
#define ESPACIO_EN_BLANCO " "

extern t_log * kernel_logger; 




void * iniciar_consola(void * arg);
//void atender_instruccion_validada(char*);
bool validacion_de_instruccion_de_consola(char*);
void iniciar_proceso(t_buffer*);
void finalizar_proceso(t_buffer*);
void detener_planificacion(t_buffer*);
void iniciar_planificacion(t_buffer*);
void proceso_estado(t_buffer*);
void multiprogramacion(t_buffer*);

#endif
