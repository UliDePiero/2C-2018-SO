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
					   "TAM_PAGINA"
					 };

	t_config* archivoConfig = archivoConfigCrear(RUTA_CONFIG, campos);

	//Relleno los campos con la info del archivo
	strcpy(configuracion->puerto, archivoConfigSacarStringDe(archivoConfig, "PUERTO"));
	strcpy(configuracion->modo, archivoConfigSacarStringDe(archivoConfig, "MODO"));
	configuracion->tamanio = archivoConfigSacarIntDe(archivoConfig, "TAMANIO");
	configuracion->max_linea = archivoConfigSacarIntDe(archivoConfig, "MAX_LINEA");
	configuracion->tam_pagina = archivoConfigSacarIntDe(archivoConfig, "TAM_PAGINA");

	archivoConfigDestruir(archivoConfig);
}
int main(){
	configuracion = malloc(sizeof(ConfiguracionFM9));
	configurar(configuracion);

	//printf("puerto: %s\n", configuracion->puerto);
	//printf("modo: %s\n", configuracion->modo);

	if (strcmp(configuracion->modo, "SEG")==0) {
		segmentacionPura(configuracion);
	}
	else if (strcmp(configuracion->modo, "TPI")==0) {
		paginasInvertidas(configuracion);
	}
	else if (strcmp(configuracion->modo, "SPA")==0) {
		segmentacionPura(configuracion);
	}
	else {
		segmentacionPaginada(configuracion); //Default para que no de error
	}
	//servidor
	/*
	int socketEscucha= levantarServidorIPautomatica(configuracion->puerto, BACKLOG); //BACKLOG es la cantidad de clientes que pueden conectarse a este servidor
	int	socketActivo = aceptarComunicaciones(socketEscucha);
	//conversacionComoServidor(&socketActivo);
	recibirUnMensaje(socketActivo);
	conversar(&socketActivo);
	cerrarSocket(socketActivo);
	cerrarSocket(socketEscucha);*/

	free(configuracion);
}
//Segmentacion pura
void segmentacionPura(){
	totalLineas = configuracion->tamanio / configuracion->max_linea;
	char storage[totalLineas][configuracion->max_linea]; //Memoria real
	int tablaSegmentos[totalLineas][3];  //0=vacio 1=archivo 2+=proceso
	inicializar(tablaSegmentos, storage);

/*	strcpy(storage[0], "prueba2");
	tablaSegmentos[0][0] = 2;
	tablaSegmentos[0][1] = 0;
	tablaSegmentos[0][2] = 0;

	strcpy(storage[4], "prueba3.1");
	strcpy(storage[5], "prueba3.2");
	tablaSegmentos[4][0] = 3;
	tablaSegmentos[4][1] = 4;
	tablaSegmentos[4][2] = 5;

	strcpy(storage[8], "prueba4.1");
	strcpy(storage[9], "prueba4.2");
	strcpy(storage[10], "prueba4.3");
	tablaSegmentos[9][0] = 4;
	tablaSegmentos[9][1] = 8;
	tablaSegmentos[9][2] = 10;

	strcpy(storage[15], "prueba5");
	tablaSegmentos[15][0] = 5;
	tablaSegmentos[15][1] = 15;
	tablaSegmentos[15][2] = 15;*/

/*	//Prueba carga de archivo
	char nombre[configuracion->max_linea];
	char archivo[3][configuracion->max_linea];
	strcpy(nombre, "nombreArchivo");
	strcpy(archivo[0], "archivo1");
	strcpy(archivo[1], "archivo2");
	strcpy(archivo[2], "archivo3");
	cargarArchivo(tablaSegmentos, storage, archivo, nombre, 3);*/

	//ordenarTabla(tablaSegmentos);
	ordenar(tablaSegmentos, storage);

	for(int i=0; i < totalLineas; i++){
		printf("tabla %d: %d %d %d\n", i, tablaSegmentos[i][0], tablaSegmentos[i][1], tablaSegmentos[i][2]);
	}
	for(int i=0; i < totalLineas; i++){
		printf("storage %d: %s\n", i, storage[i]);
	}


}
void inicializar(int (*tabla)[3], char (*storage)[configuracion->max_linea]){
	for(int i=0; i < totalLineas; i++){
		strcpy(storage[i], "\0");
		tabla[i][0] = tabla[i][1] = tabla[i][2] = 0;
	}
	tabla[totalLineas][0] = tabla[totalLineas][1] = tabla[totalLineas][2] = 0;
}
int cantidadSegmentos(int (*tabla)[3]){
	//Devuelve la cantidad de segmentos en memoria
	int resu = 0;
	for(int i = 0; i < totalLineas; i++){
		if(tabla[i][0] != 0){
			resu++;
		}
	}
	return resu;
}
void ordenarTabla(int (*tabla)[3]){
	//ordena la tabla de semgentos
	int cant = cantidadSegmentos(tabla);
	for(int i = 0; i < totalLineas; i++){
		if(cant == 0){
			return;
		}
		while(tabla[i][0] == 0){
			for(int u = i; u < totalLineas; u++){
				tabla[u][0] = tabla[u+1][0];
				tabla[u][1] = tabla[u+1][1];
				tabla[u][2] = tabla[u+1][2];
			}
			tabla[totalLineas][0] = tabla[totalLineas][1] = tabla[totalLineas][2] = 0;
		}
		cant--;
	}
}
void ordenar(int (*tabla)[3], char (*storage)[configuracion->max_linea]){
	//Ordena los procesos/archivos para evitar fragmentacion
	ordenarTabla(tabla);
	int cant = cantidadSegmentos(tabla);
	int a = 0;
	for(int i = 0; i < totalLineas; i++){
		if(cant == 0){
			return;
		}
		while(tabla[i][1] != a){
			for(int u = a; u <= tabla[i][2]; u++){
				strcpy(storage[u], storage[u+1]);
			}
			strcpy(storage[tabla[i][2]], "\0");
			tabla[i][1]--;
			tabla[i][2]--;
		}
		cant--;
		a+= tabla[i][2] - tabla[i][1] + 1;
	}
}
int espacioLibre(int (*tabla)[3]){
	//Retorna la cantidad de lineas libres
	ordenarTabla(tabla);
	for(int i = 0; i < totalLineas-1; i++){
		if(tabla[i][0] == 0){
			return totalLineas - tabla[i-1][2] -1;
		}
	}
	return totalLineas;
}
int encontrarSegmento(int (*tabla)[3], int linea){
	//Retorna el segmento que contiene la linea
	for(int i = 0; i < totalLineas; i++){
		if(tabla[i][1] <= linea && linea <= tabla[i][2]){
			return i;
		}
	}
	return -1;
}

