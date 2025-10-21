
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{
	/*
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport_character;
	*/
}

 bool Game::init()
{

	//init background
	background.initSprite("../Data/Images/background.png");
	background.getSprite()->setPosition(0, 0);

	//init character
	passport.initSprite();

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
		passport.dragPassport(window, drag_offset);
	}
}

void Game::render()
{
	window.draw(*background.getSprite());
	passport.renderPassport(window);
}

void Game::mousePressed(sf::Event event)
{
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (passport.getSprite()->getGlobalBounds().contains(clickf))
		{
			dragged = passport.getSprite();
			drag_offset = clickf - passport.getSprite()->getPosition();
		}
	}
}

void Game::mouseReleased(sf::Event event)
{//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

	if (passport.getSprite()->getGlobalBounds().contains(clickf))
	{
		dragged = nullptr;
	}
}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		window.close();
	}
	if (event.key.code == sf::Keyboard::Enter)
	{
		passport.changePhoto();
	}
}


