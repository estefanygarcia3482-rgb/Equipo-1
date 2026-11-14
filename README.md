# Equipo-1
Para el proyecto de estructura de datos.
Los te de manzanilla
Lizeth Yoselyn Gonzalez Ruiz 
Diana Lisette Becerra Muñiz 
Estefany Monserrat Garcia Olmos
3B, Ingieneria en electronica y computación


La Estación Vigía es un sistema de monitoreo y control simulado desarrollado en C que opera mediante una interfaz de consola interactiva. Su propósito principal es supervisar flujos de datos provenientes de diferentes sensores, permitiendo capturar lecturas numéricas, calcular estadísticas en tiempo real (como promedios, valores máximos y mínimos) y registrar eventos de alerta cuando una medición supera un umbral crítico establecido.

El programa resuelve el problema de la gestión y automatización de procesos de control al integrar estructuras de datos avanzadas como listas enlazadas (para el historial de alertas), colas FIFO (para el envío ordenado de órdenes a actuadores) y pilas LIFO (para permitir la funcionalidad de deshacer comandos). De este modo, facilita una respuesta operativa organizada y un seguimiento estructurado ante situaciones anómalas.

==Carecteristicas==

*-Monitoreo de Sensores: Captura hasta 100 lecturas dinámicas y calcula métricas estadísticas (promedio, valor máximo y mínimo).
*-Alertas Inteligentes: Si una lectura supera el umbral de `50.0`, el sistema solicita automáticamente los detalles del sensor (tipo y tiempo simulado) y los almacena en una lista enlazada.
*-Gestión de Actuadores (Cola FIFO): Permite encolar y ejecutar comandos destinados a actuadores de forma secuencial.
*-Control de Historial (Pila LIFO): Implementa una función de "Deshacer" (`undo`) para revertir el último comando ejecutado liberando su memoria de forma segura.
*-Gestión de Memoria: Limpieza completa de memoria dinámica al salir del programa para evitar fugas (memory leaks).

==Requisitos previos==

Para compilar y ejecutar este programa, necesitas tener instalado:
*-Un compilador de C compatible con C99 o superior (como GCC).
*-Una terminal de comandos (Bash, Zsh, CMD o PowerShell).

==Instrucciones de compilación y ejecución (GCC)==

1. Clona o guarda el código fuente en un archivo llamado `main.c`.
2. Abre tu terminal y navega hasta la carpeta donde guardaste el archivo.
3. Compila el código ejecutando el siguiente comando con GCC:
   ```bash
   gcc main.c -o main
   gcc -Wall main.c -o main
   
   en Linus/macOS
   ./main

   Windows CMD/Powershell
   main.exe

==Ejemplo de uso==
Capturar una lectura normal:
    Elige la opción 1.
    Ingresa un valor numérico por debajo del umbral (por ejemplo: 42.5). El sistema lo registrará sin generar alertas.

Capturar una lectura crítica (Alerta):
    Elige la opción 1 nuevamente.
    Ingresa un valor superior al umbral (por ejemplo: 65.0). El sistema detectará la anomalía (¡La lectura supera el umbral, wiu wiu!).
    Introduce el tipo de sensor (ej: Temperatura, Aceite, Ruedas o Voltaje) y el tiempo simulado (ej: 30).

Ver estadísticas:
    Elige la opción 2 para visualizar el promedio, el valor máximo y el mínimo de las lecturas capturadas hasta el momento.

Consultar el registro de eventos:
    Elige la opción 3 y luego la subopción 1 para recorrer y listar todas las alertas generadas.
    Elige la opción 3 y luego la subopción 2 para buscar un evento por tipo de sensor.
    Elige la opción 3 y luego la subopción 3 para eliminar un evento.

Enviar un comando al actuador:
    Elige la opción 4.
    Ingresa el nombre del comando (ej: Encender). El sistema lo encolará y lo ejecutará inmediatamente, pasándolo al historial.

Deshacer el último comando:
    Elige la opción 5. El sistema deshará la última acción realizada y lo notificará en pantalla.

Salir del programa:
    Elige la opción 0 para finalizar la ejecución de forma segura con la liberación automática de memoria.