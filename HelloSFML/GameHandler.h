#include "TilemapHandler.h"
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"
#include "Enemies.h"
#include "Effect.h"
#include "Platform.h"
#include "WaveHandler.h"
#include "Items.h"

extern vector<TilemapHandler> Maps;
extern sf::RenderWindow windowRender;
extern sf::Texture playerTexture;
extern sf::Texture particles;
extern sf::Texture hp_bar;
extern Player player;
extern WaveHandler WaveController;
extern vector<Enemies> enemies_list;
extern vector<Effect> effect_list;
extern vector<Items> items_list;
extern sf::Texture mobTexture;
extern sf::Texture mobTexture_2;
extern sf::Texture items_hp_potion;
extern sf::Texture items_strength_potion;
extern sf::Texture items_speed_potion;
extern sf::Texture items_nuke;

class MapHandler
{

public:

	static void loadTexture() {
		playerTexture.loadFromFile("assets/texture/player.png");
	}

};

