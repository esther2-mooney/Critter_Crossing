#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"


class CharacterObject : public GameObject
{
	public:
	std::vector<int> generateCharacter();
	void renderCharacter(sf::RenderWindow& window);
	std::shared_ptr<sf::Sprite> getSprite();
	void setCharacterPosition(float x, float y);
	void moveCharacter();

	GameObject character;

};
