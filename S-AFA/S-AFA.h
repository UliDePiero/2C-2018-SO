/*
 * S-AFA.h
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */

#ifndef S_AFA_H_
#define S_AFA_H_
//Ruta del archivo de configuraciones
#define RUTA_CONFIG "S-AFA.config"
#define TAMMAXNOMBREALGORITMO 6
//#include <sockets.h>

#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <arpa/inet.h>
#include <conexionSockets.h>
#include <commons/collections/queue.h>

///---------------------VARIABLES A UTILIZAR-------------------------
int operacion;
//Colas de procesos
t_queue *listos;
t_queue *ejecucion;
t_queue *bloqueados;
t_queue *terminados;
int* primeroListos;
int* primeroEjecucion;
int* primeroBloqueados;
int* primeroTerminados;
///---------------------ESTRUCTURA DE CONFIGURACION DE S-AFA-------------------------

//Estructura para datos del archivo de configuracion
typedef struct {
	char puerto[10];
	int algoritmo;						//Se lee una cadena, pero se guarda con un entero (constante predefinida)
	int quantum;
	int multiprogramacion;
	int retardo_planif;
	//char ip_safa[20];
} ConfiguracionSAFA;
/*
PUERTO=8000
ALGORITMO=RR
QUANTUM=2
MULTIPROGRAMACION=3
RETARDO_PLANIF=600
*/
//Estructura para guardar la configuracion del proceso
ConfiguracionSAFA* configuracion;

#endif /* S_AFA_H_ */
