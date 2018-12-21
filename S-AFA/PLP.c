/*
 * PLP.c
 *
 *  Created on: 31 ago. 2018
 *      Author: utnso
 */
/*
 *Planificador de Largo Plazo
El subsistema de PLP será el punto de entrada, encargado de crear los DTB asociados a los programas G.DT
y agregarlos a la cola NEW. Además, será el encargado de mantener el grado de multiprogramación del sistema,
planificando los pases a READY según el algoritmo FIFO (First In, First Out). Estos pases a READY implicarán
la carga en memoria del script Escriptorio asociado, responsabilidad del Gestor de programas G.DT descrito más adelante.
 *
 */
#include "S-AFA.h"
#include "Consola.h"

void cargarNuevoDTB(EstructuraDTB* DTB) {
	DTB->ID = ID_DTBs++;
	strcpy(DTB->RutaScript,rutaScript );
	/*
	strcpy(DTB->PC,"\0" );
	strcpy(DTB->TablaArchivosAbiertos,"\0" );
	*/
	DTB->FlagIncializado = 1;
}
void planificacionLP(){
while(1){
	if(nuevoIngresoGDT == 1){
		pthread_mutex_lock(&mutexEjecutar);
		nuevoIngresoGDT = 0;
		DTB = malloc(sizeof(EstructuraDTB));
		//free(DTB);
		list_add(ListaDTB, DTB);
		cargarNuevoDTB(DTB);
		queue_push(New, &DTB->ID);
		pthread_mutex_unlock(&mutexEjecutar);
	}
	if(procesosEnReady < configuracion->multiprogramacion){
		int *ID;
		ID = queue_pop(New);
		DTB_Ready = list_find(ListaDTB, (void*)(DTB->ID == *ID));
		//queue_push(Ready, &DTB_Ready->ID);
		//sprocesosEnReady++;
		sem_post(&semEjecutar);
	}

}
}
