/*
 * FunesMemory9.c
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */
#include "FunesMemory9.h"

void configurar(ConfiguracionFM9* configuracion) {

	char* campos[] = {
					   "PUERTO",
					   "MODO",
					   "TAMANIO",
					   "MAX_LINEA",
					   "TAM_PAGINA"
					 };

	t_config* archivoConfig = archivoConfigCrear(RUTA_CONFIG, campos);

	//Relleno los campos con la info del archivo
	strcpy(configuracion->puerto, archivoConfigSacarStringDe(archivoConfig, "PUERTO"));
	strcpy(configuracion->modo, archivoConfigSacarStringDe(archivoConfig, "MODO"));
	configuracion->tamanio = archivoConfigSacarIntDe(archivoConfig, "TAMANIO");
	configuracion->max_linea = archivoConfigSacarIntDe(archivoConfig, "MAX_LINEA");
	configuracion->tam_pagina = archivoConfigSacarIntDe(archivoConfig, "TAM_PAGINA");

	archivoConfigDestruir(archivoConfig);
}
main()
{
	configuracion = malloc(sizeof(ConfiguracionFM9));
	configurar(configuracion);
	printf("puerto: %s\n", configuracion->puerto);
	printf("modo: %s\n", configuracion->modo);
	if (strcmp(configuracion->modo, "SEG")==0) {
		segmentacionPura(configuracion);
	}
	else if (strcmp(configuracion->modo, "TPI")==0) {
		paginasInvertidas(configuracion);
	}
	else if (strcmp(configuracion->modo, "SPA")==0) {
		segmentacionPura(configuracion);
	}
	else {
		segmentacionPaginada(configuracion); //Default para que no de error
	}
	//servidor
	/*
	int socketEscucha= levantarServidorIPautomatica(configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	int	socketActivo = aceptarComunicaciones(socketEscucha);
	//conversacionComoServidor(&socketActivo);
	recibirUnMensaje(socketActivo);
	conversar(&socketActivo);
	cerrarSocket(socketActivo);
	cerrarSocket(socketEscucha);*/

	free(configuracion);
}
void segmentacionPura(ConfiguracionFM9* configuracion)
{
	int cantidadSegmentos = configuracion->max_linea / configuracion->tamanio;
	char storage[cantidadSegmentos][configuracion->max_linea]; //Memoria real
	int tablaSegmentos[cantidadSegmentos][3];

	for(int i=0; i < cantidadSegmentos; i++)
	{
		strcpy(storage[0], "\0");
		tablaSegmentos[i][0] = tablaSegmentos[i][1] = tablaSegmentos[i][2] = 0;
	}


}
void paginasInvertidas(ConfiguracionFM9* configuracion)
{

}
void segmentacionPaginada(ConfiguracionFM9* configuracion)
{

}
