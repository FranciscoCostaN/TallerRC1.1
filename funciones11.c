#include "funciones11.h"

//Funciones del Menu y Validaciones

void mostrarMenu() {
    printf("\n--- SISTEMA DE GESTION DE FABRICA ---\n");
    printf("1. Listar productos en catalogo\n");
    printf("2. Comprar Pedido (Carrito)\n");
    printf("3. Cotizar Pedido (Simulacion)\n");
    printf("4. Editar Producto\n");
    printf("5. Eliminar Producto\n");
    printf("6. Reabastecer Recursos\n");
    printf("7. Salir\n");
    printf("---------------------------------------\n");
}

int leerEntero(char* mensaje) {
    char buffer[100];
    int valor;
    char extra;

    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        if (sscanf(buffer, "%d%c", &valor, &extra) == 2 && extra == '\n') {
            if (valor < 0) {
                printf("Error: El numero no puede ser negativo.\n");
            } else {
                return valor;
            }
        } else {
            printf("Error: Entrada invalida. Por favor ingrese solo un numero entero.\n");
        }
    }
}

void leerCadena(char* mensaje, char* destino, int max) {
    char buffer[256];
    int len;

    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

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
            printf("Error: Entrada demasiado larga (max %d caracteres).\n", max - 1);
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
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        if (strlen(buffer) == 2 && (buffer[0] == 's' || buffer[0] == 'S')) return 1;
        if (strlen(buffer) == 2 && (buffer[0] == 'n' || buffer[0] == 'N')) return 0;

        printf("Error: ingrese 's' para si o 'n' para no.\n");
    }
}

//Funciones de Logica del Negocio

void inicializarDatos(char nombres[][MAX_NOMBRE],
                        int tiempos[],
                        int precios[],
                        int reqRecursos[][NUM_RECURSOS],
                        char nombresRecursos[][MAX_RECURSO_NOMBRE],
                        int almacenRecursos[]) {
    
    strcpy(nombres[0], "Monitor");
    strcpy(nombres[1], "Tarjetas Graficas");
    strcpy(nombres[2], "SSD NVME");
    strcpy(nombres[3], "Refrigeracion Liquida");
    strcpy(nombres[4], "Teclados Mecanicos");

    tiempos[0] = 3; tiempos[1] = 2; tiempos[2] = 1; tiempos[3] = 4; tiempos[4] = 1;

    precios[0] = 150; precios[1] = 400; precios[2] = 80; precios[3] = 120; precios[4] = 70;

    strcpy(nombresRecursos[0], "Chips");
    strcpy(nombresRecursos[1], "Plastico");
    strcpy(nombresRecursos[2], "Pantallas");
    strcpy(nombresRecursos[3], "Metal");
    strcpy(nombresRecursos[4], "LiquidoRefrig");

    almacenRecursos[0] = 1000;
    almacenRecursos[1] = 5000;
    almacenRecursos[2] = 200;
    almacenRecursos[3] = 2000;
    almacenRecursos[4] = 1000;

    reqRecursos[0][0] = 5;  reqRecursos[0][1] = 10; reqRecursos[0][2] = 1; reqRecursos[0][3] = 2; reqRecursos[0][4] = 0;
    reqRecursos[1][0] = 20; reqRecursos[1][1] = 5;  reqRecursos[1][2] = 0; reqRecursos[1][3] = 1; reqRecursos[1][4] = 0;
    reqRecursos[2][0] = 8;  reqRecursos[2][1] = 2;  reqRecursos[2][2] = 0; reqRecursos[2][3] = 1; reqRecursos[2][4] = 0;
    reqRecursos[3][0] = 2;  reqRecursos[3][1] = 10; reqRecursos[3][2] = 0; reqRecursos[3][3] = 5; reqRecursos[3][4] = 2;
    reqRecursos[4][0] = 1;  reqRecursos[4][1] = 15; reqRecursos[4][2] = 0; reqRecursos[4][3] = 3; reqRecursos[4][4] = 0;

    printf("Datos iniciales cargados.\n");
}

