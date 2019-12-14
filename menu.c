#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "menu.h"
#include "cliente.h"
#include "archivo.h"

void mostrar_menu(Menu menu)
{
	switch(menu) {
	case PRINCIPAL:
		system("cls");
		menu_principal();
		break;
	case CLIENTE:
		system("cls");
		menu_cliente();
		break;
	case CREDITO:
		system("cls");
		menu_credito();
		break;
	default:
		printf("Error: Menu invalido.\n");
		break;
	}
}

void menu_principal(void)
{
	int salir = 0;
	while(!salir) {
		system("cls");
		printf("                          Final Algoritmos y Programacion III\n\n\n\n");
		printf("     Bienvenido al Sitestema de gestion de creditos\n\n\n");
		printf("     Introduzca el numero de opcion para acceder al menu deseado:\n\n\n");
		printf("     1- Gestionar clientes\n\n     2- Gestionar Creditos\n\n     3- Salir\n\n");
		int opcion = 0;
		if(scanf("     %d", &opcion) < 1) {
			printf("     Entrada invalida.\n\n");
			return;
		}
		switch(opcion) {
		case 1:
			mostrar_menu(CLIENTE);
			break;
		case 2:
			mostrar_menu(CREDITO);
			break;
		case 3:
			guardar_clientes();
			salir = 1;
			system("pause");
			break;
		default:
			printf("     Usted ha ingresado una opcion invalida, por favor, intente de nuevo.\n\n");
			break;
		}
	}
}

void menu_cliente(void)
{
	int volver = 0;
	printf("                          Final Algoritmos y Programacion III\n\n\n\n");
	printf("     1- Registrar cliente\n\n     2- Mostrar clientes\n\n     3- Eliminar cliente\n\n     4- Buscar cliente\n\n     5- Volver al menu principal\n\n");
	while(!volver) {
		int opcion = 0;
		if(scanf("     %d", &opcion) < 1) {
			printf("     Entrada invalida.\n\n");
			exit(1);
		}
		switch(opcion) {
		case 1:
			pedir_datos();
			break;
		case 2: {
			int n = 0;
			if(client_count == 0) {
				printf("     No se encontraron clientes registrados en el sistema.\n\n");
				break;
			}
			printf("     Ingrese el numero de clientes a mostrar (max %d): ", client_count);
			if(scanf("     %d", &n)) {
				if(n > client_count || n < 1) {
					printf("\n\n     El numero de clientes a mostrar no puede ser menor a 1 o mayor al total de clientes (%d)\n\n", client_count);
					break;
				}
			}
			listar_clientes(n);
			break;
		}
		case 3: {
			int id = 0;
			printf("     Introduzca el ID del cliente a eliminar: ");
			if(scanf("     %d", &id)) {
				borrar_cliente(id);
				guardar_clientes();
			}
			break;
		}
		case 4:
			menu_busqueda_cliente();
			break;
		case 5:
			volver = 1; // detiene el loop del menú de clientes y retorna automáticamente al menú principal
			break;
		default:
			printf("     Usted ha ingresado una opcion invalida, por favor, intente de nuevo.\n\n");
			break;
		}
	}
}

void menu_credito(void)
{
	int volver = 0;
	printf("                          Final Algoritmos y Programacion III\n\n\n\n");
	
	printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n     4- Volver al menu principal\n\n");
	while(!volver) {
		int opcion = 0;
		if(!scanf("     %d", &opcion)) return;
		switch(opcion) {
		case 1: {
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			int dni;
			printf("     Ingrese el dni del cliente que solicita el credito: ");
			if(scanf("     %d", &dni))
				printf("\n\n");
				pedir_credito(dni);
				
			guardar_clientes();
			break;
		}
		case 2: {
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			int dni, monto;
			printf("     Ingrese el dni del cliente para el cual quiere registrar el pago: ");
			if(scanf("     %d", &dni))
				printf("\n\n");
				printf("     Ingrese el monto del pago: ");
			if(scanf("     %d", &monto))
				printf("\n\n");
				pagar_credito(dni, monto);
			guardar_clientes();	
			break;
		}
		case 3: {
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			int dni, index;
			printf("     Ingrese el dni del cliente para el cual quiere cancelar creditos: ");
			if(scanf("     %d", &dni))
				printf("\n\n");
				printf("     Indique el numero de credito que desea cancelar, o bien, indique 0 para cancelar todos los creditos activos: ");
			if(scanf("     %d", &index))
				cancelar_credito(dni, index);
				printf("     1- Pedir credito\n\n     2- Pagar credito\n\n     3- Cancelar credito\n\n    4- Volver al menu principal\n\n");
			break;
			guardar_clientes();
		}
		case 4:
			volver = 1;
			break;
		default:
			printf("     Usted ha ingresado una opcion invalida, por favor, intente de nuevo.\n\n");
			break;
		}
	}
}

void menu_busqueda_cliente(void)
{
	int volver = 0;
	while(!volver) {
		printf("     Escoja el metodo de busqueda a utilizar:\n\n     1- Buscar por nombre\n\n     2- Buscar por rango de edad\n\n     3- Volver al menu para gestion de Clientes.\n\n");
		int opcion = 0;
		if(!scanf("     %d", &opcion)) return;
		switch(opcion) {
		case 0:
			volver = 1;
			break;
		case 1: {
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			char nombre[24];
			char apellido[24];
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			printf("     Ingrese el nombre del cliente: ");
			if(scanf(     "%s", nombre))
				printf("\n\n");
				printf("     Ingrese el apellido del cliente, o bien precione 0 para continuar: ");
				printf("\n\n");
			if(scanf("     %s", apellido))
				buscar_nombre(nombre, apellido);
			break;
		}
		case 2: {
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			int edad_inicial, edad_final;
			printf("     Ingrese la edad minima: ");
			printf("\n\n");
			if(scanf("     %d", &edad_inicial))
				printf("     Ingrese la edad maxima: ");
				printf("\n\n");
			if(scanf("     %d", &edad_final))
				buscar_edad(edad_inicial, edad_final);
			break;
		}
		case 3:
			system("cls");
			printf("                          Final Algoritmos y Programacion III\n\n\n\n");
			printf("     Busqueda cancelada.\n\n\n");
			printf("     1- Registrar cliente\n\n     2- Mostrar clientes\n\n     3- Eliminar cliente\n\n     4- Buscar cliente\n\n     5- Volver al menu principal\n\n");
			printf("     Ingrese una nueva opcion\n\n");
			volver = 1;
			break;
		default:
			printf("     Usted ha ingresado una opcion invalida, por favor, intente de nuevo.\n\n");
			break;
		}
	}
}
