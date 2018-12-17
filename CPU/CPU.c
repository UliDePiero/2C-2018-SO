/*
 * CPU.c
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */
/*#include "CPU.h"

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
}*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parserFinDeLinea(char * instruccion, int i, char * buffer){
	int j=0;
	while(instruccion[i] != '\0'){
		buffer[j] = instruccion[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
}

int parserEspacio(char * instruccion, int i, char * buffer){
	int j = 0;
	while(instruccion[i] != ' '){
		buffer[j] = instruccion[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	return i;
}

void ejecutarConcentrar(){
	sleep(1);
}

void ejecutarAsignar(char * instruccion){
	//int linea
	int i = 0;
	char path[100], sLinea[10], datos[50];
	bzero((char *)&path, sizeof(path));
	bzero((char *)&sLinea, sizeof(sLinea));
	bzero((char *)&datos, sizeof(datos));
	//path = (char*)malloc(100 * sizeof(char));
	//sLinea = (char*)malloc(10 * sizeof(char));
	//datos = (char*)malloc(50 * sizeof(char));
	i = parserEspacio(instruccion, 8, path);
	i++;
	i = parserEspacio(instruccion, i, sLinea);
	i++;
	parserFinDeLinea(instruccion, i, datos);
	//printf("Path: %s \n", path);
	//printf("Linea: %s \n", sLinea);
	//printf("Datos: %s \n", datos);

	//verificarArchivoAbierto();
	//enviarDatosFM9();
}

void ejecutarAbrir(char * instruccion){
	char path[100];
	bzero((char *)&path, sizeof(path));
	//path = (char*)malloc(100 * sizeof(char));
	parserFinDeLinea(instruccion, 6, path);
	//printf("Path: %s \n", path);

	//verificarArchivoAbierto();
	//if(not open) -----> solicitarArchivoAlDiego();
}

void ejecutarWait(char * instruccion){
	char recurso[50];
	bzero((char *)&recurso, sizeof(recurso));
	//recurso = (char*)malloc(50 * sizeof(char));
	parserFinDeLinea(instruccion, 5, recurso);
	//printf("Recurso: %s \n", recurso);

	//retenerRecurso(recurso);
}

void ejecutarSignal(char * instruccion){
	char recurso[50];
	bzero((char *)&recurso, sizeof(recurso));
	//recurso = (char*)malloc(50 * sizeof(char));
	parserFinDeLinea(instruccion, 7, recurso);
	//printf("Recurso: %s \n", recurso);

	//liberarRecurso(recurso);
}

void ejecutarFlush(char * instruccion){
	char path[100];
	bzero((char *)&path, sizeof(path));
	//path = (char*)malloc(100 * sizeof(char));
	parserFinDeLinea(instruccion, 6, path);

	//verificarArchivoAbierto();
	//solicitarFlushADiego();
}

void ejecutarCrear(char * instruccion){
	int i = 0;
	char path[100], cantLineas[10];
	bzero((char *)&path, sizeof(path));
	bzero((char *)&cantLineas, sizeof(cantLineas));
	//path = (char*)malloc(100 * sizeof(char));
	//cantLineas = (char*)malloc(10 * sizeof(char));
	i = parserEspacio(instruccion, 6, path);
	i++;
	parserFinDeLinea(instruccion, i, cantLineas);
	//printf("Path: %s \n", path);
	//printf("Cantidad de lineas: %s \n", cantLineas);

	//verificarArchivoAbierto();
	//solicitarCreacionDeArchivo();
}

void ejecutarBorrar(char * instruccion){
	char path[100];
	bzero((char *)&path, sizeof(path));
	//path = (char*)malloc(100 * sizeof(char));
	parserFinDeLinea(instruccion, 7, path);
	//printf("Path: %s \n", path);

	//solicitarEliminacionDeArchivo();
}

void ejecutarClose(char * instruccion){
	char path[100];
	bzero((char *)&path, sizeof(path));
	parserFinDeLinea(instruccion, 6, path);
	//printf("Path: %s \n", path);

	//verificarArchivoAbierto();
	//solicitarFM9LiberarMemoria();
}

int parser(char * instruccion){
	//char buffer[50];
	char l1, l2;
	//bzero((char *)&buffer, sizeof(buffer));
	l1 = instruccion[0];
	if (l1 != '#' && l1 != ' '){
		//parserEspacio(instruccion, 0, buffer);
		// printf("Palabra reservada: %s \n", buffer);
		l2 = instruccion[1];
		if(l1 == 'a' && l2 == 'b')
			return 1;
		if(l1 == 'c' && l2 == 'o')
			return 2;
		if(l1 == 'a' && l2 == 's')
			return 3;
		if(l1 == 'w')
			return 4;
		if(l1 == 's')
			return 5;
		if(l1 == 'f')
			return 6;
		if(l1 == 'c' && l2 == 'l')
			return 7;
		if(l1 == 'c' && l2 == 'r')
			return 8;
		if(l1 == 'b')
			return 9;
	}else if (l1 == '#')
		return 10;
	return 11;
}

int ejecutarInstruccion(char * instruccion){
	int opcion = 0;
	opcion = parser (instruccion);
	switch(opcion){
		case 1:
			ejecutarAbrir(instruccion);
			break;
		case 2:
			ejecutarConcentrar();
			break;
		case 3:
			ejecutarAsignar(instruccion);
			break;
		case 4:
			ejecutarWait(instruccion);
			break;
		case 5:
			ejecutarSignal(instruccion);
			break;
		case 6:
			ejecutarFlush(instruccion);
			break;
		case 7:
			ejecutarClose(instruccion);
			break;
		case 8:
			ejecutarCrear(instruccion);
			break;
		case 9:
			ejecutarBorrar(instruccion);
			break;
		default:
			//printf("Es un comentario o fin de linea \n");
			break;
	}
	return opcion;
}

int main()
{
	/*configuracion = malloc(sizeof(ConfiguracionCPU));
	configurar(configuracion);

	// cliente
	int socketSAFA = conectarAUnServidor(configuracion->ip_safa, configuracion->puerto_safa);
	int socketDAM = conectarAUnServidor(configuracion->ip_diego, configuracion->puerto_diego);
	enviarUnMensaje(socketSAFA);
	conversar(&socketSAFA);
	enviarUnMensaje(socketDAM);
	conversar(&socketDAM);*/
	/*
	conversacionComoCliente((void*) socketSAFA);
	conversacionComoCliente((void*) socketDAM);
	*/
	/*cerrarSocket(socketSAFA);
	cerrarSocket(socketDAM);
	free(configuracion);*/

	int opcion;
	char instruccion[200];
	bzero((char *)&instruccion, sizeof(instruccion));
	FILE * archivo;//Linea para probar el parser
	archivo = fopen("prueba.txt", "r");//Linea para probar el parser
	do{
		fgets(instruccion, 200, (FILE*) archivo);//Linea para probar el parser
		opcion = ejecutarInstruccion(instruccion);
	}while(opcion != 11);
	return 0;
}
