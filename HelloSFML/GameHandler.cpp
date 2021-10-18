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
WaveHandler WaveController;
