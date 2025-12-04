#include "PassportObject.h"

void PassportObject::initSprite(std::vector<int> indices)
{
	back.initSprite("../Data/Images/passport_back.png");
	back.getSprite()->setScale(0.4, 0.4);
	back.getSprite()->setPosition(position);
	photo.initSprite("../Data/Images/c_animals/rhino.png");
	generateCharacter(indices);
	front.initSprite("../Data/Images/passport_front.png");
	front.getSprite()->setScale(0.4, 0.4);
	front.getSprite()->setPosition(position);
}

void PassportObject::generateCharacter(std::vector<int> indices)
{
	if (rand() % 2 == 0)
	{
		accept = false;
		std::cout << "Accept = false \n";
	}
	else
	{
		accept = true;
		std::cout << "Accept = true \n";
	}

	animal_index = indices[0];
	shape_index = indices[1];

	//set right text
	if (shape_index == 0)
	{
		shape_written = do_text.makeText("Circle", 25, sf::Color::Black);
	}
	else if (shape_index == 1)
	{
		shape_written = do_text.makeText("Square", 25, sf::Color::Black);
	}
	species_string = animals[animal_index];
	colour_string = animal_colours[animal_index];
	species_string[0] = toupper(species_string[0]);
	colour_string[0] = toupper(colour_string[0]);

	species_written = do_text.makeText(species_string, 25, sf::Color::Black);
	colour_written = do_text.makeText(colour_string, 25, sf::Color::Black);

	is_stamped = "";

	changePhoto();
}

void PassportObject::changePhoto()
{
	position = {600,100};
	if (accept)
	{ // if the passport should be accepted
		ifShapeIndex(shape_index, animal_index);
	}
	else
	{ // if the passport shouldnt be accepted
		if (rand() % 2 == 0)
		{ // 50% chance for the picture to be right anyway
			ifShapeIndex(shape_index, animal_index);
		}
		else
		{ // 50% chance for the image to be wrong
			int random_animal = rand() % 30;
			int temp_shape = 0;
			if (random_animal == animal_index)
			{
				if (shape_index == 0)
				{
					temp_shape = 1;
				}
				else
				{
					temp_shape = 0;
				}
			}
			else
			{
				temp_shape = rand() % 2;
			}
			ifShapeIndex(temp_shape, random_animal);
		}
		//random chance for any 1 of the 3 text items to be right
		int random_chance = rand() % 3;
		if (random_chance == 0) // species is right
		{
			right_species = true;
		}
		else if (random_chance == 1) // shape is right
		{
			right_shape = true;
		}
		else if (random_chance == 2) // colour is right
		{
			right_colour = true;
		}

		if (!right_shape)
		{
			if (shape_index == 0)
			{
				shape_written = do_text.makeText("Square", 25, sf::Color::Black);
			}
			else if (shape_index == 1)
			{
				shape_written = do_text.makeText("Circle", 25, sf::Color::Black);
			}
		}
		if (!right_colour)
		{
			while (true)
			{
				int random_colour = rand() % 10;
				if (animal_colours[animal_index] != all_colours[random_colour])
				{
					colour_string = all_colours[random_colour];
					break;
				}
			}
		}
		if (!right_species)
		{
			while (true)
			{
				int random_animal = rand() % 30;
				if (random_animal != animal_index)
				{
					species_string = animals[random_animal];
					break;
				}
			}
		}
		right_species = false;
		right_colour = false;
		right_shape = false;
	}
	species_string[0] = toupper(species_string[0]);
	colour_string[0] = toupper(colour_string[0]);

	species_written = do_text.makeText(species_string, 25, sf::Color::Black);
	colour_written = do_text.makeText(colour_string, 25, sf::Color::Black);

	float width = photo.getSprite()->getGlobalBounds().width;
	float scale = 125 / width;
	photo.getSprite()->setScale(scale, scale);

	offset.x = (285 * 0.4) - photo.getSprite()->getGlobalBounds().width / 2;
	offset.y = (1050 * 0.4) - photo.getSprite()->getGlobalBounds().height / 2;

}

void PassportObject::renderPassport(sf::RenderWindow& window)
{
	back.getSprite()->setPosition(position);
	window.draw(*back.getSprite());
	photo.getSprite()->setPosition(position.x + offset.x, position.y + offset.y);
	window.draw(*photo.getSprite());
	front.getSprite()->setPosition(position);
	window.draw(*front.getSprite());

	//text
	species_written.setPosition(position.x + 235, position.y + 335);
	colour_written.setPosition(position.x + 235, position.y + 412);
	shape_written.setPosition(position.x + 235, position.y + 495);
	window.draw(species_written);
	window.draw(colour_written);
	window.draw(shape_written);

	if (is_stamped == "accept")
	{
		stamp.initSprite("../Data/Images/accept.png");
	}
	else
	{
		stamp.initSprite("../Data/Images/reject.png");
	}
	if (is_stamped != "")
	{
		stamp.getSprite()->setScale(0.4, 0.4);
		stamp.getSprite()->setPosition(position.x + 30, position.y + 100);
		window.draw(*stamp.getSprite());
	}

}

void PassportObject::dragPassport(sf::RenderWindow& window, sf::Vector2f drag_offset)
{
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);
	sf::Vector2f drag_position = mouse_positionf - drag_offset;
	position = {drag_position.x, drag_position.y};
}

std::shared_ptr<sf::Sprite> PassportObject::getSprite()
{
	return front.getSprite();
}

void PassportObject::ifShapeIndex(int shape, int animal)
{
	if (shape == 0)
	{
		photo.initSprite("../Data/Images/c_animals/" + animals[animal] + ".png");
	}
	else
	{
		photo.initSprite("../Data/Images/s_animals/" + animals[animal] + ".png");
	}
}