void listarProductos(char nombres[][MAX_NOMBRE], int tiempos[], int precios[], int numProductos) {
    printf("\n--- CATALOGO DE PRODUCTOS ---\n");
    printf("ID   | Nombre                | Tiempo (h) | Precio ($)\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%-5d| %-22s| %-11d| %d\n", i, nombres[i], tiempos[i], precios[i]);
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

//Procesa una compra de cliente (MODIFICADO PARA CARRITO PERSISTENTE)
void comprarPedido(char nombres[][MAX_NOMBRE],
                   int tiempos[],
                   int precios[],
                   int reqRecursos[][NUM_RECURSOS],
                   int numProductos,
                   char nombresRecursos[][MAX_RECURSO_NOMBRE],
                   int almacenRecursos[],
                   int carrito[]) { // Recibe el carrito desde main

    printf("\n--- GESTION DEL CARRITO DE COMPRAS ---\n");
    mostrarAlmacen(nombresRecursos, almacenRecursos);
    
    // Ya no usamos demandas local, usamos 'carrito' que viene del main
    int idProducto = 0;
    int cantidad = 0;

    // 1. Mostrar estado actual del carrito
    printf("\n--- Contenido Actual del Carrito ---\n");
    int hayItems = 0;
    for(int i=0; i<numProductos; i++) {
        if(carrito[i] > 0) {
            printf("- %d x %s\n", carrito[i], nombres[i]);
            hayItems = 1;
        }
    }
    if(!hayItems) printf("(Vacio)\n");

    // 2. Preguntar si desea agregar mas productos
    if (leerConfirmacion("\nDesea agregar productos al carrito? (s/n): ")) {
        while (1) {
            listarProductos(nombres, tiempos, precios, numProductos);
            idProducto = leerEntero("Ingrese el ID del producto a agregar (0-4): ");
            
            if (idProducto < 0 || idProducto >= numProductos) {
                printf("Error: ID de producto no valido.\n");
                continue;
            }

            cantidad = leerEntero("Ingrese la cantidad: ");
            
            // SUMA al carrito persistente
            carrito[idProducto] += cantidad;

            printf("Agregado. Total actual de %s: %d\n", nombres[idProducto], carrito[idProducto]);

            if (leerConfirmacion("Desea agregar otro producto? (s/n): ") == 0) {
                break;
            }
        }
    }

    // Si despues de agregar (o no) el carrito sigue vacio, salimos
    hayItems = 0;
    for(int i=0; i<numProductos; i++) if(carrito[i] > 0) hayItems = 1;
    
    if (!hayItems) {
        printf("El carrito esta vacio. Volviendo al menu.\n");
        return;
    }

    // 3. Calcular totales (Usando el carrito persistente)
    int totalPrecio = 0;
    int totalTiempo = 0;
    // IMPORTANTE: Inicializar en 0 para evitar basura
    int totalRecursosReq[NUM_RECURSOS] = {0}; 
    
    int esViable = 1;

    for (int i = 0; i < numProductos; i++) {
        if (carrito[i] > 0) {
            totalPrecio += carrito[i] * precios[i];
            totalTiempo += carrito[i] * tiempos[i];
            
            for (int j = 0; j < NUM_RECURSOS; j++) {
                totalRecursosReq[j] += carrito[i] * reqRecursos[i][j];
            }
        }
    }

    // 4. Mostrar Resumen del Pedido
    printf("\n--- RESUMEN DEL PEDIDO A PAGAR ---\n");
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

    // 5. Confirmar o Rechazar la Compra
    if (esViable) {
        printf("\nEl pedido ES VIABLE.\n");
        if (leerConfirmacion("Desea finalizar la compra y pagar? (s/n): ") == 1) {
            // Descontar del almacen
            for (int j = 0; j < NUM_RECURSOS; j++) {
                almacenRecursos[j] -= totalRecursosReq[j];
            }
            
            // VACIAR EL CARRITO (Solo se vacia si paga)
            for(int i=0; i<numProductos; i++) {
                carrito[i] = 0;
            }

            printf("\n¡Compra realizada! Gracias por preferirnos.\n");
            printf("El almacen ha sido actualizado y el carrito vaciado.\n");
        } else {
            printf("\nCompra pospuesta. Sus productos siguen guardados en el carrito.\n");
        }
    } else {
        printf("\nEl pedido NO ES VIABLE por falta de recursos.\n");
        printf("Sus productos siguen en el carrito por si desea intentar mas tarde o reabastecer.\n");
    }
}


//Opcion 3: Simula un pedido sin afectar el almacen.
void cotizarProduccion(char nombres[][MAX_NOMBRE],
                       int tiempos[],
                       int precios[],
                       int reqRecursos[][NUM_RECURSOS],
                       int numProductos,
                       char nombresRecursos[][MAX_RECURSO_NOMBRE]) {

    printf("\n--- COTIZACION DE PRODUCCION (SIMULACION) ---\n");
    
    int demandas[MAX_PRODUCTOS] = {0};
    int idProducto = 0;
    int cantidad = 0;

    //Armar el carrito de cotizacion
    while (1) {
        listarProductos(nombres, tiempos, precios, numProductos);
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

    //Calcular totales
    int totalPrecio = 0;
    int totalTiempo = 0;
    // IMPORTANTE: Inicializar en 0
    int totalRecursosReq[NUM_RECURSOS] = {0}; 

    for (int i = 0; i < numProductos; i++) {
        if (demandas[i] > 0) {
            totalPrecio += demandas[i] * precios[i];
            totalTiempo += demandas[i] * tiempos[i];
            for (int j = 0; j < NUM_RECURSOS; j++) {
                totalRecursosReq[j] += demandas[i] * reqRecursos[i][j];
            }
        }
    }
    
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

//EDITAR PRODUCTO
void editarProducto(char nombres[][MAX_NOMBRE],
                    int tiempos[],
                    int precios[],
                    int reqRecursos[][NUM_RECURSOS],
                    int numProductos,
                    char nombresRecursos[][MAX_RECURSO_NOMBRE]) {

    printf("\n--- EDITAR PRODUCTO ---\n");
    listarProductos(nombres, tiempos, precios, numProductos);

    int id = leerEntero("Ingrese el ID del producto a editar: ");

    if (id < 0 || id >= numProductos) {
        printf("Error: ID no valido.\n");
        return;
    }

    printf("\nQue desea editar?\n");
    printf("1. Nombre\n");
    printf("2. Tiempo\n");
    printf("3. Precio\n");
    printf("4. Recursos\n");

    int op = leerEntero("Seleccione: ");

    switch (op) {
        case 1:
            leerCadena("Nuevo nombre: ", nombres[id], MAX_NOMBRE);
            printf("Nombre actualizado.\n");
            break;
        case 2:
            tiempos[id] = leerEntero("Nuevo tiempo: ");
            printf("Tiempo actualizado.\n");
            break;
        case 3:
            precios[id] = leerEntero("Nuevo precio: ");
            printf("Precio actualizado.\n");
            break;
        case 4:
            for (int j = 0; j < NUM_RECURSOS; j++) {
                char msg[80];
                sprintf(msg, "Nuevo requerimiento de %s: ", nombresRecursos[j]);
                reqRecursos[id][j] = leerEntero(msg);
            }
            printf("Recursos actualizados.\n");
            break;
        default:
            printf("Opcion invalida.\n");
    }
}

//ELIMINAR PRODUCTO
void eliminarProducto(char nombres[][MAX_NOMBRE],
                      int tiempos[],
                      int precios[],
                      int reqRecursos[][NUM_RECURSOS],
                      int* numProductos) {

    printf("\n--- ELIMINAR PRODUCTO ---\n");
    listarProductos(nombres, tiempos, precios, *numProductos);

    int id = leerEntero("Ingrese el ID a eliminar: ");

    if (id < 0 || id >= *numProductos) {
        printf("Error: ID no valido.\n");
        return;
    }

    if (!leerConfirmacion("Seguro? (s/n): ")) {
        printf("Operacion cancelada.\n");
        return;
    }

    for (int i = id; i < *numProductos - 1; i++) {
        strcpy(nombres[i], nombres[i+1]);
        tiempos[i] = tiempos[i+1];
        precios[i] = precios[i+1];
        for (int j = 0; j < NUM_RECURSOS; j++) {
            reqRecursos[i][j] = reqRecursos[i+1][j];
        }
    }

    (*numProductos)--;

    printf("Producto eliminado.\n");
}

//REABASTECER RECURSOS
void reabastecerRecursos(char nombresRecursos[][MAX_RECURSO_NOMBRE],
                         int almacenRecursos[]) {

    printf("\n--- REABASTECER RECURSOS ---\n");

    for (int i = 0; i < NUM_RECURSOS; i++) {
        char msg[80];
        sprintf(msg, "Agregar a %s: ", nombresRecursos[i]);
        int cant = leerEntero(msg);
        almacenRecursos[i] += cant;
    }

    printf("Almacen actualizado.\n");
}