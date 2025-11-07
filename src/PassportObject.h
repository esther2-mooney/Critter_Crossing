#pragma once
#include <iostream>
#include "GameObject.h"

class PassportObject : public GameObject
{
	public:
	void initSprite(std::vector<int> indices);
	void generateCharacter(std::vector<int> indices);
	void changePhoto();
	void renderPassport(sf::RenderWindow& game_window);
	void dragPassport(sf::RenderWindow& window, sf::Vector2f drag_offset);
	std::shared_ptr<sf::Sprite> getSprite();
	void ifShapeIndex(int shape, int animal);
	bool accept = false;
	std::string is_stamped = "";


	// make it more likely to be correct (like 50/50)
	// change "age" to colour
	//add an array for colours so its easier to mkae it correct or nah
	//eugh

	//generate character
	// save value of animal type 
	// 50% chnace that its completely correct
	// shape is 50/50 anyway
	// colour if 50% right, 50% random



	private:
	sf::Vector2f position;
	sf::Vector2f offset;
	GameObject back;
	GameObject photo;
	GameObject front;
	GameObject stamp;

	GameObject do_text;
	sf::Text species_written;
	sf::Text shape_written;
	sf::Text colour_written;
	sf::String species_string;
	sf::String shape_string;
	sf::String colour_string;

	int animal_index = 0;
	int shape_index = 0;
	bool right_species = false;
	bool right_shape = false;
	bool right_colour = false;

	std::string animal_colours[30] =
	{"brown", "brown", "yellow", "white", "b&w", "green", "grey", "green", "grey", "green",
		"yellow", "brown", "black", "blue", "brown", "brown", "brown", "blue", "brown", "b&w",
		"red", "b&w", "pink", "grey", "grey", "brown", "green", "brown", "b&w", "b&w"};
	std::string all_colours[10] = {"brown", "yellow", "white", "b&w", "grey", "green", "blue", "pink", "black", "red"};
};