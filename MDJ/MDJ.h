/*
 * MDJ.h
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */

#ifndef MDJ_H_
#define MDJ_H_

//#include <sockets.h>
#include <conexionSockets.h>
//Ruta del archivo de configuraciones
#define RUTA_CONFIG "MDJ.config"

///---------------------ESTRUCTURA DE CONFIGURACION DE MDJ-------------------------

//Estructura para datos del archivo de configuracion
typedef struct {
	char puerto[10];
	char punto_montaje[20];
	int retardo;
	char ip_mdj[20];
} ConfiguracionMDJ;
/*
PUERTO=5003
PUNTO_MONTAJE=/mnt/FIFA_FS/
RETARDO=500
IP_MDJ=192.168.1.3
*/
//Estructura para guardar la configuracion del proceso
ConfiguracionMDJ* configuracion;

#endif /* MDJ_H_ */
