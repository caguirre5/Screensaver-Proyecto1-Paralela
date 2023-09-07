## Integrantes

- Paola de León         20361
- Marco Jurado          20308
- Cristian Aguirre      20231

## Descripción

Este proyecto consiste en desarrollar un screensaver dinámico que se ejecuta tanto en versión secuencial como en paralelo. Utiliza OpenMP para la programación paralela y está diseñado para ser visualmente atractivo y funcional. Este screensaver admite múltiples colores y patrones, y presenta características de física o trigonometría para mejorar la interactividad y el atractivo visual.

## Caracteristicas

- Número de elementos (N): Puedes especificar la cantidad de elementos (por ejemplo, círculos) a renderizar a través de un parámetro.

- Colores Pseudoaleatorios: El screensaver utiliza colores generados de forma pseudoaleatoria para una mejor estética.

## Instalacion
Asegúrate de tener la biblioteca SFML instalada en tu sistema antes de compilar el programa. Puedes descargar SFML desde el sitio web oficial de SFML o instalarlo utilizando un administrador de paquetes, como en Linux:

sudo apt-get install libsfml-dev

## Compilación
Puedes compilar el programa utilizando un compilador de C++ compatible con SFML. Asegúrate de incluir la biblioteca SFML al compilar.

g++ ScreenSaverSeq.cpp -o ScreenSaverSeq -lsfml-graphics -lsfml-window -lsfml-system

** Version paralelizada **

g++ ScreenSaverOmp.cpp -o ScreenSaverOmp -lsfml-graphics -lsfml-window -lsfml-system -fopenmp

## Ejecución
Para ejecutarlo desde la línea de comandos. Debes proporcionar el número de círculos como argumento. Por ejemplo, para ejecutarlo con 50 círculos:

./ScreenSaverOmp 50

## Uso
Los círculos se moverán automáticamente por la pantalla después de ejecutar el programa.
Para detener el programa, simplemente cierra la ventana del salvapantallas, presiona la tecla "Esc" o cualquier tecla.
