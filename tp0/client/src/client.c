#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;


	/* ---------------- LOGGING ---------------- */
	logger = iniciar_logger();
	log_info(logger,"inicio programa :)");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");
	log_info(logger,"El valor es %s ,la IP %s y el puerto es %s: ",valor, ip, puerto);

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);
	enviar_mensaje("hola",conexion);
	// Armamos y enviamos el paquete
	paquete(conexion,logger);


	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log *logguer;
	if((logguer=log_create("tp0.log","log",true, LOG_LEVEL_INFO)) == NULL){
		printf("Error crear logger");
		exit(1);
	}else{
		return logguer;
	}

}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	if((nuevo_config=config_create("cliente.config")) == NULL){
		printf("Error crear config \n");
		exit(1);
	}else{
		return nuevo_config;
	}
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa

	while(1){
		leido = readline(">");
		if(strcmp(leido,"")==0){
			free(leido);
			break;
		}
		log_info(logger,"Leyo de consola: %s",leido);

		free(leido);

	}

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion,t_log* logger)
{
	t_paquete* paquete = crear_paquete();
	// Ahora toca lo divertido!
	char* leido;

	while(1){
			leido = readline(">");
			if(strcmp(leido,"")==0){
				free(leido);
				break;
			}
			log_info(logger,"Leyo de consola: %s",leido);
			agregar_a_paquete(paquete,leido,strlen(leido) + 1);
			free(leido);

		}


	// Leemos y esta vez agregamos las lineas al paquete


	enviar_paquete(paquete, conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	if(logger!=NULL){
		log_destroy(logger);
	}
	if(config!=NULL){
		config_destroy(config);
	}

	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
