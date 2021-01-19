#include "MenuObject.hpp"

MenuObject::MenuObject(MenuState value, sf::Color color, sf::Vector2f pos, sf::Font& font, sf::Texture* icon, bool _isBuyable, int price) {
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
        textPrice.setPosition(sf::Vector2f(pos.x - textBounds.width / 2.0, pos.y - 14));
        moneyIcon.setSize(sf::Vector2f(22, 20));
        moneyIcon.setOrigin(11, 10);
        moneyIcon.setPosition(sf::Vector2f(pos.x, pos.y + 14));
        moneyIcon.setTexture(icon);
    }
}

MenuState MenuObject::ReturnVal() {
    return itemVal;
}

void MenuObject::UpdateEntity(double dt) {
    if (!isSpawned) {
        SpawnObject(dt);
    }
}

void MenuObject::SpawnObject(double dt) {
    if (spawnTimer >= 0.75) {
        isSpawned = true;
    }
    else {
        spawnTimer += dt;
        sprite.setScale(sf::Vector2f(spawnTimer / 0.75, spawnTimer / 0.75));
    }
}

void MenuObject::StartSpawn() {
    spawnTimer = 0;
    isSpawned = false;
}

void MenuObject::SetPrice(int price) {
    textPrice.setString(std::to_string(price));
    sf::FloatRect textBounds = textPrice.getLocalBounds();
    textPrice.setPosition(sf::Vector2f(GetPosition().x - textBounds.width / 2.0, GetPosition().y - 14));
}

void MenuObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    target.draw(textEffect, states);
    if (isBuyable) {
        target.draw(textPrice, states);
        target.draw(moneyIcon, states);
    }
}

void MenuObject::SetText() {
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
