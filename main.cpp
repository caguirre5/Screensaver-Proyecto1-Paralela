// Universidad del Valle de Guatemala
// Computacion Paralela y distribuida
// Proyecto 1
// Cristian Aguirre   20361
// Paola de Leon      20308
// Marco Jurado       20231

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main()
{
    // Inicialización para números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Crear una ventana a pantalla completa
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(vm, "Screen Saver", sf::Style::Fullscreen);

    const int NUM_CIRCLES = 10;
    sf::CircleShape circles[NUM_CIRCLES];

    // Inicializar los círculos con tamaños y colores aleatorios
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
        float radius = std::rand() % 100 + 10;
        circles[i].setRadius(radius);
        circles[i].setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
        circles[i].setPosition(std::rand() % (static_cast<int>(vm.width) - static_cast<int>(radius * 2)),
                               std::rand() % (static_cast<int>(vm.height) - static_cast<int>(radius * 2)));
    }

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

        // Dibujar todo
        window.clear();
        for (int i = 0; i < NUM_CIRCLES; ++i)
        {
            window.draw(circles[i]);
        }
        window.display();
    }

    return 0;
}
