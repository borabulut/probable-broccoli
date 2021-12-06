
#

using namespace sf;


{
    RenderWindow game(VideoMode(1007, 1007), "Mancala ver EC327");

    Texture title, win, lose;

    title.loadFromFile("images/Title.PNG");
    // win.loadFromFile();
    // lose.loadFromFile();

    SoundBuffer buffer;

    Music music;

    if (!buffer.loadFromFile("images/clatter.wav"))
      exit(0); // error
    
    Sprite sBackground1(title);
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    //CircleShape shape(500.f);
    //shape.setFillColor(Color::Blue);

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
//Fariza
/*RenderWindow window(VideoMode(640,480),"Mancala EC327");
sf::SoundBuffer buffer;
if(!buffer.loadFromFile)*/


    return 0;
}
