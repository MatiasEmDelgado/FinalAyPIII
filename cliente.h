#ifndef CLIENTE_H
#define CLIENTE_H

#include "credito.h"

struct Cliente {
	char nombre[24];
	char apellido[24];
	char mail[24];
	int edad;
	int dni;
	int id;
	int creditos_usados;
	struct Credito credito[MAX_CREDITOS];
	struct Cliente *next;
};

extern struct Cliente *head; // cabeza de la lista enlazada
extern int client_count; // número de clientes

int buscar_nombre(char nombre[], char apellido[]); // busca uno o mas usuarios por un nombre, retorna 1 en caso de exito y 0 en caso de fallo
int buscar_edad(int edad_inicial, int edad_final);
void mostrar_cliente(struct Cliente *cliente);

void pedir_datos(void);	// pide al usuario que ingrese un nuevo cliente
void agregar_cliente(char nombre[], char apellido[], int edad, int dni, char mail[], int credito_1, int credito_2); // agrega un nuevo cliente a la lista enlazada
void listar_clientes(int n); // muestra la lista de clientes desde 0 a n
void borrar_cliente(int id); // elimina un cliente del sistema (dada la id), liberando la memoria reservada por malloc
struct Cliente *buscar_cliente(int id); // busca un usuario en el que id y dni coincidan y retorna NULL si no lo encuentra
struct Cliente *buscar_cliente_para_credito(int id); // busca un usuario en el que id y dni coincidan y retorna NULL si no lo encuentra
int obtener_nueva_id(); // obtiene una id que no esté en uso para nuevos clientes
int buscar_id(int id); // recorre la lista enlazada buscando una id de cliente que coincida con el parámetro id. retorna 0 en caso de error. -- cambiar por buscar_cliente

#endif
