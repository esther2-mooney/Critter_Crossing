#include "PassportObject.h"
#include <iostream>

void PassportObject::initSprite()
{
	position = {0,0};
	back.initSprite("../Data/Images/passport_back.png");
	back.getSprite()->setScale(0.4, 0.4);
	front.initSprite("../Data/Images/passport_front.png");
	front.getSprite()->setScale(0.4, 0.4);
	character.initSprite("../Data/c_animals/moose.png");
}

void PassportObject::changeSprite()
{
	int random = rand() % 30;
	int randomNum = rand() % 2;
	if (randomNum == 0)
	{
		character.initSprite("../Data/c_animals/" + animals[random] + ".png");
	}
	else if (randomNum == 1)
	{
		character.initSprite("../Data/s_animals/" + animals[random] + ".png");
	}
}

void PassportObject::render(sf::RenderWindow& window)
{
	back.getSprite()->setPosition(position);
	front.getSprite()->setPosition(position);
	character.getSprite()->setPosition(position.x + (300 * front.getSprite()->getScale().x)
		- character.getSprite()->getGlobalBounds().width / 2, position.y +
		(300 * front.getSprite()->getScale().y) - character.getSprite()->getGlobalBounds().height / 2);
	window.draw(*back.getSprite());
	window.draw(*character.getSprite());
	window.draw(*front.getSprite());
}

sf::Sprite* PassportObject::getASprite()
{
	return front.getSprite();
}

void PassportObject::changePosition(sf::Vector2f input_position)
{
	position = input_position;
}