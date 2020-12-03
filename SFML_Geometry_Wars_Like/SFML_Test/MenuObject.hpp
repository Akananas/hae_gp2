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
    MenuObject(MenuState value, sf::Color color, sf::Vector2f pos, sf::Font& font, bool _isBuyable, int price = 5) {
        itemVal = value;
        isBuyable = _isBuyable;
        sprite.setFillColor(color);
        sprite.setSize(sf::Vector2f(64, 64));
        sprite.setOrigin(sf::Vector2f(32, 32));
        SetPosition(pos);
        radius = 32;
        textEffect.setFont(font);
        textEffect.setCharacterSize(14);
        textEffect.setFillColor(color);
        SetText();
        sf::FloatRect textBounds = textEffect.getLocalBounds();
        textEffect.setPosition(pos + sf::Vector2f(-textBounds.width / 2.0f, -56));
        if (isBuyable) {
            textPrice.setFont(font);
            textPrice.setCharacterSize(24);
            textPrice.setFillColor(sf::Color::White);
            textPrice.setOrigin(sf::Vector2f(0, 12));
            SetPrice(price);
            textBounds = textPrice.getLocalBounds();
            textPrice.setPosition(sf::Vector2f(pos.x - textBounds.width / 2.0, pos.y));
        }
    }
    MenuState ReturnVal() {
        return itemVal;
    }
    void UpdateEntity(double dt) {
        if (!isSpawned) {
            SpawnObject(dt);
        }
    }
    void SpawnObject(double dt) {
        if (spawnTimer >= 0.75) {
            isSpawned = true;
        }
        else {
            spawnTimer += dt;
            sprite.setScale(sf::Vector2f(spawnTimer / 0.75, spawnTimer / 0.75));
        }
    }
    sf::Color GetColor() {
        return sprite.getFillColor();
    }
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
            textEffect.setString("Power Up");
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

