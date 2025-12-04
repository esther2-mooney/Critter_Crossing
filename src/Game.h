
#ifndef PASSPORT_GAME_H
#define PASSPORT_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "PassportObject.h"
#include "CharacterObject.h"
#include <thread>
#include<chrono>

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
	void resetLevel();
	void resetGame();

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
	GameObject backdrop_1;
	GameObject backdrop_2;
	GameObject text_objects;
	GameObject exit_button;
	GameObject play_button;
	GameObject replay_button;
	GameObject stamps;
	PassportObject passport;
	CharacterObject character;
	GameObject bubble;

	int lives = 0;
	int tally = 0;
	bool show_stamps = false;
	bool allow_return = false;
	bool next_character = false;
	bool move_onscreen = false;
	bool move_offscreen = false;
	bool character_enters = false;//???
	bool do_emotes = false;
	int emote_count = 0;

	enum GameState
	{
		MAIN_MENU, PLAY, WIN, LOSE
	};
	GameState state;
	enum Emote
	{
		HAPPY, SAD, ANGRY, EVIL, NONE
	};
	Emote emote;
};

#endif // PASSPORT_GAME_H
