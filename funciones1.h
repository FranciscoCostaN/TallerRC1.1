#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <string.h>

//Constantes del Programa
#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50

//Constantes de Recursos
#define NUM_RECURSOS 5
#define MAX_RECURSO_NOMBRE 20

//Prototipos de Funciones

//Funciones del Menu y Validaciones
void mostrarMenu();
int leerEntero(char* mensaje);
void leerCadena(char* mensaje, char* destino, int max);
int leerConfirmacion(char* mensaje);

// Funciones de Logica del Negocio
void inicializarDatos(char nombres[][MAX_NOMBRE],
                        int tiempos[],
                        int precios[],
                        int reqRecursos[][NUM_RECURSOS],
                        char nombresRecursos[][MAX_RECURSO_NOMBRE],
                        int almacenRecursos[]);

void listarProductos(char nombres[][MAX_NOMBRE], int tiempos[], int precios[], int numProductos);

//Funciones Principales de Calculo
void comprarPedido(char nombres[][MAX_NOMBRE],
                   int tiempos[],
                   int precios[],
                   int reqRecursos[][NUM_RECURSOS],
                   int numProductos,
                   char nombresRecursos[][MAX_RECURSO_NOMBRE],
                   int almacenRecursos[]);

void cotizarProduccion(char nombres[][MAX_NOMBRE],
                       int tiempos[],
                       int precios[],
                       int reqRecursos[][NUM_RECURSOS],
                       int numProductos,
                       char nombresRecursos[][MAX_RECURSO_NOMBRE]);

#endif