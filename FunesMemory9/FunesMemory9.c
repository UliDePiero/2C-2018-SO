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
					   "TAM_PAGINA",
					//   "IP_FM9"
					 };

	t_config* archivoConfig = archivoConfigCrear(RUTA_CONFIG, campos);

	//Relleno los campos con la info del archivo
	strcpy(configuracion->puerto, archivoConfigSacarStringDe(archivoConfig, "PUERTO"));

	configuracion->modo = archivoConfigSacarIntDe(archivoConfig, "MODO"); //OPCION A

	//strcpy(configuracion->modo, archivoConfigSacarStringDe(archivoConfig, "MODO")); //OPCION B

	configuracion->tamanio = archivoConfigSacarIntDe(archivoConfig, "TAMANIO");
	configuracion->max_linea = archivoConfigSacarIntDe(archivoConfig, "MAX_LINEA");
	configuracion->tam_pagina = archivoConfigSacarIntDe(archivoConfig, "TAM_PAGINA");
  //strcpy(configuracion->ip_fm9, archivoConfigSacarStringDe(archivoConfig, "IP_FM9"));

	archivoConfigDestruir(archivoConfig);
}
main()
{
	configuracion = malloc(sizeof(ConfiguracionFM9));
	configurar(configuracion);
	switch(configuracion->modo)
	{
		case 1:
			paginasInvertidas(configuracion);
			break;
		case 2:
			segmentacionPaginada(configuracion);
			break;
		default: //Default para que no de error
			segmentacionPura(configuracion);
			break;
	}
	//servidor

	int socketEscucha= levantarServidorIPautomatica(configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	int	socketActivo = aceptarComunicaciones(socketEscucha);
	//conversacionComoServidor(&socketActivo);
	recibirUnMensaje(socketActivo);
	conversar(&socketActivo);
	cerrarSocket(socketActivo);
	cerrarSocket(socketEscucha);
	free(configuracion);
}
segmentacionPura(ConfiguracionFM9* configuracion)
{
	int cantidadSegmentos = configuracion->max_linea / configuracion->tamanio;
	char storage[cantidadSegmentos][configuracion->max_linea]; //Memoria real
	int tablaSegmentos[cantidadSegmentos][3];
	char tablaPaths[cantidadSegmentos][configuracion->max_linea]; //Tabla para saber la localizacion de los archivos

	for(int i=0; i < cantidadSegmentos; i++)
	{
		strcpy(storage[0], "\0");
		tablaSegmentos[i][0] = tablaSegmentos[i][1] = tablaSegmentos[i][2] = 0;
		strcpy(tablaPaths[0], "\0");
	}


}
paginasInvertidas(ConfiguracionFM9* configuracion)
{

}
segmentacionPaginada(ConfiguracionFM9* configuracion)
{

}
