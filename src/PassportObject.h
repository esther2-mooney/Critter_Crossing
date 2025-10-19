#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class PassportObject : public GameObject
{
	public:
	void initSprite();
	void changeSprite();
	void render(sf::RenderWindow& window);
	sf::Sprite* getASprite();
	void changePosition(sf::Vector2f input_position);
	sf::Vector2f position;

	private:
	GameObject front;
	GameObject back;
	GameObject character;
	std::string animals[30] = {"bear", "buffalo", "chick", "chicken", "cow", "crocodile", "dog",
		"duck", "elephant", "frog", "giraffe", "goat", "gorilla", "hippo", "horse", "monkey",
		"moose", "narwhal", "owl", "panda", "parrot", "penguin", "pig", "rabbit", "rhino", "sloth",
		"snake", "walrus", "whale", "zebra"};

}
;