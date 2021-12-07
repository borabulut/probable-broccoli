#include "audio.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

using namespace sf;

//Base for setting up videomode window
void windowsetup(){

  RenderWindow game(VideoMode(210, 210), "Mancala Music Player");
	Texture title;
	title.loadFromFile("audiofiles/mancala_title.PNG");
	Sprite sBackground1(title);
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
}

void backgroundmusic1(){

	RenderWindow game(VideoMode(210, 210), "Mancala Music Player");
	Texture title;
	title.loadFromFile("audiofiles/mancala_title.PNG");
	Sprite sBackground1(title);

	Music m1;
	if(!m1.openFromFile("audiofiles/audiomirage__daydream.wav"))
			exit(0);
	m1.setLoop(false);
	m1.play();

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
    		game.close();
			}
		}
		return;
}

void backgroundmusic2(){
	RenderWindow game(VideoMode(210, 210), "Mancala Music Player");
	Texture title;
	title.loadFromFile("audiofiles/mancala_title.PNG");
	Sprite sBackground1(title);

	Music m2;
	if(!m2.openFromFile("audiofiles/bloodpixelhero_background.wav"))
		exit(0);
	m2.setLoop(false);
	m2.play();

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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					game.close();
				}
			}
  }

void backgroundmusic3(){
	RenderWindow game(VideoMode(210, 210), "Mancala Music Player");
	Texture title;
	title.loadFromFile("audiofiles/mancala_title.PNG");
	Sprite sBackground1(title);

	Music m1;
	if(!m1.openFromFile("audiofiles/JuliusH_jazz_loop.wav"))
		 exit(0);
	m1.setLoop(false);
	m1.play();

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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					game.close();
				}
		}
}

void backgroundmusic4(){
	RenderWindow game(VideoMode(210, 210), "Mancala Music Player");
	Texture title;
	title.loadFromFile("audiofiles/mancala_title.PNG");
	Sprite sBackground1(title);

	Music m1;
	if(!m1.openFromFile("audiofiles/PDillow_chillbeatmix.wav"))
		 exit(0);
	m1.setLoop(false);
	m1.play();

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
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						game.close();
					}
				}
    }

void backgroundmusic5(){
	RenderWindow game(VideoMode(210, 210), "Mancala Music Player");
	Texture title;
	title.loadFromFile("audiofiles/mancala_title.PNG");
	Sprite sBackground1(title);

	Music m1;
 	if(!m1.openFromFile("audiofiles/PDillow_lofi_basskeyboard.wav"))
 		exit(0);
 	m1.setLoop(false);
 	m1.play();

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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					game.close();
				}
		}
 }

void backgroundmusic6(){
	RenderWindow game(VideoMode(210, 210), "Mancala Music Player");
	Texture title;
	title.loadFromFile("audiofiles/mancala_title.PNG");
	Sprite sBackground1(title);
	Music m1;

	if(!m1.openFromFile("audiofiles/PDillow_lofi_chill.wav"))
		 exit(0);
	m1.setLoop(false);
	m1.play();

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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					game.close();
				}
			}
	}
