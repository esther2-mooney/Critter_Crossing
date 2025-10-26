
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{}

bool Game::init()
{
	int tally = 0;
	//init background
	background.initSprite("../Data/Images/background.png");
	background.getSprite()->setPosition(0, 0);
	stamps.initSprite("../Data/Images/stamps.png");
	stamps.getSprite()->setScale(0.25, 0.25);

	//init passport
	indices = character.generateCharacter();
	passport.initSprite(indices);

	return true;
}

void Game::update(float dt)
{
	if (dragged != nullptr)
	{
		passport.dragPassport(window, drag_offset);
	}
	std::string tally_string = std::to_string(tally);
	tally_string = "Tally: " + tally_string;
	tally_text = background.makeText(tally_string, 30, sf::Color::Black);
	tally_text.setPosition(10, 10);
	if (next_character)
	{
		indices = character.generateCharacter();
		passport.initSprite(indices);

		next_character = false;
	}
}

void Game::render()
{
	window.draw(*background.getSprite());
	window.draw(tally_text);
	character.renderCharacter(window);
	passport.renderPassport(window);
	if (show_stamps)
	{
		window.draw(*stamps.getSprite());
	}
}

void Game::mousePressed(sf::Event event)
{
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (passport.getSprite()->getGlobalBounds().contains(clickf))
		{
			dragged = passport.getSprite();
			drag_offset = clickf - passport.getSprite()->getPosition();
		}
		if (show_stamps)
		{
			if (stamps.getSprite()->getGlobalBounds().contains(clickf))
			{
				if (passport.is_stamped == "")
				{
					if (clickf.y < stamps.getSprite()->getPosition().y + stamps.getSprite()->getGlobalBounds().height / 2)
					{
						passport.is_stamped = "accept";
						allow_return = true;
					}
					else
					{
						passport.is_stamped = "deny";
						allow_return = true;
					}
				}
			}
			show_stamps = false;
		}
	}
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		show_stamps = true;
		stamps.getSprite()->setPosition(clickf);
	}
}

void Game::mouseReleased(sf::Event event)
{//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

	if (passport.getSprite()->getGlobalBounds().contains(clickf))
	{
		dragged = nullptr;
	}
	if (allow_return and character.getSprite()->getGlobalBounds().contains(clickf))
	{
		if (passport.accept and passport.is_stamped == "accept")
		{
			tally++;
		}
		else if (!passport.accept and passport.is_stamped == "deny")
		{
			tally++;
		}
		else
		{
			tally = 0;
		}

		next_character = true;
		allow_return = false;
	}


}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		window.close();
	}
}


