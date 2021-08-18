#include "TilemapHandler.h"
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"

extern vector<TilemapHandler> Maps;
extern sf::RenderWindow windowRender;
extern sf::Texture playerTexture;
extern Player player;

class MapHandler
{

public:

	static void loadTexture() {
		playerTexture.loadFromFile("character_betaT.png");
	}

};

