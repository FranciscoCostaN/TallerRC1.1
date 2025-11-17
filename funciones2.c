#include "funciones2.h"
#include <stdio.h>
#include <string.h>

//Funciones del Menu y Validaciones

void mostrarMenu() {
    printf("\n--- SISTEMA DE GESTION DE FABRICA ---\n");
    printf("1. Listar productos en catalogo\n");
    printf("2. Comprar Pedido\n");
    printf("3. Cotizar Pedido (Simulacion)\n");
    printf("4. Salir\n");
    printf("---------------------------------------\n");
}

int leerEntero(char* mensaje) {
    char buffer[100];
    int valor;
    char extra;

    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }

        if (sscanf(buffer, "%d%c", &valor, &extra) == 2 && extra == '\n') {
            if (valor < 0) {
                 printf("Error: El numero no puede ser negativo.\n");
            } else {
                return valor;
            }
        } else {
            printf("Error: Entrada invalida. Por favor, ingrese solo un numero entero (ej: 42).\n");
        }
    }
}

void leerCadena(char* mensaje, char* destino, int max) {
    char buffer[256];
    int len;

    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }

        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        if (len == 0) {
            printf("Error: La entrada no puede estar vacia.\n");
            continue;
        }
        if (len >= max) {
            printf("Error: La entrada es demasiado larga (max %d caracteres).\n", max - 1);
            continue;
        }

        strcpy(destino, buffer);
        break;
    }
}

int leerConfirmacion(char* mensaje) {
    char buffer[10];
    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }
        
        if (strlen(buffer) == 2 && (buffer[0] == 's' || buffer[0] == 'S') && buffer[1] == '\n') {
            return 1; // Si
        }
        if (strlen(buffer) == 2 && (buffer[0] == 'n' || buffer[0] == 'N') && buffer[1] == '\n') {
            return 0; // No
        }

        printf("Error: Por favor, ingrese solo 's' (si) o 'n' (no).\n");
    }
}

//Funciones de Logica del Negocio

//Quema todos los datos iniciales en la nueva matriz unificada.
void inicializarDatos(char nombres[][MAX_NOMBRE],
                        int datosProductos[][NUM_ATRIBUTOS],
                        char nombresRecursos[][MAX_RECURSO_NOMBRE],
                        int almacenRecursos[]) {
    
    //Nombres de Productos
    strcpy(nombres[0], "Monitor");
    strcpy(nombres[1], "Tarjetas Graficas");
    strcpy(nombres[2], "SSD NVME");
    strcpy(nombres[3], "Refrigeracion Liquida");
    strcpy(nombres[4], "Teclados Mecanicos");

    //Nombres de Recursos
    strcpy(nombresRecursos[0], "Chips");
    strcpy(nombresRecursos[1], "Plastico");
    strcpy(nombresRecursos[2], "Pantallas");
    strcpy(nombresRecursos[3], "Metal");
    strcpy(nombresRecursos[4], "LiquidoRefrig");

    //Almacen Inicial de Recursos
    almacenRecursos[0] = 1000; // Chips
    almacenRecursos[1] = 5000; // Plastico
    almacenRecursos[2] = 200;  // Pantallas
    almacenRecursos[3] = 2000; // Metal
    almacenRecursos[4] = 1000; // LiquidoRefrig

    //Matriz de Datos
    //Tiempo, Precio, Chips, Plastico, Pantallas, Metal, Liquido
    
    //Monitor (ID 0)
    datosProductos[0][COL_TIEMPO]   = 3;
    datosProductos[0][COL_PRECIO]   = 150;
    datosProductos[0][COL_CHIPS]    = 5;
    datosProductos[0][COL_PLASTICO] = 10;
    datosProductos[0][COL_PANTALLAS]= 1;
    datosProductos[0][COL_METAL]    = 2;
    datosProductos[0][COL_LIQUIDO]  = 0;

    //Tarjeta Grafica (ID 1)
    datosProductos[1][COL_TIEMPO]   = 2;
    datosProductos[1][COL_PRECIO]   = 400;
    datosProductos[1][COL_CHIPS]    = 20;
    datosProductos[1][COL_PLASTICO] = 5;
    datosProductos[1][COL_PANTALLAS]= 0;
    datosProductos[1][COL_METAL]    = 1;
    datosProductos[1][COL_LIQUIDO]  = 0;

    //SSD NVME (ID 2)
    datosProductos[2][COL_TIEMPO]   = 1;
    datosProductos[2][COL_PRECIO]   = 80;
    datosProductos[2][COL_CHIPS]    = 8;
    datosProductos[2][COL_PLASTICO] = 2;
    datosProductos[2][COL_PANTALLAS]= 0;
    datosProductos[2][COL_METAL]    = 1;
    datosProductos[2][COL_LIQUIDO]  = 0;

    //Refrigeracion Liquida (ID 3)
    datosProductos[3][COL_TIEMPO]   = 4;
    datosProductos[3][COL_PRECIO]   = 120;
    datosProductos[3][COL_CHIPS]    = 2;
    datosProductos[3][COL_PLASTICO] = 10;
    datosProductos[3][COL_PANTALLAS]= 0;
    datosProductos[3][COL_METAL]    = 5;
    datosProductos[3][COL_LIQUIDO]  = 2;

    //Teclados Mecanicos (ID 4)
    datosProductos[4][COL_TIEMPO]   = 1;
    datosProductos[4][COL_PRECIO]   = 70;
    datosProductos[4][COL_CHIPS]    = 1;
    datosProductos[4][COL_PLASTICO] = 15;
    datosProductos[4][COL_PANTALLAS]= 0;
    datosProductos[4][COL_METAL]    = 3;
    datosProductos[4][COL_LIQUIDO]  = 0;
    
    printf("Datos iniciales de productos y recursos cargados.\n");
}

