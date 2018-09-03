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
	configuracion->puerto = archivoConfigSacarIntDe(archivoConfig, "PUERTO");
	configuracion->puerto_safa = archivoConfigSacarIntDe(archivoConfig, "PUERTO_SAFA");
	configuracion->puerto_mdj = archivoConfigSacarIntDe(archivoConfig, "PUERTO_MDJ");
	configuracion->puerto_fm9 = archivoConfigSacarIntDe(archivoConfig, "PUERTO_FM9");
	strcpy(configuracion->ip_safa, archivoConfigSacarStringDe(archivoConfig, "IP_SAFA"));
	strcpy(configuracion->ip_mdj, archivoConfigSacarStringDe(archivoConfig, "IP_MDJ"));
	strcpy(configuracion->ip_fm9, archivoConfigSacarStringDe(archivoConfig, "IP_FM9"));
	configuracion->transfer_size = archivoConfigSacarIntDe(archivoConfig, "TRANSFER_SIZE");

	archivoConfigDestruir(archivoConfig);
}
main()
{
	configurar(configuracion);

	// cliente
	int socketSAFA = conectarAUnServidor(configuracion->ip_safa, configuracion->puerto_safa);
	int socketMDJ = conectarAUnServidor(configuracion->ip_mdj, configuracion->puerto_mdj);
	int socketFM9 = conectarAUnServidor(configuracion->ip_fm9, configuracion->puerto_fm9);
	conversacionComoCliente((void*) socketSAFA);
	conversacionComoCliente((void*) socketMDJ);
	conversacionComoCliente((void*) socketFM9);

}
