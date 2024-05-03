#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <stdlib.h>
#include <stdio.h>//Biblioteca de flujos de entrada y salida
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include <pthread.h>//Biblioteca para la programación multiproceso
#include<commons/log.h> 
#include<commons/config.h>

#include <utils/hello.h>
#include <utils/util.h>

#include "consola.h"
#include "inicializar_kernel.h"
#include "pcb.h"
#include "kernel_io.h"

//------CREACION DE VARIABLES GLOBALES------

t_log * nuestro_log_kernel; 
t_log * kernel_logger; 
t_config * kernel_config;


//-------CREACION DE VARIABLES GLOBALES-------
char* PUERTO_ESCUCHA;
char * PUERTO_MEMORIA;
char* IP_MEMORIA;
char * IP_CPU;
char* PUERTO_CPU_DISPATCH;
char* PUERTO_CPU_INTERRUPT;
char* ALGORITMO_PLANIFICACION;
int QUANTUM;
char** RECURSOS;
char** INSTANCIAS_RECURSOS;
int GRADO_MULTIPROGRAMACION;


int fd_cpu, fd_memoria, fd_kernel, fd_entradasalida;
#endif
