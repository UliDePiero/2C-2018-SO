/*
 * Protocolo.h
 *
 *  Created on: 1 dic. 2018
 *      Author: utnso
 */

#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define VALOR_EXIT 1
#define FALLO_ENVIO_DE_MENSAJE "No se pudo enviar mensaje a traves del socket"
#define LARGO_MAXIMO_CLAVE 40

//HEADER (IMPORTANTE: IR CAMBIANDO)
typedef enum{
	CONEXION, //Un cliente informa a un servidor que se ha conectado. Payload: Algun t_cliente
	FALLO_AL_RECIBIR,//Indica que un mensaje no se recibio correctamente en prot_recibir_mensaje
	DESCONEXION, //Indica que un cliente se ha desconectado (usado para instancias)
	FALLO_AL_ENVIAR,//Todavia no aplicado. Analogo al de arriba

	EJECUTAR_SCRIPTS, //Orden del planificador al ESI para que parsee y ejecute script
	EJECUCION_CORRECTA, //Respuesta del ESI al Planificador que la operacion se ejecuto bien
	EJECUCION_FALLO, //Respuesta del ESI al Planificador que la operacion se ejecuto bien
	RESULTADO_OPERACION_CORRECTA, //Respuesta del coordinador al ESI
	RESULTADO_OPERACION_FALLO, //Respuesta del coordinador al ESI
	SCRITP_FINALIZADO, //Mensaje del ESI al planificador luego de haber leido y parseado el script.

	/*Solicitudes del Coordinador al soporte del Planificador*/
	SOLICITUD_CLAVE_LIBRE, //Payload string de la clave
	SOLICITUD_CLAVE_BLOQUEADA_POR_ESI, //Payload string de la clave
	BLOQUEAR_ESI,//Orden del Coordinador para que bloquee el esi ejecutando. Payload: clave bloqueante

	/*Respuestas del Coordinador al soporte del Planificador*/
	RESPUESTA_CLAVE_LIBRE, //Planificador responde al coordinador que la clave esta libre.
	RESPUESTA_CLAVE_BLOQUEADA, ////Planificador responde al coordinador que la clave ya esta bloqueada.
	RESPUESTA_CLAVE_BLOQUEADA_POR_ESI_OK, //Respuesta del Planificador al Coordinador que indica que la clave se encuentra bloqueada por el ESI que la quiere persistir
	RESPUESTA_CLAVE_BLOQUEADA_POR_ESI_FALLO, //Respuesta del Planificador al Coordinador que indica que la clave NO se encuentra bloqueada por el ESI que la quiere persistir

	/*Para el GET*/
	SOLICITAR_CLAVE, //Payload: string de la clave
	CLAVE_LIBRE, //Respuesta del coordinador al esi
	CLAVE_YA_BLOQUEADA, //Respuesta del coordinador al esi

	/*Para el SET*/
	ASIGNAR_VALOR, //Mensaje del ESI al Coordinador. Payload: clave + valor

	/*Para es STORE*/
	PERSISTIR_CLAVE, //Payload: string de la clave

	/*Ordenes Coordinador - Planificador*/
	ABORTAR_ESI, //Sin payload. Bloquea ESI en ejecucion
	DESBLOQUEAR_CLAVE_DEL_ESI_EJECUTANDO, //Payload: string de la clave
	BLOQUEAR_CLAVE_PARA_ESI_EJECUTANDO, //Payload: string de la clave
	ORDEN_EJECUTADA, //Respuesta para que el coordinador sepa que ya hizo lo que se pidio

	/*Para Coordinador*/
	ENVIA_CONFIGURACIONES,

	/*Para Instancia*/
	GUARDAR_CLAVE,
	CLAVE_GUARDADA,
	CLAVE_NO_GUARDADA,
	SETEAR_VALOR,
	VALOR_SETEADO,
	VALOR_NO_SETEADO,
	STOREAR_CLAVE,
	CLAVE_STOREADA,
	CLAVE_NO_STOREADA,

	/*Para ESI*/
	NOMBRE,

	/*Planificador*/
	PIDE_STATUS,
	ENVIA_STATUS,

	/*Para dump*/
	DUMP_INICIADO,
	DUMP_TERMINADO,
	DTBID,
	DUMMY_DTBID,
	FLAG,
	DUMMY_FLAG,
	SCRIPT
}t_header;

typedef struct{
	t_header head;
	size_t tamanio;
	void* payload;
}t_prot_mensaje;

//Para t_clientes
typedef enum{
	CPU,
	ElDiego
}t_cliente;
/* Posiciones [0][0] Proceso SAFA [0][1] Diego [0][2] Cantidad CPUs
 * Posiciones [1][0] Proceso FM9  [1][1] Diego [1][2] Cantidad CPUs
 * Posiciones [2][0] Proceso MDJ  [2][1] Diego
 * Posiciones [3][0] Proceso DIEGO			   [3][2] Cantidad CPUs
 */
int MatrizDeConexiones[4][3];
int socketDiegoSAFA, socketDiegoFM9, socketDiegoMDJ;
int socketCPUSAFA[20][2], socketCPUFM9[20], socketCPUDIEGO[20];
int socketCPUdisponible;
t_prot_mensaje* RecibirMensaje(int socket_origen);
t_prot_mensaje* ErrorRecibirMensaje();
t_prot_mensaje* DesconexionRecibirMensaje();
void enviarMensaje(int socket_destino,t_header header , size_t tamanio_payload, void* payload);
void LiberarMensaje(t_prot_mensaje* victima);
//void* prot_armar_payload_con_clave_valor(char* clave, char* valor);

/*Para cuando el payload es un string simple.
 * Lo lee y retorna el char* al mensaje
 * Hace el malloc dentro*/
char* LeerMensaje(t_prot_mensaje* mensaje);

#endif /* PROTOCOLO_H_ */
