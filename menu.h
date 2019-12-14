#ifndef MENU_H
#define MENU_H

typedef enum { PRINCIPAL = 1, CLIENTE, CREDITO } Menu;

void mostrar_menu(Menu menu);
void menu_principal(void);
void menu_cliente(void);
void menu_credito(void);
void menu_busqueda_cliente(void);

#endif
