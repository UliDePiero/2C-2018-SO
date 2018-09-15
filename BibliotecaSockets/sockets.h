#ifndef REDISTINTO_SOCKETS_H_
#define REDISTINTO_SOCKETS_H_

//----------------DEFINICION DE MACROS----------------//

#define TRUE				1
#define FALSE				0
#define BACKLOG 10
#define TAM_MESSAGE 240


///----------------BIBLIOTECAS INCLUIDAS----------------///

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>
#include <commons/collections/dictionary.h>
#include <commons/config.h>
#include <readline/readline.h>
#include <parsi/parser.h>
#include <pthread.h>
#include <semaphore.h>

///----------------STRUCTS-----------------///

//Encabezamiento de los protocolos
typedef struct {
	int32_t codigoOperacion;			 //0 para SET, 1 para GET, 2 para STORE
	int32_t tamanio;
} Header;

//Estructura para las conexiones
typedef struct {
	struct addrinfo* info;
	struct sockaddr_in address;			//Direccion contenida, en forma binaria
	socklen_t tamanioAddress;
	char* port;							//Puerto e ip, en forma de cadenas
	char* ip;
} Conexion;

//Estructura para las operaciones
typedef struct Operacion{
	char codigoOp;
	char* clave;
	char * valor;
}Operacion;

//Configuracion de tabla para las instancias
typedef struct InstanciaConfiguracion{
	int numero_entradas;
	int tam_entrada;
}InstanciaConfiguracion;

///----------------FUNCIONES-----------------///

//Funciones de archivos de configuracion
t_config* archivoConfigCrear(char* path, char** campos);
bool archivoConfigTieneCampo(t_config* archivoConfig, char* campo);
bool archivoConfigFaltaCampo(t_config* archivoConfig, char* campo);
char* archivoConfigSacarStringDe(t_config* archivoConfig, char* campo);
int archivoConfigSacarIntDe(t_config* archivoConfig, char* campo);
long archivoConfigSacarLongDe(t_config* archivoConfig, char* campo);
double archivoConfigSacarDoubleDe(t_config* archivoConfig, char* campo);
char** archivoConfigSacarArrayDe(t_config* archivoConfig, char* campo);
int archivoConfigCantidadCampos(t_config* archivoConfig);
void archivoConfigDestruir(t_config* archivoConfig);
void archivoConfigSetearCampo(t_config* archivoConfig, char* campo, char* valor);
bool archivoConfigInvalido(t_config* archivoConfig, char** campos);
bool archivoConfigInexistente(t_config* archivoConfig);
bool archivoConfigIncompleto(t_config* archivoConfig, char** campos);

//Funciones de hilos
void crearHilo(pthread_t* hilo, void *(*funcion) (void *), void *__restrict argumento, char* proceso);

//Funciones de conexion
void configurarConexion(Conexion* conexion,char* ip, int* puerto);
void puertoPosta(Conexion* conexion);
void mostrarIPs();
int crearSocket(Conexion* conexion, char* ip, int* puerto);
void cerrarSocket(int socket);

//Funciones especificas de clientes
void conectarSocket(Conexion* conexion, int unSocket);
int conectarAUnServidor(char* ip, int* puerto);

//Funciones especificas de servidores
void bindearSocket(Conexion* conexion, int unSocket);
void ponerAEscuchar(int unSocket, int ClientesEnEspera);
int aceptarComunicaciones(int socketEscucha);
void* obtenerIPCliente(struct sockaddr* sa);
struct timeval configurarTimeout(int segundos, int microsegundos);
int levantarServidor(char* ip, int* puerto, int backlog);

//Funciones de comunicacion
void recibirMensajes(int unSocket);		//DEPRECADO
int recibirUnMensaje(int unSocket);
void ingresarMensaje(char* cadena);		//DEPRECADO
void enviarMensajes(int unSocket);		//DEPRECADO
int enviarUnMensaje(int unSocket);
void enviarMensajeConInstrucciones(int unSocket, char* clave, char* valor, int codOp);
void enviarMensajeEspecifico(int unSocket, char* mensaje);
int primerMensaje(int unSocket);
void conversar(int* unSocket);//void conversar(void* unSocket);
void conversacionComoServidor(int* unSocket);//void conversacionComoServidor(void* unSocket);   //DEPRECADO
void conversacionComoCliente(void* unSocket);
int conversacionSimple(int unSocket);
void multiplexarComunicaciones(int unSocket/*, struct timeval* timeout*/);
Header crearHeader(int32_t codOp, int32_t tam);

//Funciones de error
void fallo(char* mensajeError);
void terminarConError(int socket, char* error_msg, void* buffer);

//Funciones prototipo
//void getInfoConexion(Conexion* conexion, char* direccion, char* puerto); ¿NECESARIA?

//

#endif /* REDISTINTO_SOCKETS_H_ */
