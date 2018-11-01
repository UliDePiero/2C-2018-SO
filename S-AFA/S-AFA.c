/*
 * S-AFA.c
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */
#include "S-AFA.h"
void configurar(ConfiguracionSAFA* configuracion) {

	//char* cadenaAlgoritmo = malloc(TAMMAXNOMBREALGORITMO*sizeof(char)); //Necesario para OPCION C
	char* campos[] = {
					   "PUERTO",
					   "ALGORITMO",
					   "QUANTUM",
					   "MULTIPROGRAMACION",
					   "RETARDO_PLANIF",
					   "IP_SAFA"
					 };

	t_config* archivoConfig = archivoConfigCrear(RUTA_CONFIG, campos);

	//Relleno los campos con la info del archivo
	strcpy(configuracion->puerto, archivoConfigSacarStringDe(archivoConfig, "PUERTO"));

	configuracion->algoritmo = archivoConfigSacarIntDe(archivoConfig, "ALGORITMO"); //OPCION A

	//strcpy(configuracion->algoritmo, archivoConfigSacarStringDe(archivoConfig, "ALGORITMO")); //OPCION B
	/*
	strcpy(cadenaAlgoritmo, archivoConfigSacarStringDe(archivoConfig, "ALGORITMO")); //OPCION C
	setearAlgoritmoDistribucion(configuracion, cadenaAlgoritmo);
	*/
	configuracion->quantum = archivoConfigSacarIntDe(archivoConfig, "QUANTUM");
	configuracion->multiprogramacion = archivoConfigSacarIntDe(archivoConfig, "MULTIPROGRAMACION");
	configuracion->retardo_planif = archivoConfigSacarIntDe(archivoConfig, "RETARDO_PLANIF");
	strcpy(configuracion->ip_safa, archivoConfigSacarStringDe(archivoConfig, "IP_SAFA"));

	archivoConfigDestruir(archivoConfig);
}
main()
{
	configuracion = malloc(sizeof(ConfiguracionSAFA));
	configurar(configuracion);

	//servidor
	printf("mostrar: %c, %c",configuracion->ip_safa,configuracion->puerto);
	int socketEscucha= levantarServidor(configuracion->ip_safa,configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	int	socketActivo = aceptarComunicaciones(socketEscucha);
	//conversacionComoServidor(&socketActivo);
	recibirUnMensaje(socketActivo);
	conversar(&socketActivo);

	cerrarSocket(socketActivo);
	cerrarSocket(socketEscucha);
	free(configuracion);
}
