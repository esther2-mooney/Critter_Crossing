
#ifndef PASSPORT_GAME_H
#define PASSPORT_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "PassportObject.h"
#include "CharacterObject.h"

class Game
{
	public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	void mousePressed(sf::Event event);
	void mouseReleased(sf::Event event);
	void keyPressed(sf::Event event);

	private:
	sf::RenderWindow& window;
	std::shared_ptr<sf::Sprite> dragged = nullptr;
	sf::Vector2f drag_offset;
	std::vector<int> indices;
	sf::Text lives_text;
	sf::Text tally_text;
	sf::Text title_text;
	sf::Text lost_text;
	sf::Text won_text;
	GameObject background;
	GameObject text_objects;
	GameObject exit_button;
	GameObject play_button;
	GameObject replay_button;
	GameObject stamps;
	PassportObject passport;
	CharacterObject character;
	int lives = 0;
	int tally = 0;
	bool show_stamps = false;
	bool allow_return = false;
	bool next_character = false;

	enum GameState
	{
		MAIN_MENU, PLAY, WIN, LOSE
	};
	GameState state;

};

#endif // PASSPORT_GAME_H
