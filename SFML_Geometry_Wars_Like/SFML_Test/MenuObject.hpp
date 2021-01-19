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
    MenuObject(MenuState value, sf::Color color, sf::Vector2f pos, sf::Font& font, bool _isBuyable, int price = 5);
   
    MenuState ReturnVal();

    void UpdateEntity(double dt);

    void SpawnObject(double dt);


    void StartSpawn() {
        spawnTimer = 0;
        isSpawned = false;
    }
    void SetPrice(int price) {
        textPrice.setString(std::to_string(price));
        sf::FloatRect textBounds = textPrice.getLocalBounds();
        textPrice.setPosition(sf::Vector2f(GetPosition().x - textBounds.width / 2.0, GetPosition().y));
    }
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
        target.draw(textEffect, states);
        if (isBuyable) {
            target.draw(textPrice, states);
        }
    }
    void SetText() {
        switch (itemVal) {
        case StartState:
            textEffect.setString("Start");
            break;
        case PowerUpState:
            textEffect.setString("Damage Up");
            break;
        case AttackSpeedState:
            textEffect.setString("Attack Speed");
            break;
        case BombState:
            textEffect.setString("Bomb");
            break;
        default:
            textEffect.setString("");
            break;
        }
    }
    bool isBuyable = false;
    bool isSpawned = false;
    float spawnTimer = 0;
    sf::Text textEffect;
    sf::Text textPrice;
    MenuState itemVal = NothingState;
};

