#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	font.loadFromFile("../Data/Fonts/pixelated.ttf");
}
GameObject::~GameObject()
{}

void GameObject::initSprite(std::string filename)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture, true);
}

sf::Sprite* GameObject::getSprite()
{
	return &sprite;
}

sf::Text GameObject::makeText(sf::String string, int size, sf::Color colour)
{
	sf::Text text;
	text.setString(string);
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(colour);
	return text;
}