#include "Collider.h"
#include <iostream>

using namespace std;

Collider::Collider(sf::RectangleShape body) :
    body(body)
{
}

bool Collider::CheckCollision(Collider other) {

    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    sf::RectangleShape thisBody = GetBody();

    //cout << "OTHER POSITION: " << otherPosition.x << " " << otherPosition.y << " OTHER HALF SIZE: " << other.GetHalfSize().x << "," << other.GetHalfSize().y << endl;
    //cout << "THIS POSITION: " << thisPosition.x << " " << thisPosition.y << " THIS HALF SIZE: " << GetHalfSize().x << "," << GetHalfSize().y  << endl;

    float deltaX = otherPosition.x - (thisPosition.x + (thisBody.getSize().x / 2.0f));
    float deltaY = otherPosition.y - (thisPosition.y + (thisBody.getSize().y / 2.0f));

    float IntersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float IntersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (IntersectX < 0.0f && IntersectY < 0.0f) {

        return true;
    }

    return false;
}
