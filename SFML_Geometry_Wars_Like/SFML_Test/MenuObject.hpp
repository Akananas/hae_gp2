#pragma once

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
    MenuObject(MenuState value, sf::Color color, sf::Vector2f pos, sf::Font& font) {
        itemVal = value;
        sprite.setFillColor(color);
        sprite.setSize(sf::Vector2f(64, 64));
        sprite.setOrigin(sf::Vector2f(32, 32));
        SetPosition(pos);
        radius = 32;
        text.setFont(font);
        text.setCharacterSize(14);
        text.setFillColor(color);
        SetText();
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(pos + sf::Vector2f(-textBounds.width/2.0f, -56));
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
    void StartSpawn() {
        spawnTimer = 0;
        isSpawned = false;
    }
    void DrawText(sf::RenderWindow& win) {
        win.draw(text);
    }
private:

    void SetText() {
        switch (itemVal) {
        case StartState:
            text.setString("Start");
            break;
        case PowerUpState:
            text.setString("PowerUp");
            break;
        case AttackSpeedState:
            text.setString("AttackSpeed");
            break;
        default:
            text.setString("");
            break;
        }
    }
    bool isSpawned = false;
    float spawnTimer = 0;
    sf::Text text;
    MenuState itemVal = NothingState;
};

