#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *leer(){
    FILE* archivo;
    char caracter;
    char todo[500] = "";

    archivo = fopen("readme.txt", "r");

    if(NULL == archivo){
        return "ERROR";
        printf("No se pudo leer el archivo\n");
    }

    do{
        caracter = fgetc(archivo);
        strcat(todo, caracter);

    }while(caracter != EOF);
    fclose(archivo);
    return todo;

}