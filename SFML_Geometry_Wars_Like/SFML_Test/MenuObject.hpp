#pragma once
#include <string>
enum MenuState {
    StartState,
    PowerUpState,
    RevertState,
    AttackSpeedState,
    BombState,
    LevelUpState,
    LevelDownState,
    NothingState
};
#include "Entity.hpp"
class MenuObject : public Entity{
public:
    MenuObject(MenuState value, sf::Color color, sf::Vector2f pos, sf::Font& font, sf::Texture* icon, bool _isBuyable, int price = 5);
   
    MenuState ReturnVal();

    void UpdateEntity(double dt);

    void SpawnObject(double dt);


    void StartSpawn();
    void SetPrice(int price);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void SetText();
    bool isBuyable = false;
    bool isSpawned = false;
    float spawnTimer = 0;
    sf::Text textEffect;
    sf::Text textPrice;
    sf::RectangleShape moneyIcon;
    MenuState itemVal = NothingState;
};

