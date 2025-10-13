#include "PassportObject.h"
#include <iostream>

void PassportObject::initSprite()
{
	back.initSprite("../Data/Images/passport_back.png");
	back.getSprite()->setScale(0.6, 0.6);
	front.initSprite("../Data/Images/passport_back.png");
	front.getSprite()->setScale(0.6, 0.6);
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
	window.draw(*back.getSprite());
	window.draw(*character.getSprite());
	window.draw(*front.getSprite());
}
