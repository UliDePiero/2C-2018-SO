/*
 * FunesMemory9.h
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */

#ifndef FUNESMEMORY9_H_
#define FUNESMEMORY9_H_
//#include <sockets.h>
#include <conexionSockets.h>
//Ruta del archivo de configuraciones
#define RUTA_CONFIG "FM9Configuracion.txt"

///---------------------ESTRUCTURA DE CONFIGURACION DE FM9-------------------------

//Estructura para datos del archivo de configuracion
typedef struct {
	char puerto[10];
	char modo[3];
	int tamanio;
	int max_linea;
	int tam_pagina;
} ConfiguracionFM9;
/*
PUERTO=8000
MODO=SEG
TAMANIO=2048
MAX_LINEA=128
TAM_PAGINA=1024
*/
//Estructura para guardar la configuracion del proceso
ConfiguracionFM9* configuracion;


#endif /* FUNESMEMORY9_H_ */
