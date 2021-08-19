#include "GameHandler.h"
#include "Platform.h"

vector<TilemapHandler> Maps;
sf::RenderWindow windowRender(sf::VideoMode(1024, 925), "SFML Hello", sf::Style::Close | sf::Style::Resize);
sf::Texture playerTexture;
Player player(&playerTexture, sf::Vector2u(3, 8), 0.3f, 100.0f);
