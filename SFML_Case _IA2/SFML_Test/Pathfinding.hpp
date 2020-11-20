#pragma once
#include "SFML/Graphics.hpp"
#include <limits>
class PathFinding {
public:
	std::vector<sf::Vector2f> availableNode;
	std::map<sf::Vector2f, float> value;
	std::map<sf::Vector2f, sf::Vector2f> parentNode;
	sf::Vector2f start;
	float GetMag(sf::Vector2f a, sf::Vector2f b) {
		sf::Vector2f tmp = a - b;
		return sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
	}
	PathFinding(std::vector<sf::Vector2f>& node, sf::Vector2f _start ) {
		availableNode = node;
		for (sf::Vector2f& n : availableNode) {
			value[n] = std::numeric_limits<float>::max();
		}
		start = _start;
		value[start] = 0;
		parentNode[start] = start;
	}

	sf::Vector2f FindMin(std::vector<sf::Vector2f>& _node) {
		float mini = std::numeric_limits<float>::max();
		sf::Vector2f sommet(-1,-1);
		for (int i = 0; i < _node.size(); i++) {
			if (value[_node[i]] < mini) {
				mini = value[_node[i]];
				sommet = _node[i];
			}
		}
		return sommet;
	}

	void maj_distance(sf::Vector2f s1, sf::Vector2f s2) {
		if (value[s2] > value[s1] + GetMag(s1, s2)) {
			value[s2] = value[s1] + GetMag(s1, s2);
			parentNode[s2] = s1;
		}
	}
};