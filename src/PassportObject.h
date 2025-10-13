#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class PassportObject : public GameObject
{
	public:
	void initSprite();
	void changeSprite();
	void render(sf::RenderWindow& window);

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