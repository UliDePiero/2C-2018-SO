/*
 * MDJ.c
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */
#include "MDJ.h"
void configurar(ConfiguracionMDJ* configuracion) {

	char* campos[] = {
					   "PUERTO",
					   "PUNTO_MONTAJE",
					   "RETARDO",
					   "IP_MDJ"
					 };

	t_config* archivoConfig = archivoConfigCrear(RUTA_CONFIG, campos);

	//Relleno los campos con la info del archivo
	configuracion->puerto = archivoConfigSacarIntDe(archivoConfig, "PUERTO");
	strcpy(configuracion->punto_montaje, archivoConfigSacarStringDe(archivoConfig, "PUNTO_MONTAJE"));
	configuracion->retardo = archivoConfigSacarIntDe(archivoConfig, "RETARDO");
	strcpy(configuracion->ip_mdj, archivoConfigSacarStringDe(archivoConfig, "IP_MDJ"));

	archivoConfigDestruir(archivoConfig);
}
main()
{
	configurar(configuracion);

	//servidor

	int socketEscucha= levantarServidor(configuracion->ip_mdj,configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	int	socketActivo = aceptarPlanificador(socketEscucha);
	conversacionComoServidor((void*) socketActivo);
	//recibirUnMensaje(socketActivo);
}

