#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"


class CharacterObject : public GameObject
{
	public:
	std::vector<int> generateCharacter();
	void renderCharacter(sf::RenderWindow& window);
	sf::Sprite* getSprite();

	GameObject character;

};
