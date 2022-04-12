/**
 * METODO CLIENTE PARA LA CONEXION CON EL SERVIDOR (RECIVE Y ENVIA MENSAJES)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "/home/user/Escritorio/Repos GitHub/polePositionCR/Cliente-Servidor-Java-C/Cliente-C/Socket_Cliente.c"
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "/home/user/Escritorio/Repos GitHub/polePositionCR/Cliente-Servidor-Java-C/Cliente-C/Socket.c"


char mensajeRecibido[100] = "";
int numberH = 0, numberT = 0, numberV = 0, tiempoLimite = 0;
bool cerrarVentana = false;
int Socket_Con_Servidor;

/**
 * @brief Funcion para enviar datos
 * 
 * @param mensaje Mensaje a enviar
 */
void enviarMensaje(char mensaje[50]){
    u_long Longitud_Cadena = strlen(mensaje)+1;
    u_long Aux = htonl (Longitud_Cadena);
    Escribe_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(Longitud_Cadena));
    Escribe_Socket (Socket_Con_Servidor, mensaje, Longitud_Cadena);
    printf ("Mensaje enviado: %s\n", mensaje); // #tipo-X(distancia)-Y
}
/**
 * @brief Se espera a que llenguen mensajes del cliente
 * 
 * @param valor 
 * @return void* 
 */
void *RecibirDatos(void *valor){
    printf("Se inicia el segundo hilo recibir.........\n");
    u_long Longitud_Cadena = 0;
    u_long Aux;
    char dist[100];
    int contGuion = 0;
    char Cadena[100];

    while(1){
        Lee_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(int));
        Longitud_Cadena = ntohl (Aux);
        Lee_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
        strcpy(mensajeRecibido, Cadena);
        printf ("Mensaje recibido: %s\n", Cadena);

        // Si se quiere crear un hueco
        if (Cadena[0] == '2')
        {
            for (int i = 2; i < strlen(Cadena); i++){
                if(Cadena[i] == '-')
                    break;
                else
                    dist[i-2] = Cadena[i];
            }
            int numero = 0;
            int potencia = strlen(dist);
            for (int i = 0; i < strlen(dist); i++)
            {
                int ia = dist[i] - '0';
                numero += pow(10,potencia-1)*ia;
                potencia--;
            }
            numberH = numero;
        }
        // Si se quiere crear una vida
        else if (Cadena[0] == '3')
        {
            for (int i = 2; i < strlen(Cadena); i++){
                if(Cadena[i] == '-')
                    break;
                else
                    dist[i-2] = Cadena[i];
            }
            int numero = 0;
            int potencia = strlen(dist);
            for (int i = 0; i < strlen(dist); i++)
            {
                int ia = dist[i] - '0';
                numero += pow(10,potencia-1)*ia;
                potencia--;
            }
            numberV = numero;
        }
        // Si se quiere crear un turbo
        else if (Cadena[0] == '4')
        {
            for (int i = 2; i < strlen(Cadena); i++){
                if(Cadena[i] == '-')
                    break;
                else
                    dist[i-2] = Cadena[i];
            }
            int numero = 0;
            int potencia = strlen(dist);
            for (int i = 0; i < strlen(dist); i++)
            {
                int ia = dist[i] - '0';
                numero += pow(10,potencia-1)*ia;
                potencia--;
            }
            numberT = numero;
        }
        printf("tiempo limite: %d\n", tiempoLimite);
        tiempoLimite++;
        if(tiempoLimite >= 100){
            printf("Se perdio la conexion con el servidor...\n");
            cerrarVentana = true;
            break;
        }
            
        if (Longitud_Cadena<0){
            break;
        }
    }
    close (Socket_Con_Servidor);
}


/**
 * @brief Se inicia la conexion con el servidor
 */
void iniciarServidor(){
    /*
    * Descriptor del socket y buffer para datos
    */
     // descriptor


    Socket_Con_Servidor = Abre_Conexion_Inet (); // retorna el numero del descriptor
    if (Socket_Con_Servidor < 0) // si el numero es menor que cero, no hay conexion con servidor
    {
        printf ("No puedo establecer conexion con el servidor\n");
        exit (-1);
    }
    else{ printf("Conectado correctamente!\n");}

    pthread_t hiloRecibir;
    pthread_create(&hiloRecibir,NULL,RecibirDatos,NULL);
}

char *getMensaje(){
    return mensajeRecibido;
}
// Retorna la posicion del hueco
int getNumeroH(){
    return numberH;
}
// Retorna la posicion del turbo
int getNumeroT(){
    return numberT;
}
// Retorna la posicion de la vida
int getNumeroV(){
    return numberV;
}
bool getConexion(){
    return cerrarVentana;
}