/**
 * Muestra el catalogo, leyendo desde la matriz unificada.
 */
void listarProductos(char nombres[][MAX_NOMBRE], int datosProductos[][NUM_ATRIBUTOS], int numProductos) {
    printf("\n--- CATALOGO DE PRODUCTOS ---\n");
    printf("ID   | Nombre                | Tiempo (h) | Precio ($)\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%-5d| %-22s| %-11d| %d\n", 
               i, 
               nombres[i], 
               datosProductos[i][COL_TIEMPO], // Lee de la matriz
               datosProductos[i][COL_PRECIO]); // Lee de la matriz
    }
}


//Funciones Principales de Calculo

void mostrarAlmacen(char nombresRecursos[][MAX_RECURSO_NOMBRE], int almacenRecursos[]) {
    printf("\n--- ESTADO DEL ALMACEN ---\n");
    for (int i = 0; i < NUM_RECURSOS; i++) {
        printf("%-10s: %d unidades\n", nombresRecursos[i], almacenRecursos[i]);
    }
    printf("---------------------------\n");
}

void comprarPedido(char nombres[][MAX_NOMBRE],
                   int datosProductos[][NUM_ATRIBUTOS],
                   int numProductos,
                   char nombresRecursos[][MAX_RECURSO_NOMBRE],
                   int almacenRecursos[]) {

    printf("\n--- NUEVO PEDIDO DE COMPRA ---\n");
    mostrarAlmacen(nombresRecursos, almacenRecursos);
    
    int demandas[MAX_PRODUCTOS] = {0};
    int idProducto = 0;
    int cantidad = 0;

    //Armar el carrito de compras
    while (1) {
        listarProductos(nombres, datosProductos, numProductos);
        idProducto = leerEntero("Ingrese el ID del producto que desea comprar (0-4): ");
        
        if (idProducto < 0 || idProducto >= numProductos) {
            printf("Error: ID de producto no valido.\n");
            continue;
        }

        cantidad = leerEntero("Ingrese la cantidad que desea: ");
        demandas[idProducto] += cantidad;

        printf("Agregado: %d x %s\n", cantidad, nombres[idProducto]);

        if (leerConfirmacion("Desea agregar otro producto? (s/n): ") == 0) {
            break;
        }
    }

    //Calcular totales
    int totalPrecio = 0;
    int totalTiempo = 0;
    int totalRecursosReq[NUM_RECURSOS] = {0};
    int esViable = 1;

    for (int i = 0; i < numProductos; i++) {
        if (demandas[i] > 0) {
            totalPrecio += demandas[i] * datosProductos[i][COL_PRECIO];
            totalTiempo += demandas[i] * datosProductos[i][COL_TIEMPO];
            
            // Calcula recursos
            for (int j = 0; j < NUM_RECURSOS; j++) {
                int col_recurso = j + COL_CHIPS; 
                totalRecursosReq[j] += demandas[i] * datosProductos[i][col_recurso];
            }
        }
    }

    //Mostrar Resumen del Pedido
    printf("\n--- RESUMEN DEL PEDIDO ---\n");
    printf("Precio Total: $%d\n", totalPrecio);
    printf("Tiempo de Entrega Total: %d horas\n", totalTiempo);
    
    printf("\nRecursos Requeridos vs. Almacen:\n");
    for (int j = 0; j < NUM_RECURSOS; j++) {
        printf("  %s: %d requeridos / %d en almacen\n", 
               nombresRecursos[j], totalRecursosReq[j], almacenRecursos[j]);
        
        if (totalRecursosReq[j] > almacenRecursos[j]) {
            esViable = 0;
            printf("    -> FALTAN %d UNIDADES DE %s\n", 
                   totalRecursosReq[j] - almacenRecursos[j], nombresRecursos[j]);
        }
    }

    //Confirmar o Rechazar la Compra
    if (esViable) {
        printf("\nEl pedido ES VIABLE.\n");
        if (leerConfirmacion("Desea confirmar la compra? (s/n): ") == 1) {
            for (int j = 0; j < NUM_RECURSOS; j++) {
                almacenRecursos[j] -= totalRecursosReq[j];
            }
            printf("\n¡Compra realizada! Gracias por preferirnos.\n");
            printf("El almacen ha sido actualizado.\n");
        } else {
            printf("\nPedido cancelado. Lamentamos mucho no poderle ayudar, esperamos que vuelva pronto.\n");
        }
    } else {
        printf("\nEl pedido NO ES VIABLE por falta de recursos.\n");
        printf("Lamentamos mucho no poderle ayudar, esperamos que vuelva pronto.\n");
    }
}


