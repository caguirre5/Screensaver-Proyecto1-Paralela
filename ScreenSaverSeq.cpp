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

struct MovingCircle
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Uso: " << argv[0] << " [Numero de circulos]\n";
        return 1;
    }

    int NUM_CIRCLES = std::stoi(argv[1]);
    if (NUM_CIRCLES <= 0)
    {
        std::cout << "Por favor, introduce un numero de circulos positivo.\n";
        return 1;
    }

    // Inicialización para números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Crear una ventana a pantalla completa
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(vm, "Screen Saver", sf::Style::Fullscreen);

    // LImite de FPS
    window.setFramerateLimit(50);

    // Desactivar la sincronización vertical
    window.setVerticalSyncEnabled(false);

    sf::Clock clock; // Inicializa un reloj para medir el tiempo entre frames
    float lastTime = 0;

    MovingCircle circles[NUM_CIRCLES];

    // Inicializar los círculos
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
        float radius = std::rand() % 100 + 10;
        circles[i].shape.setRadius(radius);
        circles[i].shape.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
        circles[i].shape.setPosition(std::rand() % (static_cast<int>(vm.width) - static_cast<int>(radius * 2)),
                                     std::rand() % (static_cast<int>(vm.height) - static_cast<int>(radius * 2)));
        circles[i].velocity = sf::Vector2f(std::rand() % 200 - 100, std::rand() % 200 - 100);
    }

    while (window.isOpen())
    {
        float currentTime = clock.restart().asSeconds(); // reiniciar reloj y obtener tiempo como float
        float fps = 1.f / currentTime;                   // calcular los FPS
        std::cout << "FPS: " << fps << std::endl;        // mostrar los FPS en la consola

        lastTime = currentTime; // actualizar lastTime

        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed)
            {
                window.close();
            }
        }

        // Mover y comprobar colisiones para cada círculo
        for (int i = 0; i < NUM_CIRCLES; ++i)
        {
            sf::Vector2f pos = circles[i].shape.getPosition();
            sf::Vector2f &vel = circles[i].velocity;
            float radius = circles[i].shape.getRadius();

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

            circles[i].shape.move(vel * 0.05f);
        }

        // Dibujar todo
        window.clear();
        for (int i = 0; i < NUM_CIRCLES; ++i)
        {
            window.draw(circles[i].shape);
        }
        window.display();
    }

    return 0;
}