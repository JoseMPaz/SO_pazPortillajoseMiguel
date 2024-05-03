#ifndef _MEMORIA_H_
#define _MEMORIA_H_

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


//------CREACION DE VARIABLES GLOBALES------


//------CREACION DE FYLE DESCRIPTORS------
	int fd_memoria;
    int fd_kernel;
    int fd_cpu;
    int fd_entradasalida;





#endif
