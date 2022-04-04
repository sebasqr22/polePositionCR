
#ifndef _SOCKET_CLIENTE_H
#define _SOCKET_CLIENTE_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>

/**
 * Abre un socket INET con un servidor que est� corriendo en Host_Servidor y que atienda
 * al servicio cuyo nombre es Servicio. 
 * Host_Servidor debe estar dado de alta en /etc/hosts.
 * Servicio debe estar dado de alta en /etc/services como tcp.
 */
int Abre_Conexion_Inet ();

#endif
