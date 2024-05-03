#ifndef _ENTRADASALIDA_H_
#define _ENTRADASALIDA_H_

#include <stdlib.h>
#include <stdio.h>

#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

#include<commons/log.h> 
#include<commons/config.h>

#include <utils/hello.h>
#include <utils/util.h>

//Variables GLOBALES
t_log* nuestro_log;
t_log* logger_entradasalida;
t_config* entradasalida_config;

//-----CREACION FYLE DESCRIPTORS------
int fd_kernel;
int fd_memoria;

char *IP_ENTRADA_SALIDA;
char *PUERTO_ENTRADA_SALIDA;
char *PUERTO_ESCUCHA_DISPATCH_ENTRADA_SALIDA;
char *PUERTO_ESCUCHA_INTERRUPT_ENTRADA_SALIDA;
char *CANTIDAD_ENTRADAS_TLB_ENTRADA_SALIDA;
char *ALGORITMO_TLB_ENTRADA_SALIDA;

char *TIPO_INTERFAZ;
char *TIEMPO_UNIDAD_TRABAJO;
//char *IP_KERNEL;
//char *PUERTO_KERNEL;
//char *IP_MEMORIA;
//char *PUERTO_MEMORIA;
char *PATH_BASE_DIALFS;
char *BLOCK_SIZE;
char *BLOCK_COUNT;

#endif
