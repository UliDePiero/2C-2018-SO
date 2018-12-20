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
int socketEscucha;
int	socketActivo;
pthread_t hiloConexionesEntrantes;
pthread_t hiloPlanificacion;
pthread_t hiloPLP;
pthread_t hiloPCP;
pthread_t hiloConsola;
pthread_mutex_t mutexEjecutar;
sem_t semEjecutar;
//Colas de procesos
t_queue *New;
t_queue *Ready;
t_queue *Exec;
t_queue *Block;
t_queue *Exit;
t_list *ListaDTB;
int* primeroNew;
int* primeroReady;
int* primeroExec;
int* primeroBlock;
int* primeroExit;
int* nuevoCliente; //Puntero al nuevo Cliente entrante
int idCLI; //ID del nuevo Cliente entrante
int operacion;
char rutaScript[100];
int nuevoIngresoGDT = 0;
int procesosEnReady = 0;
int ID_DTBs = 0;
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

//MOVER A PROTOCOLO.h
typedef struct {
	int ID;
	FILE* Script;
	char RutaScript[100];
	char PC[20];
	char TablaArchivosAbiertos[10];
	int FlagIncializado;
} EstructuraDTB;
EstructuraDTB* DTB;
EstructuraDTB* DTB_Ready;
/*
El ID de G.DT
El Escriptorio a abrir
El Program Counter (PC)
Flag G.DT inicializado
Tabla de direcciones de archivos abiertos
*/

#endif /* S_AFA_H_ */
