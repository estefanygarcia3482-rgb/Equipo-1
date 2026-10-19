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
        
        // Se corrigió el doble scanf que tenías antes
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada no válida. Por favor, ingresa un número.\n");
            while (getchar() != '\n'); // Limpia el buffer de entrada
            opcion = -1; // Asigna un valor incorrecto para que vuelva a pedir la opción
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
        } else if (opcion == 2) { // Corregido: Se quitó la llave extra
            // lecturas y estadísticas
            printf("Mostrando lecturas y estadísticas...\n");
            if (contador == 0) {
                printf("No hay lecturas registradas.\n");
            } else {
                for (int i = 0; i < contador; i++){
                    printf("Lectura %d: %.2f\n", i + 1, lecturas[i]);
                }
            }
        } else if (opcion == 3) { // Corregido: Se cambió 'else' por 'else if'
            printf("Ver registro de eventos/alertas...\n");
            // registro de eventos/alertas
        } else if (opcion == 4) { // Corregido: Se cambió 'else' por 'else if'
            printf("Enviando comando al actuador...\n");
            // enviar un comando al actuador
        } else if (opcion == 5) { // Corregido: Se cambió 'else' por 'else if'
            printf("Deshaciendo último comando...\n");
            // deshacer el último comando
        } else if (opcion == 6) { // Corregido: Se cambió 'else' por 'else if'
            printf("Generando reporte final...\n");
            // generar un reporte final
        } else if (opcion == 0) { // Corregido: Se cambió 'else' por 'else if'
            printf("Saliendo del programa...\n");
        } else {
            printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }

    } while (opcion != 0); // Corregido: El ciclo ahora cierra correctamente aquí abajo

    free(lecturas);
    return 0;
}