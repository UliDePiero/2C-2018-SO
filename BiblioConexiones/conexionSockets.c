#include "conexionSockets.h"

//t_log * logger;

///FUNCIONES DE ARCHIVOS DE CONFIGURACION

//Crea un archivo de configuracion a guardar en path, con los campos ingresados por parametro
t_config* archivoConfigCrear(char* path, char** campos) {

	t_config* archivoConfig = config_create(path);
	if(archivoConfigInvalido(archivoConfig, campos))
	{
		puts("Archivo de configuracion invalido\n");
		exit(EXIT_FAILURE);
	}
	return archivoConfig;

}
//---------------------------------------------

//Devuelve true si el archivo apuntado por "archivoConfig" posee el campo "campo", false en caso contrario
bool archivoConfigTieneCampo(t_config* archivoConfig, char* campo) {

	return config_has_property(archivoConfig, campo);

}
//---------------------------------------------

//Contrario a archivoConfigTieneCampo, se fija si el archivo carece del campo
bool archivoConfigFaltaCampo(t_config* archivoConfig, char* campo) {

	return !archivoConfigTieneCampo(archivoConfig, campo);

}
//---------------------------------------------

//Devuelve el valor cadena del campo "campo" en el archivo apuntado por "archivoConfig"
char* archivoConfigSacarStringDe(t_config* archivoConfig, char* campo) {

	return config_get_string_value(archivoConfig, campo);

}
//---------------------------------------------

//Devuelve el valor entero del campo "campo" en el archivo apuntado por "archivoConfig"
int archivoConfigSacarIntDe(t_config* archivoConfig, char* campo) {

	return config_get_int_value(archivoConfig, campo);

}
//---------------------------------------------

//Devuelve el valor long del campo "campo" en el archivo apuntado por "archivoConfig"
long archivoConfigSacarLongDe(t_config* archivoConfig, char* campo) {

	return config_get_long_value(archivoConfig, campo);

}
//---------------------------------------------

//Devuelve el valor doble precision del campo "campo" en el archivo apuntado por "archivoConfig"
double archivoConfigSacarDoubleDe(t_config* archivoConfig, char* campo) {

	return config_get_double_value(archivoConfig, campo);

}
//---------------------------------------------

//Devuelve el array de cadenas del campo "campo" en el archivo apuntado por "archivoConfig"
char** archivoConfigSacarArrayDe(t_config* archivoConfig, char* campo) {

	return config_get_array_value(archivoConfig, campo);

}
//---------------------------------------------

//Devuelve la cantidad de campos que posee el archivo apuntado por "archivoConfig"
int archivoConfigCantidadCampos(t_config* archivoConfig) {

	return config_keys_amount(archivoConfig);

}
//---------------------------------------------

//Destruye el archivo apuntado por "archivoConfig"
void archivoConfigDestruir(t_config* archivoConfig) {

	config_destroy(archivoConfig);

}
//---------------------------------------------

//Guarda el valor "valor" en el campo "campo" del archivo apuntado por "archivoConfig"
void archivoConfigSetearCampo(t_config* archivoConfig, char* campo, char* valor) {

	config_set_value(archivoConfig, campo, valor);

}
//---------------------------------------------

//Devuelve true si el archivo apuntado por "archivoConfig" no existe o bien no posee los campos del array "campos"
bool archivoConfigInvalido(t_config* archivoConfig, char** campos) {

	return (archivoConfigIncompleto(archivoConfig, campos) || archivoConfigInexistente(archivoConfig)) ;
}
//---------------------------------------------

//Devuelve true si el archivo apuntado por "archivoConfig" no existe
bool archivoConfigInexistente(t_config* archivoConfig) {

	return archivoConfig == NULL;

}
//---------------------------------------------

