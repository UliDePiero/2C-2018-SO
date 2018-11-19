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
int totalLineas;
void configurar(ConfiguracionFM9* configuracion);

//Segmentacion pura
void segmentacionPura();
void inicializar(int (*tabla)[3], char (*storage)[configuracion->max_linea]);
int cantidadSegmentos(int (*tabla)[3]);
int encontrarProceso(int (*tabla)[3], int PId);
int borrarProceso(int (*tabla)[3], char (*storage)[configuracion->max_linea], int PId);
void ordenarTabla(int (*tabla)[3]);
void ordenar(int (*tabla)[3], char (*storage)[configuracion->max_linea]);
int cargarProceso(int (*tabla)[3], char (*storage)[configuracion->max_linea], char (*proceso)[configuracion->max_linea], int PId, int cantLineas);
int espacioLibre(int (*tabla)[3]);
int encontrarArchivo(int (*tabla)[3], char (*storage)[configuracion->max_linea], char *nombreArchivo);
int encontrarSegmento(int (*tabla)[3], int linea);
int cargarArchivo(int (*tabla)[3], char (*storage)[configuracion->max_linea], char (*archivo)[configuracion->max_linea], char *nombreArchivo, int cantLineas);


//Paginacion inversa
void paginasInvertidas();

//Segmentacion paginada
void segmentacionPaginada();


#endif /* FUNESMEMORY9_H_ */
