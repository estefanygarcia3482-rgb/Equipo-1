#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct S_Evento {
    char tipo_sensor[20];
    float valor;
    int tiempo_simulado;
};
typedef struct S_Evento Evento;

struct S_Grupo {
    Evento* eventos;
    int cantidad_eventos;
    struct S_Grupo* siguiente;
};
typedef struct S_Grupo Grupo;

struct S_Comando {
    char nombre[50];
    struct S_Comando* siguiente;
};
typedef struct S_Comando Comando;

Comando* frente = NULL;
Comando* final = NULL;

Comando* pila = NULL;

void encolar(char nombre[]) {
    Comando* nuevo = (Comando*)malloc(sizeof(Comando));

    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }

    strcpy(nuevo->nombre, nombre);
    nuevo->siguiente = NULL;

    if (frente == NULL) {
        frente = nuevo;
        final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }

    printf("Comando agregado a la cola.\n");
}

void ejecutarCola() {
    while (frente != NULL) {
        Comando* actual = frente;

        frente = frente->siguiente;

        if (frente == NULL) {
            final = NULL;
        }

        printf("Ejecutando comando: %s\n", actual->nombre);

        actual->siguiente = pila;
        pila = actual;
    }
}

void deshacerComando() {
    if (pila == NULL) {
        printf("No hay comandos para deshacer.\n");
        return;
    }

    Comando* actual = pila;

    printf("Deshaciendo comando: %s\n", actual->nombre);

    pila = pila->siguiente;

    free(actual);
}


