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

typedef struct{
	int ID;
	FILE* Script;
	char RutaScript[100];
	char PC[20];
	char TablaArchivosAbiertos[10];
	int FlagInicializado;
}EstructuraDTB;


main()
{
	configuracion = malloc(sizeof(ConfiguracionDAM));
	configurar(configuracion);

	// cliente
	int socketSAFA = conectarAUnServidor(configuracion->ip_safa, configuracion->puerto_safa);
	int socketMDJ = conectarAUnServidor(configuracion->ip_mdj, configuracion->puerto_mdj);
	int socketFM9 = conectarAUnServidor(configuracion->ip_fm9, configuracion->puerto_fm9);

	/*enviarUnMensaje(socketSAFA);
	conversar(&socketSAFA);
	enviarUnMensaje(socketMDJ);
	conversar(&socketMDJ);
	enviarUnMensaje(socketFM9);
	conversar(&socketFM9);*/
	/*
	conversacionComoCliente((void*) socketSAFA);
	conversacionComoCliente((void*) socketMDJ);
	conversacionComoCliente((void*) socketFM9);
	*/

	//servidor

	int socketEscucha= levantarServidorIPautomatica(configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	int	socketActivo = aceptarComunicaciones(socketEscucha);

	pthread_t hiloConexionesEntrantesDiego;
	crearHilo(&hiloConexionesEntrantesDiego, (void*) aceptarComunicacionesParaHilo, (void*) socketEscucha, "elDiego");
	pthread_join(hiloConexionesEntrantesDiego, NULL);
	MatrizDeConexiones[3][0] = socketEscucha;

	//conversacionComoServidor((void*) socketActivo);
	/*recibirUnMensaje(socketActivo);
	conversar(&socketActivo);*/

	t_prot_mensaje mensaje;
	EstructuraDTB * DTB;


    int maxfd, j, result;
    fd_set readset;

    // Initialize the set
    FD_ZERO(&readset);
    maxfd = 0;
    for (j=0; j<19; j++) {
       FD_SET(socketCPUDIEGO[j], &readset);
       maxfd = (maxfd>socketCPUDIEGO[j])?maxfd:socketCPUDIEGO[j];
    }

    // Now, check for readability
    result = select(maxfd+1, &readset, NULL, NULL, NULL);
    if (result == -1) {
       // Some error...
    }
    else {
       for (j=0; j<19; j++) {
          if (FD_ISSET(socketCPUDIEGO[j], &readset)) {
            mensaje = RecibirMensaje(socketCPUDIEGO[j]);
         	DTB->ID = mensaje->payload;

         	mensaje = RecibirMensaje(socketCPUDIEGO[j]);
         	DTB->RutaScript = mensaje->payload;

         	switch(mensaje->head)
         	case ABRIR_PATH:
         		enviarMensaje(socketMDJ, SCRIPT, sizeof(char) * strlen(DTB->RutaScript), DTB->RutaScript);
         		enviarMensaje(socketMDJ, DTBID, sizeof(int), DTB->ID);
          }
       }
    }









	cerrarSocket(socketSAFA);
	cerrarSocket(socketMDJ);
	cerrarSocket(socketFM9);
	cerrarSocket(socketActivo);
	cerrarSocket(socketEscucha);
	free(configuracion);
}
