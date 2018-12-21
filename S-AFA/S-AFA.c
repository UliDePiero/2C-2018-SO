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
					   //"IP_SAFA"
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
	//strcpy(configuracion->ip_safa, archivoConfigSacarStringDe(archivoConfig, "IP_SAFA"));

	archivoConfigDestruir(archivoConfig);
}
int main()
{
	configuracion = malloc(sizeof(ConfiguracionSAFA));
	configurar(configuracion);

	New = queue_create(); //queue_push(New, nuevoCliente);
	Ready = queue_create();
	Exec = queue_create();
	Block = queue_create();
	Exit = queue_create();
	ListaDTB = list_create();
	//servidor
	socketEscucha= levantarServidorIPautomatica(configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	MatrizDeConexiones[0][0] = socketEscucha;
	//socketActivo = aceptarComunicaciones(socketEscucha);
	free(configuracion);

	crearHilo(&hiloConexionesEntrantes,(void*) aceptarComunicacionesParaHilo, (void*)socketEscucha, "Planificador");

	printf("Estado: Corrupto");
		/*
		 En dicho estado no podrá aceptar el ingreso de ningún run para un programa G.DT. Para que salga de dicho estado deberán pasar dos cosas:
		 *La conexión del proceso “El Diego”.
		 *La conexión de por lo menos un Proceso CPU.
		 */
	while((MatrizDeConexiones[0][1] * MatrizDeConexiones[0][2]) == 0);

	printf("Estado: Operativo");

	crearHilo(&hiloPLP,(void*)planificacionLP, NULL, "Planificador");
	//pthread_create(&hiloPLP, NULL, (void*)planificacionLP, NULL);
	crearHilo(&hiloPCP,(void*)planificacionCP, NULL, "Planificador");
	//pthread_create(&hiloPCP, NULL, (void*)planificacionCP, NULL);

	pthread_join(hiloConexionesEntrantes, NULL);
	pthread_join(hiloPLP, NULL);
	pthread_join(hiloPCP, NULL);

	/*
	pthread_create(&hiloPlanificacion, NULL, (void*)planificar, NULL);
	pthread_create(&hiloConsola, NULL, (void*)iniciar_consola, NULL);

	pthread_join(hiloConexionesEntrantes, NULL);
	pthread_join(hiloPlanificacion, NULL);
	pthread_join(hiloConsola, NULL);
	*/

	cerrarSocket(socketActivo);
	cerrarSocket(socketEscucha);
}
