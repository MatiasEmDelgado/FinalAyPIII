#ifndef CREDITO_H
#define CREDITO_H

#define MAX_CREDITOS 2

#define MIN_MONTO 5000
#define MAX_MONTO 500000

struct Credito { // a agregar: tipos de crédito, cuotas (con o sin interés?), etc...
	int monto;
};
// posible cambio: id por mail
void pedir_credito(int dni); // solicita un crédito dada la id y el dni del cliente
void pagar_credito(int dni, int monto); // paga parte o el total de un crédito del cliente id
void cancelar_credito(int dni, int index); // elimina uno o todos los créditos del cliente id
int mostrar_creditos(struct Cliente *cliente); // imprime los créditos del cliente pasado como parámetro, asumiendo que existan
int sumar_creditos(struct Cliente *cliente); // suma el monto de todos los creditos mayores a 0 de un cliente y retorna error si dicho total es mayor a MAX_MONTo

#endif
