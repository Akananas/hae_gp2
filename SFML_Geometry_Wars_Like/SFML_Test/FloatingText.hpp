#pragma once
#include "SFML/Graphics.hpp"
class FloatingText : public sf::Drawable{
public:
	sf::Text text;
	sf::Color col;
	sf::Vector2f curPos;
	float time = 0;
	bool destroyed = false;
	FloatingText(std::string textString, sf::Font& font, sf::Vector2f pos, sf::Color _col) {
		text.setFont(font);
		text.setCharacterSize(20);
		text.setString(textString);
		sf::FloatRect textBounds = text.getLocalBounds();
		curPos = pos + sf::Vector2f(-textBounds.width / 2.0f,-56);
		col = _col;
		text.setPosition(pos);
		text.setFillColor(col);
	}
	void UpdateText(double dt) {
		time += dt;
		if (time>0.5) {
			destroyed = true;
		}
		curPos.y += -100 * (float)dt;
		text.setPosition(curPos);
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text, states);
	}
};