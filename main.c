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


int main(){
    int opcion;
    float* lecturas = (float*)malloc(100 * sizeof(float));
    if (lecturas == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }
    float* Lec = lecturas;
    int contador = 0;
    Grupo* lista = NULL;

    do {
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
            printf("Entrada no válida. Por favor, ingresa un número.\n");
            while (getchar() != '\n'); // Limpia el buffer de entrada
            opcion = -1;
            continue;
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
                            printf ("Ingresa el tiempo de tu simulación: \n");
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
                scanf("%d", &op2); // Nota: usa %d en lugar de %D

                if (op2 == 1) {
                    Grupo* actual = lista;
                    int num = 1;
                    while (actual != NULL) {
                        for (int i = 0; i < actual->cantidad_eventos; i++){
                            printf("Evento %d | Tipo de sensor: %s | Valor: %.2f | Tiempo simulado: %d\n", num++, actual->eventos[i].tipo_sensor, actual->eventos[i].valor, actual->eventos[i].tiempo_simulado);
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
                                printf("Encontrado :D Tipo: %s | Valor %.2f | Tiempo: %d\n", actual->eventos[i].tipo_sensor, actual->eventos[i].valor, actual->eventos[i].tiempo_simulado);
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
                            if (anterior == NULL){
                                lista = actual->siguiente;
                            } else {
                                anterior->siguiente = actual->siguiente;
                            }
                            free(actual->eventos);
                            free(actual);
                            eliminado = 1;
                            printf("Evento eliminado.\n");
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
            printf("Enviando comando al actuador...\n");
        } else if (opcion == 5) { 
            printf("Deshaciendo último comando...\n");
        } else if (opcion == 6) { 
            printf("Generando reporte final...\n");
        } else if (opcion == 0) {
            printf("Saliendo del programa...\n");
        } else {
            printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }

    } while (opcion != 0);

    Grupo* actual = lista;
    while (actual != NULL) {
        Grupo* siguiente_nodo = actual->siguiente;
        free(actual->eventos);
        free(actual);
        actual = siguiente_nodo;
    }
    
    free(lecturas);
    return 0;
}