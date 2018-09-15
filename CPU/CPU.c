/*
 * CPU.c
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */
#include "CPU.h"

void configurar(ConfiguracionCPU* configuracion) {

	char* campos[] = {
					   "PUERTO_SAFA",
					   "PUERTO_DIEGO",
					   "RETARDO",
					   "IP_SAFA",
					   "IP_DAM"
					 };

	t_config* archivoConfig = archivoConfigCrear(RUTA_CONFIG, campos);

	//Relleno los campos con la info del archivo
	strcpy(configuracion->puerto_safa, archivoConfigSacarStringDe(archivoConfig, "PUERTO_SAFA"));
	strcpy(configuracion->puerto_diego, archivoConfigSacarStringDe(archivoConfig, "PUERTO_DIEGO"));
	configuracion->retardo = archivoConfigSacarIntDe(archivoConfig, "RETARDO");
	strcpy(configuracion->ip_safa, archivoConfigSacarStringDe(archivoConfig, "IP_SAFA"));
	strcpy(configuracion->ip_diego, archivoConfigSacarStringDe(archivoConfig, "IP_DAM"));

	archivoConfigDestruir(archivoConfig);
}
main()
{
	configurar(configuracion);

	// cliente
	int socketSAFA = conectarAUnServidor(configuracion->ip_safa, configuracion->puerto_safa);
	int socketDAM = conectarAUnServidor(configuracion->ip_diego, configuracion->puerto_diego);
	enviarUnMensaje(socketSAFA);
	conversar(&socketSAFA);
	enviarUnMensaje(socketDAM);
	conversar(&socketDAM);
	/*
	conversacionComoCliente((void*) socketSAFA);
	conversacionComoCliente((void*) socketDAM);
	*/
}
