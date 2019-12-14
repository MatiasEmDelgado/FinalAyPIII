#ifndef CREDITO_H
#define CREDITO_H

#define MAX_CREDITOS 2

#define MIN_MONTO 5000
#define MAX_MONTO 500000

struct Credito { // a agregar: tipos de cr�dito, cuotas (con o sin inter�s?), etc...
	int monto;
};
// posible cambio: id por mail
void pedir_credito(int dni); // solicita un cr�dito dada la id y el dni del cliente
void pagar_credito(int dni, int monto); // paga parte o el total de un cr�dito del cliente id
void cancelar_credito(int dni, int index); // elimina uno o todos los cr�ditos del cliente id
int mostrar_creditos(struct Cliente *cliente); // imprime los cr�ditos del cliente pasado como par�metro, asumiendo que existan
int sumar_creditos(struct Cliente *cliente); // suma el monto de todos los creditos mayores a 0 de un cliente y retorna error si dicho total es mayor a MAX_MONTo

#endif
