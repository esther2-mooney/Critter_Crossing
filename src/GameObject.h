#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
	public:
	GameObject();
	~GameObject();
	void initSprite(std::string filename);
<<<<<<< Updated upstream
	sf::Sprite* getSprite();
=======
	std::shared_ptr<sf::Sprite> getSprite();
>>>>>>> Stashed changes
	sf::Text makeText(sf::String string, int size, sf::Color colour);
	sf::Font font;

	protected:
	sf::Texture texture;
	std::string temp_filename;
	sf::Sprite sprite;
<<<<<<< Updated upstream
=======
	std::shared_ptr<sf::Sprite> sprite_ptr;
>>>>>>> Stashed changes
	std::string animals[30] =
	{"bear", "buffalo", "chick", "chicken", "cow", "crocodile", "dog", "duck", "elephant", "frog",
		"giraffe", "goat", "gorilla", "hippo", "horse", "monkey", "moose", "narwhal", "owl", "panda",
		"parrot", "penguin", "pig", "rabbit", "rhino", "sloth", "snake", "walrus", "whale", "zebra"};
};
