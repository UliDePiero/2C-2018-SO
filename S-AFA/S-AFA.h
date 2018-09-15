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
#include <sockets.h>

int operacion;
///---------------------ESTRUCTURA DE CONFIGURACION DE S-AFA-------------------------

//Estructura para datos del archivo de configuracion
typedef struct {
	char puerto[10];
	int algoritmo;						//Se lee una cadena, pero se guarda con un entero (constante predefinida)
	int quantum;
	int multiprogramacion;
	int retardo_planif;
	char ip_safa[20];
} ConfiguracionSAFA;
/*
PUERTO=8000
ALGORITMO=RR
QUANTUM=2
MULTIPROGRAMACION=3
RETARDO_PLANIF=600
IP_SAFA=192.168.1.2
*/
//Estructura para guardar la configuracion del proceso
ConfiguracionSAFA* configuracion;

#endif /* S_AFA_H_ */
