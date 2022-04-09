
// Esta clase lo que hace es crear el socket y conectarse con el servidor

/*
* Includes del sistema
*/
#include "Socket_Cliente.h"

/*
* Conecta con un servidor remoto a traves de socket INET
*/
int Abre_Conexion_Inet ()
{
	struct sockaddr_in Direccion;
	int Descriptor;
	
	Descriptor = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Descriptor <0)
		return -1;


    Direccion.sin_family = AF_INET;
    Direccion.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip del servidor
    Direccion.sin_port = ntohs (1025);
    memset(&Direccion.sin_zero, 0, sizeof(Direccion.sin_zero)); // Clean structure

	if (connect (Descriptor,(struct sockaddr *)&Direccion,
            (socklen_t) sizeof(Direccion)) < 0)
	{
		return -1;
	}

	return Descriptor; // numero de cliente
}
