/**
 * METODO CLIENTE PARA LA CONEXION CON EL SERVIDOR (RECIVE Y ENVIA MENSAJES)
 */
#include <stdio.h>
#include <stdlib.h>
#include "Socket_Cliente.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "Socket.h"

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
    * "127.0.0.1" Es la direccion ip del servidor.
    * El servicio debe ser 8080 que es el puerto que va a atender el servidor
    * java.
    */
    Socket_Con_Servidor = Abre_Conexion_Inet (); // retorna el numero del descriptor
    if (Socket_Con_Servidor < 0) // si el numero es menor que cero, no hay conexion con servidor
    {
        printf ("No puedo establecer conexion con el servidor\n");
        exit (-1);
    }
    else{ printf("Conectado correctamente!\n");}

    /* Se inicia la comunicacion entre el cliente y el servidor */
    while (1){

        /** Primero se obtienen todos los datos necesarios por parte del servidor */

        /* Se lee un entero con la longitud de la cadena, incluido el \0 */
        Lee_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(int));
        Longitud_Cadena = ntohl (Aux);
        //printf ("Cliente C: Recibido %d\n", Longitud_Cadena-1);

        /* Se lee la cadena de la longitud indicada */
        Lee_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
        printf ("Mensaje recibido: %s\n", Cadena);

        /*
        * Se va a enviar una cadena de 6 caracteres, incluido el \0. Previamente se
        * envía un entero con el 6. strlen(char)
        */
        char message[50]; // Aquí alojaremos el valor leído
        printf("Escribe un mensaje:\n");
        scanf("%s", message); // No usamos &
        //printf("Mensaje enviado: %s \n", message);

        Longitud_Cadena = strlen(message)+1;

        /* Antes de enviar el entero hay que transformalo a formato red */
        Aux = htonl (Longitud_Cadena);
        Escribe_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(Longitud_Cadena));
        //printf ("Cliente C: Enviado %d\n", Longitud_Cadena-1);

        /* Se envía la cadena */
        Escribe_Socket (Socket_Con_Servidor, message, Longitud_Cadena);
        printf ("Mensaje enviado: %s\n", message);

        char cad[]="salir";
        char *p1 = cad;
        char *p2 = message;

        // si el mensaje enviado es "salir", se cierra la conexion primero en el servidor y luego en el cliente
        if(strcmp(p1, p2) == 0){
            break;
        }

        strcpy (Cadena, "");
    }

    /*
    * Se cierra el socket con el servidor
    */
    close (Socket_Con_Servidor);

    return 0;
}