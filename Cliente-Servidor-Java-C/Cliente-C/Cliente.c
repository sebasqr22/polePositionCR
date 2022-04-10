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
#include <pthread.h>

char mensajeRecibido[100] = "";
int Socket_Con_Servidor;


void enviarMensaje(char mensaje[50]){
    u_long Longitud_Cadena = strlen(mensaje)+1;
    u_long Aux = htonl (Longitud_Cadena);
    Escribe_Socket (Socket_Con_Servidor, mensaje, Longitud_Cadena);
    printf ("Mensaje enviado: %s\n", mensaje);
}

void *Comunicacion(void *valor){
    printf("Se inicia el segundo hilo.........");
    u_long Longitud_Cadena = 0;
    u_long Aux;
    char Cadena[100];
    while(1){
        Lee_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(int));
        Longitud_Cadena = ntohl (Aux);
        Lee_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
        strcpy(mensajeRecibido, Cadena);
        printf ("Mensaje recibido: %s\n", Cadena);
        if (Longitud_Cadena<0){
            break;
        }
    }
    close (Socket_Con_Servidor);
}
void iniciarServidor(){
    /*
    * Descriptor del socket y buffer para datos
    */
     // descriptor
    u_long Longitud_Cadena = 0;
    u_long Aux;
    char Cadena[100];


    Socket_Con_Servidor = Abre_Conexion_Inet (); // retorna el numero del descriptor
    if (Socket_Con_Servidor < 0) // si el numero es menor que cero, no hay conexion con servidor
    {
        printf ("No puedo establecer conexion con el servidor\n");
        exit (-1);
    }
    else{ printf("Conectado correctamente!\n");}

    pthread_t hilo;
    pthread_create(&hilo,NULL,Comunicacion,NULL);


}

char *getMensaje(){
    return mensajeRecibido;
}
