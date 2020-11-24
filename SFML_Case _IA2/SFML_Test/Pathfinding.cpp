#include "Pathfinding.hpp"

void Pathfinding::UpdatePath(std::vector<sf::Vector2i> node, sf::Vector2i _start) {
	Init(node, _start);
	while (node.size() > 0) {
		sf::Vector2i s1 = FindMin(node);
		node.erase(node.begin() + getIndex(s1, node));
		std::vector<sf::Vector2i> neightbours = getNeightbour(s1);
		for (int i = 0; i < neightbours.size(); i++) {
			maj_distance(s1, neightbours[i]);
		}
	}
}

void Pathfinding::Init(std::vector<sf::Vector2i> node, sf::Vector2i _start) {
	availableNode = node;
	for (sf::Vector2i& n : availableNode) {
		value[n] = std::numeric_limits<float>::max();
	}
	start = _start;
	value[start] = 0;
	parentNode[start] = start;
}

int Pathfinding::getIndex(sf::Vector2i val, std::vector<sf::Vector2i>& node) {
	for (int i = 0; i < node.size(); i++) {
		if (val == node[i]) {
			return i;
		}
	}
	return -1;
}

std::vector<sf::Vector2i> Pathfinding::getNeightbour(sf::Vector2i val) {
	std::vector<sf::Vector2i> neightbour;
	if (getIndex(sf::Vector2i(val.x + 1, val.y), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x + 1, val.y)); }
	if (getIndex(sf::Vector2i(val.x - 1, val.y), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x - 1, val.y)); }
	if (getIndex(sf::Vector2i(val.x, val.y + 1), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x, val.y + 1)); }
	if (getIndex(sf::Vector2i(val.x, val.y - 1), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x, val.y - 1)); }
	return neightbour;
}

sf::Vector2i Pathfinding::FindMin(std::vector<sf::Vector2i>& _node) {
	float mini = std::numeric_limits<float>::max();
	sf::Vector2i sommet(-1, -1);
	for (int i = 0; i < _node.size(); i++) {
		if (value[_node[i]] < mini) {
			mini = value[_node[i]];
			sommet = _node[i];
		}
	}
	return sommet;
}

void Pathfinding::maj_distance(sf::Vector2i s1, sf::Vector2i s2) {
	if (value[s2] > value[s1] + GetMag(s1, s2)) {
		value[s2] = value[s1] + GetMag(s1, s2);
		parentNode[s2] = s1;
	}
}
