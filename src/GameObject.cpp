#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf");
}
GameObject::~GameObject()
{}

void GameObject::initSprite(std::string filename)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture, true);
	sprite_ptr = std::make_unique<sf::Sprite>(sprite);
}

std::unique_ptr<sf::Sprite> GameObject::getSprite()
{
	return sprite_ptr; // deleted function?
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