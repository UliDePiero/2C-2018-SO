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
	cantidadSegmentos = configuracion->tamanio / configuracion->max_linea;
	char storage[cantidadSegmentos][configuracion->max_linea]; //Memoria real
	int tablaSegmentos[cantidadSegmentos][3];
	inicializar(tablaSegmentos, storage);

	/*strcpy(storage[0], "prueba1");
	tablaSegmentos[0][0] = 1;
	tablaSegmentos[0][1] = 0;
	tablaSegmentos[0][2] = 0;

	strcpy(storage[4], "prueba2.1");
	strcpy(storage[5], "prueba2.2");
	tablaSegmentos[4][0] = 2;
	tablaSegmentos[4][1] = 4;
	tablaSegmentos[4][2] = 5;

	strcpy(storage[8], "prueba3.1");
	strcpy(storage[9], "prueba3.2");
	strcpy(storage[10], "prueba3.3");
	tablaSegmentos[9][0] = 3;
	tablaSegmentos[9][1] = 8;
	tablaSegmentos[9][2] = 10;

	strcpy(storage[15], "prueba4");
	tablaSegmentos[15][0] = 4;
	tablaSegmentos[15][1] = 15;
	tablaSegmentos[15][2] = 15;

	ordenar(tablaSegmentos, storage);*/

	for(int i=0; i < cantidadSegmentos; i++){
		printf("tabla %d: %d %d %d\n", i, tablaSegmentos[i][0], tablaSegmentos[i][1], tablaSegmentos[i][2]);
	}
	for(int i=0; i < cantidadSegmentos; i++){
		printf("storage %d: %s\n", i, storage[i]);
	}


}
void inicializar(int (*tabla)[3], char (*storage)[configuracion->max_linea]){
	for(int i=0; i < cantidadSegmentos; i++){
		strcpy(storage[i], "\0");
		tabla[i][0] = tabla[i][1] = tabla[i][2] = 0;
	}
	tabla[cantidadSegmentos][0] = tabla[cantidadSegmentos][1] = tabla[cantidadSegmentos][2] = 0;
}
int cantidadProcesos(int (*tabla)[3]){
	//Devuelve la cantidad de procesos en memoria
	int resu = 0;
	for(int i = 0; i<cantidadSegmentos; i++){
		if(tabla[i][0]!=0){
			resu++;
		}
	}
	return resu;
}
int encontrarProceso(int (*tabla)[3], int PId){
	//Retorna el lugar del proceso en la tabla de segmentos o -1
	for(int i = 0; i<cantidadSegmentos; i++){
		if(tabla[i][0] == PId){
			return i;
		}
	}
	return -1;
}
int borrarProceso(int (*tabla)[3], char (*storage)[configuracion->max_linea], int PId){
	//Borra el proceso de la tabla de segmentos y memoria
	int lugar = encontrarProceso(tabla, PId);
	if(lugar == -1){
		return -1;
	}
	for(int i = tabla[lugar][1]; i <= tabla[lugar][2]; i++){
		strcpy(storage[i], "\0");
	}
	tabla[lugar][0] = tabla[lugar][1] = tabla[lugar][2] = 0;
	return 1;
}
void ordenarTabla(int (*tabla)[3]){
	//ordena la tabla de semgentos
	int cant = cantidadProcesos(tabla);
	for(int i = 0; i < cantidadSegmentos; i++){
		if(cant == 0){
			return;
		}
		while(tabla[i][0] == 0){
			for(int u = i; u < cantidadSegmentos; u++){
				tabla[u][0] = tabla[u+1][0];
				tabla[u][1] = tabla[u+1][1];
				tabla[u][2] = tabla[u+1][2];
			}
			tabla[cantidadSegmentos][0] = tabla[cantidadSegmentos][1] = tabla[cantidadSegmentos][2] = 0;
		}
		cant--;
	}
}
void ordenar(int (*tabla)[3], char (*storage)[configuracion->max_linea]){
	//Ordena los procesos/archivos para evitar fragmentacion
	ordenarTabla(tabla);
	int cant = cantidadProcesos(tabla);
	int a = 0;
	for(int i = 0; i < cantidadSegmentos; i++){
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

//Paginas invertidas
void paginasInvertidas(){

}

//Segmentacion paginada
void segmentacionPaginada(){

}
