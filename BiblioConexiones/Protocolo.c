/*
 * Protocolo.c
 *
 *  Created on: 1 dic. 2018
 *      Author: utnso
 */
#include "Protocolo.h"

void enviarMensaje(int unSocket,t_header header , size_t tamanioPayload, void* payload){
	int resultado = 0;

	//Se arma el paquete de envio
	t_prot_mensaje* mensaje = (t_prot_mensaje*) malloc(sizeof(t_prot_mensaje));
	mensaje->head = header;
	mensaje->payload = malloc(tamanioPayload);
	mensaje->tamanio = sizeof(t_header) + tamanioPayload;

	//Se arma el payload
	memset(mensaje->payload, 0, tamanioPayload);
	memcpy(mensaje->payload, payload, tamanioPayload);

	//Envio del tamaño del mensaje, siendo mensaje : header + payload
	resultado = send(unSocket, &(mensaje->tamanio) , sizeof(size_t), 0);

	if( resultado <= 0){
		printf("ERROR: %s\n",FALLO_ENVIO_DE_MENSAJE);
		LiberarMensaje(mensaje);

	}else{
		//Se crea el conjunto de bytes : header + payload
		//1. Reservar lugar para crear el buffer
		void* buffer = malloc(mensaje->tamanio);

		//2. Los primeros bytes son para el HEADER
		memcpy(buffer, &(mensaje->head), sizeof(t_header));

		//3. El resto para el payload
		memcpy(buffer + sizeof(t_header), mensaje->payload, mensaje->tamanio - sizeof(t_header));

		resultado = send(unSocket, buffer, mensaje->tamanio, 0);

		if( resultado <= 0){
			printf("ERROR: %s\n",FALLO_ENVIO_DE_MENSAJE);
		}

		free(buffer);
		LiberarMensaje(mensaje);
	}
}

t_prot_mensaje* RecibirMensaje(int unSocket){

	t_prot_mensaje* retorno = (t_prot_mensaje*) malloc(sizeof(t_prot_mensaje));
	/* Si llega 0 es que hubo un close si llega -1 es error*/

	int resultado = recv(unSocket, &(retorno->tamanio), sizeof(size_t), MSG_WAITALL);

	if ( resultado == 0 ){
		close(unSocket);
		//Si el programa corta aca hay que hacer los free aca porque no continua el flujo
		free(retorno);
		return ErrorRecibirMensaje();
	}

	if ( resultado == -1 ){
		close(unSocket);
		//Si el programa corta aca hay que hacer los free aca porque no continua el flujo
		free(retorno);
		return DesconexionRecibirMensaje();
	}

	void* buffer = malloc(retorno->tamanio);

	resultado = recv(unSocket, buffer, retorno->tamanio, MSG_WAITALL);

	if( resultado == 0 ){
		close(unSocket);
		//Si el programa corta aca hay que hacer los free aca porque no continua el flujo
		free(retorno);
		free(buffer);
		return ErrorRecibirMensaje();
	}

	if( resultado == -1 ){
		close(unSocket);
		//Si el programa corta aca hay que hacer los free aca porque no continua el flujo
		free(retorno);
		free(buffer);
		return DesconexionRecibirMensaje();
	}

	void* payload = malloc(retorno->tamanio - sizeof(t_header));
	t_header header;

	memcpy( &header, buffer, sizeof(t_header));
	memcpy( payload, buffer + sizeof(t_header), retorno->tamanio - sizeof(t_header));

	retorno->head = header;
	retorno->payload = payload;

	free(buffer);
	return retorno;
}

void LiberarMensaje(t_prot_mensaje* mensaje){
	if(mensaje != NULL){
		if(mensaje->payload != NULL){
			free(mensaje->payload);
		}
		free(mensaje);
	}
}
/*
void* prot_armar_payload_con_clave_valor(char* clave, char* valor){
	size_t tamanio_clave = strlen(clave);
	size_t tamanio_valor = strlen(valor);
	size_t tamanio_buffer = sizeof(size_t) * 2 + tamanio_clave + tamanio_valor;
	void* buffer = malloc(tamanio_buffer);
	memset(buffer, 0, tamanio_buffer);
	memcpy(buffer, &tamanio_clave , sizeof(size_t));
	memcpy(buffer + sizeof(size_t), &tamanio_valor , sizeof(size_t));
	memcpy(buffer + sizeof(size_t)*2, clave , tamanio_clave );
	memcpy(buffer + sizeof(size_t)*2 + tamanio_clave, valor , tamanio_valor );
	//Buffer: tamanio_clave + tamanio_valor + clave + valor
	return buffer;
}
*/

t_prot_mensaje* ErrorRecibirMensaje(){
	t_prot_mensaje* retorno = (t_prot_mensaje*) malloc(sizeof(t_prot_mensaje));
	retorno->head = FALLO_AL_RECIBIR;
	retorno->payload = NULL;
	return retorno;
}

t_prot_mensaje* DesconexionRecibirMensaje(){
	t_prot_mensaje* retorno = (t_prot_mensaje*) malloc(sizeof(t_prot_mensaje));
	retorno->head = DESCONEXION;
	retorno->payload = NULL;
	return retorno;
}

char* LeerMensaje(t_prot_mensaje* mensaje){
	size_t largoStringMensaje = mensaje->tamanio - sizeof(t_header);
	char* string = (char*) malloc(largoStringMensaje + 1); // +1 por el '\0'
	memset(string, 0, largoStringMensaje);
	memcpy(string, mensaje->payload, largoStringMensaje );
	string[largoStringMensaje] = '\0';
	return string;
}

