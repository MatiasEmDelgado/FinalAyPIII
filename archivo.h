#ifndef ARCHIVO_H
#define ARCHIVO_H

extern int line_count;

void guardar_clientes(void); // guarda los datos de todos los clientes registrados al salir del programa o ser llamado explicitamente durante el mismo.
void cargar_clientes(void); // carga los clientes guardados en clientes.csv

#endif
