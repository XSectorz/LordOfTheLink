#include "GameHandler.h"

vector<TilemapHandler> Maps;
sf::RenderWindow windowRender(sf::VideoMode(1280, 925), "SFML Hello", sf::Style::Close);
sf::Texture playerTexture;
Player player(&playerTexture, sf::Vector2u(3, 8), 0.3f, 200.0f);
vector<Enemies> enemies_list;
vector<Effect> effect_list;
vector<Items> items_list;
sf::Texture particles;
sf::Texture hp_bar;
sf::Texture mobTexture;
sf::Texture mobTexture_2;
sf::Texture items_hp_potion;
sf::Texture items_strength_potion;
sf::Texture items_speed_potion;
sf::Texture items_nuke;
sf::Texture resumeMenu;
sf::Texture restartMenu;
sf::Texture quitMenu;
sf::Texture MainMenu;
sf::Texture PlayButton;
sf::Texture ScoreButton;
sf::Texture ExitButton;
sf::Texture HowButton;
sf::SoundBuffer buffer_hit_person;
sf::Sound sound_hit_person;
sf::SoundBuffer buffer_hit_enemies;
sf::Sound sound_hit_enemies;
sf::SoundBuffer buffer_nextR;
sf::Sound sound_nextR;
sf::SoundBuffer buffer_xp_mc; 
sf::Sound sound_xp_mc;
sf::Texture arrow;
sf::Texture SelectNameUI;
sf::Texture Left_button;
sf::Texture Right_button;

float cooldownNext = 0.0f;
bool isNext = false;

WaveHandler WaveController;