void cotizarProduccion(char nombres[][MAX_NOMBRE],
                       int datosProductos[][NUM_ATRIBUTOS],
                       int numProductos,
                       char nombresRecursos[][MAX_RECURSO_NOMBRE]) {

    printf("\n--- COTIZACION DE PRODUCCION (SIMULACION) ---\n");
    
    int demandas[MAX_PRODUCTOS] = {0};
    int idProducto = 0;
    int cantidad = 0;

    while (1) {
        listarProductos(nombres, datosProductos, numProductos);
        idProducto = leerEntero("Ingrese el ID del producto a cotizar (0-4): ");
        
        if (idProducto < 0 || idProducto >= numProductos) {
            printf("Error: ID de producto no valido.\n");
            continue;
        }

        cantidad = leerEntero("Ingrese la cantidad: ");
        demandas[idProducto] += cantidad;

        printf("Agregado: %d x %s\n", cantidad, nombres[idProducto]);

        if (leerConfirmacion("Desea agregar otro producto? (s/n): ") == 0) {
            break;
        }
    }

    int totalPrecio = 0;
    int totalTiempo = 0;
    int totalRecursosReq[NUM_RECURSOS] = {0};

    for (int i = 0; i < numProductos; i++) {
        if (demandas[i] > 0) {
            // Lee precio y tiempo desde la matriz unificada
            totalPrecio += demandas[i] * datosProductos[i][COL_PRECIO];
            totalTiempo += demandas[i] * datosProductos[i][COL_TIEMPO];
            
            // Calcula recursos
            for (int j = 0; j < NUM_RECURSOS; j++) {
                int col_recurso = j + COL_CHIPS; 
                totalRecursosReq[j] += demandas[i] * datosProductos[i][col_recurso];
            }
        }
    }
    
    //Mostrar Resumen de Cotizacion
    printf("\n--- Totales Requeridos para la Cotizacion ---\n");
    printf("Precio Total: $%d\n", totalPrecio);
    printf("Tiempo total de fabricacion: %d horas\n", totalTiempo);
    for (int j = 0; j < NUM_RECURSOS; j++) {
        printf("Recursos (%s): %d unidades\n", nombresRecursos[j], totalRecursosReq[j]);
    }

    //Pedir limites de la fabrica
    printf("\n--- Verificacion de Limites de Simulacion ---\n");
    int limiteTiempo = leerEntero("Ingrese el tiempo total de produccion DISPONIBLE (horas): ");
    
    int limitesRecursos[NUM_RECURSOS];
    for (int j = 0; j < NUM_RECURSOS; j++) {
        char mensaje[100];
        sprintf(mensaje, "Ingrese los recursos DISPONIBLES de %s: ", nombresRecursos[j]);
        limitesRecursos[j] = leerEntero(mensaje);
    }
    
    //Evaluar viabilidad de la simulacion
    int esViableTiempo = (totalTiempo <= limiteTiempo);
    int esViableRecursos = 1;

    printf("\n==> RESULTADO DE LA COTIZACION:\n");

    if (esViableTiempo && esViableRecursos) {
        for (int j = 0; j < NUM_RECURSOS; j++) {
            if (totalRecursosReq[j] > limitesRecursos[j]) {
                esViableRecursos = 0;
                printf("    FALTAN %d unidades de %s.\n", 
                       totalRecursosReq[j] - limitesRecursos[j], nombresRecursos[j]);
            }
        }
    }
    
    if (!esViableTiempo) {
        printf("    FALTAN %d horas de tiempo de produccion (Tiempo de espera adicional).\n", 
               totalTiempo - limiteTiempo);
    }

    if (esViableTiempo && esViableRecursos) {
        printf("\n==> COTIZACION VIABLE! La fabrica PUEDE cumplir con la demanda.\n");
    } else {
        printf("\n==> COTIZACION NO VIABLE! La fabrica NO PUEDE cumplir con la demanda.\n");
    }
}