
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
	//init background
	background.initSprite("../Data/Images/background.png");
	background.getSprite()->setPosition(0, 0);

	//init character
	character.changeSprite();
	character.getSprite()->setPosition(0, 0);

	return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
	window.draw(*background.getSprite());
	window.draw(*character.getSprite());
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Enter)
	{
		character.changeSprite();
	}
	if (event.key.code == sf::Keyboard::P)
	{
		int random = rand() % 30;
		std::cout << random << "\n";
	}
}


