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
extern sf::Texture mobTexture_3;
extern sf::Texture mobTexture_4;
extern sf::Texture mobTexture_5;
extern sf::Texture items_hp_potion;
extern sf::Texture items_strength_potion;
extern sf::Texture items_speed_potion;
extern sf::Texture items_nuke;
extern sf::Texture items_shield;
extern sf::Texture resumeMenu;
extern sf::SoundBuffer buffer_hit_person;
extern sf::Sound sound_hit_person;
extern sf::SoundBuffer buffer_hit_enemies;
extern sf::SoundBuffer buffer_xp_mc;
extern sf::Sound sound_xp_mc;
extern sf::Sound sound_hit_enemies;
extern sf::SoundBuffer buffer_nextR;
extern sf::Sound sound_nextR;
extern sf::SoundBuffer buffer_lose;
extern sf::Sound sound_lose;
extern sf::SoundBuffer buffer_shot;
extern sf::Sound sound_shot;
extern sf::SoundBuffer buffer_pickup;
extern sf::Sound sound_pickup;
extern sf::SoundBuffer buffer_block;
extern sf::Sound sound_block;
extern sf::SoundBuffer buffer_shot_heavy;
extern sf::Sound sound_shot_heavy;
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
extern sf::Texture ScoreMenu;
extern sf::Texture resultUI;
extern sf::Texture HomeButton;
extern sf::Texture backToLobby;
extern sf::Texture HowtoPlay;
extern sf::Texture BacktoMain;
extern sf::Texture ClockTimer;
extern sf::Texture ManaBar;
extern float cooldownNext;
extern bool isNext;
extern float Damage_Wizard;
extern sf::Music music_day;
extern sf::Music music_Hard;

class MapHandler
{

public:

	static void loadTexture() {
		playerTexture.loadFromFile("assets/texture/player.png");
	}

};

