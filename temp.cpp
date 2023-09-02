#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    // Inicialización para números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Crear una ventana a pantalla completa
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(vm, "Simple Circle", sf::Style::Fullscreen);

    // Inicializar el círculo
    sf::CircleShape circle;
    float radius = 50; // Un radio de tamaño fijo, por ejemplo 50
    circle.setRadius(radius);
    circle.setFillColor(sf::Color::Green); // Color fijo, por ejemplo verde

    // Posición aleatoria
    circle.setPosition(std::rand() % (static_cast<int>(vm.width) - static_cast<int>(radius * 2)),
                       std::rand() % (static_cast<int>(vm.height) - static_cast<int>(radius * 2)));

    while (window.isOpen())
    {
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

        // Dibujar el círculo
        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}