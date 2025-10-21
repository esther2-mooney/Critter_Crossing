#pragma once
#include <iostream>
#include "GameObject.h"

class PassportObject : public GameObject
{
	public:
	void initSprite();
	void generateCharacter();
	void changePhoto();
	void renderPassport(sf::RenderWindow& game_window);
	void dragPassport(sf::RenderWindow& window, sf::Vector2f drag_offset);
	sf::Sprite* getSprite();
	void comparePassport();

	// make it more likely to be correct (like 50/50)
	// change "age" to colour
	//add an array for colours so its easier to mkae it correct or nah
	//eugh



	private:
	sf::Vector2f position;
	sf::Vector2f offset;
	GameObject back;
	GameObject photo;
	GameObject front;
	GameObject character;
	int animal_index;
	int shape_index;

	std::string animals[30] =
	{"bear", "buffalo", "chick", "chicken", "cow", "crocodile", "dog", "duck", "elephant", "frog",
		"giraffe", "goat", "gorilla", "hippo", "horse", "monkey", "moose", "narwhal", "owl", "panda",
		"parrot", "penguin", "pig", "rabbit", "rhino", "sloth", "snake", "walrus", "whale", "zebra"};
	std::string colours[30] =
	{"brown", "brown", "yellow", "white", "b&w", "green", "grey", "green", "grey", "green",
		"yellow", "brown", "black", "blue", "brown", "brown", "brown", "blue", "brown", "b&w",
		"red", "b&w", "pink", "grey", "grey", "brown", "green", "brown", "b&w", "b&w"};

};