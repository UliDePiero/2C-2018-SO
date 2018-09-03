/*
 * FunesMemory9.h
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */

#ifndef FUNESMEMORY9_H_
#define FUNESMEMORY9_H_
#include <sockets.h>
//Ruta del archivo de configuraciones
#define RUTA_CONFIG "FunesMemory9.config"

///---------------------ESTRUCTURA DE CONFIGURACION DE FM9-------------------------

//Estructura para datos del archivo de configuracion
typedef struct {
	int puerto;
	int modo;						//Se lee una cadena, pero se guarda con un entero (constante predefinida)
	int tamanio;
	int max_linea;
	int tam_pagina;
	char ip_fm9[20];
} ConfiguracionFM9;
/*
PUERTO=8000
MODO="SEG"
TAMANIO=2048
MAX_LINEA=128
TAM_PAGINA=1024
IP_FM9="192.168.1.4"
*/
//Estructura para guardar la configuracion del proceso
ConfiguracionFM9* configuracion;


#endif /* FUNESMEMORY9_H_ */