int main(){
    int opcion;
    int intentos_invalidos = 0;
    int primis = 1;
    int salida = 0;
    float* lecturas = (float*)malloc(100 * sizeof(float));
    if (lecturas == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }
    float* Lec = lecturas;
    int contador = 0;
    Grupo* lista = NULL;

    do {
        if (!primis){
            char respuesta[10];
            printf("¿Deseas realizar otra operación? (s/n): \n");
            scanf("%s", respuesta);
            if (strcmp(respuesta, "n") == 0 || strcmp(respuesta, "N") == 0 || strcmp (respuesta, "no") == 0 || strcmp(respuesta, "NO") == 0) {
                printf("Generando reporte final...\n");
                salida = 1;
                break;
            }
        }
        primis = 0;
        printf("======Estación vigia======\n");
        printf("1. Captura lectura de sensor\n");
        printf("2. Mostrar lecturas y estadisticas\n");
        printf("3. Ver registro de eventos/alertas\n");
        printf("4. Enviar comando al actuador\n");
        printf("5. Deshacer ultimo comando\n");
        printf("6. Generar reporte final\n");
        printf("0. Salir\n");
        printf("Ingresa tu opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            intentos_invalidos++;
            printf("Entrada no válida. Por favor, ingresa un número.\n");
            while (getchar() != '\n');
            if (intentos_invalidos >= 3){
                printf("Haz superado el límite de 3 intentos inválidos. Cerrando el programa...\n");
                printf("Generando reporte final...\n");
                break;
            }
            continue;
        }
        if (opcion >= 0 && opcion <= 6){
            intentos_invalidos = 0;
        }

        if (opcion == 1) {
            // lectura del sensor
            if (contador < 100){
                printf("Capturando lectura de sensor...\n");
                printf("Ingresa el valor númerico: ");
                scanf("%f", Lec);
                
                if (*Lec > 50.0f) {
                    printf("La lectura supera el umbral, wiu wiu.\n");

                    Grupo* nuevo_nodo = (Grupo*)malloc(sizeof(Grupo));
                    if (nuevo_nodo != NULL) { 
                        nuevo_nodo->eventos = (Evento*)malloc(sizeof(Evento));
                        if (nuevo_nodo->eventos != NULL) {
                            nuevo_nodo->cantidad_eventos = 1;
                            printf("Dime de que tipo de sensor tienes.\n");
                            scanf("%s", nuevo_nodo->eventos[0].tipo_sensor);
                            nuevo_nodo->eventos[0].valor = *Lec;
                            printf ("Ingresa el tiempo de tu simulación (minutos): \n");
                            scanf("%d", &nuevo_nodo->eventos[0].tiempo_simulado);
                            nuevo_nodo->siguiente = lista;
                            lista = nuevo_nodo;
                            printf ("Ya quedo.\n");
                        }
                    }
                }
                Lec++;
                contador++;
                printf("¡Lectura capturada!\n");
            } else {
                printf("Se ha alcanzado el límite de lecturas.\n");
            }
        } else if (opcion == 2) {
            // lecturas y estadísticas
            printf("Mostrando lecturas y estadísticas...\n");
            if (contador == 0) {
                printf("No hay lecturas registradas.\n");
            } else {
                float suma = 0;
                float max = lecturas[0];
                float min = lecturas[0];
                for (int i = 0; i < contador; i++){
                    suma += lecturas[i];
                    if (lecturas[i] > max) {
                        max = lecturas[i];
                    }
                    if (lecturas[i] < min) {
                        min = lecturas[i];
                    }
                }
                printf("Estadísticas:\n");
                printf("Promedio: %.2f\n", suma / contador);
                printf("Máximo: %.2f\n", max);
                printf("Mínimo: %.2f\n", min);
            }
        } else if (opcion == 3) { 
            printf("Ver registro de eventos/alertas...\n");
            // registro de eventos/alertas
            if (lista == NULL) {
                printf("No hay eventos registrados.\n");
            } else {
                int op2;
                printf("1. Recorrer y mostrar eventos.\n");
                printf("2. Buscar un evento por tipo de sensor.\n");
                printf("3. Elimina un evento.\n");
                printf("Ingresa tu opción: ");
                scanf("%d", &op2);

                if (op2 == 1) {
                    Grupo* actual = lista;
                    int num = 1;
                    while (actual != NULL) {
                        for (int i = 0; i < actual->cantidad_eventos; i++){
                            printf("Evento %d | Tipo de sensor: %s | Valor: %.2f | Tiempo simulado: %d\n", num++, actual->eventos[i].tipo_sensor,
                                actual->eventos[i].valor, actual->eventos[i].tiempo_simulado);
                        }
                        actual = actual->siguiente;
                    }
                } else if (op2 == 2) {
                    char buscar_tipo[20];
                    printf("Ingresa el tipo de sensor a buscar: \n");
                    scanf("%s", buscar_tipo);

                    Grupo* actual = lista;
                    int encontrado = 0;
                    while (actual != NULL) {
                        for (int i = 0; i < actual->cantidad_eventos; i++) {
                            if (strcmp(actual->eventos[i].tipo_sensor, buscar_tipo) == 0) {
                                printf("Encontrado :D Tipo: %s | Valor %.2f | Tiempo: %d\n", actual->eventos[i].tipo_sensor, actual->eventos[i].valor,
                                    actual->eventos[i].tiempo_simulado);
                                encontrado++;
                            }
                        }
                        actual = actual->siguiente;
                    }
                    if (encontrado == 0) {
                        printf("No se encontraron eventos con el tipo '%s'.\n", buscar_tipo);
                    }
                } else if (op2 == 3) {
                    char eliminar_tipo[20];
                    printf("Ingresa el tipo de sensor del evento a eliminar: \n");
                    scanf("%s", eliminar_tipo);

                    Grupo* actual = lista;
                    Grupo* anterior = NULL;
                    int eliminado = 0;

                    while (actual != NULL) {
                        if (strcmp(actual->eventos[0].tipo_sensor, eliminar_tipo) == 0) {
                            char confi[10];
                            printf("¿Estas seguro de querer eliminar el evento del sensor '%s'? (s/n): ", eliminar_tipo);
                            scanf("%s", confi);
                            if (strcmp(confi, "s") != 0 && strcmp(confi, "S") != 0 || strcmp(confi, "si") != 0 && strcmp(confi, "SI") != 0){
                                if (anterior == NULL){
                                    lista = actual->siguiente;
                                } else {
                                    anterior->siguiente = actual->siguiente;
                                }
                            free(actual->eventos);
                            free(actual);
                            eliminado = 1;
                            printf("Evento eliminado.\n");
                            } else {
                                printf("Eliminación cancelada.\n");
                                eliminado = 1;
                            }
                            break; 
                        }
                        
                        anterior = actual;
                        actual = actual->siguiente;
                    }
                    
                    if (!eliminado){
                        printf("No se encontro ningun evento para eliminar.\n");
                    }
                }
            }
        
        } else if (opcion == 4) {
            char nombre_comando[50];

            printf("Enviando comando al actuador...\n");
            printf("Ingresa el nombre del comando: ");
            scanf("%49s", nombre_comando);

            if (strlen (nombre_comando) == 0){
                printf("El nombre del comando no puede estar vacío.\n");
            }else {
                encolar(nombre_comando);
                ejecutarCola();
             }
        } else if (opcion == 5) {

            printf("Deshaciendo último comando...\n");
            if (pila == NULL) {
                printf("No hay comandos para deshacer.\n");
            } else {
                char confi[10];
                printf("¿Estas seguro de querer deshacer el último comando ('%s')? (s/n): ", pila->nombre);
                scanf("%s", confi);
                if (strcmp(confi, "s") == 0 || strcmp(confi, "S") == 0 || strcmp(confi, "si") == 0 || strcmp(confi, "SI") == 0){
                    deshacerComando();
                } else {
                    printf("Deshacer comando cancelado.\n");
                }
            }
        } else if (opcion == 6) {

            printf("Generando reporte final...\n");

        } else if (opcion == 0) {

            printf("Saliendo del programa...\n");

        } else {
            intentos_invalidos++;
            printf("Opción no válida. Por favor, intenta de nuevo.\n");

            if (intentos_invalidos >= 3){
                printf("Haz superado el límite de 3 intentos inválidos. Cerrando el programa...\n");
                printf("Generando reporte final...\n");
                break;
            }
        }

    } while (!salida);


    Grupo* actual = lista;
    while (actual != NULL) {
        Grupo* siguiente_nodo = actual->siguiente;
        free(actual->eventos);
        free(actual);
        actual = siguiente_nodo;
    }
    free(lecturas);

     while (frente != NULL) {
        Comando* siguiente = frente->siguiente;
        free(frente);
        frente = siguiente;
    }

     while (pila != NULL) {
        Comando* siguiente = pila->siguiente;
        free(pila);
        pila = siguiente;
    }

    return 0;
}