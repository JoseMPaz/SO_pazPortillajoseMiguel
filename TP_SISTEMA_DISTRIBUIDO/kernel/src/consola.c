#include "consola.h"

/*
void * iniciar_consola(void * arg)
{
	char * leido = NULL;
	
	 bool validacion_leido;


	leido = readline("Introduzca una opcion: ");





    while (strcmp(leido, CADENA_VACIA) != 0)
    {
    
   
        validacion_leido = validacion_de_instruccion_de_consola(leido);

        if(!validacion_leido){
            log_error(kernel_logger, "Comando de CONSOLA no reconocido");
            free(leido);
            leido=readline("Introduzca una opcion: ");
            continue; //Saltar y continuar con el resto de la iteracion
        }
        //atender_instruccion_validada(leido);
        free(leido);
        leido = readline("Introduzca una opcion: ");
        //system("clear");
    }
    free(leido);

    pthread_exit(NULL);  
}

bool validacion_de_instruccion_de_consola(char * leido)
{
    bool resultado_validacion = false;
    char * fin_de_cadena;
    FILE * pf;
    
    char** comando_consola = string_split (leido, ESPACIO_EN_BLANCO); // CONVIERTE LO INGRESADO EN PALABRAS SEPARADAS
    
    if( strcmp(comando_consola[0], "INICIAR_PROCESO") == 0 )
    {
        printf("Comando Iniciar proceso ok\n");
        if ((pf = fopen(comando_consola[1],"r")) != NULL )
        {
            puts("Abrio archivo ok");
            fclose(pf);
            resultado_validacion = true;
        }     
    }else if(strcmp(comando_consola[0], "EJECUTAR_SCRIPT") == 0 && fopen(comando_consola[1],"r") != NULL ){
        resultado_validacion = true;    
    }else if(strcmp(comando_consola[0], "FINALIZAR_PROCESO" ) == 0 ) {
        strtol (comando_consola[1], &fin_de_cadena, BASE_DECIMAL);
        if (*fin_de_cadena == '\0')  //Cuando la cadena contiene un numero entero
            resultado_validacion = true;
    }else if(strcmp(comando_consola[0], "DETENER_PLANIFICACION") == 0){
        resultado_validacion = true;
    }else if(strcmp(comando_consola[0], "INICIAR_PLANIFCACION") == 0){
        resultado_validacion = true;
    }else if(strcmp(comando_consola[0], "MULTIPROGRAMACION") == 0){
        resultado_validacion = true;
    }else if(strcmp(comando_consola[0], "PROCESO_ESTADO") == 0){
        resultado_validacion = true;
    }else{
        log_error(kernel_logger, "Comando no reconocido");
        resultado_validacion = false;
    }
    string_array_destroy(comando_consola);
    return resultado_validacion;
}
void atender_instruccion_validada(char * leido)
{
    //char** comando_consola = string_split(leido, " ");
    //t_buffer* un_buffer = crear_buffer();  ESTO LO HACEMOS 
    

    // iniciar_proceso path 
       
    if(strcmp(comando_consola[0], "INICIAR_PROCESO") == 0){
        //cargar_string_al_buffer(un_buffer, comando_consola[1]);
         //   iniciar_proceso(un_buffer); //estas son funciones que despues tenemos que programar
    }else if(strcmp(comando_consola[0], "FINALIZAR_PROCESO") == 0){
        //cargar_string_al_buffer(un_buffer, comando_consola[1]);
            finalizar_proceso(un_buffer);
    }else if(strcmp(comando_consola[0], "DETENER_PLANIFICACION") == 0){
            detener_planificacion(un_buffer);
    }else if(strcmp(comando_consola[0], "INICIAR_PLANIFICACION") == 0){
            iniciar_planificacion(un_buffer);
    }else if(strcmp(comando_consola[0], "MULTIPROGRAMACION") == 0){
        //cargar_string_al_buffer(un_buffer, comando_consola[1]);
         //   multiprogramacion(un_buffer);
    }else if(strcmp(comando_consola[0], "PROCESO_ESTADO") == 0){
          //  proceso_estado(un_buffer);
    }else{
        log_error(kernel_logger, "Comando no reconocido");
        exit(EXIT_FAILURE);
    }
    string_array_destroy(comando_consola);

    
}*/



