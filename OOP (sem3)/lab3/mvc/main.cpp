#include "../mvc/Game.hpp"
#include "../mvc/Controller.hpp"
#include "../mvc/View.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <windows.h>


int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 600), "Tower Defense Game");

	Game game;

	std::ifstream levelFile("myland.txt");
	if (!levelFile.is_open()) {
		std::cerr << "No level flle?" << std::endl;
		return -1;
	}
	bool is_ok = game.initializeGame(levelFile);
	levelFile.close();
	if (!is_ok) {
		std::cout << "Something's not good wonk-wonk" << std::endl;
		return -1;
	}

	View view(window, game.getLandscape()->getWidth(), game.getLandscape()->getHeight());

	sf::View gameView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	gameView.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
	Controller controller(&game, &view, &gameView);

	// initialize it so the table for prices now exists
	PriceTable::instance();

	int clk = 0;

	sf::Clock gameClock;
	while (window.isOpen()) {
		while (!game.isGameOver()) {
			bool isOpen = controller.handleUserInput();
			if (!isOpen) {
				break;
			}

			if (gameClock.getElapsedTime().asSeconds() >= 1.0f) {
				std::cout << "hii clk: --------------------------------------------------------------------" << clk << std::endl;
				++clk;
				game.update();
				controller.updateGameView();
				gameClock.restart();
			}

			controller.updateUI();

			view.display(gameView);

			if (game.isGameOver()) {
				std::cout << "game...over? " << game.isGameOver() << std::endl;

				sf::Font font;
				font.loadFromFile("res/font.ttf");

				sf::Text message;
				message.setFont(font);
				message.setCharacterSize(50);
				message.setFillColor(sf::Color::Red);
				message.setPosition(100, 250);

				if (game.isGameOver() == -1) {
					message.setString("Yooooouuuuuu Loooooooost!");
				} else if (game.isGameOver() == 1) {
					message.setString("Congratulations! Youve Won!");
				}

				window.draw(message);
				window.display();

				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
					}
					window.display();
				}
			}
		}
	}

	return 0;
}
