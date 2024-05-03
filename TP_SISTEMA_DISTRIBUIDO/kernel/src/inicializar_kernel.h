#ifndef _INICIALIZAR_KERNEL_H_
#define _INICIALIZAR_KERNEL_H_

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

//-------USO DE VARIABLES GLOBALES-------
extern t_config * kernel_config;
extern char* PUERTO_ESCUCHA;
extern char * PUERTO_MEMORIA;
extern char* IP_MEMORIA;
extern char * IP_CPU;
extern char* PUERTO_CPU_DISPATCH;
extern char* PUERTO_CPU_INTERRUPT;
extern char* ALGORITMO_PLANIFICACION;
extern int QUANTUM;
extern char** RECURSOS;
extern char** INSTANCIAS_RECURSOS;
extern int GRADO_MULTIPROGRAMACION;


//------CREACION DE FUNCIONES------
void inicializar_kernel();  

#endif