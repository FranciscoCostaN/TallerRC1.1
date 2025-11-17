#include "funciones1.h"

int main() {
    //Definicion de Arreglos Paralelos y Matrices
    char nombresProductos[MAX_PRODUCTOS][MAX_NOMBRE];
    int tiemposFabricacion[MAX_PRODUCTOS];
    int precios[MAX_PRODUCTOS];

    //Sistema de Recursos
    char nombresRecursos[NUM_RECURSOS][MAX_RECURSO_NOMBRE];
    int almacenRecursos[NUM_RECURSOS];
    int reqRecursos[MAX_PRODUCTOS][NUM_RECURSOS];

    int numProductosActuales = MAX_PRODUCTOS;
    int opcion = 0;

    //Carga Inicial de TODOS los Datos
    inicializarDatos(nombresProductos, 
                     tiemposFabricacion, 
                     precios, 
                     reqRecursos, 
                     nombresRecursos, 
                     almacenRecursos);

    //Bucle Principal del Menu
    do {
        mostrarMenu();
        opcion = leerEntero("Seleccione una opcion (1-4): ");

        switch (opcion) {
            case 1:
                listarProductos(nombresProductos, tiemposFabricacion, precios, numProductosActuales);
                break;
            case 2:
                comprarPedido(nombresProductos, 
                              tiemposFabricacion, 
                              precios, 
                              reqRecursos, 
                              numProductosActuales, 
                              nombresRecursos, 
                              almacenRecursos);
                break;
            case 3:
                cotizarProduccion(nombresProductos, 
                                  tiemposFabricacion, 
                                  precios, 
                                  reqRecursos, 
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