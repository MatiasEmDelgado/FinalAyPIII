#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "menu.h"
#include "archivo.h"

int main(void)
{	
	cargar_clientes();
	mostrar_menu(PRINCIPAL);
	return 0;
}
