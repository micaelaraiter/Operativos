/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "utils.h"

//TODO
/*
 * Recibe un paquete a serializar, y un puntero a un int en el que dejar
 * el tamaño del stream de bytes serializados que devuelve
 */
void* serializar_paquete(t_paquete* paquete, int *bytes) // *bytes es el valor que hay en ese puntero
{

	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer->size = sizeof(paquete->buffer->stream);

	void* stream = malloc(buffer->size);
	int offset = 0;

	memcpy(stream + offset, &(paquete->buffer->stream), sizeof(paquete->buffer->stream));
	offset += sizeof(paquete->buffer->stream);

	buffer->stream = stream;

	paquete = malloc(sizeof(paquete));
	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = buffer;


	void* a_enviar = malloc(buffer->size + sizeof(op_code));
	int sndoffset = 0;

	memcpy(a_enviar + sndoffset, &(paquete->codigo_operacion), sizeof(op_code));
	sndoffset += sizeof(op_code);
	memcpy(a_enviar + sndoffset, &(paquete->buffer->size), sizeof(int));
	sndoffset += sizeof(int);
	memcpy(a_enviar + sndoffset, paquete->buffer->stream, paquete->buffer->size);

	return a_enviar;

	free(a_enviar);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

typedef struct {
    int mensaje_lenght;
    char* mensaje;
} t_mensaje;

t_mensaje* deserializar_mensaje(t_buffer* buffer){
    t_mensaje* mensaje= malloc(sizeof(mensaje));

    void* stream = buffer->stream;

    memcpy(&(mensaje->mensaje_lenght), stream ,sizeof(int));
    stream += sizeof(int);
    memcpy(&(mensaje->mensaje), stream, mensaje->mensaje_lenght);
    stream += mensaje->mensaje_lenght;


    return mensaje;
}
int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

//TODO
void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_paquete* unPaquete = malloc(sizeof(t_paquete*));
	unPaquete->codigo_operacion = 1;
	unPaquete->buffer->size=sizeof(mensaje);
	unPaquete->buffer->stream = mensaje;

	void* a_enviar = serializar_paquete(unPaquete,unPaquete->buffer->size);
	send(socket_cliente,a_enviar, unPaquete->buffer->size + sizeof(int), 0);

	free(a_enviar);
	free(unPaquete->buffer->stream);
	free(unPaquete->buffer);
	free(unPaquete);

}


//TODO
char* recibir_mensaje(int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(paquete));
	recv(socket_cliente,&(paquete->codigo_operacion),sizeof(op_code),0);
	recv(socket_cliente, &(paquete->buffer->size), sizeof(int), 0);
	recv(socket_cliente, &(paquete->buffer->stream), paquete->buffer->size, 0);

	op_code CODIGO = paquete->codigo_operacion;
	t_mensaje* unMensaje = deserializar_mensaje(paquete->buffer);

	printf("%d",unMensaje->mensaje);
	return unMensaje->mensaje;

	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);

}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}


