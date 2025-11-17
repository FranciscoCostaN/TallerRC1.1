#include "funciones2.h"
#include <stdio.h>
#include <string.h>

int main() {
    //Definicion de Arreglos Paralelos y Matriz Unificada ---
    char nombresProductos[MAX_PRODUCTOS][MAX_NOMBRE];
    
    //Matriz Unificada para todos los datos numericos
    int datosProductos[MAX_PRODUCTOS][NUM_ATRIBUTOS];

    //Los recursos aun se manejan por separado
    char nombresRecursos[NUM_RECURSOS][MAX_RECURSO_NOMBRE];
    int almacenRecursos[NUM_RECURSOS]; //El almacen real

    int numProductosActuales = MAX_PRODUCTOS;
    int opcion = 0;

    //Carga Inicial de TODOS los Datos
    inicializarDatos(nombresProductos, 
                     datosProductos, 
                     nombresRecursos, 
                     almacenRecursos);

    //Bucle Principal del Menu
    do {
        mostrarMenu();
        opcion = leerEntero("Seleccione una opcion (1-4): ");

        switch (opcion) {
            case 1:
                //Pasa la nueva matriz
                listarProductos(nombresProductos, datosProductos, numProductosActuales);
                break;
            case 2:
                //Pasa la nueva matriz
                comprarPedido(nombresProductos, 
                              datosProductos, 
                              numProductosActuales, 
                              nombresRecursos, 
                              almacenRecursos);
                break;
            case 3:
                //Pasa la nueva matriz
                cotizarProduccion(nombresProductos, 
                                  datosProductos, 
                                  numProductosActuales, 
                                  nombresRecursos);
                break;
            case 4:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
        }

    } while (opcion != 4);

    return 0;
}