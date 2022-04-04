/*
* Javier Abellan, 9 Dic 2003
* #include <Ws2tcpip.h>
* Programa Cliente de un socket INET, que se conectará con un servidor java.
*/
#include <stdio.h>
#include <stdlib.h>
#include "Socket_Cliente.h"

#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "Socket.h"
#include <unistd.h> // for close

int main ()
{
    /*
    * Descriptor del socket y buffer para datos
    */
    int Socket_Con_Servidor; // descriptor
    u_long Longitud_Cadena = 0;
    u_long Aux;
    char Cadena[100];

    /*
    * Se abre la conexion con el servidor, pasando el nombre del ordenador
    * y el servicio solicitado.
    * "localhost" corresponde al nombre del mismo ordenador en el que
    * estamos corriendo. Esta dado de alta en /etc/hosts
    * "cpp_java" es un servicio dado de alta en /etc/services.
   * El servicio debe ser 35557 que es el puerto que va a atender el servidor
   * java.
    */
    Socket_Con_Servidor = Abre_Conexion_Inet (); // retorna el numero del descriptor
    if (Socket_Con_Servidor < 0) // si el numero es menor que cero, no hay conexion con servidor
    {
        printf ("No puedo establecer conexion con el servidor\n");
        exit (-1);
    }
    else{ printf("Conectado correctamente!");}

    /* Se lee un entero con la longitud de la cadena, incluido el \0 */
    Lee_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(int));
    Longitud_Cadena = ntohl (Aux);
    printf ("Cliente C: Recibido %d\n", Longitud_Cadena-1);

    /* Se lee la cadena de la longitud indicada */
    Lee_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
    printf ("Cliente C: Recibido %s\n", Cadena);

    /*
    * Se va a enviar una cadena de 6 caracteres, incluido el \0. Previamente se
    * envía un entero con el 6.
    */
    strcpy (Cadena, "jaja");
    Longitud_Cadena = 5;

    /* Antes de enviar el entero hay que transformalo a formato red */
    Aux = htonl (Longitud_Cadena);
    Escribe_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(Longitud_Cadena));
    printf ("Cliente C: Enviado %d\n", Longitud_Cadena-1);

    /* Se envía la cadena */
    Escribe_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
    printf ("Cliente C: Enviado %s\n", Cadena);

    /*
    * Se cierra el socket con el servidor
    */
    close (Socket_Con_Servidor);

    return 0;
}

/**
 * Do not try to find a match for your include files from Linux to Windows. Instead, try to compile your code step by step
 * and add those include files that you need. What I can see in the code:
 * Instead of inet_addr you can use inet_pton that is inside the <Ws2tcpip.h> include file.
 * Instead of dub2 use _dub2 in windows, that is inside <io.h>.
 * instead of execve, use std::system.
*/