#include "GameHandler.h"

vector<TilemapHandler> Maps;
sf::RenderWindow windowRender(sf::VideoMode(1024, 925), "SFML Hello", sf::Style::Close | sf::Style::Resize);
sf::Texture playerTexture;
Player player(&playerTexture, sf::Vector2u(3, 8), 0.3f, 200.0f);
vector<Enemies> enemies_list;
vector<Effect> effect_list;
