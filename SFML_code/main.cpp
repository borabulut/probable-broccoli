#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow game(VideoMode(1007, 1007), "Mancala ver EC327");
    
    Texture title, credit, board, small_well, big_well, stone;

    title.loadFromFile("images/Title.PNG");

    Sprite sBackground1(title);

    CircleShape shape(500.f);
    shape.setFillColor(Color::Blue);

    while (game.isOpen())
    {
        Event event;
        while (game.pollEvent(event))
        {
            if (event.type == Event::Closed)
                game.close();
        }

        game.clear();
        game.draw(sBackground1);
        game.display();
    }

    return 0;
}