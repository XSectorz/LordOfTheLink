#include "TilemapHandler.h"
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"
#include "Enemies.h"

extern vector<TilemapHandler> Maps;
extern sf::RenderWindow windowRender;
extern sf::Texture playerTexture;
extern Player player;
extern vector<Enemies> enemies_list;

class MapHandler
{

public:

	static void loadTexture() {
		playerTexture.loadFromFile("character_betaT.png");
	}

};

