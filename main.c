#include <stdio.h>
#include <stdlib.h>

int main(){
    int opcion;
    float* lecturas = (float*)malloc(100 * sizeof(float));
    if (lecturas == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }
    float* Lec = lecturas;
    int contador = 0;

    do {
        printf("======Estación vigia======\n");
        printf("1. Capturar lectura de sensor\n");
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
        } else if (opcion == 4) { 
            printf("Enviando comando al actuador...\n");
            // enviar un comando al actuador
        } else if (opcion == 5) { 
            printf("Deshaciendo último comando...\n");
            // deshacer el último comando
        } else if (opcion == 6) { 
            printf("Generando reporte final...\n");
            // generar un reporte final
        } else if (opcion == 0) {
            printf("Saliendo del programa...\n");
        } else {
            printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }

    } while (opcion != 0);

    free(lecturas);
    return 0;
}