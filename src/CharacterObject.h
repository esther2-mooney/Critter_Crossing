#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"


class CharacterObject : public GameObject
{
	public:
	std::vector<int> generateCharacter();
	void renderCharacter(sf::RenderWindow& window);
	std::unique_ptr<sf::Sprite> getSprite();

	GameObject character;

};
