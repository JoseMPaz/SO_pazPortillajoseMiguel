#ifndef _UTIL_H_
#define _UTIL_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include <pthread.h>
#include <utils/cliente.h>
#define CADENA_VACIA ""

extern t_log * logger;//Para el archivo historico 

t_log * iniciar_logger (void);
t_config * iniciar_config (void);
void leer_consola (t_log*);
void paquete (int);
void terminar_programa (int, t_log*, t_config*);

#endif 
