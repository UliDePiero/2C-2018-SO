/*
 * PCP.c
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */
/*
 * Planificador de Corto Plazo
El subsistema de PCP será el encargado de distribuir los distintos DTB en las CPUs,
interactuando con las colas READY y EXEC. Este recibirá las conexiones de los procesos CPUs y
quedará a la espera de DT Blocks en la cola READY. Finalmente, al concluir la ejecución de un DT Block,
deberá mover el mismo a la cola EXIT.
 *
 */
#include "S-AFA.h"
void moverDTB(t_queue *cola, int ID){
	EstructuraDTB* DTB_Elegido = list_find(ListaDTB, (void*) (DTB->ID == ID));
	queue_push(cola, &DTB_Elegido->ID);

}
void iniciarDTBDummy(){

	while(1){
		sem_wait(&semDTBDUMMY);
		DTB_Dummy->ID = DTB_Ready->ID;
		strcpy(DTB_Dummy->RutaScript,rutaScript);
		DTB_Dummy->FlagIncializado = 0;
		queue_push(Ready, &DTB_Dummy->ID);
	}

}
void planificacionCP(){

	int *ID, q, flagCPUencontrada, cantCPUs;
while(1){
	//ALGORITMO
	ID = queue_pop(Ready);
	DTB = list_find(ListaDTB, (void*)(DTB->ID == *ID));
	moverDTB(Exec, *ID);

	q = 1; flagCPUencontrada = 0;

	while(flagCPUencontrada==0){
		while ( (q<20) && ( (socketCPUSAFA[q][0] == 0) || ((socketCPUSAFA[q][0] != 0) && (socketCPUSAFA[q][1] != 0)) ) ) q++; //busca CPU disponible
		if (q<20){
			socketCPUdisponible = socketCPUSAFA[q][0];
			socketCPUSAFA[q][1] = 1;
			flagCPUencontrada = 1;
			//sem_post(&semCPUdisponible);
			enviarMensaje(socketCPUdisponible, DTBID , sizeof(DTB->ID), &DTB->ID); //el tamaño no se si esta bien
			enviarMensaje(socketCPUdisponible, FLAG , sizeof(DTB->FlagIncializado), &DTB->FlagIncializado); //el tamaño no se si esta bien
			enviarMensaje(socketCPUdisponible, SCRIPT , sizeof(DTB->RutaScript), &DTB->RutaScript); //el tamaño no se si esta bien
		}
		else {
			cantCPUs = MatrizDeConexiones[0][2];
			printf("No hay CPU disponible.");
			while(cantCPUs == MatrizDeConexiones[0][2]);
			//sem_wait(&semLiberoCPU);
		}
	}
	t_prot_mensaje* respuestaCPU_DTBID = RecibirMensaje(socketCPUdisponible);
	t_prot_mensaje* respuestaCPU_FLAG = RecibirMensaje(socketCPUdisponible);
	socketCPUSAFA[q][1] = 0;
	switch(respuestaCPU_FLAG->payload == 0){
		case 0:
			ID = queue_pop(Exec);
			moverDTB(Block, *ID);
			break;
		case 1:
			ID = queue_pop(Exec);
			moverDTB(Ready, *ID);
			break;
		case 2:
			ID = queue_pop(Exec);
			moverDTB(Exit, *ID);
			break;
	}
}
}
