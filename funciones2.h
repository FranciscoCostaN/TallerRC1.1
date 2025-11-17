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

//Constantes de la Matriz
//Estas constantes definen que columna es cada cosa
#define COL_TIEMPO 0
#define COL_PRECIO 1
#define COL_CHIPS 2
#define COL_PLASTICO 3
#define COL_PANTALLAS 4
#define COL_METAL 5
#define COL_LIQUIDO 6
#define NUM_ATRIBUTOS 7 //7 columnas en total (0 a 6)

//Prototipos de Funciones

//Funciones del Menu y Validaciones
void mostrarMenu();
int leerEntero(char* mensaje);
void leerCadena(char* mensaje, char* destino, int max);
int leerConfirmacion(char* mensaje);

//Funciones de Logica del Negocio
void inicializarDatos(char nombres[][MAX_NOMBRE],
                        int datosProductos[][NUM_ATRIBUTOS],
                        char nombresRecursos[][MAX_RECURSO_NOMBRE],
                        int almacenRecursos[]);

void listarProductos(char nombres[][MAX_NOMBRE],
                     int datosProductos[][NUM_ATRIBUTOS],
                     int numProductos);

//Funciones Principales de Calculo
void comprarPedido(char nombres[][MAX_NOMBRE],
                   int datosProductos[][NUM_ATRIBUTOS],
                   int numProductos,
                   char nombresRecursos[][MAX_RECURSO_NOMBRE],
                   int almacenRecursos[]);

void cotizarProduccion(char nombres[][MAX_NOMBRE],
                       int datosProductos[][NUM_ATRIBUTOS],
                       int numProductos,
                       char nombresRecursos[][MAX_RECURSO_NOMBRE]);

#endif