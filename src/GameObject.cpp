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

sf::Sprite* GameObject::getSprite()
{
	return &sprite;
}
