#include "PassportObject.h"

void PassportObject::initSprite()
{
	back.initSprite("../Data/Images/passport_back.png");
	back.getSprite()->setScale(0.4, 0.4);
	back.getSprite()->setPosition(position);
	generateCharacter();
	front.initSprite("../Data/Images/passport_front.png");
	front.getSprite()->setScale(0.4, 0.4);
	front.getSprite()->setPosition(position);
}

void PassportObject::generateCharacter()
{
	character.getSprite()->setPosition(50, 100);
	if (rand() % 2 == 0)
	{
		accept = false;
	}
	else
	{
		accept = true;
	}
	animal_index = rand() % 30;
	shape_index = rand() % 2;
	if (shape_index == 0)
	{
		character.initSprite("../Data/Images/c_animals/" + animals[animal_index] + ".png");
	}
	else if (shape_index == 1)
	{
		character.initSprite("../Data/Images/s_animals/" + animals[animal_index] + ".png");
	}
	character.getSprite()->setScale(1.5, 1.5);
	changePhoto();
}

void PassportObject::changePhoto()
{
	position = {500,100};
	photo.getSprite()->setScale(0.8, 0.8);
	if (accept)
	{ // if the passport should be accepted
		ifShapeIndex(photo, animal_index, shape_index);
	}
	else
	{ // if the passport shouldnt be accepted
		if (rand() % 2 == 0)
		{ // 50% chance for the picture to be right anyway
			ifShapeIndex(photo, animal_index, shape_index);
		}
		else
		{ // 50% chance for the image to be wrong
			int randAnimal = rand() % 30;
			if (randAnimal == animal_index)
			{
				if (shape_index == 0)
				{
					shape_index = 1;
				}
				else
				{
					shape_index = 0;
				}
			}
			else
			{
				shape_index = rand() % 2;
			}
			ifShapeIndex(photo, animal_index, shape_index);
		}
		int random_chance = rand() % 3;
		if (random_chance == 0)
		{
			// each odd means 1 text item is false
			// shape, colour or snimal
		}


	}

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
	offset.x = (285 * 0.4) - photo.getSprite()->getGlobalBounds().width / 2;
	offset.y = (1050 * 0.4) - photo.getSprite()->getGlobalBounds().height / 2;
}

void PassportObject::renderPassport(sf::RenderWindow& window)
{
	window.draw(*character.getSprite());
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

void PassportObject::ifShapeIndex(GameObject image, int shape, int animal)
{
	if (shape == 0)
	{
		image.initSprite("../Data/Images/c_animals/" + animals[animal] + ".png");
	}
	else
	{
		image.initSprite("../Data/Images/s_animals/" + animals[animal] + ".png");
	}
}

