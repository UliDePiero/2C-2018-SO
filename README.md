# tp-2018-2c-Intel-y-Gentes
Pasos a seguir:

A) Armar una carpeta llamada workspace en home/utnso/

B) Ahí dentro, descargar las commons de https://github.com/sisoputnfrba/so-commons-library , siguiendo los pasos del video

C) Importar los proyectos al workspace, de a uno (haber seteado el workspace de Eclipse ahi)
	D.1) File -> Import -> General -> Existing Projects Into Workspace. Importar los cuatro del repositorio, uno por uno
	
D) Desde la consola, ejecutar:

	cd         		// para pararnos en home/utnso/
	
	leafpad .bashrc		// para abrir el editor de texto en .bashrc
	
	Ahi, ir a la ultima linea del archivo, y setear la variable LD_LIBRARY_PATH. Esta ultima linea tiene que decir:
	
	 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/utnso/workspace/tp-2018-2c-Intel-y-Gentes/BiblioConexiones/Debug

E) Verificar que cada ejecutable haya quedado bien linkeado a la BibliotecaSockets
	F.1) Desde la consola, en la carpeta Debug de cada proyecto, ejecutar ldd Ejecutable y ver como esta libBiblioConexiones.so
