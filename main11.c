#include "funciones11.h"

int main() {

    char nombresProductos[MAX_PRODUCTOS][MAX_NOMBRE];
    int tiemposFabricacion[MAX_PRODUCTOS];
    int precios[MAX_PRODUCTOS];

    char nombresRecursos[NUM_RECURSOS][MAX_RECURSO_NOMBRE];
    int almacenRecursos[NUM_RECURSOS];
    int reqRecursos[MAX_PRODUCTOS][NUM_RECURSOS];

    // NUEVO: Carrito persistente (vive en el main, no se borra al salir de la funcion)
    int carrito[MAX_PRODUCTOS] = {0};

    int numProductosActuales = 5;
    int opcion = 0;

    inicializarDatos(nombresProductos,
                     tiemposFabricacion,
                     precios,
                     reqRecursos,
                     nombresRecursos,
                     almacenRecursos);

    do {
        mostrarMenu();
        opcion = leerEntero("Seleccione una opcion (1-7): ");

        switch (opcion) {

            case 1:
                listarProductos(nombresProductos, tiemposFabricacion, precios, numProductosActuales);
                break;

            case 2:
                // Se pasa el carrito persistente a la funcion
                comprarPedido(nombresProductos, tiemposFabricacion, precios,
                              reqRecursos, numProductosActuales,
                              nombresRecursos, almacenRecursos, 
                              carrito);
                break;

            case 3:
                cotizarProduccion(nombresProductos, tiemposFabricacion, precios,
                                  reqRecursos, numProductosActuales,
                                  nombresRecursos);
                break;

            case 4:
                editarProducto(nombresProductos, tiemposFabricacion, precios,
                               reqRecursos, numProductosActuales, nombresRecursos);
                break;

            case 5:
                eliminarProducto(nombresProductos, tiemposFabricacion, precios,
                                 reqRecursos, &numProductosActuales);
                break;

            case 6:
                reabastecerRecursos(nombresRecursos, almacenRecursos);
                break;

            case 7:
                printf("Saliendo del sistema.\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 7);

    return 0;
}