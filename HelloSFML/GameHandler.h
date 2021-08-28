#include "TilemapHandler.h"
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"
#include "Enemies.h"
#include "Effect.h"
#include "Platform.h"

extern vector<TilemapHandler> Maps;
extern sf::RenderWindow windowRender;
extern sf::Texture playerTexture;
extern Player player;
extern vector<Enemies> enemies_list;
extern vector<Effect> effect_list;

class MapHandler
{

public:

	static void loadTexture() {
		playerTexture.loadFromFile("character_betaT.png");
	}

};

