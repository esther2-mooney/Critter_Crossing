#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
	public:
	GameObject();
	~GameObject();
	void initSprite(std::string filename);
	void changeSprite();
	sf::Sprite* getSprite();

	protected:
	sf::Texture texture;
	std::string temp_filename;
	sf::Sprite sprite;
};
