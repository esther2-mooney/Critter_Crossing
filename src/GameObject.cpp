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
<<<<<<< Updated upstream
}

sf::Sprite* GameObject::getSprite()
{
	return &sprite;
=======
	sprite_ptr = std::make_shared<sf::Sprite>(sprite);
}

std::shared_ptr<sf::Sprite> GameObject::getSprite()
{
	return sprite_ptr;
>>>>>>> Stashed changes
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