#include "TilemapHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
extern sf::Texture resumeMenu;
extern sf::SoundBuffer buffer_hit_person;
extern sf::Sound sound_hit_person;
extern sf::SoundBuffer buffer_hit_enemies;
extern sf::SoundBuffer buffer_xp_mc;
extern sf::Sound sound_xp_mc;
extern sf::Sound sound_hit_enemies;
extern sf::SoundBuffer buffer_nextR;
extern sf::Sound sound_nextR;
extern sf::Texture restartMenu;
extern sf::Texture quitMenu;
extern sf::Texture MainMenu;
extern sf::Texture PlayButton;
extern sf::Texture ScoreButton;
extern sf::Texture HowButton;
extern sf::Texture ExitButton;
extern sf::Texture SelectNameUI;
extern sf::Texture arrow;
extern sf::Texture Left_button;
extern sf::Texture Right_button;
extern float cooldownNext;
extern bool isNext;

class MapHandler
{

public:

	static void loadTexture() {
		playerTexture.loadFromFile("assets/texture/player.png");
	}

};

