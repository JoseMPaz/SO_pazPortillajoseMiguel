#ifndef _KERNEL_IO_H_
#define _KERNEL_IO_H_

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


extern t_log * kernel_logger; 
extern int fd_entradasalida; 

void atender_io ();

#endif

