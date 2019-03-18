/***************************************************************************
                          main.c  -  client
                             -------------------
    begin                : lun feb  4 16:00:04 CET 2002
    copyright            : (C) 2002 by A. Moreno
    email                : amoreno@euss.es
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


#define REQUEST_MSG_SIZE	1024
#define REPLY_MSG_SIZE		500
#define SERVER_PORT_NUM		5001



 /************************
*
*
* tcpClient
*
*
*/
void ImprimirMenu(void)
{
	printf("\n\nMenu:\n");
	printf("--------------------\n");
	printf("1: Opció 1\n");
	printf("2: Opció 2\n");
	printf("3: Opció 3\n");
	printf("4: Opció 4\n");
	printf("5: Opció 5\n");
	printf("6: Opció 6\n");
	printf("0: Sortir\n");
	printf("--------------------\n");
}
int main(int argc, char *argv[]){
	struct sockaddr_in	serverAddr;
	char	    serverName[] = "127.0.0.1"; //Adreça IP on est� el servidor
	int			sockAddrSize;
	int			sFd;
	int			mlen;
	int 		result;
	char		buffer[256];
	int 		opcio = -1;
	char param[4];

	/*Crear el socket*/
	sFd=socket(AF_INET,SOCK_STREAM,0);

	/*Construir l'adreça*/
	sockAddrSize = sizeof(struct sockaddr_in);
	bzero ((char *)&serverAddr, sockAddrSize); //Posar l'estructura a zero
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons (SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = inet_addr(serverName);

	/*Conexió*/
	result = connect (sFd, (struct sockaddr *) &serverAddr, sockAddrSize);
	if (result < 0)
	{
		printf("Error en establir la connexió\n");
		exit(-1);
	}
	printf("\nConnexió establerta amb el servidor: adreça %s, port %d\n",	inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

	
	while (opcio != '0'){ //opcio = 0 => sortir
		opcio = (int) getchar();
		switch(opcio){
		case (int)'1': //start/stop
			printf("Heu seleccionat l'opció 1\n");
			printf("Escriu els parametres: ");
			scanf("%s", param);
			
			
			/*Enviar*/
			strcpy(buffer, "{M");
			printf("Marxa(1)/Parada(0)\n");
			scanf("%s", &param[2]);
			printf("Temps (posar un 0 als decimals)\n");
			scanf("%s, %s", &param[3], &param[4]);
			printf("Número de mostres\n");
			scanf("%s", &param[5]);
			strcat(buffer, param);
			strcat(buffer, "}");
			result = write(sFd, buffer, strlen(buffer));
			printf("Missatge enviat a servidor(bytes %d): %s\n",	result, buffer);


			/*
			strcpy(buffer, "{M"); //Copiar missatge a buffer
			strcat(buffer, param);
			strcat(buffer, "}");
			result = write(sFd, buffer, strlen(buffer));
			printf("Missatge enviat a servidor(bytes %d): %s\n",	result, buffer);*/

			/*Rebre*/
			result = read(sFd, buffer, 256);
			printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
			ImprimirMenu();
			break; 
			
		case (int)'2':
			printf("Heu seleccionat l'opció 2\n");
			/*Enviar*/
			strcpy(buffer, "{U"); //Copiar missatge a buffer
			strcat(buffer, "}");
			result = write(sFd, buffer, strlen(buffer));
			printf("Missatge enviat a servidor(bytes %d): %s\n",	result, buffer);

			/*Rebre*/
			result = read(sFd, buffer, 256);
			printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
			ImprimirMenu();
		break;
		case (int)'3':
			printf("Heu seleccionat l'opció 3\n");
			/*Enviar*/
			strcpy(buffer, "{X}"); //Copiar missatge a buffer
			result = write(sFd, buffer, strlen(buffer));
			printf("Missatge enviat a servidor(bytes %d): %s\n",	result, buffer);
/*Rebre*/
			result = read(sFd, buffer, 256);
			printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
			ImprimirMenu();
		break;
		case (int)'4': //demanar minim
			printf("Heu seleccionat l'opció 4\n");
			/*Enviar*/
			strcpy(buffer, "{Y}"); //Copiar missatge a buffer
			result = write(sFd, buffer, strlen(buffer));
			printf("Missatge enviat a servidor(bytes %d): %s\n",	result, buffer);

/*Rebre*/
			result = read(sFd, buffer, 256);
			printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
			ImprimirMenu();
		break;
		//case (int)'5': //reset
			printf("Heu seleccionat l'opció 5\n");
			/*Enviar*/
			/*Enviar*/
			strcpy(buffer, "{R}"); //Copiar missatge a buffer
			result = write(sFd, buffer, strlen(buffer));
			printf("Missatge enviat a servidor(bytes %d): %s\n",	result, buffer);

/*Rebre*/
			result = read(sFd, buffer, 256);
			printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
			ImprimirMenu();
		break;
		case (int)'6': //demanar comptador
			printf("Heu seleccionat l'opció 6\n");
			/*Enviar*/
			strcpy(buffer, "{B}"); //Copiar missatge a buffer
			result = write(sFd, buffer, strlen(buffer));
			printf("Missatge enviat a servidor(bytes %d): %s\n",	result, buffer);

/*Rebre*/
			result = read(sFd, buffer, 256);
			printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
			ImprimirMenu();
		break;
		case 0x0a:  
		break;

		default:
			printf("Opció incorrecta \n");
			printf("He llegit 0x%hhx \n",opcio);
			break;
		
		}
	}

	/*Tancar el socket*/
	close(sFd);

	return 0;
	}
