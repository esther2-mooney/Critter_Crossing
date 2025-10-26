
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
	//void dragSprite(sf::Sprite* sprite);

	private:
	sf::RenderWindow& window;
	sf::Sprite* dragged = nullptr;
	sf::Vector2f drag_offset;
	int tally = 0;
	sf::Text tally_text;
	GameObject background;
	PassportObject passport;
	CharacterObject character;
	GameObject stamps;
	bool show_stamps = false;
	bool allow_return = false;
	std::vector<int> indices;
	bool next_character = false;;

};

#endif // PASSPORT_GAME_H