//Devuelve true si no existe un archivo apuntado por "archivoConfig" que posea todos los campos del array "campos"
bool archivoConfigIncompleto(t_config* archivoConfig, char** campos) {

	int indice;
	for(indice = 0; indice < archivoConfigCantidadCampos(archivoConfig); indice++)
	{
		if(archivoConfigFaltaCampo(archivoConfig, campos[indice]))
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------

///FUNCIONES DE HILOS

//Creo un hilo asociado a hilo, con cierta funcion y cierto argumento asociado, y lo detacheo
void crearHilo(pthread_t* hilo, void *(*funcion) (void *), void *__restrict argumento, char* proceso) {

	pthread_create(hilo, NULL, (void*) funcion, (void*) argumento);
	printf("Creado el hilo %lu para el %s", *hilo, proceso);
	pthread_detach((int) hilo);

}
//---------------------------------------------

///FUNCIONES DE CONEXION

//Guardo en una estructura conexion los datos de una conexion a cierto ip y cierto puerto
void configurarConexion(Conexion* conexion, char* ip, char* puerto){

	struct addrinfo hints;
	int errorCheck;													//Para checkear que no haya error
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	//errorCheck = getaddrinfo(ip, puerto, &hints, &(conexion->info));
	errorCheck = getaddrinfo(NULL, puerto, &hints, &(conexion->info));
	if(errorCheck != 0)
	{
		fallo("No pudo configurarse una conexion al puerto/direccion \n");
	}
	conexion->port = strdup(puerto);								//Para guardarlos tambien como
	conexion->ip = strdup(ip);										//cadenas, y no solo binariamente
	printf("\nESTADO: Conexion para la ip %s en el puerto %s configurada \n", ip, puerto);
	return;

}
//---------------------------------------------

//Printf para debuggear e imprimir los verdaderos valores de la conexion esperada
void puertoPosta(Conexion* conexion){

	struct sockaddr_in* direccionAux;
	direccionAux = (struct sockaddr_in *)conexion->info->ai_addr; //Casteo necesario
	printf("El puerto pinta que es %d \n", ntohs(direccionAux->sin_port));

}
//---------------------------------------------

//Lista todas las IPs del proceso/equipo/componente en el que estoy
void mostrarIPs()
{
	int i;
	char nombreHost[128];
	struct hostent *he;
	struct in_addr **listaDeIPs;
	gethostname(nombreHost, sizeof(nombreHost));
	printf("%s", nombreHost);
	he = gethostbyname(nombreHost);
	printf("Mis IPs son: \n");
	listaDeIPs = (struct in_addr **)he->h_addr_list;
	for(i = 0; listaDeIPs[i] != NULL; i++) {
		printf(">%s\n", inet_ntoa(*listaDeIPs[i]));
	}
}
//---------------------------------------------

//Configura una conexion a una ip y un puerto, crea un socket para ella y le asigna un descriptor
int crearSocket(Conexion* conexion, char* ip, char* puerto){

	configurarConexion(conexion, ip, puerto);
	int descriptor = socket(conexion->info->ai_family, conexion->info->ai_socktype, conexion->info->ai_protocol);
	if(descriptor == -1){
		terminarConError((int)socket,"No se pudo asignar un socket a la conexion \n", NULL);
	}
	printf("ESTADO: Conexion para la ip %s en el puerto %s configurada; creado un socket apropiado, cuyo descriptor es %d \n", ip, puerto, descriptor);
	return descriptor;

}
//---------------------------------------------

//Cierra el socket descripto por descriptorSocket; de no ser posible, avisa por pantalla
void cerrarSocket(int descriptorSocket){

     if((close(descriptorSocket) !=0 )){
    	 terminarConError(descriptorSocket, "No se pudo cerrar el socket. \n", NULL);
     }
     printf("ESTADO: Socket descripto por %d cerrado, fin de la conexion a traves de el \n", descriptorSocket);
     return;

}
//---------------------------------------------

///FUNCIONES DE CLIENTE

//Conecta el socket descripto por unSocket a la direccion guardada en "conexion"
void conectarSocket(Conexion* conexion, int unSocket){

	int estadoDeConexion;
	if ((estadoDeConexion = connect(unSocket, conexion->info->ai_addr, conexion->info->ai_addrlen)) != 0){
		terminarConError(estadoDeConexion, "No pudo conectarse el socket a la conexion \n",NULL);
	}
	printf("ESTADO: Conectado al server de ip %s en el puerto %s, a traves del socket descripto por %d \n", conexion->ip, conexion->port, unSocket);
	freeaddrinfo(conexion->info);
	return;

}
//---------------------------------------------

//Conecta a un servidor en la ip y el puerto determinados
int conectarAUnServidor(char *ip, char *puerto){ //TERMINAR!

	Conexion conexion;
	int socketServidor = crearSocket(&conexion, ip, puerto);
	conectarSocket(&conexion,socketServidor);
	return socketServidor;

}
//---------------------------------------------

///FUNCIONES DE SERVIDOR
#include <errno.h>
//Asocia/bindea el socket descripto por unSocket a la conexion guardada en "conexion"
void bindearSocket(Conexion* conexion, int unSocket){

	int estadoDelBindeo;
	puertoPosta(conexion);
	if ((estadoDelBindeo = bind(unSocket, conexion->info->ai_addr, conexion->info->ai_addrlen)) != 0){
		printf("flags %d ,familia %d ,protocolo %d ,tipo socket %d,longitud %d  ", conexion->info->ai_flags, conexion->info->ai_family, conexion->info->ai_protocol,conexion->info->ai_socktype,conexion->info->ai_addrlen);
		for(int a=0; a<14; a++) printf("%d-", *conexion->info->ai_addr->sa_data );
		perror("\nError: ");
		printf("Errno: %d\n",errno);
		terminarConError(estadoDelBindeo, "No pudo asociarse el socket a la conexion \n", NULL);
	}
	printf("ESTADO: Socket de descriptor %d asociado a la conexion en la ip %s en el puerto %s \n", unSocket, conexion->ip, conexion->port);
	return;

}
//---------------------------------------------

//Pone el socket unSocket a escuchar, aceptando un maximo de "clientesEnEspera" en la cola
void ponerAEscuchar(int unSocket, int clientesEnEspera){

	int estadoDelListen;
	if ((estadoDelListen = listen(unSocket, clientesEnEspera)) != 0){
		terminarConError(estadoDelListen, "No se pudo poner al socket a escuchar \n", NULL);
	}
	printf("ESTADO: El socket descripto por %d ya esta escuchando! Con un maximo de %d clientes en espera \n", unSocket, clientesEnEspera);
	return;

}
//---------------------------------------------

//Aceptar la primera comunicacion que se presente al puerto bindeado con el socket "socketEscucha"
int aceptarComunicaciones(int socketEscucha) {

	struct sockaddr_storage conexionEntrante;
	socklen_t tamanioDir = sizeof(conexionEntrante);
	int socketActivo;
	char s[INET_ADDRSTRLEN];

	do{ //Loop a la espera de conexiones
		socketActivo = accept(socketEscucha, (struct sockaddr *)&conexionEntrante, &tamanioDir);
	}while(socketActivo == -1);

	inet_ntop(conexionEntrante.ss_family, obtenerIPCliente((struct sockaddr *)&conexionEntrante), s, sizeof(s)); //Guardar IP del cliente en conexion.ip
	printf("ESTADO: Conexion con el cliente de ip %s establecida a traves del socket descripto por %d \n", s, socketActivo);
	return socketActivo;
}
//---------------------------------------------

//Devuelve, segun el protocolo, una estructura sin_addr con la IP del cliente cuyo sockaddr es apuntado por sa
void *obtenerIPCliente(struct sockaddr *sa)
{

  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);

}
//---------------------------------------------

//Configura el tiempo maximo de espera del servidor al hacer el select, en tmax segundos
struct timeval configurarTimeout(int segundos, int microsegundos) {

	struct timeval timeout;
	timeout.tv_sec = segundos;
	timeout.tv_usec = microsegundos;
	return timeout;

}

//---------------------------------------------

//Levanta un servidor en la ip y el puerto determinados
int levantarServidor(char* ip, char* puerto, int backlog) {

	Conexion conexion;
	int activado = TRUE;
	int socketEscucha = crearSocket(&conexion, ip, puerto);
	conexion.tamanioAddress = sizeof(conexion.address);
	setsockopt(socketEscucha, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));//mientras este en etapa de pruebas
	bindearSocket(&conexion, socketEscucha);
	freeaddrinfo(conexion.info);
	ponerAEscuchar(socketEscucha, backlog);
	return socketEscucha;

}
//---------------------------------------------

