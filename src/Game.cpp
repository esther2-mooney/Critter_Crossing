
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;

}

bool Game::init()
{
	character = new sf::Sprite;
	passport = new sf::Sprite;

	animals[0].loadFromFile("../Data/c_animals/penguin.png");
	animals[1].loadFromFile("../Data/c_animals/moose.png");
	animals[2].loadFromFile("../Data/c_animals/zebra.png");

	passports[0].loadFromFile("../Data/s_animals/penguin.png");
	passports[1].loadFromFile("../Data/s_animals/moose.png");
	passports[2].loadFromFile("../Data/s_animals/zebra.png");





	//init background
	background.initSprite("../Data/Images/background.png");
	background.getSprite()->setPosition(0, 0);
	/*
	//init character
	character.changeSprite();
	character.getSprite()->setPosition(0, 0);
	*/

	return true;
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->setTexture(animals[passport_index], true);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);
}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);
		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition(drag_position.x, drag_position.y);
	}
}


void Game::update(float dt)
{
	if (dragged != nullptr)
	{
		dragSprite(dragged);
	}
}

void Game::render()
{
	window.draw(*background.getSprite());
	/*
	window.draw(*character.getSprite());
	*/

	window.draw(*character);
	window.draw(*passport);
}

void Game::mousePressed(sf::Event event)
{
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

	if (event.mouseButton.button == sf::Mouse::Left)
	{

		if (passport->getGlobalBounds().contains(clickf))
		{
			dragged = passport;
			drag_offset = clickf - passport->getPosition();
		}
		if (character->getGlobalBounds().contains(clickf))
		{
			dragged = character;
			drag_offset = clickf - character->getPosition();
		}
	}
}

void Game::mouseReleased(sf::Event event)
{//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

	if (passport->getGlobalBounds().contains(clickf))
	{
		dragged = nullptr;
	}
	if (character->getGlobalBounds().contains(clickf))
	{
		dragged = nullptr;
	}
}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Enter)
	{
		//character.changeSprite();
	}
	if (event.key.code == sf::Keyboard::P)
	{
		int random = rand() % 30;
		std::cout << random << "\n";
	}
	if (event.key.code == sf::Keyboard::K)
	{
		newAnimal();
	}
}


