#include <stdio.h>
#include <stdlib.h>
#include "credito.h"
#include "cliente.h"

void pedir_credito(int dni)
{
	struct Cliente *cliente;
	if((cliente = buscar_cliente_para_credito(dni)) != NULL) { 
		if(cliente->creditos_usados == MAX_CREDITOS || ((sumar_creditos(cliente)) >= MAX_MONTO)) {
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			if(cliente->creditos_usados == MAX_CREDITOS) {
				printf("     El cliente ha superado el limite de creditos disponibles\n\n");
			} else if ((sumar_creditos(cliente)) >= MAX_MONTO) {
				printf("     El cliente ha superado el limite de deuda, las sumas de sus creditos supera al maximo valor permitido de %d\n\n", MAX_MONTO);
			}
				
			printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
			printf("     Ingrese una nueva opcion \n\n");
			return;
		}
		int monto;
		printf("     Ingrese el monto solicitado: ");
		while(1) {
			if(!scanf("%d", &monto)) return;
			printf("\n\n");
			if(monto > MAX_MONTO || monto < MIN_MONTO) {
				printf("     El monto del prestamo debe ser de al menos %d y no puede superar los %d, ingrese el monto solicitado nuevamente\n\n", MIN_MONTO, MAX_MONTO);
			} else if((sumar_creditos(cliente) + monto) > MAX_MONTO){
				printf("     No se le puede otorgar esa suma al cliente debido a que el cliente deberia mas de lo que el sistema permite. Un cliente no puede deber mas de: %d\n\n", MAX_MONTO);
			 	printf("     Ingrese el monto solicitado nuevamente: ");
			} else {
				break;
			}
		}
		for(int i = 0; i < MAX_CREDITOS; ++i) {
			if(cliente->credito[i].monto == 0) {
				cliente->credito[i].monto = monto;
				cliente->creditos_usados += 1;
				system("cls");
				printf("                          Final Algoritmos y Programacion III\n\n\n\n");
				printf("     Se ha otorgado un credito de %d al cliente %s %s DNI: %d.\n\n", monto, cliente->nombre, cliente->apellido, cliente->dni);
				printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
				printf("     Ingrese una nueva opcion \n\n");
				break;
			}
		}
	}
}

void pagar_credito(int dni, int monto)
{
	struct Cliente *aux = NULL;
	if((aux = buscar_cliente_para_credito(dni)) != NULL) {
		if(!mostrar_creditos(aux)) {
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			printf("     El cliente no tiene creditos activos.\n\n");
			printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
			printf("     Ingrese una nueva opcion ");
			printf("\n\n");
			return;
		}
		int index = 0;
		printf("     Ingrese el numero de credito para el cual quiere registrar el pago o 0 para cancelar: ");
		if(!scanf("%d", &index)) return;
		if(index == 0) { 
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			printf("     Operacion cancelada.\n\n");
			printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
			return;
		}
		if(index < 1 || index > MAX_CREDITOS) {
			printf("\n\n");
			printf("     El numero de creditos posible para un Cliente no supera la cantidad de 3\n\n", MAX_CREDITOS);
			printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
			printf("     Ingrese una nueva opcion ");
			printf("\n\n");
			return;
		}
		if(aux->credito[index-1].monto == 0) {
			printf("\n\n");
			printf("     El numero de credito ingresado no se encuentra para este cliente.\n\n");
			printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
			printf("     Ingrese una nueva opcion ");
			printf("\n\n");
			return;
		}
		if(aux->credito[index-1].monto - monto < 0) {
			printf("\n\n");
			printf("     El monto ingresado supera el monto del credito, el sistema no permite registrar creditos con saldos negativos.\n\n");
			printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
			printf("     Ingrese una nueva opcion ");
			printf("\n\n");
			return;
		}
		aux->credito[index-1].monto -= monto;
		if(aux->credito[index-1].monto == 0){
			aux->creditos_usados -= 1;
		}
		printf("\n\n");
		printf("     %d Se ha registrado el pago, el saldo de la deuda es: %d\n\n", monto, aux->credito[index-1].monto);
		printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
	}
}

void cancelar_credito(int dni, int index)
{
	struct Cliente *aux = NULL;
	if((aux = buscar_cliente(dni)) != NULL) {
		if(!mostrar_creditos(aux)) {
			printf("El cliente no tiene creditos activos.\n\n");
			return;
		}
		if(index == 0) {
			int count = 0;
			for(int i = 0; i < MAX_CREDITOS; ++i) {
				if(aux->credito[i].monto > 0) {
					aux->credito[i].monto = 0;
					++count;
				}
			}
			printf("     %d Creditos cancelados.\n\n", count);
		}
		else if(index >= 1 && index <= MAX_CREDITOS) {
			if(aux->credito[index-1].monto > 0)
				aux->credito[index-1].monto = 0;
			printf("     Credito cancelado.\n\n");
		}
		else {
			printf("     Numero de credito invalido. El Cliente solo puede tener 3 creditos, introduzca el numero de credito que desea cancelar\n\n", MAX_CREDITOS);
			return;
		}
	}
}

int mostrar_creditos(struct Cliente *cliente)
{
	int count = 0;
	printf("     Cliente:\n\n");
	mostrar_cliente(cliente);
	printf("\n\n");
	for(int i = 0; i < MAX_CREDITOS; ++i) {
		if(cliente->credito[i].monto > 0) {
			int num_credito = i + 1;
			printf("     Credito %i- $%d\n\n", num_credito, cliente->credito[i].monto);
			++count;
		}
	}
	if(count > 0) {
		printf("     Creditos activos: %d\n\n", count);
		return 1;
	}
	else {
		return 0;
	}
}

int sumar_creditos(struct Cliente *cliente)
{
	int aux = 0;
	for(int i = 0; i < MAX_CREDITOS; ++i) {
		if(cliente->credito[i].monto > 0)
			aux += cliente->credito[i].monto;
	}
	return aux;
}
