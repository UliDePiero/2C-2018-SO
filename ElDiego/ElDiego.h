/*
 * ElDiego.h
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */

#ifndef ELDIEGO_H_
#define ELDIEGO_H_

//Ruta del archivo de configuraciones
#define RUTA_CONFIG "ElDiego.config"
//#include <sockets.h>
#include <conexionSockets.h>

///---------------------ESTRUCTURA DE CONFIGURACION DE DAM-------------------------

//Estructura para datos del archivo de configuracion
typedef struct {
	char puerto[10];
	char puerto_safa[10];
	char puerto_mdj[10];
	char puerto_fm9[10];
	char ip_safa[20];
	char ip_mdj[20];
	char ip_fm9[20];
	int transfer_size;
	//char ip_dam[20];
} ConfiguracionDAM;
/*
PUERTO=8001
IP_SAFA=192.168.1.1
PUERTO_SAFA=8000
IP_MDJ=192.168.1.3
PUERTO_MDJ=8002
IP_FM9=192.168.1.4
PUERTO_FM9=8003
TRANSFER_SIZE=16
*/
//Estructura para guardar la configuracion del proceso
ConfiguracionDAM* configuracion;

//Desde aca Prueba
//Prototipo Intermediario CPU S-AFA. CPU quiere cargar archivo en memoria(FM9)
//breve diagrama: CPU(pide cargar archivo) -> Diego(le dice a FM9) -> FM9 -> MDJ -> S-AFA(se notifica lo ocurrido)
void cargarArchivo(char * path, int PID)
{
	//Cuando se pide cargar un archivo
	printf("Ehhh, voy a buscar %s para %i \n",path,PID);

//Comunicar implica enviar o recibir mediante sockets

	/* Comunicarse con FM9 y cargar archivos en MDJ
	magia();
	*/

	/*Comunicar a S-AFA
	if(se cargo el archivo)
	{
	comunicarSafa(OK) // Ya S-AFA puede desbloquear el archivo
	comunicarSafa(): Se abrio tal archivo con tal dato de mem virtual 
	}
	else
	{
	comunicarSafa(MAL); // S-AFA debe mandar al proceso a la cola de exit
	}
	*/
}
/*
Cada vez que el El Diego reciba una solicitud de “Abrir” (ver Anexo 1) se deberá ejecutar una
operación de escritura a FM9 que constará de ir a buscar el contenido del path recibido a MDJ y
luego enviarlo a FM9.


/* Problema mayor:  Si el archivo a obtener/escribir es mayor que este transfer size se deberán
obtener/escribir mediante múltiples solicitudes. Como dividir la obtencion/Escritura.*/
//Ej: abrir /equipos/Racing.txt
void abrirArchivo(char *path)
{
		//contenidoAEscribir = Buscar(MDJ,path)
		//Escribir(FM9,contenidoAEscribir)
}

void flush(char *pathDestino, char* pathOrigen)
{
	//datosAEscribir = Escuchar(FM9,pathOrigen)
	//Escribir(MDJ,datosAEscribir,pathDestino)
}

#endif /* ELDIEGO_H_ */