///FUNCIONES DE COMUNICACION

//Recibir y mostrar por pantalla los mensajes que llegan a traves del socket descripto por unSocket   TEMPORAL
void recibirMensajes(int unSocket){

	int bytesRecibidos = 1;
	char mensaje[TAM_MESSAGE];

	while(bytesRecibidos != 0)
	{
		bytesRecibidos = recv(unSocket, (void*) mensaje, TAM_MESSAGE, 0);
		if(bytesRecibidos < 0)
		{
			terminarConError(unSocket, "Error en la recepcion de mensajes\n", 0);
		}
		/*else if(bytesRecibidos == 0)
		{
			cerrarSocket(unSocket);
		}*/
		else if(bytesRecibidos > 0)
		{
			printf("Al socket descripto por %d llego el mensaje \"%s\" \n", unSocket, mensaje);
		}
	}

}
//---------------------------------------------

//Recepcion atomica de un mensaje, a traves del socket descripto por unSocket
int recibirUnMensaje(int unSocket) {

	int bytesRecibidos;
	char mensaje[TAM_MESSAGE];

	bytesRecibidos = recv(unSocket, (void*) mensaje, TAM_MESSAGE, 0);
	if(bytesRecibidos < 0)
	{
		terminarConError(unSocket, "Error en la recepcion de mensajes\n", 0);
	}
	else if(bytesRecibidos == 0)
	{
		cerrarSocket(unSocket);
	}
	else if(bytesRecibidos > 0)
	{
		printf("\nA traves del socket descripto por %d llego el mensaje \"%s\" \n", unSocket, mensaje);
		return TRUE;
	}
	return FALSE;

}
//---------------------------------------------

