/*
 * ElDiego.c
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */
#include "ElDiego.h"

void configurar(ConfiguracionDAM* configuracion) {

	char* campos[] = {
					   "PUERTO",
					  // "IP_DIEGO",
					   "PUERTO_SAFA",
					   "PUERTO_MDJ",
					   "PUERTO_FM9",
					   "IP_SAFA",
					   "IP_MDJ",
					   "IP_FM9",
					   "TRANSFER_SIZE"
					 };

	t_config* archivoConfig = archivoConfigCrear(RUTA_CONFIG, campos);

	//Relleno los campos con la info del archivo
	strcpy(configuracion->puerto, archivoConfigSacarStringDe(archivoConfig, "PUERTO"));
	//strcpy(configuracion->ip_dam, archivoConfigSacarStringDe(archivoConfig, "IP_DIEGO"));
	strcpy(configuracion->ip_safa, archivoConfigSacarStringDe(archivoConfig, "PUERTO_SAFA"));
	strcpy(configuracion->ip_mdj, archivoConfigSacarStringDe(archivoConfig, "PUERTO_MDJ"));
	strcpy(configuracion->ip_fm9, archivoConfigSacarStringDe(archivoConfig, "PUERTO_FM9"));
	strcpy(configuracion->ip_safa, archivoConfigSacarStringDe(archivoConfig, "IP_SAFA"));
	strcpy(configuracion->ip_mdj, archivoConfigSacarStringDe(archivoConfig, "IP_MDJ"));
	strcpy(configuracion->ip_fm9, archivoConfigSacarStringDe(archivoConfig, "IP_FM9"));
	configuracion->transfer_size = archivoConfigSacarIntDe(archivoConfig, "TRANSFER_SIZE");

	archivoConfigDestruir(archivoConfig);
}
main()
{
	configuracion = malloc(sizeof(ConfiguracionDAM));
	configurar(configuracion);

	// cliente
	int socketSAFA = conectarAUnServidor(configuracion->ip_safa, configuracion->puerto_safa);
	int socketMDJ = conectarAUnServidor(configuracion->ip_mdj, configuracion->puerto_mdj);
	int socketFM9 = conectarAUnServidor(configuracion->ip_fm9, configuracion->puerto_fm9);
	enviarUnMensaje(socketSAFA);
	conversar(&socketSAFA);
	enviarUnMensaje(socketMDJ);
	conversar(&socketMDJ);
	enviarUnMensaje(socketFM9);
	conversar(&socketFM9);
	/*
	conversacionComoCliente((void*) socketSAFA);
	conversacionComoCliente((void*) socketMDJ);
	conversacionComoCliente((void*) socketFM9);
	*/
	cerrarSocket(socketSAFA);
	cerrarSocket(socketMDJ);
	cerrarSocket(socketFM9);
	//servidor

	int socketEscucha= levantarServidorIPautomatica(configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	int	socketActivo = aceptarComunicaciones(socketEscucha);
	//conversacionComoServidor((void*) socketActivo);
	recibirUnMensaje(socketActivo);
	conversar(&socketActivo);
	cerrarSocket(socketActivo);
	cerrarSocket(socketEscucha);
	free(configuracion);
}
