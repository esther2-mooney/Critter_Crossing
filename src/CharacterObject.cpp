#include "CharacterObject.h"


std::vector<int> CharacterObject::generateCharacter()
{
	int animal_index = rand() % 30;
	int shape_index = rand() % 2;
	if (shape_index == 0)
	{
		character.initSprite("../Data/Images/c_animals/" + animals[animal_index] + ".png");
	}
	else if (shape_index == 1)
	{
		character.initSprite("../Data/Images/s_animals/" + animals[animal_index] + ".png");
	}
	character.getSprite()->setPosition(200 - character.getSprite()->getGlobalBounds().width / 2, 300 - character.getSprite()->getGlobalBounds().height / 2);
	character.getSprite()->setScale(1.6, 1.6);
	std::vector<int> indices = {animal_index, shape_index};
	return(indices);
}

void CharacterObject::renderCharacter(sf::RenderWindow& window)
{
	window.draw(*character.getSprite());
}

std::unique_ptr<sf::Sprite> CharacterObject::getSprite()
{
	return character.getSprite();
}