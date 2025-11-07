#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"


class CharacterObject : public GameObject
{
	public:
	std::vector<int> generateCharacter();
	void renderCharacter(sf::RenderWindow& window);
<<<<<<< Updated upstream
	sf::Sprite* getSprite();
=======
	std::shared_ptr<sf::Sprite> getSprite();
>>>>>>> Stashed changes

	GameObject character;

};
