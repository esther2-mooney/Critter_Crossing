#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window), state(MAIN_MENU)
{
	srand(time(NULL));
}

Game::~Game()
{}

bool Game::init()
{
	int tally = 0;
	//init backgrounds (layered to hide character moving off screen)
	backdrop_1.initSprite("../Data/Images/backdrop_1.png");
	backdrop_2.initSprite("../Data/Images/backdrop_2.png");
	backdrop_1.getSprite()->setPosition(0, 0);
	backdrop_2.getSprite()->setPosition(0, 0);

	//init stamps
	stamps.initSprite("../Data/Images/stamps.png");
	stamps.getSprite()->setScale(0.25, 0.25);

	//init passport
	indices = character.generateCharacter();
	passport.initSprite(indices);

	// setup values
	resetGame();
	state = MAIN_MENU;
	move_onscreen = true;

	// init text
	title_text = text_objects.makeText("Critter Crossing", 100, sf::Color::White);
	title_text.setPosition(50, 20);

	lost_text = text_objects.makeText("You Lose!", 100, sf::Color::Red);
	lost_text.setPosition(50, 20);

	won_text = text_objects.makeText("You Win!", 100, sf::Color::Green);
	won_text.setPosition(50, 20);

	// init buttons
	exit_button.initSprite("../Data/Images/exit_button.png");
	exit_button.getSprite()->setPosition(window.getSize().x - exit_button.getSprite()->getGlobalBounds().width - 40, 40);

	play_button.initSprite("../Data/Images/play_button.png");
	play_button.getSprite()->setPosition(window.getSize().x / 2 - play_button.getSprite()->getGlobalBounds().width / 2, window.getSize().y / 2 - play_button.getSprite()->getGlobalBounds().height / 2);

	replay_button.initSprite("../Data/Images/replay_button.png");
	replay_button.getSprite()->setPosition(window.getSize().x / 2 - replay_button.getSprite()->getGlobalBounds().width / 2, window.getSize().y / 2 - replay_button.getSprite()->getGlobalBounds().height / 2);

	// init emote bubble 
	bubble.initSprite("../Data/Images/emotes/emote_heart.png");

	return true;
}

void Game::update(float dt)
{
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
		lives_text = text_objects.makeText(lives_string, 30, sf::Color::Black);
		lives_text.setPosition(30, 20);

		std::string tally_string = std::to_string(tally);
		tally_string = "Tally: " + tally_string;
		tally_text = text_objects.makeText(tally_string, 30, sf::Color::Black);
		tally_text.setPosition(window.getSize().x - 30 - tally_text.getGlobalBounds().width, 20);

		if (do_emotes)
		{
			// change rotation every 400ms for emphasis
			if (emote_count % 2 == 0)
			{
				bubble.getSprite()->setRotation(40);
			}
			else
			{
				bubble.getSprite()->setRotation(20);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
			// loop 5 times
			if (emote_count >= 5)
			{
				do_emotes = false;
				move_offscreen = true;
				// then character moves off screen
			}
			// increment
			emote_count++;
		}
		if (move_offscreen)
		{
			if (character.getSprite()->getPosition().x >= -10 - character.getSprite()->getGlobalBounds().width and character.getSprite()->getPosition().x <= window.getSize().x / 2 + 10)
			{
				// if you deny the character they have to go back to the left
				if (passport.is_stamped == "deny")
				{
					character.setCharacterPosition(character.getSprite()->getPosition().x - 10, character.getSprite()->getPosition().y + (10 * sin(0.03 * character.getSprite()->getPosition().x)));
				}
				else
				{
					character.setCharacterPosition(character.getSprite()->getPosition().x + 10, character.getSprite()->getPosition().y + (10 * sin(0.03 * character.getSprite()->getPosition().x)));
				}
			}
			else
			{
				next_character = true;
				move_offscreen = false;
			}
		}
		if (next_character)
		{
			if (lives <= 0)
			{
				state = LOSE;
			}
			else if (tally >= 10)
			{
				state = WIN;
			}
			else
			{
				move_onscreen = true;
				next_character = false;
				indices = character.generateCharacter();
				passport.initSprite(indices);
			}
		}
		if (move_onscreen)
		{
			if (character.getSprite()->getPosition().x <= 270 - character.getSprite()->getGlobalBounds().width / 2)
			{
				character.setCharacterPosition(character.getSprite()->getPosition().x + 10, character.getSprite()->getPosition().y + (10 * sin(0.03 * character.getSprite()->getPosition().x)));
			}
			else
			{
				move_onscreen = false;
			}
		}
	}
}

void Game::render()
{
	if (state == MAIN_MENU)
	{
		window.draw(title_text);
		window.draw(*exit_button.getSprite());
		window.draw(*play_button.getSprite());
	}
	else if (state == PLAY)
	{
		window.draw(*backdrop_1.getSprite());
		character.renderCharacter(window);
		if (do_emotes)
		{
			window.draw(*bubble.getSprite());
		}
		window.draw(*backdrop_2.getSprite());
		if (!move_offscreen && !move_onscreen && !do_emotes)
		{
			passport.renderPassport(window);
		}
		window.draw(lives_text);
		window.draw(tally_text);
		if (show_stamps)
		{
			window.draw(*stamps.getSprite());
		}
	}
	else
	{
		if (state == LOSE)
		{
			window.draw(lost_text);
		}
		if (state == WIN)
		{
			window.draw(won_text);
		}
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
	else if (state == PLAY)
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
		if (!move_onscreen && !move_offscreen)
		{
			if (event.mouseButton.button == sf::Mouse::Right) //right click shows stamps
			{
				if (passport.getSprite()->getGlobalBounds().contains(clickf)) //... on passport
				{
					show_stamps = true;
					if (clickf.x > window.getSize().x - stamps.getSprite()->getGlobalBounds().width)
					{
						clickf.x = window.getSize().x - stamps.getSprite()->getGlobalBounds().width;
					}
					if (clickf.y > window.getSize().y - stamps.getSprite()->getGlobalBounds().height)
					{
						clickf.y = window.getSize().y - stamps.getSprite()->getGlobalBounds().height;
					}
					stamps.getSprite()->setPosition(clickf);
				}
			}
		}
	}
	else
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

			if (allow_return && character.getSprite()->getGlobalBounds().contains(clickf))
			{   //... over the character while trying to return it
				if (passport.accept && passport.is_stamped == "deny") //if youre wrong
				{
					lives--;
					tally = 0;
					bubble.initSprite("../Data/Images/emotes/emote_anger.png");
				}
				else if (!passport.accept && passport.is_stamped == "accept") //if youre wrong
				{
					lives--;
					tally = 0;
					bubble.initSprite("../Data/Images/emotes/emote_question.png");
				}
				else if (passport.accept && passport.is_stamped == "accept") //if youre correct
				{
					tally++;
					bubble.initSprite("../Data/Images/emotes/emote_heart.png");
				}
				else if (!passport.accept && passport.is_stamped == "deny") //if youre correct
				{
					tally++;
					bubble.initSprite("../Data/Images/emotes/emote_faceSad.png");
				}
				// move to chcracter emoting
				emote_count = 0;
				bubble.getSprite()->setScale(2.5, 2.5);
				bubble.getSprite()->setPosition(400, 70);
				do_emotes = true;
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
	if (event.key.code == sf::Keyboard::A)
	{
		passport.is_stamped = "accept";
	}
	if (event.key.code == sf::Keyboard::D)
	{
		passport.is_stamped = "deny";
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


