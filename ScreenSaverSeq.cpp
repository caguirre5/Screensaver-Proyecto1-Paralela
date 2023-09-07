// Universidad del Valle de Guatemala
// Computacion Paralela y distribuida
// Proyecto 1
// Cristian Aguirre   20361
// Paola de Leon      20308
// Marco Jurado       20231

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>

// Estructura para representar un círculo móvil
struct MovingCircle
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

// Función para mover los círculos y comprobar colisiones
void MoveCircles(MovingCircle circles[], int NUM_CIRCLES, sf::VideoMode vm)
{
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
        sf::Vector2f pos = circles[i].shape.getPosition();
        sf::Vector2f &vel = circles[i].velocity;
        float radius = circles[i].shape.getRadius();

        // Comprobar colisiones con los bordes de la pantalla
        if (pos.x <= 0 || pos.x + 2 * radius >= vm.width)
        {
            // Asegurarse de que la nueva velocidad sea lo suficientemente alta
            do
            {
                vel.x = std::rand() % 200 - 100;
            } while (std::abs(vel.x) < 50); // velocidad mínima de 50

            // Corregir la posición para evitar pegarse al borde
            if (pos.x <= 0)
            {
                circles[i].shape.setPosition(1.0f, pos.y);
            }
            else
            {
                circles[i].shape.setPosition(vm.width - 2 * radius - 1.0f, pos.y);
            }
        }
        if (pos.y <= 0 || pos.y + 2 * radius >= vm.height)
        {
            // Asegurarse de que la nueva velocidad sea lo suficientemente alta
            do
            {
                vel.y = std::rand() % 200 - 100;
            } while (std::abs(vel.y) < 50); // velocidad mínima de 50

            // Corregir la posición para evitar pegarse al borde
            if (pos.y <= 0)
            {
                circles[i].shape.setPosition(pos.x, 1.0f);
            }
            else
            {
                circles[i].shape.setPosition(pos.x, vm.height - 2 * radius - 1.0f);
            }
        }

        // Mover el círculo basado en su velocidad
        circles[i].shape.move(vel * 0.05f);
    }
}

// Función para renderizar los círculos y el texto de los FPS
void RenderCircles(sf::RenderWindow &window, MovingCircle circles[], int NUM_CIRCLES, sf::Text &fpsText)
{
    // Limpiar la ventana
    window.clear();

    // Dibujar los círculos en la ventana
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
        window.draw(circles[i].shape);
    }

    // Dibujar el texto de los FPS en la ventana
    window.draw(fpsText);

    // Mostrar los cambios en la ventana
    window.display();
}

int main(int argc, char *argv[])
{
    // Verificar la cantidad correcta de argumentos
    if (argc != 2)
    {
        std::cout << "Uso: " << argv[0] << " [Numero de circulos]\n";
        return 1;
    }

    // Obtener el número de círculos desde los argumentos de la línea de comandos
    int NUM_CIRCLES = std::stoi(argv[1]);

    // Verificar que el número de círculos sea positivo
    if (NUM_CIRCLES <= 0)
    {
        std::cout << "Por favor, introduce un numero de circulos positivo.\n";
        return 1;
    }

    // Inicialización para números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Crear una ventana a pantalla completa
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(vm, "Screen Saver", sf::Style::Default);

    // Cargar una fuente para mostrar el texto de los FPS
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // Manejo de errores si la fuente no se carga correctamente
        std::cout << "No se pudo cargar la fuente.\n";
        return 1;
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24); // en píxeles, no puntos
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10); // posición en la pantalla

    // Límite de FPS
    window.setFramerateLimit(40);

    // Desactivar la sincronización vertical (VSync)
    window.setVerticalSyncEnabled(false);

    // Crear un arreglo de círculos móviles
    MovingCircle circles[NUM_CIRCLES];

    // Inicializar los círculos con valores aleatorios
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
        float radius = std::rand() % 100 + 10; // Radio aleatorio
        circles[i].shape.setRadius(radius);
        circles[i].shape.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256)); // Color aleatorio
        circles[i].shape.setPosition(std::rand() % (static_cast<int>(vm.width) - static_cast<int>(radius * 2)),
                                     std::rand() % (static_cast<int>(vm.height) - static_cast<int>(radius * 2))); // Posición aleatoria
        circles[i].velocity = sf::Vector2f(std::rand() % 200 - 100, std::rand() % 200 - 100);                     // Velocidad aleatoria
    }

    sf::Clock clock;
    float frameCounter = 0;
    double tiempo_total = 0.0;
    int numiteraciones = 0;
    int total_frames = 0;

    while (window.isOpen())
    {
        // Calcular el tiempo transcurrido desde el último fotograma
        float currentTime = clock.restart().asSeconds();

        // Calcular los FPS (fotogramas por segundo)
        float fps = 1.f / currentTime;
        total_frames++;


        // Mostrar los FPS en la consola
        std::cout << "FPS: " << fps << std::endl;

        // Actualizar el texto de los FPS
        fpsText.setString("FPS: " + std::to_string(fps));

        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Cerrar la ventana si se presiona la tecla Esc, cierra o se hace clic en el botón de cierre
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed)
            {
                window.close();
            }
        }
        auto start_time = std::chrono::high_resolution_clock::now();
        // Mover y comprobar colisiones para cada círculo
        MoveCircles(circles, NUM_CIRCLES, vm);

        // Renderizar los círculos y el texto de los FPS
        RenderCircles(window, circles, NUM_CIRCLES, fpsText);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        double tiempo_iteracion = duration.count() / 1e6; // Convierte microsegundos a segundos
        tiempo_total += tiempo_iteracion;
        numiteraciones += 1;

        std::cout << "Tiempo transcurrido: " << duration.count() << " microsegundos" << std::endl;

    }
    double tiempo_promedio = tiempo_total / numiteraciones;
    std::cout << "Tiempo promedio de ejecución: " << tiempo_promedio << " segundos" << std::endl;
    float promedio_fps = static_cast<float>(total_frames) / tiempo_total;
    std::cout << "Promedio de FPS: " << promedio_fps << std::endl;

    return 0;
}
