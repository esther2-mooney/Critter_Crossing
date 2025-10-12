#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{}
GameObject::~GameObject()
{}

void GameObject::initSprite(std::string filename)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture, true);
	temp_filename = filename;
}

void GameObject::changeSprite()
{
	int random = rand() % 30;
	int randomNum = rand() % 2;
	std::cout << random << " / " << randomNum << "\n";
	if (randomNum == 0)
	{
		initSprite("../Data/c_animals/" + animals[random] + ".png");
	}
	else if (randomNum == 1)
	{
		initSprite("../Data/s_animals/" + animals[random] + ".png");
	}
}

sf::Sprite* GameObject::getSprite()
{
	return &sprite;
}