int cargarProceso(int (*tabla)[3], char (*storage)[configuracion->max_linea], char (*proceso)[configuracion->max_linea], int PId, int cantLineas){
	//Carga un nuevo proceso en memoria
	//Retorna -1 si no hay espacio disponible
	ordenar(tabla, storage);
	int espLibre = espacioLibre(tabla);
	int cantSegmentos = cantidadSegmentos(tabla);
	int a = 0;
	if(cantLineas > espLibre){
		return -1;
	}
	tabla[cantSegmentos][0] = PId;
	tabla[cantSegmentos][1] = tabla[cantSegmentos-1][2] +1;
	tabla[cantSegmentos][2] = tabla[cantSegmentos-1][2] + cantLineas;
	for(int i = tabla[cantSegmentos][1]; i <= tabla[cantSegmentos][2]; i++){
		strcpy(storage[i], proceso[a]);
		a++;
	}

	return 1;
}
int borrarProceso(int (*tabla)[3], char (*storage)[configuracion->max_linea], int PId){
	//Borra el proceso de la tabla de segmentos y memoria
	//Retorna -1 si no existe el proceso
	int segmento = encontrarProceso(tabla, PId);
	if(segmento == -1){
		return -1;
	}
	for(int i = tabla[segmento][1]; i <= tabla[segmento][2]; i++){
		strcpy(storage[i], "\0");
	}
	tabla[segmento][0] = tabla[segmento][1] = tabla[segmento][2] = 0;
	return 1;
}
int encontrarProceso(int (*tabla)[3], int PId){
	//Retorna el lugar del proceso en la tabla de segmentos
	//Retorna -1 si no existe el proceso
	for(int i = 0; i<totalLineas; i++){
		if(tabla[i][0] == PId){
			return i;
		}
	}
	return -1;
}

int encontrarArchivo(int (*tabla)[3], char (*storage)[configuracion->max_linea], char *nombreArchivo){
	//Retorna el segmento del archivo
	ordenar(tabla, storage);
	for(int i = 0; i < totalLineas; i++){
		if(strcmp(storage[i], nombreArchivo)==0){
			return encontrarSegmento(tabla, i);
		}
	}
	return -1;
}
int borrarArchivo(int (*tabla)[3], char (*storage)[configuracion->max_linea], char *nombreArchivo){
	//Borra el archivo de la tabla de segmentos y memoria
	//Retorna -1 si no existe
	int segmento = encontrarArchivo(tabla, storage, nombreArchivo);
	if(segmento == -1){
		return -1;
	}
	for(int i = tabla[segmento][1]; i <= tabla[segmento][2]; i++){
		strcpy(storage[i], "\0");
	}
	tabla[segmento][0] = tabla[segmento][1] = tabla[segmento][2] = 0;
	return 1;
}
int cargarArchivo(int (*tabla)[3], char (*storage)[configuracion->max_linea], char (*archivo)[configuracion->max_linea], char *nombreArchivo, int cantLineas){
	//Carga un nuevo archivo en memoria
	//Retorna -1 si no hay espacio disponible
	ordenar(tabla, storage);
	int espLibre = espacioLibre(tabla);
	int cantSegmentos = cantidadSegmentos(tabla);
	int a = 0;
	if(cantLineas+1 > espLibre){
		printf("cantLineas %d espLibre %d\n", cantLineas+1, espacioLibre(tabla));
		return -1;
	}
	tabla[cantSegmentos][0] = 1; //Significa que el segmento es de un archivo
	tabla[cantSegmentos][1] = tabla[cantSegmentos-1][2] +1;
	tabla[cantSegmentos][2] = tabla[cantSegmentos-1][2] + cantLineas + 1;
	strcpy(storage[tabla[cantSegmentos][1]], nombreArchivo);
	for(int i = tabla[cantSegmentos][1]+1; i <= tabla[cantSegmentos][2]; i++){
		strcpy(storage[i], archivo[a]);
		a++;
	}

	return 1;
}

//Paginas invertidas
void paginasInvertidas(){

}

//Segmentacion paginada
void segmentacionPaginada(){

}
