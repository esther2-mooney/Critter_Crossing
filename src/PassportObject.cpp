#include "PassportObject.h"

void PassportObject::initSprite()
{
	back.initSprite("../Data/Images/passport_back.png");
	back.getSprite()->setScale(0.4, 0.4);
	back.getSprite()->setPosition(position);
	changePhoto();
	photo.getSprite()->setColor(sf::Color::Blue);
	front.initSprite("../Data/Images/passport_front.png");
	front.getSprite()->setScale(0.4, 0.4);
	front.getSprite()->setPosition(position);
}

void PassportObject::generateCharacter()
{
	int animal_index = rand() % 30;
	int shape_index = rand() % 2;
	if (shape_index == 0)
	{
		character.initSprite("../Data/Images/c_animals/" + animals[animal_index] + ".png");
	}
	else if (shape_index == 1)
	{
		character.initSprite("../Data/Images/s_animals/" + animals[animal_index] + ".png");
	}
	photo.getSprite()->setScale(0.8, 0.8);
}

void PassportObject::changePhoto()
{
	position = {0,0};
	int randAnimal = rand() % 30;
	int randShape = rand() % 2;
	if (randShape == 0)
	{
		photo.initSprite("../Data/Images/c_animals/" + animals[randAnimal] + ".png");
	}
	else if (randShape == 1)
	{
		photo.initSprite("../Data/Images/s_animals/" + animals[randAnimal] + ".png");
	}
	photo.getSprite()->setScale(0.8, 0.8);
	offset.x = (285 * 0.4) - photo.getSprite()->getGlobalBounds().width / 2;
	offset.y = (1050 * 0.4) - photo.getSprite()->getGlobalBounds().height / 2;
}

void PassportObject::renderPassport(sf::RenderWindow& window)
{
	back.getSprite()->setPosition(position);
	window.draw(*back.getSprite());
	photo.getSprite()->setPosition(position.x + offset.x, position.y + offset.y);
	window.draw(*photo.getSprite());
	front.getSprite()->setPosition(position);
	window.draw(*front.getSprite());
}

void PassportObject::dragPassport(sf::RenderWindow& window, sf::Vector2f drag_offset)
{
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);
	sf::Vector2f drag_position = mouse_positionf - drag_offset;
	position = {drag_position.x, drag_position.y};
}

sf::Sprite* PassportObject::getSprite()
{
	return front.getSprite();
}

void PassportObject::comparePassport()
{}


