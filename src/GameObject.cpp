#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{}
GameObject::~GameObject()
{}

void GameObject::initSprite(std::string filename)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
	temp_filename = filename;
}

void GameObject::changeSprite()
{
	int random = rand() % 31;
	int randomNum = rand() % 2;
	std::cout << random << " / " << randomNum << "\n";
	if (randomNum == 0)
	{
		texture.loadFromFile("../Data/Images/c_animals/" + animals[random] + ".png");
	}
	else if (randomNum == 1)
	{
		texture.loadFromFile("../Data/Images/s_animals/" + animals[random] + ".png");
	}
	sprite.setTexture(texture);
}

sf::Sprite* GameObject::getSprite()
{
	return &sprite;
}
