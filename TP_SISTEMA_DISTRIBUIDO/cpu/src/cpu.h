#ifndef _CPU_H_
#define _CPU_H_

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


t_log* cpu_logger;
t_config* cpu_config;


char* ip_memoria;
char* puerto_memoria;
char* puerto_escucha_dispatch;
char* puerto_escucha_interrupt;
int cant_entradas_tlb;
char* algoritmo_tlb;

//------CREACION DE FYLE DESCRIPTORS------
	int fd_memoria;
    int fd_kernel;
    int fd_cpu;




#endif
