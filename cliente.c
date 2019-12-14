#include <stdio.h>
#include <Windows.h> 
#include <string.h>
#include "cliente.h"
#include "archivo.h"
#include "menu.h"

struct Cliente *head = NULL;
int client_count = 0;

void agregar_cliente(char nombre[], char apellido[], int edad, int dni, char mail[], int credito_1, int credito_2)
{
	struct Cliente *cliente;
	cliente = (struct Cliente*)malloc(sizeof(struct Cliente));
	if(cliente) { 
		strcpy(cliente->nombre, nombre);
		strcpy(cliente->apellido, apellido);
		cliente->edad = edad;
		cliente->dni = dni;
		cliente->id = obtener_nueva_id();
		strcpy(cliente->mail, mail);
		cliente->credito[0].monto = credito_1;
		cliente->credito[1].monto = credito_2;
		// cliente se transforma en la cabeza de la lista luego de que cliente->next apunte a la cabeza anterior
		cliente->next = head; 
		head = cliente;
		++client_count;
	}
	else {
		printf("Error: out of memory\n");
		return;
	}
}

void pedir_datos(void)
{
	char nombre[24];
	char apellido[24];
	int edad = 0;
	int dni = 0;
	char mail[24];
	printf("     Nombre y apellido: ");
	if(scanf("%s %s", nombre, apellido)) 
	printf("\n\n");
		printf("     Edad: ");
	if(!scanf("%d", &edad)) return;
		printf("\n\n");
		printf("     DNI: ");
	if(!scanf("%d", &dni)) return;
		printf("\n\n");
		printf("     Mail: ");
	if(scanf("%s", mail)) 
		agregar_cliente(nombre, apellido, edad, dni, mail, 0, 0); // agrega un nuevo cliente. inicializa creditos en 0
		
	system("cls");
	printf("\n\n\n     Cliente registrado.\n\n\n");
	guardar_clientes();
	printf("\n\n");
	menu_cliente();
}

void listar_clientes(int n)
{
	struct Cliente *aux = head;
	if(aux == NULL) {
		printf("     No se encontraron clientes registrados en el sistema.\n\n");
		return;
	}
	system("cls");
	printf("                          Final Algoritmos y Programacion III\n\n\n\n");
	printf("\n\n     Listado de clientes:\n\n");
	int count = 0;
	while(aux != NULL && count < n) {
		printf("     Cliente:\n\n");
		mostrar_cliente(aux);
		aux = aux->next;
		++count;
	}
	printf("     1- Registrar cliente\n\n     2- Mostrar clientes\n\n     3- Eliminar cliente\n\n     4- Buscar cliente\n\n     5- Volver al menu principal\n\n");
	printf("     Ingrese una nueva opcion\n\n");
}

struct Cliente *buscar_cliente(int dni)
{
	struct Cliente *aux = head;
	if(aux == NULL) {
		printf("     No se encontraron clientes registrados en el sistema.\n\n");
		return NULL;
	}
	while(aux != NULL) {
		if(aux->dni == dni)
			return aux;
		aux = aux->next;
	}
	printf("No se encontro ningun cliente con el DNI que usted a ingresado.\n\n");
	return NULL;
}

struct Cliente *buscar_cliente_para_credito(int dni)
{
	struct Cliente *aux = head;
	if(aux == NULL) {
		printf("     No se encontraron clientes registrados en el sistema.\n\n");
		return NULL;
	}
	while(aux != NULL) {
		if(aux->dni == dni)
			return aux;
		aux = aux->next;
	}
	system("cls");
	printf("                          Final Algoritmos y Programacion III\n\n\n\n");
	printf("No se encontro ningun cliente con el ID que usted a ingresado.\n\n");
	printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
	printf("     Ingrese una nueva opcion\n\n");
	return NULL;
}

