#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>


void fail(char *mensaje){
    perror(mensaje);
    exit(0);
}

void iniciarServidor(int puerto){
    int cliente;
    struct hostent *servidor;

    cliente = socket(AF_INET, SOCK_STREAM, 0);

    if (cliente < 0){
        fail("NO SE ABRIO EL PUERTO.");
    }

    //servidor = gethostbyname()
}
int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);

    for(int i = 0; i < argc; i++)
        printf("%s\n", argv++);

    return 0;
}