//DEPRECADO. Lo borro?
//Para ingresar por teclado un mensaje a enviar, dandole el formato deseado (pudiendo ingresar espacios) y copiarlo en cadena
void ingresarMensaje(char* cadena) {

	char mensaje[TAM_MESSAGE];
	int size;
	fgets(mensaje,TAM_MESSAGE,stdin);
	size = strlen(mensaje);
	mensaje[size-1] = '\0';
	strcpy(cadena, mensaje);

}
//---------------------------------------------

//Escribir y enviar mensajes a traves del socket descripto por unSocket    TEMPORAL
void enviarMensajes(int unSocket){

	int enviar = FALSE;
	int flagEnvio = 0;                                       //Para no hacer el primer envio (RESOLVER) ni imprimir >> al pedo
	char mensaje[TAM_MESSAGE];
	printf("Escriba los mensajes a enviar, o bien escriba \"salir\" para abandonar \n\n");

	do{

		if(flagEnvio > 0)
		{
			printf(">>");
		}
		//printf(">>");
		ingresarMensaje(mensaje);
		if(strcmp(mensaje,"salir"))
		{
			enviar = TRUE;
		}
		else
		{
			enviar = FALSE;
		}
		if(enviar == TRUE && flagEnvio > 0)
		{
			send(unSocket, mensaje, strlen(mensaje)+1, 0);
		}
		flagEnvio++;
	}while(enviar);

	printf("\nFin del envio de mensajes a traves del socket descripto por %d \n", unSocket);

}
//---------------------------------------------

//Envio atomico de un mensaje a unSocket
int enviarUnMensaje(int unSocket) {

	int enviar = FALSE;
	char* mensaje;
	printf("\nEscriba el mensaje a enviar, o bien escriba \"salir\" para abandonar \n");
	mensaje = readline(">>");
	if((mensaje != NULL) && (strcmp(mensaje,"salir")))
	{
		enviar = TRUE;
	}
	else
	{
		cerrarSocket(unSocket);
	}
	if(enviar == TRUE)
	{
		send(unSocket, mensaje, strlen(mensaje)+1, 0);
		free(mensaje);
	}
	return enviar;

}
//---------------------------------------------

