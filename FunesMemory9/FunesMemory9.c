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
					   "IP_FM9"
					 };

	t_config* archivoConfig = archivoConfigCrear(RUTA_CONFIG, campos);

	//Relleno los campos con la info del archivo
	configuracion->puerto = archivoConfigSacarIntDe(archivoConfig, "PUERTO");

	configuracion->modo = archivoConfigSacarIntDe(archivoConfig, "MODO"); //OPCION A

	//strcpy(configuracion->modo, archivoConfigSacarStringDe(archivoConfig, "MODO")); //OPCION B

	configuracion->tamanio = archivoConfigSacarIntDe(archivoConfig, "TAMANIO");
	configuracion->max_linea = archivoConfigSacarIntDe(archivoConfig, "MAX_LINEA");
	configuracion->tam_pagina = archivoConfigSacarIntDe(archivoConfig, "TAM_PAGINA");
	strcpy(configuracion->ip_fm9, archivoConfigSacarStringDe(archivoConfig, "IP_FM9"));

	archivoConfigDestruir(archivoConfig);
}
main()
{
	configurar(configuracion);

	//servidor

	int socketEscucha= levantarServidor(configuracion->ip_fm9,configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	int	socketActivo = aceptarComunicaciones(socketEscucha);
	conversacionComoServidor((void*) socketActivo);
	//recibirUnMensaje(socketActivo);
}
