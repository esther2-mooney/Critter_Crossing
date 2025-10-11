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
	std::string animals[30] = {"bear", "buffalo", "chick", "chicken", "cow", "crocodile", "dog",
		"duck", "elephant", "frog", "giraffe", "goat", "gorilla", "hippo", "horse", "monkey",
		"moose", "narwhal", "owl", "panda", "parrot", "penguin", "pig", "rabbit", "rhino", "sloth",
		"snake", "walrus", "whale", "zebra"};
};