//Envia al socket descripto por "unSocket" un mensaje con la clave y el valor. segun el codigo de la operacion "codOp"
void enviarMensajeConInstrucciones(int unSocket, char* clave, char* valor, int codOp){

	char* mensaje;
	char* operacion;										//PROBAR!!

	switch(codOp) {
		case 1:
			operacion = malloc(4);
			strcpy(operacion, "GET ");
			break;
		case 2:
			operacion = malloc(4);
			strcpy(operacion, "SET ");
			break;
		case 3:
			operacion = malloc(6);
			strcpy(operacion, "STORE ");
			break;
		default:
			fallo("Codigo de operacion no valido, envio cancelado");
	}

	int length = strlen(operacion) + strlen(clave) + strlen(valor);
	mensaje = malloc(sizeof(char) * length);
	strcpy(mensaje, operacion);
	strcat(mensaje, clave);
	if (codOp == 3) {
		strcat(mensaje, " ");
		strcat(mensaje, valor);
	}

	send(unSocket, mensaje, strlen(mensaje)+1, 0);
	free(mensaje);

}
//---------------------------------------------

//Envia un mensaje pasado por parametro a traves del socket descripto por unSocket
void enviarMensajeEspecifico(int unSocket, char* mensaje) {

	int longitud;
	longitud = strlen(mensaje);
	send(unSocket, mensaje, longitud, 0);

}
//---------------------------------------------

//Envia un solo mensaje, atomicamente, al socket descripto por unSocket, y retorna un entero(booleano) para saber si seguir o no conversando
int primerMensaje(int unSocket) {

	int hablar;
	char mensaje[TAM_MESSAGE];
	ingresarMensaje(mensaje);
	hablar = enviarUnMensaje(unSocket);
	return hablar;

}
//---------------------------------------------

//Entabla una conversacion (envio y recepcion de mensajes) por medio del socket descripto por unSocket
void conversar(int* unSocket) {//void conversar(void* unSocket) {

	int unSocketPosta = *unSocket;//int unSocketPosta = (int) unSocket;
	int seguirHablando = TRUE;
	while(seguirHablando)
	{
		seguirHablando = FALSE;
		seguirHablando = recibirUnMensaje(unSocketPosta);
		if(seguirHablando == FALSE)
		{
			//cerrarSocket((int) unSocket);
			break;								//Para salir si no recibi nada
		}
		seguirHablando = enviarUnMensaje(unSocketPosta);
	}

}
//---------------------------------------------

//DEPRECADO. Lo borramos?
//Entablar una conversacion como servidor (es el primero en recibir un mensaje)
void conversacionComoServidor(int* unSocket) {//void conversacionComoServidor(void* unSocket) {

	recibirUnMensaje(*unSocket);//recibirUnMensaje((int) unSocket);
	conversar(unSocket);

}
//---------------------------------------------

//Entablar una conversacion como cliente (es el primero en enviar un mensaje)
void conversacionComoCliente(void* unSocket) {

	enviarUnMensaje((int) unSocket);
	conversar(unSocket);

}
//---------------------------------------------

//Abstraccion para hacer una conversacion simple (recibe un mensaje, y responde) en cada socket activo del servidor, al recorrer el select
int conversacionSimple(int unSocket) {

	int flagConversacion;
	flagConversacion = recibirUnMensaje(unSocket);
	if(flagConversacion == TRUE)
	{
		enviarUnMensaje(unSocket);
	}
	return flagConversacion;

}
//---------------------------------------------

