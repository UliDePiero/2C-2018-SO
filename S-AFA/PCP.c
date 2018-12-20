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
//#include "S-AFA.h"
void moverDTB(t_queue cola, int ID){
	EstructuraDTB* DTB_Elegido = list_find(ListaDTB, DTB->ID = ID);
	queue_push(cola, DTB_Elegido->ID);
}

void planificacionCP(){

	int ID = queue_pop(Ready);
	moverDTB(Exec, ID);

	moverDTB(Block,ID);
	moverDTB(Ready, ID);
	moverDTB(Exec, ID);

	moverDTB(Exit, ID);

}
