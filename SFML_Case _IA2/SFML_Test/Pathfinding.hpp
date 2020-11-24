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
	void UpdatePath(std::vector<sf::Vector2i> node, sf::Vector2i _start);
	void Init(std::vector<sf::Vector2i> node, sf::Vector2i _start);
	int getIndex(sf::Vector2i val, std::vector<sf::Vector2i>& node);

	std::vector<sf::Vector2i> getNeightbour(sf::Vector2i val);

	sf::Vector2i FindMin(std::vector<sf::Vector2i>& _node);

	void maj_distance(sf::Vector2i s1, sf::Vector2i s2);
};