//Recorrer sets de descriptores e ir atendiendo las multiples conexiones, a lo largo de un intervalo timeout (no, para siempre)
void multiplexarComunicaciones(int unSocket /*, struct timeval* timeout*/) {

	fd_set master, socketsReceptores; //socketsReceptores son los que reciben mensajes, busco ahi si hay mensajes nuevos
	FD_ZERO(&master);
	FD_ZERO(&socketsReceptores);
	FD_SET(unSocket, &master);
	int i;
	int descriptorMaximo = unSocket;
	for(;;)
	{
		socketsReceptores = master;
		//Salgo del ciclo si hay un error de select, y mientras tanto lo hago
		if(select(descriptorMaximo + 1, &socketsReceptores, NULL, NULL, NULL) == -1)
		{
			terminarConError(unSocket, "Error de multiplexacion, no se pudo hacer select \n", NULL);
		}
		//Recorro los descriptores existentes, esperando mensajes entrantes
		for(i = 0; i <= descriptorMaximo; i++)
		{
			if(FD_ISSET(i, &socketsReceptores))			//Si esta entre los sockets receptores
			{
				if(i == unSocket)						//Si es un nuevo cliente que quiere comunicarse
				{
					struct sockaddr_storage conexionEntrante;
					socklen_t tamanioDir = sizeof(conexionEntrante);
					int socketActivo;
					char s[INET_ADDRSTRLEN];
					socketActivo = accept(unSocket, (struct sockaddr *)&conexionEntrante, &tamanioDir);
					if(socketActivo == -1)
					{
						terminarConError(unSocket, "No se pudo aceptar una conexion entrante en el socket \n", NULL);
					}
					else
					{
						FD_SET(socketActivo,&master);        //Agrego el nuevo descriptor al set general o master
						if(socketActivo > descriptorMaximo)
						{
							descriptorMaximo = socketActivo;
						}
						inet_ntop(conexionEntrante.ss_family, obtenerIPCliente((struct sockaddr *)&conexionEntrante), s, sizeof(s)); //Guardar IP del cliente en conexion.ip
						printf("ESTADO: Conexion con el cliente de ip %s establecida a traves del socket descripto por %d \n", s, socketActivo);
					}
				}
				else										 //Si es un cliente ya activo, esta
				{
					int continuar =	conversacionSimple(i);	 //Recibo y envio un mensaje a traves del socket i, y me fijo como fue para saber si seguir hablando
					if(continuar == FALSE)
					{
						cerrarSocket(i);						 //Cierro el socket una vez termine de recibir los mensajes
						FD_CLR(i, &master);						 //Lo limpio de master
					}

				}
			}
		}
	}

}
//---------------------------------------------

//Crea un encabezamiento para un protocolo
Header crearHeader( int32_t codOp, int32_t tam) {

	Header header;
	header.codigoOperacion = codOp;
	header.tamanio = tam;
	return header;

}
//---------------------------------------------

///FUNCIONES DE ERROR

//Terminar la ejecucion, mostrando por pantalla el texto de mensajeError
void fallo(char *mensajeError){

	printf("%s\n",mensajeError);
	exit(1);

}
//---------------------------------------------

//Cierra el socket "socket", emite el mensajeError, y lo registra en el logger, terminando la ejecucion
void terminarConError(int socket, char* mensajeError, void * buffer) {

  if(buffer) {
    free(buffer);
  }
  close(socket);
  fallo(mensajeError);

}
//---------------------------------------------

///FUNCIONES PROTOTIPO (A DEFINIR/TEMPORALES)

//Guarda la direccion e ip de una conexion, en forma textual, en las cadena "direccion" y "puerto"
//void getInfoConexion(Conexion *conexion, char* direccion, char* puerto){

	// Funcionara asi también? PRUEBA PENDIENTE
	//if(conexion->info->ai_addr->sa_family == AF_INET){
	//	 dirBinaria = strdup(&(((struct sockaddr_in*)conexion->info->ai_addr)->sin_addr));
	//}
	//int longDirBinaria = strlen(dirBinaria);
	//dirBinaria[longDirBinaria] = '\0';
	//inet_ntop(conexion->info->ai_family, dirBinaria, direccion, sizeof(direccion));

//}
//---------------------------------------------
