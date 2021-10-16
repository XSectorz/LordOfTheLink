#include "GameHandler.h"

vector<TilemapHandler> Maps;
sf::RenderWindow windowRender(sf::VideoMode(1280, 925), "SFML Hello", sf::Style::Close);
sf::Texture playerTexture;
Player player(&playerTexture, sf::Vector2u(3, 8), 0.3f, 200.0f);
vector<Enemies> enemies_list;
vector<Effect> effect_list;
sf::Texture particles;
sf::Texture hp_bar;
sf::Texture mobTexture;
sf::Texture mobTexture_2;
WaveHandler WaveController;
