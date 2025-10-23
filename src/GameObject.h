#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
	public:
	GameObject();
	~GameObject();
	void initSprite(std::string filename);
	sf::Sprite* getSprite();
	sf::Text makeText(sf::String string, int size, sf::Color colour);
	sf::Font font;

	protected:
	sf::Texture texture;
	std::string temp_filename;
	sf::Sprite sprite;
};
