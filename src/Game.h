
#ifndef PASSPORT_GAME_H
#define PASSPORT_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "PassportObject.h"

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
	void newAnimal();
	void dragSprite(sf::Sprite* sprite);
	void dragPassport(PassportObject passport);

	private:
	sf::RenderWindow& window;
	sf::Sprite* character;
	sf::Sprite* passport_character;
	PassportObject passport;
	sf::Texture* animals = new sf::Texture[3];
	sf::Texture* passports = new sf::Texture[3];
	sf::Sprite* dragged = nullptr;
	sf::Vector2f drag_offset;
	bool passport_accepted;
	bool passport_rejected;
	bool should_accept;



	GameObject background;
	//GameObject character;

};

#endif // PASSPORT_GAME_H