void borrar_cliente(int id)
{
	if(head == NULL) {
		printf("     No se encontraron clientes registrados en el sistemas.\n\n");
		return;
	}
	if(!buscar_id(id)) {
		system("cls");
		printf("                          Final Algoritmos y Programacion III\n\n\n\n");
		printf("No se encontro ningun cliente con el ID que usted a ingresado.\n\n\n");
		printf("     1- Registrar cliente\n\n     2- Mostrar clientes\n\n     3- Eliminar cliente\n\n     4- Buscar cliente\n\n     5- Volver al menu principal\n\n");
		printf("     Ingrese una nueva opcion\n\n");
		return;
	}
	if(id == head->id) {
		struct Cliente *temp = head->next;
		//head->next = NULL; // test
		free(head);
		head = temp;
		--client_count; // reduzco el contador de clientes en 1
		printf("\n\n     Se ha eliminado el cliente con el id ID %d \n\n", id);
		return;
	}
	struct Cliente *aux = head;
	struct Cliente *temp = head->next; // aux va siempre delante de temp
	int count = 0;
	while(aux != NULL) {
		if(temp->id == id) {
			aux->next = temp->next; // temp pasa a apuntar a la referencia next de aux para mantener la lista conectada
			free(temp);
			--client_count;
			printf("\n\n     Se ha eliminado el cliente con el id ID %d \n\n", id);
			return;
		}
		aux = aux->next;
		temp = temp->next;
	}
}

int obtener_nueva_id()
{
	if(client_count == 0) return 1; // si la lista esta vacia la id es 1
	return head->id + 1;
}

int buscar_id(int id)
{
	if(id < 1) return 0;
	struct Cliente *aux = head;
	while(aux != NULL) {
		if(aux->id == id) return id;
		aux = aux->next;
	}
	return 0;
}

int buscar_nombre(char nombre[], char apellido[])
{
	struct Cliente *aux = head;
	int count = 0;
	if(aux == NULL) {
		printf("     No se encontraron clientes registrados en el sistema.\n\n");
		return 0;
	}
	while(aux != NULL) {
		if(apellido[0] == '0') {
			if((strcmp(aux->nombre, nombre) == 0)) {
				printf("     Cliente:\n\n");
				mostrar_cliente(aux);
				++count;
			}
		}
		else if((strcmp(aux->nombre, nombre) == 0) && strcmp(aux->apellido, apellido) == 0) {
			printf("     Cliente:\n\n");
			mostrar_cliente(aux);
			++count;
		}
		aux = aux->next;
	}
	if(count > 0) { 
		printf("     Clientes encontrados: %d\n\n", count);
		return 1;
	}
	else {
		printf("     No se encontro el cliente.\n\n");
		return 0;
	}
}

int buscar_edad(int edad_inicial, int edad_final)
{
	struct Cliente *aux = head;
	int count = 0;
	if(aux == NULL) {
		printf("     No se encontraron clientes registrados en el sistema.\n\n");
		return 0;
	}
	if(edad_inicial > edad_final) {
		int temp = edad_final;
		edad_final = edad_inicial;
		edad_inicial = temp;
	}
	while(aux != NULL) {
		if(aux->edad >= edad_inicial && aux->edad <= edad_final) {
			++count;
			if (count == 1) {
				printf("\n\n     Listado de clientes:\n\n");
			}
			printf("     Cliente:\n\n");
			mostrar_cliente(aux);
		}
		aux = aux->next;
	}
	if(count > 0) {
		printf("     Clientes encontrados: %d\n\n", count);
		return 1;
	}
	else {
		printf("     No se encontraron clientes en el rango de edad [%d-%d]\n\n", edad_inicial, edad_final);
		return 0;
	}
}

void mostrar_cliente(struct Cliente *cliente)
{	
	printf("               Id: %d\n\n               Nombre: %s %s\n\n               Edad: %d\n\n               DNI: %d\n\n               Email: %s\n\n", cliente->id, cliente->nombre, cliente->apellido, cliente->edad, cliente->dni, cliente->mail);
	for(int i = 0; i < MAX_CREDITOS; ++i) {
		if(cliente->credito[i].monto > 0) {
			int num_credito = i + 1;
			printf("\n\n");	
			printf("               Credito %i: %d\n\n", num_credito, cliente->credito[i].monto);
		}
	}
	printf("\n\n");
}
