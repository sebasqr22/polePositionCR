
#ifndef _SOCKET_H
#define _SOCKET_H

/** Lee Datos de tama�o Longitud de un socket cuyo descriptor es fd.
 * Devuelve el numero de bytes leidos o -1 si ha habido error */
int Lee_Socket (int fd, char *Datos, u_long Longitud);

/** Envia Datos de tama�o Longitud por el socket cuyo descriptor es fd.
 * Devuelve el n�mero de bytes escritos o -1 si ha habido error. */
int Escribe_Socket (int fd, char *Datos, u_long Longitud);

#endif
