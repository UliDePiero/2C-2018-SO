/*
 * CPU.h
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */


//Actualizar ENUM con SCRIPT, QUANTUM, FLAG, DTBID, DUMMY_DTBID, DUMMY_FLAG




#ifndef CPU_H_
#define CPU_H_
//Ruta del archivo de configuraciones
#define RUTA_CONFIG "CPU.config"
//#include <sockets.h>
#include <conexionSockets.h>

///---------------------ESTRUCTURA DE CONFIGURACION DE CPU-------------------------

//Estructura para datos del archivo de configuracion
typedef struct {
	char puerto_safa[10];
	char puerto_diego[10];
	int retardo;
	char ip_safa[20];
	char ip_diego[20];
} ConfiguracionCPU;
/*
IP_SAFA=192.168.1.1
PUERTO_SAFA=8000
IP_DIEGO=192.168.1.2
PUERTO_DIEGO=8001
RETARDO=1000
*/
//Estructura para guardar la configuracion del proceso
ConfiguracionCPU* configuracion;



#endif /* CPU_H_ */
