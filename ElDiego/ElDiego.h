/*
 * ElDiego.h
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */

#ifndef ELDIEGO_H_
#define ELDIEGO_H_

//Ruta del archivo de configuraciones
#define RUTA_CONFIG "ElDiego.config"
#include <sockets.h>

///---------------------ESTRUCTURA DE CONFIGURACION DE DAM-------------------------

//Estructura para datos del archivo de configuracion
typedef struct {
	int puerto;
	int puerto_safa;
	int puerto_mdj;
	int puerto_fm9;
	char ip_safa[20];
	char ip_mdj[20];
	char ip_fm9[20];
	int transfer_size;
	char ip_dam[20];
} ConfiguracionDAM;
/*
PUERTO=8001
IP_DIEGO="192.168.1.2"
IP_SAFA="192.168.1.1"
PUERTO_SAFA=8000
IP_MDJ="192.168.1.3"
PUERTO_MDJ=8002
IP_FM9="192.168.1.4"
PUERTO_FM9=8003
TRANSFER_SIZE=16
*/
//Estructura para guardar la configuracion del proceso
ConfiguracionDAM* configuracion;

#endif /* ELDIEGO_H_ */
