#pragma once
#include "SFML/Graphics.hpp"
#include <limits>
#include <unordered_map> 
namespace std
{
    template <class T>
    struct hash<sf::Vector2<T>>
    {
        std::size_t operator()(const sf::Vector2<T>& v) const
        {
            using std::hash;

            std::size_t tmp0 = hash<T>()(v.x);
            std::size_t tmp1 = hash<T>()(v.y);

            tmp0 ^= tmp1 + 0x9e3779b9 + (tmp0 << 6) + (tmp0 >> 2);
			return tmp0;
         }
    };
}
class Pathfinding {
public:
	std::vector<sf::Vector2i> availableNode;
	std::unordered_map<sf::Vector2i, float> value;
	std::unordered_map<sf::Vector2i, sf::Vector2i> parentNode;
	sf::Vector2i start;

	float GetMag(sf::Vector2i a, sf::Vector2i b) {
		sf::Vector2i tmp = a - b;
		return sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
	}
	void UpdatePath(std::vector<sf::Vector2i> node, sf::Vector2i _start ) {
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
	void Init(std::vector<sf::Vector2i> node, sf::Vector2i _start) {
		availableNode = node;
		for (sf::Vector2i& n : availableNode) {
			value[n] = std::numeric_limits<float>::max();
		}
		start = _start;
		value[start] = 0;
		parentNode[start] = start;
	}
	int getIndex(sf::Vector2i val, std::vector<sf::Vector2i>& node) {
		for (int i = 0; i < node.size(); i++) {
			if (val == node[i]) {
				return i;
			}
		}
		return -1;
	}
	std::vector<sf::Vector2i> getNeightbour(sf::Vector2i val) {
		std::vector<sf::Vector2i> neightbour;
		if (getIndex(sf::Vector2i(val.x + 1, val.y), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x + 1, val.y)); }
		if (getIndex(sf::Vector2i(val.x - 1, val.y), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x - 1, val.y)); }
		if (getIndex(sf::Vector2i(val.x, val.y + 1), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x, val.y + 1)); }
		if (getIndex(sf::Vector2i(val.x, val.y - 1), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x, val.y - 1)); }
		return neightbour;
	}
	sf::Vector2i FindMin(std::vector<sf::Vector2i>& _node) {
		float mini = std::numeric_limits<float>::max();
		sf::Vector2i sommet(-1,-1);
		for (int i = 0; i < _node.size(); i++) {
			if (value[_node[i]] < mini) {
				mini = value[_node[i]];
				sommet = _node[i];
			}
		}
		return sommet;
	}

	void maj_distance(sf::Vector2i s1, sf::Vector2i s2) {
		if (value[s2] > value[s1] + GetMag(s1, s2)) {
			value[s2] = value[s1] + GetMag(s1, s2);
			parentNode[s2] = s1;
		}
	}
};