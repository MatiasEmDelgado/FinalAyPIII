#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cliente.h"
#include "archivo.h"

void guardar_clientes(void)
{
	struct Cliente *cliente = head;
	if(cliente == NULL) {
		printf("     No no se encontraron clientes registrados en el sistema.\n\n");
		return;
	}
	FILE* archivo = fopen("clientes.csv", "w");
	int count = 0;
	if(archivo != NULL) {
		while(cliente != NULL) {
			fprintf(archivo, "%s,%s,%d,%d,%s,%d,%d,%d\n\n"
				, cliente->nombre, cliente->apellido, cliente->edad, cliente->dni, cliente->mail
				, cliente->credito[0].monto, cliente->credito[1].monto);
			++count;
			cliente = cliente->next;
		}
		fclose(archivo);
	}
	else {
		printf("     No se pudo abrir la base de datos.\n\n");
		exit(1);
	}
	printf("     Se ha actualizado la base de datos (%d clientes guardados)\n\n", count);
}

void cargar_clientes(void)
{
	//int id;
	char nombre[24];
	char apellido[24];
	int edad;
	int dni;
	char mail[24];
	int credito[MAX_CREDITOS];
	//////////////////////////////
	char *token;
	char line[128];
	char s[] = ",";
	FILE *archivo = fopen("clientes.csv", "r");
	if(archivo != NULL) {
		while(fgets(line, sizeof(line), archivo) != NULL) {
			if(line[0] != '\n') {
				token = strtok(line, s); // nombre
				strcpy(nombre, token);
				token = strtok(NULL, s); // apellido
				strcpy(apellido, token);
				token = strtok(NULL, s); // edad
				edad = atoi(token);
				token = strtok(NULL, s); // dni
				dni = atoi(token);
				token = strtok(NULL, s); // mail.
				strcpy(mail, token);
				token = strtok(NULL, s); // primer credito
				credito[0] = atoi(token);
				token = strtok(NULL, s); // segundo credito
				credito[1] = atoi(token);
				agregar_cliente(nombre, apellido, edad, dni, mail, credito[0], credito[1]);
			}
			else { 
				continue;
			}
		}
		fclose(archivo);
	}
}
