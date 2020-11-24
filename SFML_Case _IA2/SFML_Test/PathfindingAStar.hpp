#pragma once
#include "SFML/Graphics.hpp"
#include <limits>
#include <unordered_map> 
class PathfindingAStar
{
public:
	sf::Vector2i start;

	float h(sf::Vector2i a, sf::Vector2i b) {
		return (abs(a.x - b.x) + abs(a.y - b.y));
	}
    std::vector<sf::Vector2i> reconstruct_path(std::unordered_map<sf::Vector2i, sf::Vector2i> cameFrom, sf::Vector2i current);
    std::vector<sf::Vector2i> UpdatePath(std::vector<sf::Vector2i>& node, sf::Vector2i& _start, sf::Vector2i& _goal);



    sf::Vector2i FindMin(std::vector<sf::Vector2i>& _node, std::unordered_map<sf::Vector2i, float> value);
    int getIndex(sf::Vector2i val, std::vector<sf::Vector2i>& node);
	std::vector<sf::Vector2i> getNeightbour(sf::Vector2i val, std::vector<sf::Vector2i>& availableNode);
};

