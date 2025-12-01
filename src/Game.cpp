
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
	//init stamps
	stamps.initSprite("../Data/Images/stamps.png");
	stamps.getSprite()->setScale(0.25, 0.25);

	//init passport
	indices = character.generateCharacter();
	passport.initSprite(indices);

	state = MAIN_MENU;
	lives = 3;
	tally = 0;
	move_onscreen = true;

	title_text = text_objects.makeText("Critter Crossing", 100, sf::Color::White);
	title_text.setPosition(50, 20);

	lost_text = text_objects.makeText("You Lose!", 100, sf::Color::Red);
	lost_text.setPosition(50, 20);

	won_text = text_objects.makeText("You Win!", 100, sf::Color::Green);
	won_text.setPosition(50, 20);

	exit_button.initSprite("../Data/Images/exit_button.png");
	exit_button.getSprite()->setPosition(window.getSize().x - exit_button.getSprite()->getGlobalBounds().width - 40, 40);

	play_button.initSprite("../Data/Images/play_button.png");
	play_button.getSprite()->setPosition(window.getSize().x / 2 - play_button.getSprite()->getGlobalBounds().width / 2, window.getSize().y / 2 - play_button.getSprite()->getGlobalBounds().height / 2);

	replay_button.initSprite("../Data/Images/replay_button.png");
	replay_button.getSprite()->setPosition(window.getSize().x / 2 - replay_button.getSprite()->getGlobalBounds().width / 2, window.getSize().y / 2 - replay_button.getSprite()->getGlobalBounds().height / 2);

	return true;
}

void Game::update(float dt)
{
	if (state == MAIN_MENU)
	{

	}
	if (state == PLAY)
	{
		// if something is being dragged
		if (dragged != nullptr)
		{
			passport.dragPassport(window, drag_offset);
		}
		// refresh on screen text
		std::string lives_string = std::to_string(lives);
		lives_string = "Lives: " + lives_string;
		lives_text = background.makeText(lives_string, 30, sf::Color::Black);
		lives_text.setPosition(10, 10);

		std::string tally_string = std::to_string(tally);
		tally_string = "Tally: " + tally_string;
		tally_text = background.makeText(tally_string, 30, sf::Color::Black);
		tally_text.setPosition(window.getSize().x - 10 - tally_text.getGlobalBounds().width, 10);

		// if the passport has been handed back
		if (next_character)
		{
			indices = character.generateCharacter();
			passport.initSprite(indices);
			next_character = false;
			move_onscreen = true;
		}
		if (move_onscreen)
		{
			if (character.getSprite()->getPosition().x <= 250 - character.getSprite()->getGlobalBounds().width / 2)
			{
				character.setCharacterPosition(character.getSprite()->getPosition().x + 10, character.getSprite()->getPosition().y + (10 * sin(0.03 * character.getSprite()->getPosition().x)));
			}
			else
			{
				move_onscreen = false;
			}
		}
		if (lives <= 0)
		{
			state = LOSE;
		}
		if (tally >= 10)
		{
			state = WIN;
		}
	}
	/*if (state == LOSE or state == WIN)
	{
		lives = 3;
		tally = 0;
		move_count = 0;
	}*/
}

void Game::render()
{
	if (state == MAIN_MENU)
	{
		window.draw(title_text);
		window.draw(*exit_button.getSprite());
		window.draw(*play_button.getSprite());
	}
	if (state == PLAY)
	{
		window.draw(*background.getSprite());
		window.draw(lives_text);
		window.draw(tally_text);
		character.renderCharacter(window);
		passport.renderPassport(window);
		if (show_stamps)
		{
			window.draw(*stamps.getSprite());
		}
	}
	if (state == LOSE)
	{
		window.draw(lost_text);
		window.draw(*replay_button.getSprite());
		window.draw(*exit_button.getSprite());
	}
	if (state == WIN)
	{
		window.draw(won_text);
		window.draw(*replay_button.getSprite());
		window.draw(*exit_button.getSprite());
	}
}

void Game::mousePressed(sf::Event event)
{
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

	if (state == MAIN_MENU)
	{
		if (event.mouseButton.button == sf::Mouse::Left) //left click...
		{
			if (exit_button.getSprite()->getGlobalBounds().contains(clickf)) //... on x
			{
				window.close();
			}
			if (play_button.getSprite()->getGlobalBounds().contains(clickf)) //... on x
			{
				state = PLAY;
			}
		}
	}
	if (state == PLAY)
	{
		if (event.mouseButton.button == sf::Mouse::Left) //left click...
		{
			if (passport.getSprite()->getGlobalBounds().contains(clickf)) //... on passport
			{
				dragged = passport.getSprite();
				drag_offset = clickf - passport.getSprite()->getPosition();
			}
			if (show_stamps) //... while stamps are shown ...
			{
				if (stamps.getSprite()->getGlobalBounds().contains(clickf)) //.. on a stamp ...
				{
					if (passport.is_stamped == "") //... when passport isnt already stamped...
					{
						if (clickf.y < stamps.getSprite()->getPosition().y + stamps.getSprite()->getGlobalBounds().height / 2)
						{ //... on the top half of the stamps sprite
							passport.is_stamped = "accept";
						}
						else
						{ //... on the bottom half of the stamps sprite
							passport.is_stamped = "deny";
						}
						allow_return = true;
					}
				}
				show_stamps = false;
			}
		}
		if (!move_onscreen)
		{
			if (event.mouseButton.button == sf::Mouse::Right) //right click shows stamps
			{
				if (passport.getSprite()->getGlobalBounds().contains(clickf)) //... on passport
				{
					show_stamps = true;
					stamps.getSprite()->setPosition(clickf);
				}
			}
		}
	}
	if (state == LOSE or state == WIN)
	{
		if (event.mouseButton.button == sf::Mouse::Left) //left click...
		{
			if (replay_button.getSprite()->getGlobalBounds().contains(clickf)) //... on passport
			{
				resetGame();
				next_character = true;
			}
		}
		if (exit_button.getSprite()->getGlobalBounds().contains(clickf)) //... on x
		{
			window.close();
		}
	}
}

void Game::mouseReleased(sf::Event event)
{
	if (state == PLAY)
	{   // get the click position
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (passport.getSprite()->getGlobalBounds().contains(clickf)) // if you let go of the passport ...
		{
			dragged = nullptr; //nothing is being dragged anymore

			if (allow_return and character.getSprite()->getGlobalBounds().contains(clickf))
			{   //... over the character while trying to return it
				if (passport.accept and passport.is_stamped == "deny") //if youre correct
				{
					lives--;
					tally = 0;
				}
				else if (!passport.accept and passport.is_stamped == "accept") //if youre correct
				{
					lives--;
					tally = 0;
				}
				else
				{
					tally++;
				}
				// move to the next character
				next_character = true;
				allow_return = false;
			}
		}
	}
}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		window.close();
	}
	if (event.key.code == sf::Keyboard::Enter)
	{
		state = PLAY;
	}
	if (event.key.code == sf::Keyboard::T)
	{
		next_character = !next_character;
	}
}

void Game::resetLevel()
{
	dragged = nullptr;
}

void Game::resetGame()
{
	resetLevel();
	state = PLAY;
	lives = 3;
	tally = 0;


}


